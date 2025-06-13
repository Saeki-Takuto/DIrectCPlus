//==================================================================
//
//背景処理 [background.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//インクルード
//================================================
#include "background.h"
#include "input.h"
#include "manager.h"
#include "bullet.h"

//================================================
//静的メンバ変数
//================================================
LPDIRECT3DTEXTURE9 CBackground::m_pTexture[BACKGROUND_TYPE_MAX] = {};

//================================================
//コンストラクタ
//================================================
CBackground::CBackground(int nPriority) : CObject2D(nPriority)
{
}

//================================================
//デストラクタ
//================================================
CBackground::~CBackground()
{
}

//================================================
//初期化処理
//================================================
HRESULT CBackground::Init(void)
{
	CObject2D::Init();
	SetType(TYPE_BACKGROUND);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CBackground::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================
//更新処理
//================================================
void CBackground::Update(void)
{
	CObject2D::Update();
}

//================================================
//描画処理
//================================================
void CBackground::Draw(void)
{
	CObject2D::Draw();
}

//================================================
//生成処理
//================================================
CBackground* CBackground::Create(BACKGROUND_TYPE backgroundtype, DRAW_TYPE drawtype, int width, int height, float scrollX, float scrollY, int animeFrameU, int animeFrameV, int animePattern, float posX, float posY, float rotZ)
{
	CBackground* pBackground = new CBackground(BACKGROUND_PRIORITY);
	pBackground->SetDrawType(drawtype);
	pBackground->SetWidth(width);
	pBackground->SetHeight(height);
	pBackground->SetScrollSpeedX(scrollX);
	pBackground->SetScrollSpeedY(scrollY);
	pBackground->SetAnimeFrameU(animeFrameU);
	pBackground->SetAnimeFrameV(animeFrameV);
	pBackground->SetAnimePattern(animePattern);
	pBackground->SetPos(D3DXVECTOR2(posX, posY));
	D3DXVECTOR3 rot = pBackground->GetRot();
	rot.z = rotZ;
	pBackground->SetRot(rot);
	pBackground->Init();
	pBackground->BindTexture(m_pTexture[backgroundtype]);
	return pBackground;
}

//================================================
//テクスチャロード処理
//================================================
HRESULT CBackground::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/001.png", &m_pTexture[BACKGROUND_TYPE_CLOUD])))
	{
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg103.jpg", &m_pTexture[BACKGROUND_TYPE_BACK])))
	{
		return E_FAIL;
	}


	return S_OK;
}

//================================================
//テクスチャアンロード処理
//================================================
void CBackground::Unload(void)
{
	for (int nCnt = 0; nCnt < BACKGROUND_TYPE_MAX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

