//==================================================================
//
//���f������ [model.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//�C���N���[�h
//================================================
#include "model.h"
#include "renderer.h"
#include "manager.h"

//================================================
//�ÓI�����o�ϐ�
//================================================

//================================================
//�R���X�g���N�^
//================================================
CModel::CModel()
{
	m_nNumKey = 2;
	m_MotionType = MOTION_TYPE_NEUTRAL;
}

//================================================
//�f�X�g���N�^
//================================================
CModel::~CModel()
{
}

//================================================
//����������
//================================================
HRESULT CModel::Init(const char* XFilePass)
{
	//�f�o�C�X�̎擾
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(XFilePass,
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

//================================================
//�I������
//================================================
void CModel::Uninit(void)
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

//================================================
//�X�V����
//================================================
void CModel::Update(void)
{
	// �L�[����0�Ȃ牽�����Ȃ�
	int numKey = m_MotionInfo[m_MotionType].nNumKey;
	if (numKey <= 0) return;

	if (m_nKey >= numKey)
	{
		m_nKey = 0;
	}

	int nDis = (m_nKey + 1) % numKey;

	int nFrame = m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].nFrame;
	if (nFrame <= 0) nFrame = 1; // 0���Z�h�~

	D3DXVECTOR3 fPosB, fRotB;
	fPosB.x = m_MotionInfo[m_MotionType].aKeyInfo[nDis].aKey.fPosX - m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fPosX;
	fPosB.y = m_MotionInfo[m_MotionType].aKeyInfo[nDis].aKey.fPosY - m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fPosY;
	fPosB.z = m_MotionInfo[m_MotionType].aKeyInfo[nDis].aKey.fPosZ - m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fPosZ;

	fRotB.x = m_MotionInfo[m_MotionType].aKeyInfo[nDis].aKey.fRotX - m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fRotX;
	fRotB.y = m_MotionInfo[m_MotionType].aKeyInfo[nDis].aKey.fRotY - m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fRotY;
	fRotB.z = m_MotionInfo[m_MotionType].aKeyInfo[nDis].aKey.fRotZ - m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fRotZ;

	float fDis = (float)m_nCounterMotion / nFrame;

	D3DXVECTOR3 fPosA, fRotA;
	fPosA.x = m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fPosX + fPosB.x * fDis;
	fPosA.y = m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fPosY + fPosB.y * fDis;
	fPosA.z = m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fPosZ + fPosB.z * fDis;

	fRotA.x = m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fRotX + fRotB.x * fDis;
	fRotA.y = m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fRotY + fRotB.y * fDis;
	fRotA.z = m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fRotZ + fRotB.z * fDis;

	m_rot = fRotA;

	m_nCounterMotion++;

	if (m_nCounterMotion >= nFrame)
	{
		m_nCounterMotion = 0;
		m_nKey++;
		if (m_nKey >= numKey)
		{
			m_nKey = 0;
		}
	}
}


//================================================
//�`�揈��
//================================================
void CModel::Draw(void)
{
	// �f�o�C�X�̎擾
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

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

	//�e�̃}�g���b�N�X�Ɗ|�����킹��
	D3DXMATRIX mtxParent;//�e���f���̃}�g���b�N�X
	if (m_pParent != NULL)
	{//�e�����݂���
		//�e���f���̃}�g���b�N�X���擾����
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{//�e�����݂��Ȃ�
		//����(�ŐV)�̃}�g���b�N�X���擾����[=�v���C���[�̃}�g���b�N�X]
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}
	//�e�̃}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

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
}

//================================================
//��������
//================================================
CModel* CModel::Create(const char* XFilePass)
{
	CModel* pCModel = new CModel;
	pCModel->Init(XFilePass);
	return pCModel;
}

void CModel::SetParent(CModel* pModel)
{
	m_pParent = pModel;
}

D3DXMATRIX CModel::GetMtxWorld(void)
{
	return m_mtxWorld;
}

void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

void CModel::SetKeyFrame0(KEY aKey)
{
	m_aKey[0] = aKey;
}

void CModel::SetKeyFrame1(KEY aKey)
{
	m_aKey[1] = aKey;
}

void CModel::SetFrame(int Frame)
{
	m_nFrame = Frame;
}

void CModel::SetMotionNumKey(int nIdx, int nNumKey)
{
	m_MotionInfo[nIdx].nNumKey = nNumKey;
}

int CModel::GetMotionNumKey(int nIdx)
{
	return m_MotionInfo[nIdx].nNumKey;
}

void CModel::SetFrame(int nIdx, int nIdx1,int nFrame)
{
	m_MotionInfo[nIdx].aKeyInfo[nIdx1].nFrame = nFrame;
}

void CModel::SetKeyPos(int nIdx, int nIdx1, float x, float y, float z)
{
	m_MotionInfo[nIdx].aKeyInfo[nIdx1].aKey.fPosX = x;
	m_MotionInfo[nIdx].aKeyInfo[nIdx1].aKey.fPosY = y;
	m_MotionInfo[nIdx].aKeyInfo[nIdx1].aKey.fPosZ = z;
}

void CModel::SetKeyRot(int nIdx, int nIdx1, float x, float y, float z)
{
	m_MotionInfo[nIdx].aKeyInfo[nIdx1].aKey.fRotX = x;
	m_MotionInfo[nIdx].aKeyInfo[nIdx1].aKey.fRotY = y;
	m_MotionInfo[nIdx].aKeyInfo[nIdx1].aKey.fRotZ = z;
}

void CModel::SetMotionLoop(int nIdx, bool bLoop)
{
	m_MotionInfo[nIdx].bLoop = bLoop;
}

void CModel::SetMotionType(MOTION_TYPE motion)
{
	m_MotionType = motion;
}

