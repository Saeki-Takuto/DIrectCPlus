//==================================================================
//
//オブジェクト2D処理 [object2D.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _WALL_H_					//このマクロ定義がされてなかったら
#define _WALL_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "object.h"
#include <string>

//================================================
//マクロ定義
//================================================
#define WALL_WIDTH (150)
#define WALL_HEIGHT (700)

//================================================
//クラス
//================================================
class CWall :public CObject
{
public:
	CWall();
	~CWall();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	typedef struct
	{
		D3DXVECTOR3 pos;//頂点座標
		D3DXVECTOR3 nor;//法線ベクトル
		D3DCOLOR col;//頂点カラー
		D3DXVECTOR2 tex;//テクスチャ座標
	}VERTEX_3D;

	static CWall* Create(void);
	D3DXVECTOR3 GetPos(void) override;
	int GetWidth(void) override;
	int GetHeight(void) override;

	float GetHeightMesh(float posx, float posz);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPolygon = NULL;//頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexturePolygon = NULL;		//テクスチャへのポインタ
	D3DXVECTOR3 m_posPolygon;//位置
	D3DXVECTOR3 m_rotPolygon;//向き
	D3DXMATRIX m_mtxWorldPolygon;//ワールドマトリックス
};

#endif