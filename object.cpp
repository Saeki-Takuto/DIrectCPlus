//==================================================================
//
//�I�u�W�F�N�g���� [object.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//�C���N���[�h
//================================================
#include "object.h"
#include "camera.h"
#include "manager.h"

//================================================
//�ÓI
//================================================
int CObject::m_nNumAll = 0;//�I�u�W�F�N�g����
CObject* CObject::m_apObject[OBJECT_PRIORITY_MAX][OBJECT_MAX] = {};

//================================================
//�R���X�g���N�^
//================================================
CObject::CObject(int nPriority)
{
	for (int nCntObject = 0; nCntObject < OBJECT_MAX; nCntObject++)
	{
		if (m_apObject[nPriority][nCntObject] == NULL)
		{
			m_nPriority = nPriority;
			m_apObject[m_nPriority][nCntObject] = this;
			m_nID = nCntObject;
			m_nNumAll++;
			break;
		}
	}
}

//================================================
//�f�X�g���N�^
//================================================
CObject::~CObject()
{
}

//================================================
//�j������
//================================================
void CObject::Release(void)
{
	int nIdx = this->m_nID;
	int nPriority = this->m_nPriority;

	if (m_apObject[nPriority][nIdx] != NULL)
	{
		delete m_apObject[nPriority][nIdx];
		m_apObject[nPriority][nIdx] = NULL;
		m_nNumAll--;
	}
}

//================================================
//�S�̔j������
//================================================
void CObject::ReleaseAll(void)
{

	for (int nCntPriority = 0; nCntPriority < OBJECT_PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < OBJECT_MAX; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				m_apObject[nCntPriority][nCntObject]->Uninit();
			}
		}
	}
	CCamera* pCamera = CManager::GetCamera();

	pCamera->Uninit();

}

//================================================
//�S�̍X�V����
//================================================
void CObject::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < OBJECT_PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < OBJECT_MAX; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				m_apObject[nCntPriority][nCntObject]->Update();
			}
		}
	}
	CCamera* pCamera = CManager::GetCamera();

	pCamera->Update();

}

//================================================
//�S�̕`�揈��
//================================================
void CObject::DrawAll(void)
{

	for (int nCntPriority = 0; nCntPriority < OBJECT_PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < OBJECT_MAX; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				m_apObject[nCntPriority][nCntObject]->Draw();
			}
		}
	}

	CCamera* pCamera = CManager::GetCamera();

	pCamera->SetCamera();

}

//================================================
//�^�C�v�Z�b�g����
//================================================
void CObject::SetType(OBJECT_TYPE type)
{
	m_type = type;
}

//================================================
//�^�C�v�擾����
//================================================
CObject::OBJECT_TYPE CObject::GetType(void)
{
	return m_type;
}


