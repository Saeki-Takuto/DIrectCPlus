//==================================================================
//
//�}�l�[�W���[���� [manager.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//�C���N���[�h
//================================================
#include "manager.h"
#include "objectAnim.h"
#include "objectBack.h"
#include "input.h"

//================================================
//�ÓI
//================================================
CRenderer* CManager::m_pRenderer = NULL;
CInputKeyboard* CManager::m_pInputKeyboard = NULL;

//================================================
//�R���X�g���N�^
//================================================
CManager::CManager()
{
	m_pRenderer = NULL;
}

//================================================
//�f�X�g���N�^
//================================================
CManager::~CManager()
{
}

//================================================
//����������
//================================================
HRESULT CManager::Init(HWND hWnd, BOOL bWindow)
{
	//�����_���[�̐ݒ�
	m_pRenderer = new CRenderer;
	//����������
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		delete m_pRenderer;
		m_pRenderer = NULL;
		return -1;
	}

	m_pInputKeyboard = new CInputKeyboard;
	if (FAILED(m_pInputKeyboard->Init(GetModuleHandle(NULL), hWnd)))
	{
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
		return -1;
	}

	//�I�u�W�F�N�g�̏�����
	CObjectBack::Create(CObjectBack::TYPE_ONE);

	//�I�u�W�F�N�g�̏�����
	CObject2D::Create(CObject2D::TYPE_ONE);

	//�I�u�W�F�N�g�̏�����
	CObject2D::Create(CObject2D::TYPE_TWO);

	//�I�u�W�F�N�g�̏�����
	CObjectAnim::Create(CObjectAnim::TYPE_ONE);

	return S_OK;
}

//================================================
//�I������
//================================================
void CManager::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	CObject::ReleaseAll();
	CObject2D::ReleaseAll();
	CObjectAnim::ReleaseAll();
	CObjectBack::ReleaseAll();

	//���̓f�o�C�X�̔j��
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//�����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		//�����_���[�̏I������
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//================================================
//�X�V����
//================================================
void CManager::Update(void)
{
	//���̓f�o�C�X�̍X�V
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
}

//================================================
//�`�揈��
//================================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();
}

//================================================
//�����_���[�擾����
//================================================
CRenderer* CManager::GetRenderer(void)
{
	return m_pRenderer;
}

CInputKeyboard* CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}
