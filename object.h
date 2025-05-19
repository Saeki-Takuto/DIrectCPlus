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

//================================================
//オブジェクトクラス
//================================================
class CObject
{
public:
	CObject();
	virtual ~CObject();

	virtual HRESULT Init(void)=0;
	virtual void Uninit(void)=0;
	virtual void Update(void)=0;
	virtual void Draw(void)=0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

protected:

private:
	static CObject* m_apObject[10];
	static int m_nNumAll;//オブジェクト総数
	int m_nID;//自分自身のID
};

#endif