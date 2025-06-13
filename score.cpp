//==================================================================
//
//�G���� [score.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//�C���N���[�h
//================================================
#include "score.h"
#include "input.h"
#include "manager.h"
#include "bullet.h"

//================================================
//�ÓI�����o�ϐ�
//================================================
LPDIRECT3DTEXTURE9 CScore::m_pTexture[SCORE_TYPE_MAX] = {};

//================================================
//�R���X�g���N�^
//================================================
CScore::CScore(int nPriority) : CNumber(nPriority)
{
}


//================================================
//�f�X�g���N�^
//================================================
CScore::~CScore()
{
}

//================================================
//����������
//================================================
HRESULT CScore::Init(void)
{
	CNumber::Init();
	//SetType(TYPE_SCORE);

	return S_OK;
}

//================================================
//�I������
//================================================
void CScore::Uninit(void)
{
	CNumber::Uninit();
}

//================================================
//�X�V����
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
//�`�揈��
//================================================
void CScore::Draw(void)
{
	CNumber::Draw();
}

//================================================
//��������
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
//�e�N�X�`�����[�h����
//================================================
HRESULT CScore::Load(void)
{
	// �f�o�C�X�̎擾
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
//�e�N�X�`���A�����[�h����
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

