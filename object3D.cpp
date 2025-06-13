#include "object3D.h"
#include "renderer.h"
#include "manager.h"

CObject3D::CObject3D()
{
}

CObject3D::~CObject3D()
{
}

HRESULT CObject3D::Init(void)
{
	//�f�o�C�X�̎擾
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/mouse.png",
		&m_pTexturePolygon);

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffPolygon, NULL);

	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N
	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W��ݒ�
	pVtx[0].pos = D3DXVECTOR3(-150.0f, 0.0f, 150.0f);
	pVtx[1].pos = D3DXVECTOR3(150.0f, 0.0f, 150.0f);
	pVtx[2].pos = D3DXVECTOR3(-150.0f, 0.0f, -150.0f);
	pVtx[3].pos = D3DXVECTOR3(150.0f, 0.0f, -150.0f);

	//�e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	pVtx[1].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	pVtx[2].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	pVtx[3].nor = D3DXVECTOR3(0.0, 1.0, 0.0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffPolygon->Unlock();

	return S_OK;
}

void CObject3D::Uninit(void)
{
	if (m_pVtxBuffPolygon != NULL)
	{
		m_pVtxBuffPolygon->Release();
		m_pVtxBuffPolygon = NULL;
	}

	if (m_pTexturePolygon != NULL)
	{
		m_pTexturePolygon->Release();
		m_pTexturePolygon = NULL;
	}
}

void CObject3D::Update(void)
{
}

void CObject3D::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorldPolygon);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotPolygon.y, m_rotPolygon.x, m_rotPolygon.z);
	D3DXMatrixMultiply(&m_mtxWorldPolygon, &m_mtxWorldPolygon, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_posPolygon.x, m_posPolygon.y, m_posPolygon.z);
	D3DXMatrixMultiply(&m_mtxWorldPolygon, &m_mtxWorldPolygon, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldPolygon);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexturePolygon);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

CObject3D* CObject3D::Create(void)
{
	CObject3D* pObject3D = new CObject3D;
	pObject3D->Init();

	return pObject3D;
}

D3DXVECTOR2 CObject3D::GetPos(void)
{
	// 3D���W��x, z��2D���W�ɕϊ��i�p�r�ɉ����Ē����j
	return D3DXVECTOR2(m_posPolygon.x, m_posPolygon.z);
}

int CObject3D::GetWidth(void)
{
	// �K�v�ɉ����ēK�؂Ȓl��Ԃ��i��: 300�j
	return 300;
}

int CObject3D::GetHeight(void)
{
	// �K�v�ɉ����ēK�؂Ȓl��Ԃ��i��: 300�j
	return 300;
}

