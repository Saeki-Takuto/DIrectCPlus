//==================================================================
//
//���͏��� [input.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _INPUT_H_					//���̃}�N����`������ĂȂ�������
#define _INPUT_H_					//2�d�C���N���[�h�h�~�̃}�N����`

//================================================
//�C���N���[�h
//================================================
#include "d3dx9.h"
#include <dinput.h>

//================================================
//���C�u�����̃����N
//================================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")											//���͏����ɕK�v

//================================================
//�}�N����`
//================================================
#define DIRECTINPUT_VERSION (0x0800)//�r���h�̌x���Ώ��p�}�N��
#define NUM_KEY_MAX (256)

//================================================
//�N���X
//================================================
class CInput
{
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//================================================
//�L�[�{�[�h���̓N���X
//================================================
class CInputKeyboard :public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);

	bool Trigger(int nKey);
	bool Release(int nKey);
	bool Repeat(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aOldState[NUM_KEY_MAX];
};

#endif