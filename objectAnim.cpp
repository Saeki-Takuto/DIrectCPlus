//==================================================================
//
//�I�u�W�F�N�g�A�j������ [objectAnim.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//�C���N���[�h
//================================================
#include "objectAnim.h"
#include "renderer.h"
#include "manager.h"

//================================================
//�ÓI�����o�ϐ�
//================================================

//================================================
//�R���X�g���N�^
//================================================
CObjectAnim::CObjectAnim()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_CounterAnim = 0;
	m_nPatternAnim = 0;
	m_Player.pos.x = 150.0f;
	m_Player.pos.y = 150.0f;
	m_Player.pos.z = 150.0f;
}

//================================================
//�f�X�g���N�^
//================================================
CObjectAnim::~CObjectAnim()
{
}

//================================================
//����������
//================================================
HRESULT CObjectAnim::Init(void)
{
	CRenderer* renderer;

	renderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = renderer->GetDevice();

	switch (m_type)
	{
	case TYPE_ONE:
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data/TEXTURE/runningman000.png",
			&m_pTexture);
		break;
	}

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	switch (m_type)
	{
	case TYPE_ONE:
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_Player.pos.x - WIDTH / 2, m_Player.pos.y - HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_Player.pos.x + WIDTH / 2, m_Player.pos.y - HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_Player.pos.x - WIDTH / 2, m_Player.pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_Player.pos.x + WIDTH / 2, m_Player.pos.y, 0.0f);
		break;
	}

	float u = 0.0f, v = 0.0f; // �����Ő錾

	switch (m_type)
	{
	case TYPE_ONE:
		// ���_���W�̐ݒ�
		u = ANIME_U(0);
		v = ANIME_V(0);
		break;
	}

	// �e�N�X�`�����W�̐ݒ�i���ʁj
	pVtx[0].tex = D3DXVECTOR2(u, v);
	pVtx[1].tex = D3DXVECTOR2(u + ANIME_UW, v);
	pVtx[2].tex = D3DXVECTOR2(u, v + ANIME_VH);
	pVtx[3].tex = D3DXVECTOR2(u + ANIME_UW, v + ANIME_VH);


	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;


	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//�I������
//================================================
void CObjectAnim::Uninit(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//================================================
//�X�V����
//================================================
void CObjectAnim::Update(void)
{
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();


	if (pInputKeyboard->Repeat(DIK_RIGHT))
	{
		m_Player.pos.x += 10.0f;
	}

	if (pInputKeyboard->Repeat(DIK_LEFT))
	{
		m_Player.pos.x -= 10.0f;
	}

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Player.pos.x - WIDTH / 2, m_Player.pos.y - HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Player.pos.x + WIDTH / 2, m_Player.pos.y - HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Player.pos.x - WIDTH / 2, m_Player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Player.pos.x + WIDTH / 2, m_Player.pos.y, 0.0f);


	m_CounterAnim++;							//�A�j���[�V�����J�E���^�[�����Z

	if ((m_CounterAnim % 5) == 0)
	{
		m_nPatternAnim = (m_nPatternAnim + 1) % (ANIME_FRAME_U_NUM * ANIME_FRAME_V_NUM);

		float u = ANIME_U(m_nPatternAnim);
		float v = ANIME_V(m_nPatternAnim);

		pVtx[0].tex = D3DXVECTOR2(u, v);
		pVtx[1].tex = D3DXVECTOR2(u + ANIME_UW, v);
		pVtx[2].tex = D3DXVECTOR2(u, v + ANIME_VH);
		pVtx[3].tex = D3DXVECTOR2(u + ANIME_UW, v + ANIME_VH);
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//================================================
//�`�揈��
//================================================
void CObjectAnim::Draw(void)
{
	CRenderer* renderer;

	renderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = renderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

CObjectAnim* CObjectAnim::Create(TYPE type)
{
	CObjectAnim* pObjectAnim;

	//�I�u�W�F�N�g�̍쐬
	pObjectAnim = new CObjectAnim;
	pObjectAnim->m_type = type;
	pObjectAnim->Init();

	return pObjectAnim;
}