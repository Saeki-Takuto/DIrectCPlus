//==================================================================
//
//オブジェクトアニメ処理 [objectAnim.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//インクルード
//================================================
#include "objectAnim.h"
#include "renderer.h"
#include "manager.h"

//================================================
//静的メンバ変数
//================================================

//================================================
//コンストラクタ
//================================================
CObjectAnim::CObjectAnim()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_CounterAnim = 0;
	m_nPatternAnim = 0;
	m_Player.pos.x = 150.0f;
	m_Player.pos.y = 150.0f;
	m_Player.pos.z = 150.0f;
}

//================================================
//デストラクタ
//================================================
CObjectAnim::~CObjectAnim()
{
}

//================================================
//初期化処理
//================================================
HRESULT CObjectAnim::Init(void)
{
	CRenderer* renderer;

	renderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = renderer->GetDevice();

	switch (m_type)
	{
	case TYPE_ONE:
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data/TEXTURE/runningman000.png",
			&m_pTexture);
		break;
	}

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	switch (m_type)
	{
	case TYPE_ONE:
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(m_Player.pos.x - WIDTH / 2, m_Player.pos.y - HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_Player.pos.x + WIDTH / 2, m_Player.pos.y - HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_Player.pos.x - WIDTH / 2, m_Player.pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_Player.pos.x + WIDTH / 2, m_Player.pos.y, 0.0f);
		break;
	}

	float u = 0.0f, v = 0.0f; // ここで宣言

	switch (m_type)
	{
	case TYPE_ONE:
		// 頂点座標の設定
		u = ANIME_U(0);
		v = ANIME_V(0);
		break;
	}

	// テクスチャ座標の設定（共通）
	pVtx[0].tex = D3DXVECTOR2(u, v);
	pVtx[1].tex = D3DXVECTOR2(u + ANIME_UW, v);
	pVtx[2].tex = D3DXVECTOR2(u, v + ANIME_VH);
	pVtx[3].tex = D3DXVECTOR2(u + ANIME_UW, v + ANIME_VH);


	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;


	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//終了処理
//================================================
void CObjectAnim::Uninit(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//================================================
//更新処理
//================================================
void CObjectAnim::Update(void)
{
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();


	if (pInputKeyboard->Repeat(DIK_RIGHT))
	{
		m_Player.pos.x += 10.0f;
	}

	if (pInputKeyboard->Repeat(DIK_LEFT))
	{
		m_Player.pos.x -= 10.0f;
	}

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_Player.pos.x - WIDTH / 2, m_Player.pos.y - HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Player.pos.x + WIDTH / 2, m_Player.pos.y - HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Player.pos.x - WIDTH / 2, m_Player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Player.pos.x + WIDTH / 2, m_Player.pos.y, 0.0f);


	m_CounterAnim++;							//アニメーションカウンターを加算

	if ((m_CounterAnim % 5) == 0)
	{
		m_nPatternAnim = (m_nPatternAnim + 1) % (ANIME_FRAME_U_NUM * ANIME_FRAME_V_NUM);

		float u = ANIME_U(m_nPatternAnim);
		float v = ANIME_V(m_nPatternAnim);

		pVtx[0].tex = D3DXVECTOR2(u, v);
		pVtx[1].tex = D3DXVECTOR2(u + ANIME_UW, v);
		pVtx[2].tex = D3DXVECTOR2(u, v + ANIME_VH);
		pVtx[3].tex = D3DXVECTOR2(u + ANIME_UW, v + ANIME_VH);
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//================================================
//描画処理
//================================================
void CObjectAnim::Draw(void)
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

CObjectAnim* CObjectAnim::Create(TYPE type)
{
	CObjectAnim* pObjectAnim;

	//オブジェクトの作成
	pObjectAnim = new CObjectAnim;
	pObjectAnim->m_type = type;
	pObjectAnim->Init();

	return pObjectAnim;
}