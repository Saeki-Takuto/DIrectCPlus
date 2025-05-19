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
CObject2D::CObject2D()
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
//初期化処理
//================================================
HRESULT CObject2D::Init(void)
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
			"data/TEXTURE/photo.png",
			&m_pTexture);
		break;
	case TYPE_TWO:
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data/TEXTURE/photo1.png",
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
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
		break;
	case TYPE_TWO:
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(100.0f, 50.0f, 0.0f);
		break;
	}

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

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//終了処理
//================================================
void CObject2D::Uninit(void)
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
void CObject2D::Update(void)
{
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

CObject2D* CObject2D::Create(TYPE type)
{
	CObject2D* pObject2D;

	//オブジェクトの作成
	pObject2D = new CObject2D;
	pObject2D->m_type = type;
	pObject2D->Init();

	return pObject2D;
}






