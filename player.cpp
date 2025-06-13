//==================================================================
//
//�v���C���[���� [player.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//�C���N���[�h
//================================================
#include "player.h"
#include "input.h"
#include "manager.h"
#include "bullet.h"
#include "effect.h"

//================================================
//�ÓI�����o�ϐ�
//================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//================================================
//�R���X�g���N�^
//================================================
CPlayer::CPlayer(int nPriority) : CObject2D(nPriority)
{
}


//================================================
//�f�X�g���N�^
//================================================
CPlayer::~CPlayer()
{
}

//================================================
//����������
//================================================
HRESULT CPlayer::Init(void)
{
	CObject2D::Init();
	SetType(TYPE_PLAYER);

	return S_OK;
}

//================================================
//�I������
//================================================
void CPlayer::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================
//�X�V����
//================================================
void CPlayer::Update(void)
{
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();


	D3DXVECTOR2 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	if (pInputKeyboard->Repeat(DIK_W))
	{
		pos.y -= 10.0f;
	}
	else if (pInputKeyboard->Repeat(DIK_S))
	{
		pos.y += 10.0f;
	}
	else if (pInputKeyboard->Repeat(DIK_A))
	{
		pos.x -= 10.0f;
	}
	else if (pInputKeyboard->Repeat(DIK_D))
	{
		pos.x += 10.0f;
	}
	else if (pInputKeyboard->Repeat(DIK_Q))
	{
		rot.z -= 0.1f;
	}
	else if (pInputKeyboard->Repeat(DIK_E))
	{
		rot.z += 0.1f;
	}

	SetPos(pos);
	SetRot(rot);

	if (pInputKeyboard->Trigger(DIK_SPACE))
	{
		CBullet* pBullet = CBullet::Create(
			CBullet::TYPE_NORMAL,
			50, 50,
			0.0f, 0.0f,
			1, 1, 0,
			pos.x,
			pos.y,
			rot.z,
			10.0f,
			100
		);
	}

	CObject2D::Update();
}

//================================================
//�`�揈��
//================================================
void CPlayer::Draw(void)
{
	CObject2D::Draw();
}

//================================================
//��������
//================================================
CPlayer* CPlayer::Create(DRAW_TYPE drawtype, int width, int height, float scrollX, float scrollY, int animeFrameU, int animeFrameV, int animePattern, float posX, float posY, float rotZ)
{
	CPlayer* pPlayer = new CPlayer(PLAYER_PRIORITY);
	pPlayer->SetDrawType(drawtype);
	pPlayer->SetWidth(width);
	pPlayer->SetHeight(height);
	pPlayer->SetAnimeFrameU(animeFrameU);
	pPlayer->SetAnimeFrameV(animeFrameV);
	pPlayer->SetAnimePattern(animePattern);
	pPlayer->SetPos(D3DXVECTOR2(posX, posY));
	D3DXVECTOR3 rot = pPlayer->GetRot();
	rot.z = rotZ;
	pPlayer->SetRot(rot);
	pPlayer->Init();
	pPlayer->BindTexture(m_pTexture);
	return pPlayer;
}

//================================================
//�e�N�X�`�����[�h����
//================================================
HRESULT CPlayer::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/mouse.png", &m_pTexture)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//================================================
//�e�N�X�`���A�����[�h����
//================================================
void CPlayer::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

