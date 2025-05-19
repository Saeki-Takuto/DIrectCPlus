//==================================================================
//
//�I�u�W�F�N�g�w�i���� [objectBack.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//�C���N���[�h
//================================================
#include "objectBack.h"
#include "renderer.h"
#include "manager.h"

//================================================
//�ÓI�����o�ϐ�
//================================================

//================================================
//�R���X�g���N�^
//================================================
CObjectBack::CObjectBack()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_aPosTexU = 0.0f;
}

//================================================
//�f�X�g���N�^
//================================================
CObjectBack::~CObjectBack()
{
}

//================================================
//����������
//================================================
HRESULT CObjectBack::Init(void)
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
			"data/TEXTURE/bg100.png",
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
		pVtx[0].pos = D3DXVECTOR3(000.0f, 000.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
		break;
	}


	switch (m_type)
	{
	case TYPE_ONE:
		break;
	}

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_aPosTexU, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_aPosTexU + 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_aPosTexU, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_aPosTexU + 1.0f, 1.0f);


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
void CObjectBack::Uninit(void)
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
void CObjectBack::Update(void)
{
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_aPosTexU += 0.001f * 1;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_aPosTexU, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_aPosTexU + 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_aPosTexU, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_aPosTexU + 1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//================================================
//�`�揈��
//================================================
void CObjectBack::Draw(void)
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

CObjectBack* CObjectBack::Create(TYPE type)
{
	CObjectBack* pObjectBack;

	//�I�u�W�F�N�g�̍쐬
	pObjectBack = new CObjectBack;
	pObjectBack->m_type = type;
	pObjectBack->Init();

	return pObjectBack;
}






