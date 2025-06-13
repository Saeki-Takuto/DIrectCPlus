//==================================================================
//
//Xファイルオブジェクト処理 [objectX.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _OBJECTX_H_					//このマクロ定義がされてなかったら
#define _OBJECTX_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "object.h"
#include <string>

//================================================
//マクロ定義
//================================================

//================================================
//クラス
//================================================
class CObjectX :public CObject
{
public:
	CObjectX();
	~CObjectX();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectX* Create(void);

	D3DXVECTOR2 GetPos(void) override;
	int GetWidth(void) override;
	int GetHeight(void) override;

private:
	LPDIRECT3DTEXTURE9 m_apTexture[128];
	LPD3DXMESH m_pMesh;
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_dwNumMat;
	D3DXMATRIX m_mtxWorld;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_rotDest;
	D3DXVECTOR3 m_move;
};

#endif