//==================================================================
//
//���͏��� [input.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//�C���N���[�h
//================================================
#include "input.h"

//================================================
//�ÓI�����o�ϐ�
//================================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//================================================
//�R���X�g���N�^
//================================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//================================================
//�f�X�g���N�^
//================================================
CInput::~CInput()
{
}

//================================================
//����������
//================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		//DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}

		return S_OK;
	}
}

//================================================
//�I������
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
//�L�[�{�[�h�R���X�g���N�^
//================================================
CInputKeyboard::CInputKeyboard()
{
	//�L�[���̃N���A
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		m_aKeyState[nCnt] = 0;
		m_aOldState[nCnt] = 0;
	}
}

//================================================
//�L�[�{�[�h�f�X�g���N�^
//================================================
CInputKeyboard::~CInputKeyboard()
{
}

//================================================
//�L�[�{�[�h����������
//================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	//�L�[�{�[�h�f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�f�o�C�X�̏�����
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�f�o�C�X�̋������[�h�̐ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�f�o�C�X�̎擾
	m_pDevice->Acquire();

	return S_OK;
}

//================================================
//�L�[�{�[�h�I������
//================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//================================================
//�L�[�{�[�h�X�V����
//================================================
void CInputKeyboard::Update(void)
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		m_aOldState[nCntKey] = m_aKeyState[nCntKey];//�ЂƂO�̃L�[�{�[�h�v���X����ۑ�
	}

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(m_aKeyState), &m_aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyState[nCntKey] = m_aKeyState[nCntKey];	//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();						//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//================================================
//�L�[�{�[�h�v���X�擾����
//================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//================================================
//�L�[�{�[�h�����u�ԏ���
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
//�L�[�{�[�h�������
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
//�L�[�{�[�h���s�[�g����
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