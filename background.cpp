//==================================================================
//
//�w�i���� [background.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//�C���N���[�h
//================================================
#include "background.h"
#include "input.h"
#include "manager.h"
#include "bullet.h"

//================================================
//�ÓI�����o�ϐ�
//================================================
LPDIRECT3DTEXTURE9 CBackground::m_pTexture[BACKGROUND_TYPE_MAX] = {};

//================================================
//�R���X�g���N�^
//================================================
CBackground::CBackground(int nPriority) : CObject2D(nPriority)
{
}

//================================================
//�f�X�g���N�^
//================================================
CBackground::~CBackground()
{
}

//================================================
//����������
//================================================
HRESULT CBackground::Init(void)
{
	CObject2D::Init();
	SetType(TYPE_BACKGROUND);

	return S_OK;
}

//================================================
//�I������
//================================================
void CBackground::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================
//�X�V����
//================================================
void CBackground::Update(void)
{
	CObject2D::Update();
}

//================================================
//�`�揈��
//================================================
void CBackground::Draw(void)
{
	CObject2D::Draw();
}

//================================================
//��������
//================================================
CBackground* CBackground::Create(BACKGROUND_TYPE backgroundtype, DRAW_TYPE drawtype, int width, int height, float scrollX, float scrollY, int animeFrameU, int animeFrameV, int animePattern, float posX, float posY, float rotZ)
{
	CBackground* pBackground = new CBackground(BACKGROUND_PRIORITY);
	pBackground->SetDrawType(drawtype);
	pBackground->SetWidth(width);
	pBackground->SetHeight(height);
	pBackground->SetScrollSpeedX(scrollX);
	pBackground->SetScrollSpeedY(scrollY);
	pBackground->SetAnimeFrameU(animeFrameU);
	pBackground->SetAnimeFrameV(animeFrameV);
	pBackground->SetAnimePattern(animePattern);
	pBackground->SetPos(D3DXVECTOR2(posX, posY));
	D3DXVECTOR3 rot = pBackground->GetRot();
	rot.z = rotZ;
	pBackground->SetRot(rot);
	pBackground->Init();
	pBackground->BindTexture(m_pTexture[backgroundtype]);
	return pBackground;
}

//================================================
//�e�N�X�`�����[�h����
//================================================
HRESULT CBackground::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/001.png", &m_pTexture[BACKGROUND_TYPE_CLOUD])))
	{
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg103.jpg", &m_pTexture[BACKGROUND_TYPE_BACK])))
	{
		return E_FAIL;
	}


	return S_OK;
}

//================================================
//�e�N�X�`���A�����[�h����
//================================================
void CBackground::Unload(void)
{
	for (int nCnt = 0; nCnt < BACKGROUND_TYPE_MAX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

