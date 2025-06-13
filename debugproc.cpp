//==================================================================
//
//�f�o�b�O�\������ [debugproc.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//�C���N���[�h
//================================================
#include "debugproc.h"
#include "manager.h"

//================================================
//�ÓI
//================================================
LPD3DXFONT CDebugProc::m_pFont = NULL;
char CDebugProc::m_aStr[1024] = {};

//================================================
//�R���X�g���N�^
//================================================
CDebugProc::CDebugProc()
{
}

//================================================
//�f�X�g���N�^
//================================================
CDebugProc::~CDebugProc()
{
}

//================================================
//����������
//================================================
void CDebugProc::Init(void)
{
	D3DXCreateFont(
		CManager::GetRenderer()->GetDevice(),
		32, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &m_pFont);
}

//================================================
//�I������
//================================================
void CDebugProc::Uninit(void)
{
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
	m_aStr[0] = {};
}

//================================================
//�������ݏ���
//================================================
void CDebugProc::Print(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vsprintf_s(m_aStr, sizeof(m_aStr), fmt, ap);
	va_end(ap);
}

//================================================
//�`�揈��
//================================================
void CDebugProc::Draw(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	m_pFont->DrawTextA(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
}
