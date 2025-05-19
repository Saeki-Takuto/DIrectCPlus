//==================================================================
//
//�}�l�[�W���[���� [manager.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _MANAGER_H_					//���̃}�N����`������ĂȂ�������
#define _MANAGER_H_					//2�d�C���N���[�h�h�~�̃}�N����`

//================================================
//�C���N���[�h
//================================================
#include "main.h"
#include "renderer.h"
#include "object.h"
#include "object2D.h"
#include "input.h"

//================================================
//���C�u�����̃����N
//================================================

//================================================
//�}�N����`
//================================================

//================================================
//�N���X
//================================================
class CManager
{
public:
	CManager();
	~CManager();

	HRESULT Init(HWND hWnd,
		BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRenderer* GetRenderer(void);
	static CInputKeyboard* GetInputKeyboard(void);

private:
	static CRenderer* m_pRenderer;
	static CInputKeyboard* m_pInputKeyboard;
};

#endif