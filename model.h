//==================================================================
//
//���f������ [model.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _MODEL_H_					//���̃}�N����`������ĂȂ�������
#define _MODEL_H_					//2�d�C���N���[�h�h�~�̃}�N����`

//================================================
//�C���N���[�h
//================================================
#include "object.h"
#include <string>

//================================================
//�}�N����`
//================================================
#define MAX_WORD (1024)
//================================================
//�N���X
//================================================
class CModel
{
public:
	CModel();
	~CModel();

	typedef enum
	{
		MOTION_TYPE_NEUTRAL=0,
		MOTION_TYPE_MOVE,
		MOTION_TYPE_ONE,
		MOTION_TYPE_TWO,
		MOTION_TYPE_THREE,
		MOTION_TYPE_MAX
	}MOTION_TYPE;

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
		KEY_INFO aKeyInfo[30];
	}MOTION_INFO;

	HRESULT Init(const char*XFilePass);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CModel* Create(const char*XFilePass);
	void SetParent(CModel* pModel);
	D3DXMATRIX GetMtxWorld(void);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	void SetKeyFrame0(KEY aKey);
	void SetKeyFrame1(KEY aKey);
	void SetFrame(int Frame);

	void SetMotionNumKey(int nIdx, int nNumKey);
	int GetMotionNumKey(int nIdx);
	void SetFrame(int nIdx,int nIdx1,int nFrame);
	void SetKeyPos(int nIdx, int nIdx1, float x, float y, float z);
	void SetKeyRot(int nIdx, int nIdx1, float x, float y, float z);
	void SetMotionLoop(int nIdx, bool bLoop);

	void SetMotionType(MOTION_TYPE motion);



private:
	LPDIRECT3DTEXTURE9 m_apTexture[128];
	LPD3DXMESH m_pMesh;
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_dwNumMat;

	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	CModel* m_pParent;//�e���f���ւ̃|�C���^

	int m_nFrame;
	KEY m_aKey[2];
	int m_nKey;
	int m_nNumKey;
	int m_nCounterMotion;

	MOTION_TYPE m_MotionType;

	MOTION_INFO m_MotionInfo[MOTION_TYPE_MAX];

};

#endif