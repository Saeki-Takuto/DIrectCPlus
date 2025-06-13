//==================================================================
//
//モデル処理 [model.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _MODEL_H_					//このマクロ定義がされてなかったら
#define _MODEL_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "object.h"
#include <string>

//================================================
//マクロ定義
//================================================
#define MAX_WORD (1024)
//================================================
//クラス
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

	//キー要素の構造体
	typedef struct
	{
		float fPosX;	//位置X
		float fPosY;	//位置Y
		float fPosZ;	//位置Z

		float fRotX;	//向きX
		float fRotY;	//向きY
		float fRotZ;	//向きZ
	}KEY;

	//キー情報の構造体
	typedef struct
	{
		int nFrame;//フレーム
		KEY aKey;
	}KEY_INFO;

	//モーション情報の構造体
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
	CModel* m_pParent;//親モデルへのポインタ

	int m_nFrame;
	KEY m_aKey[2];
	int m_nKey;
	int m_nNumKey;
	int m_nCounterMotion;

	MOTION_TYPE m_MotionType;

	MOTION_INFO m_MotionInfo[MOTION_TYPE_MAX];

};

#endif