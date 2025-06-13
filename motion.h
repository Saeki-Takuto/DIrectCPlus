//==================================================================
//
//モーション処理 [motion.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _MOTION_H_					//このマクロ定義がされてなかったら
#define _MOTION_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "model.h"

//================================================
//ライブラリのリンク
//================================================

//================================================
//マクロ定義
//================================================
#define MAX_INFO (256)
#define MAX_KEY (30)

//================================================
//クラス
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