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

//================================================
//�ÓI
//================================================
int CObject::m_nNumAll = 0;//�I�u�W�F�N�g����
CObject* CObject::m_apObject[10] = {};//�I�u�W�F�N�g�̃|�C���^�z��

//================================================
//�R���X�g���N�^
//================================================
CObject::CObject()
{
	for (int nCntObject = 0; nCntObject < 10; nCntObject++)
	{
		if (m_apObject[nCntObject] == NULL)
		{
			m_apObject[nCntObject] = this;//�������g�̑��
			m_nID = nCntObject;//�������g��ID��ۑ�
			m_nNumAll++;//�������J�E���g�A�b�v
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
//�S�̔j������
//================================================
void CObject::ReleaseAll(void)
{
	for (int nCntObject = 0; nCntObject < 10; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			m_apObject[nCntObject]->Uninit();
		}
	}
}

//================================================
//�S�̍X�V����
//================================================
void CObject::UpdateAll(void)
{
	for (int nCntObject = 0; nCntObject < 10; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			m_apObject[nCntObject]->Update();
		}
	}

}

//================================================
//�S�̕`�揈��
//================================================
void CObject::DrawAll(void)
{
	for (int nCntObject = 0; nCntObject < 10; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			m_apObject[nCntObject]->Draw();
		}
	}
}