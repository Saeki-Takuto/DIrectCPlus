//==================================================================
//
//C++��DirectX [main.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _MAIN_H_	//���̃}�N����`������ĂȂ�������
#define _MAIN_H_	//2�d�C���N���[�h�h�~�̃}�N����`

//================================================
//�C���N���[�h
//================================================
#include <windows.h>
#define DIRECTINPUT_VERSION (0x0800)	//�r���h�̌x���Ώ��p�}�N��
#include "dinput.h"						//���͏����ɕK�v

//================================================
//���C�u�����̃����N
//================================================
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")	//���͏����ɕK�v

//================================================
//�}�N����`
//================================================
#define CLASS_NAME "WindowClass"					//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "�����X�`�t�@���^�W�X�^"		//�E�B���h�E�̖��O(�L���v�V�����ɕ\��)
#define SCREEN_WIDTH (1280)							//�E�B���h�E�̕�
#define SCREEN_HEIGHT (720)							//�E�B���h�E�̍���

//================================================
//�v���g�^�C�v�錾
//================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif

