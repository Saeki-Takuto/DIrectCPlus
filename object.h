//==================================================================
//
//オブジェクト処理 [object.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _OBJECT_H_					//このマクロ定義がされてなかったら
#define _OBJECT_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "d3dx9.h"

//================================================
//ライブラリのリンク
//================================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")

//================================================
//マクロ定義
//================================================
#define OBJECT_MAX (128)
#define OBJECT_PRIORITY_MAX (8)

//================================================
//オブジェクトクラス
//================================================
class CObject
{
public:
	CObject(int nPriority = 3);
	virtual ~CObject();

	virtual HRESULT Init(void)=0;
	virtual void Uninit(void)=0;
	virtual void Update(void)=0;
	virtual void Draw(void)=0;
	virtual D3DXVECTOR2 GetPos() = 0;
	virtual int GetWidth() = 0;
	virtual int GetHeight() = 0;


	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_BULLET,
		TYPE_EXPLOSION,
		TYPE_BACKGROUND,
		TYPE_SCORE,
		TYPE_EFFECT,
		TYPE_MAX
	}OBJECT_TYPE;

	void SetType(OBJECT_TYPE type);
	OBJECT_TYPE GetType(void);

	static CObject* GetObject(int nPriority, int nIdx)
	{
		if (nPriority < 0 || nPriority >= OBJECT_PRIORITY_MAX) return nullptr;
		if (nIdx < 0 || nIdx >= OBJECT_MAX) return nullptr;
		return m_apObject[nPriority][nIdx];
	}


protected:
	void Release(void);

private:
	OBJECT_TYPE m_type;
	static int m_nNumAll;//オブジェクト総数
	int m_nID;//自分自身のID

	// object.h
	static CObject* m_apObject[OBJECT_PRIORITY_MAX][OBJECT_MAX];
	int m_nPriority; // 優先度

};

#endif