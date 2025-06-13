//==================================================================
//
//���[�V�������� [motion.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _MOTION_H_					//���̃}�N����`������ĂȂ�������
#define _MOTION_H_					//2�d�C���N���[�h�h�~�̃}�N����`

//================================================
//�C���N���[�h
//================================================
#include "model.h"

//================================================
//���C�u�����̃����N
//================================================

//================================================
//�}�N����`
//================================================
#define MAX_INFO (256)
#define MAX_KEY (30)

//================================================
//�N���X
//================================================
class CMotion
{
public:
	CMotion();
	~CMotion();

	typedef enum
	{
		MOTION_TYPE_NEUTRAL = 0,
		MOTION_TYPE_MOVE,
		MOTION_TYPE_APPEAL,
		MOTION_TYPE_JUMP,
		MOTION_TYPE_LANDING,
		MOTION_TYPE_MAX
	}TYPE;

	//�L�[�v�f�̍\����
	typedef struct
	{
		float fPosX;	//�ʒuX
		float fPosY;	//�ʒuY
		float fPosZ;	//�ʒuZ

		float fRotX;	//����X
		float fRotY;	//����Y
		float fRotZ;	//����Z
	}KEY;

	//�L�[���̍\����
	typedef struct
	{
		int nFrame;//�t���[��
		KEY aKey;
	}KEY_INFO;

	//���[�V�������̍\����
	typedef struct
	{
		bool bLoop;
		int nNumKey;
		KEY_INFO aKeyInfo[MAX_KEY];
	}INFO;

	void Set(int nType);
	void Update(void);
	int GetType(void);
	bool IsFinish(void);

	void SetInfo(INFO info);
	void SetModel(CModel** ppModel, int nNumModel);

private:
	INFO m_aInfo[MAX_INFO];
	int m_nNumAll;
	int m_nType;
	bool m_bLoop;
	int m_nNumKey;
	int m_nKey;
	int m_nCounter;
	bool m_bFinish;

	CModel** m_ppModel;
	int m_nNumModel;
};

#endif