//==================================================================
//
//オブジェクト2D処理 [object2D.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//インクルード
//================================================
#include "object2D.h"
#include "renderer.h"
#include "manager.h"

//================================================
//コンストラクタ
//================================================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
}

//================================================
//デストラクタ
//================================================
CObject2D::~CObject2D()
{
}

//================================================
// 初期化処理
//================================================
HRESULT CObject2D::Init(void)
{
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	// 頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	CObject2D::BindTexture(m_pTexture);

	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 回転対応の頂点座標計算
	float halfW = m_width * 0.5f;
	float halfH = m_height * 0.5f;
	float angle = m_rot.z;

	D3DXVECTOR2 local[4] = {
		D3DXVECTOR2(-halfW, -halfH), // 左上
		D3DXVECTOR2(halfW, -halfH), // 右上
		D3DXVECTOR2(-halfW,  halfH), // 左下
		D3DXVECTOR2(halfW,  halfH)  // 右下
	};

	for (int i = 0; i < 4; ++i) {
		float x = local[i].x * cosf(angle) - local[i].y * sinf(angle);
		float y = local[i].x * sinf(angle) + local[i].y * cosf(angle);
		pVtx[i].pos = D3DXVECTOR3(m_pos.x + x, m_pos.y + y, 0.0f);
	}

	// rhwの設定
	for (int i = 0; i < 4; ++i) pVtx[i].rhw = 1.0f;

	// 頂点カラーの設定
	for (int i = 0; i < 4; ++i) pVtx[i].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// アニメーション用テクスチャ座標の計算
	float u = 0.0f, v = 0.0f, uw = 1.0f, vh = 1.0f;
	if (m_animeFrameU > 1 || m_animeFrameV > 1) {
		int index = m_animePattern;
		u = (float)(index % m_animeFrameU) / m_animeFrameU;
		v = (float)(index / m_animeFrameU) / m_animeFrameV;
		uw = 1.0f / m_animeFrameU;
		vh = 1.0f / m_animeFrameV;
	}

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(u, v);
	pVtx[1].tex = D3DXVECTOR2(u + uw, v);
	pVtx[2].tex = D3DXVECTOR2(u, v + vh);
	pVtx[3].tex = D3DXVECTOR2(u + uw, v + vh);

	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//終了処理
//================================================
void CObject2D::Uninit(void)
{
	m_pTexture = NULL;

	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CObject::Release();
}

//================================================
// 更新処理
//================================================
void CObject2D::Update(void)
{
	bool needUpdateVertex = false;

	if (m_drawtype == TYPE_SCROLL) {
		// UVスクロール値を加算
		m_scrollPosX += m_scrollSpeedX;
		m_scrollPosY += m_scrollSpeedY;

		// 0.0～1.0の範囲でループ
		if (m_scrollPosX >= 1.0f) m_scrollPosX -= 1.0f;
		if (m_scrollPosX < 0.0f) m_scrollPosX += 1.0f;
		if (m_scrollPosY >= 1.0f) m_scrollPosY -= 1.0f;
		if (m_scrollPosY < 0.0f) m_scrollPosY += 1.0f;

		needUpdateVertex = true;
	}

	if (m_drawtype == TYPE_ANIME) {
		m_animeCounter++;
		if (m_animeFrameU > 1 || m_animeFrameV > 1) {
			if (m_animeCounter % 5 == 0) {
				m_animePattern = (m_animePattern + 1) % (m_animeFrameU * m_animeFrameV);
				needUpdateVertex = true;
			}
		}
	}

	needUpdateVertex = true;

	if (needUpdateVertex) {
		VERTEX_2D* pVtx;
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 回転対応の頂点座標計算
		float halfW = m_width * 0.5f;
		float halfH = m_height * 0.5f;
		float angle = m_rot.z;

		D3DXVECTOR2 local[4] = {
			D3DXVECTOR2(-halfW, -halfH),
			D3DXVECTOR2(halfW, -halfH),
			D3DXVECTOR2(-halfW,  halfH),
			D3DXVECTOR2(halfW,  halfH)
		};

		for (int i = 0; i < 4; ++i) {
			float x = local[i].x * cosf(angle) - local[i].y * sinf(angle);
			float y = local[i].x * sinf(angle) + local[i].y * cosf(angle);
			pVtx[i].pos = D3DXVECTOR3(m_pos.x + x, m_pos.y + y, 0.0f);
		}

		// UVスクロール
		float u = m_scrollPosX;
		float v = m_scrollPosY;
		float uw = 1.0f, vh = 1.0f;
		if (m_animeFrameU > 1 || m_animeFrameV > 1) {
			int index = m_animePattern;
			u += (float)(index % m_animeFrameU) / m_animeFrameU;
			v += (float)(index / m_animeFrameU) / m_animeFrameV;
			uw = 1.0f / m_animeFrameU;
			vh = 1.0f / m_animeFrameV;
		}
		pVtx[0].tex = D3DXVECTOR2(u, v);
		pVtx[1].tex = D3DXVECTOR2(u + uw, v);
		pVtx[2].tex = D3DXVECTOR2(u, v + vh);
		pVtx[3].tex = D3DXVECTOR2(u + uw, v + vh);

		m_pVtxBuff->Unlock();
	}
}

//================================================
//描画処理
//================================================
void CObject2D::Draw(void)
{
	CRenderer* renderer;

	renderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = renderer->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//================================================
//テクスチャ割当処理
//================================================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//================================================
// 生成処理
//================================================
CObject2D* CObject2D::Create(
	DRAW_TYPE type,
	int width,
	int height,
	float scrollX,
	float scrollY,
	int animeFrameU,
	int animeFrameV,
	int animePattern,
	float posX,
	float posY,
	float rotZ
)
{
	CObject2D* pObject2D = new CObject2D;
	pObject2D->m_drawtype = type;
	pObject2D->m_width = width;
	pObject2D->m_height = height;
	pObject2D->m_scrollSpeedX = scrollX;
	pObject2D->m_scrollSpeedY = scrollY;
	pObject2D->m_scrollPosX = 0.0f;
	pObject2D->m_scrollPosY = 0.0f;
	pObject2D->m_animeFrameU = animeFrameU;
	pObject2D->m_animeFrameV = animeFrameV;
	pObject2D->m_animePattern = animePattern;
	pObject2D->m_pos = D3DXVECTOR2(posX, posY);
	pObject2D->m_rot.z = rotZ;
	pObject2D->Init();
	return pObject2D;
}



