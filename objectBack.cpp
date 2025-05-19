//==================================================================
//
//オブジェクト背景処理 [objectBack.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//インクルード
//================================================
#include "objectBack.h"
#include "renderer.h"
#include "manager.h"

//================================================
//静的メンバ変数
//================================================

//================================================
//コンストラクタ
//================================================
CObjectBack::CObjectBack()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_aPosTexU = 0.0f;
}

//================================================
//デストラクタ
//================================================
CObjectBack::~CObjectBack()
{
}

//================================================
//初期化処理
//================================================
HRESULT CObjectBack::Init(void)
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
			"data/TEXTURE/bg100.png",
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
		pVtx[0].pos = D3DXVECTOR3(000.0f, 000.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
		break;
	}


	switch (m_type)
	{
	case TYPE_ONE:
		break;
	}

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(m_aPosTexU, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_aPosTexU + 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_aPosTexU, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_aPosTexU + 1.0f, 1.0f);


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
void CObjectBack::Uninit(void)
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
void CObjectBack::Update(void)
{
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_aPosTexU += 0.001f * 1;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(m_aPosTexU, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_aPosTexU + 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_aPosTexU, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_aPosTexU + 1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//================================================
//描画処理
//================================================
void CObjectBack::Draw(void)
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

CObjectBack* CObjectBack::Create(TYPE type)
{
	CObjectBack* pObjectBack;

	//オブジェクトの作成
	pObjectBack = new CObjectBack;
	pObjectBack->m_type = type;
	pObjectBack->Init();

	return pObjectBack;
}






