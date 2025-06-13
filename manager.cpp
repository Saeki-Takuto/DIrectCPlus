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
#include "input.h"
#include "background.h"
#include "effect.h"
#include "particle.h"
#include "objectX.h"
#include "billboard.h"
#include "3Dplayer.h"

//================================================
//�ÓI
//================================================
CRenderer* CManager::m_pRenderer = NULL;
CInputKeyboard* CManager::m_pInputKeyboard = NULL;
CPlayer* CManager::m_pPlayer = NULL;
CCamera* CManager::m_pCamera = NULL;
CLight* CManager::m_pLight = NULL;

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

	//�J�����̐ݒ�
	m_pCamera = new CCamera;
	m_pCamera->Init();

	//if (FAILED(m_pCamera->Init()))
	//{
	//	delete m_pCamera;
	//	m_pCamera = NULL;
	//	return -1;
	//}

	//���C�g�̐ݒ�
	m_pLight = new CLight;
	m_pLight->Init();
	//if (FAILED(m_pLight->Init()))
	//{
	//	delete m_pLight;
	//	m_pLight = NULL;
	//	return -1;
	//}

	CPlayer::Load();
	CBullet::Load();	
	CExplosion::Load();
	CEnemy::Load();
	CBackground::Load();
	CScore::Load();
	CEffect::Load();

	CObject3D::Create();

	//CBackground::Create(
	//	CBackground::BACKGROUND_TYPE_BACK,
	//	CObject2D::TYPE_NORMAL,
	//	1280, 720,
	//	0.0f, 0.0f,
	//	1, 1, 0,
	//	1280 * 0.5f, 720 * 0.5f,
	//	0.0f
	//);

	//CBackground::Create(
	//	CBackground::BACKGROUND_TYPE_CLOUD,
	//	CObject2D::TYPE_SCROLL,
	//	1280, 720,
	//	0.01f, 0.0f,
	//	1, 1, 0,
	//	1280 * 0.5f, 720 * 0.5f,
	//	0.0f
	//);


	//CPlayer::Create(
	//	CPlayer::TYPE_NORMAL,
	//	150, 250,
	//	0.0f, 0.0f,
	//	1, 1, 0, // �A�j���[�V����
	//	250 * 0.5f, 500 * 0.5f, // ���S���WX, Y
	//	0.0f);

	//CEnemy::Create(
	//	CEnemy::ENEMY_TYPE_NORMAL_01,
	//	CObject2D::TYPE_NORMAL,
	//	100, 100,
	//	0.0f, 0.0f,
	//	1, 1, 0,
	//	50, 50,
	//	0.0f
	//);

	//CEnemy::Create(
	//	CEnemy::ENEMY_TYPE_NORMAL_02,
	//	CObject2D::TYPE_NORMAL,
	//	100, 100,
	//	0.0f, 0.0f,
	//	1, 1, 0,
	//	200, 50,
	//	0.0f
	//);

	// �X�R�A����
	CScore::Create(
		CScore::SCORE_TYPE_NORMAL_01,
		4, 0, // �����Ə����l
		D3DXVECTOR2(1200, 50), // ���S���W
		30.0f, 50.0f, 4.0f // ���A�����A�X�y�[�X
	);

	CBillboard::Create();

	//CObjectX::Create();

	C3DPlayer::Create();

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

	CEffect::Unload();
	CBackground::Unload();
	CEnemy::Unload();
	CExplosion::Unload();
	CBullet::Unload();
	CPlayer::Unload();
	CScore::Unload();
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

//================================================
//�L�[�{�[�h�擾����
//================================================
CInputKeyboard* CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//================================================
//�v���C���[�擾����
//================================================
CPlayer* CManager::GetPlayer(void)
{
	return m_pPlayer;
}

//================================================
//�J�����擾����
//================================================
CCamera* CManager::GetCamera(void)
{
	return m_pCamera;
}

//================================================
//���C�g�擾����
//================================================
CLight* CManager::GetLight(void)
{
	return m_pLight;
}