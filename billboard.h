//==================================================================
//
//ビルボード処理 [billboard.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _BILLBOARD_H_					//このマクロ定義がされてなかったら
#define _BILLBOARD_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "object.h"
#include <string>

//================================================
//マクロ定義
//================================================
#define BILL_SIZE (15.0f)

//================================================
//クラス
//================================================
class CBillboard :public CObject
{
public:
	CBillboard();
	~CBillboard();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBillboard* Create(void);

	D3DXVECTOR2 GetPos(void) override;
	int GetWidth(void) override;
	int GetHeight(void) override;

	typedef struct
	{
		D3DXVECTOR3 pos;//頂点座標
		D3DXVECTOR3 nor;//法線ベクトル
		D3DCOLOR col;//頂点カラー
		D3DXVECTOR2 tex;//テクスチャ座標
	}VERTEX_3D;

private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;

	//LPD3DXMESH m_pMesh;
	//LPD3DXBUFFER m_pBuffMat;
	//DWORD m_dwNumMat;

	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
};

#endif