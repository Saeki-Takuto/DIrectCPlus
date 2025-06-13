#include "objectX.h"
#include "renderer.h"
#include "manager.h"

CObjectX::CObjectX()
{
}

CObjectX::~CObjectX()
{
}

HRESULT CObjectX::Init(void)
{
	//�f�o�C�X�̎擾
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/vending.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_apTexture[nCntMat]);
		}
	}

	return S_OK;
}

void CObjectX::Uninit(void)
{
	//�e�N�X�`���̉��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//���_�o�b�t�@�̉��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	for (int nCnt = 0; nCnt < 128; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

void CObjectX::Update(void)
{
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	D3DXVECTOR3 CamRot;
	//�J�����̎擾
	CCamera* pCamera = CManager::GetCamera();

	CamRot = pCamera->GetRot();

	if (pInputKeyboard->Repeat(DIK_DOWN) == true)
	{
		m_move.x += sinf(CamRot.y);
		m_move.z += cosf(CamRot.y);
		m_rotDest.y = CamRot.y - D3DX_PI;
	}
	else if (pInputKeyboard->Repeat(DIK_UP) == true)
	{
		m_move.x -= sinf(CamRot.y);
		m_move.z -= cosf(CamRot.y);
		m_rotDest.y = CamRot.y;

	}
	else if (pInputKeyboard->Repeat(DIK_RIGHT) == true)
	{
		m_move.z += sinf(CamRot.y);
		m_move.x -= cosf(CamRot.y);
		m_rotDest.y = CamRot.y + D3DX_PI * 0.5f;
	}
	else if (pInputKeyboard->Repeat(DIK_LEFT) == true)
	{
		m_move.z -= sinf(CamRot.y);
		m_move.x += cosf(CamRot.y);
		m_rotDest.y = CamRot.y - D3DX_PI * 0.5f;
	}

	if (m_rotDest.y - m_rot.y >= D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
	else if (m_rotDest.y - m_rot.y <= -D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}

	m_rot.y += (m_rotDest.y - m_rot.y) * 0.1f;

	m_pos += m_move;

	//�ړ��ʂ��X�V(����������)
	m_move.x += (0.0f - m_move.x) * 0.17f;
	m_move.z += (0.0f - m_move.z) * 0.17f;
}

void CObjectX::Draw(void)
{
	// �f�o�C�X�̎擾
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	// �����_�[�X�e�[�g�̕ۑ�
	DWORD oldLighting, oldAlphaBlend, oldZWrite, oldSrcBlend, oldDestBlend;
	pDevice->GetRenderState(D3DRS_LIGHTING, &oldLighting);
	pDevice->GetRenderState(D3DRS_ALPHABLENDENABLE, &oldAlphaBlend);
	pDevice->GetRenderState(D3DRS_ZWRITEENABLE, &oldZWrite);
	pDevice->GetRenderState(D3DRS_SRCBLEND, &oldSrcBlend);
	pDevice->GetRenderState(D3DRS_DESTBLEND, &oldDestBlend);

	// �s�������f���p�̐ݒ�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^
	 
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_apTexture[nCntMat]);

		//���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	// �����_�[�X�e�[�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, oldLighting);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, oldAlphaBlend);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, oldZWrite);
	pDevice->SetRenderState(D3DRS_SRCBLEND, oldSrcBlend);
	pDevice->SetRenderState(D3DRS_DESTBLEND, oldDestBlend);
}

CObjectX* CObjectX::Create(void)
{
	CObjectX* pObjectX = new CObjectX;
	pObjectX->Init();

	return pObjectX;
}

D3DXVECTOR2 CObjectX::GetPos(void)
{
	return D3DXVECTOR2();
}

int CObjectX::GetWidth(void)
{
	return 0;
}

int CObjectX::GetHeight(void)
{
	return 0;
}