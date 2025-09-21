//==================================================================
//
//敵処理 [time.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//インクルード
//================================================
#include "time.h"
#include "input.h"
#include "manager.h"
#include "bullet.h"

//================================================
//静的メンバ変数
//================================================
LPDIRECT3DTEXTURE9 CTime::m_pTexture[TIME_TYPE_MAX] = {};

//================================================
//コンストラクタ
//================================================
CTime::CTime(int nPriority) : CNumber(nPriority)
{
}


//================================================
//デストラクタ
//================================================
CTime::~CTime()
{
}

//================================================
//初期化処理
//================================================
HRESULT CTime::Init(void)
{
	CNumber::Init();
	//SetType(TYPE_TIME);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CTime::Uninit(void)
{
	CNumber::Uninit();
}

//================================================
//更新処理
//================================================
void CTime::Update(void)
{
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	m_nCntTime++;
	if (m_nCntTime >= 60)
	{
		m_nCntTime = 0;
 		AddValue(1);
	}


	//if (pInputKeyboard->Trigger(DIK_Z))
	//{
	//	AddValue(100);
	//}

	CNumber::Update();
}

//================================================
//描画処理
//================================================
void CTime::Draw(void)
{
	CNumber::Draw();
}

//================================================
//生成処理
//================================================
CTime* CTime::Create(TIME_TYPE timeType, int digit, int value, const D3DXVECTOR3& center, float width, float height, float spacing)
{
	CTime* pTime = new CTime(TIME_PRIORITY);
	pTime->SetTimeType(timeType);
	pTime->Init();
	pTime->SetType(TYPE_TIME);
	pTime->BindTexture(m_pTexture[timeType]);
	pTime->CNumber::Create(digit, value, center, m_pTexture[timeType], width, height, spacing);
	return pTime;
}

//================================================
//テクスチャロード処理
//================================================
HRESULT CTime::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number001.png", &m_pTexture[TIME_TYPE_NORMAL_01])))
	{
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/virus.png", &m_pTexture[TIME_TYPE_NORMAL_02])))
	{
		return E_FAIL;
	}


	return S_OK;
}

//================================================
//テクスチャアンロード処理
//================================================
void CTime::Unload(void)
{
	for (int nCnt = 0; nCnt < TIME_TYPE_MAX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

void CTime::AddTime(int value)
{
	SetValue(GetValue() + value);
}

