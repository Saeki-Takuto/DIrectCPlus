//==================================================================
//
//敵処理 [score.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//インクルード
//================================================
#include "score.h"
#include "input.h"
#include "manager.h"
#include "bullet.h"

//================================================
//静的メンバ変数
//================================================
LPDIRECT3DTEXTURE9 CScore::m_pTexture[SCORE_TYPE_MAX] = {};

//================================================
//コンストラクタ
//================================================
CScore::CScore(int nPriority) : CNumber(nPriority)
{
}


//================================================
//デストラクタ
//================================================
CScore::~CScore()
{
}

//================================================
//初期化処理
//================================================
HRESULT CScore::Init(void)
{
	CNumber::Init();
	//SetType(TYPE_SCORE);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CScore::Uninit(void)
{
	CNumber::Uninit();
}

//================================================
//更新処理
//================================================
void CScore::Update(void)
{
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	if (pInputKeyboard->Trigger(DIK_Z))
	{
		AddValue(100);
	}

	CNumber::Update();
}

//================================================
//描画処理
//================================================
void CScore::Draw(void)
{
	CNumber::Draw();
}

//================================================
//生成処理
//================================================
CScore* CScore::Create(SCORE_TYPE scoreType, int digit, int value, const D3DXVECTOR2& center, float width, float height, float spacing)
{
	CScore* pScore = new CScore(SCORE_PRIORITY);
	pScore->SetScoreType(scoreType);
	pScore->Init();
	pScore->BindTexture(m_pTexture[scoreType]);
	pScore->CNumber::Create(digit, value, center, m_pTexture[scoreType], width, height, spacing);
	return pScore;
}

//================================================
//テクスチャロード処理
//================================================
HRESULT CScore::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &m_pTexture[SCORE_TYPE_NORMAL_01])))
	{
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/virus.png", &m_pTexture[SCORE_TYPE_NORMAL_02])))
	{
		return E_FAIL;
	}


	return S_OK;
}

//================================================
//テクスチャアンロード処理
//================================================
void CScore::Unload(void)
{
	for (int nCnt = 0; nCnt < SCORE_TYPE_MAX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

void CScore::AddScore(int value)
{
	m_value += value;
}

