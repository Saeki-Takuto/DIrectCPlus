//==================================================================
//
//入力処理 [input.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//インクルード
//================================================
#include "input.h"

//================================================
//静的メンバ変数
//================================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//================================================
//コンストラクタ
//================================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//================================================
//デストラクタ
//================================================
CInput::~CInput()
{
}

//================================================
//初期化処理
//================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		//DirectInputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}

		return S_OK;
	}
}

//================================================
//終了処理
//================================================
void CInput::Uninit(void)
{
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//================================================
//キーボードコンストラクタ
//================================================
CInputKeyboard::CInputKeyboard()
{
	//キー情報のクリア
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		m_aKeyState[nCnt] = 0;
		m_aOldState[nCnt] = 0;
	}
}

//================================================
//キーボードデストラクタ
//================================================
CInputKeyboard::~CInputKeyboard()
{
}

//================================================
//キーボード初期化処理
//================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	//キーボードデバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//キーボードデバイスの初期化
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//キーボードデバイスの協調モードの設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	//キーボードデバイスの取得
	m_pDevice->Acquire();

	return S_OK;
}

//================================================
//キーボード終了処理
//================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//================================================
//キーボード更新処理
//================================================
void CInputKeyboard::Update(void)
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		m_aOldState[nCntKey] = m_aKeyState[nCntKey];//ひとつ前のキーボードプレス情報を保存
	}

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(m_aKeyState), &m_aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyState[nCntKey] = m_aKeyState[nCntKey];	//キーボードのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire();						//キーボードへのアクセス権を獲得
	}
}

//================================================
//キーボードプレス取得処理
//================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//================================================
//キーボード押下瞬間処理
//================================================
bool CInputKeyboard::Trigger(int nKey)
{
	bool Trigger = false;
	if (m_aKeyState[nKey] & 0x80 && !(m_aOldState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

//================================================
//キーボード解放処理
//================================================
bool CInputKeyboard::Release(int nKey)
{
	bool Trigger = false;
	if (m_aOldState[nKey] & 0x80 && !(m_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

//================================================
//キーボードリピート処理
//================================================
bool CInputKeyboard::Repeat(int nKey)
{
	bool Trigger = false;
	if (m_aOldState[nKey] & 0x80 && (m_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}