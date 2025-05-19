//==================================================================
//
//オブジェクト2D処理 [object2D.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _OBJECT2D_H_					//このマクロ定義がされてなかったら
#define _OBJECT2D_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "object.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラス
//================================================
class CObject2D :public CObject
{
public:
	CObject2D();
	~CObject2D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	typedef struct
	{
		D3DXVECTOR3 pos;				//頂点座標
		float rhw;						//座標変換用係数(1.0fで固定)
		D3DCOLOR col;					//頂点カラー
		D3DXVECTOR2 tex;				//テクスチャ座標
	}VERTEX_2D;

	typedef enum
	{
		TYPE_NONE=0,
		TYPE_ONE,
		TYPE_TWO,
		TYPE_MAX
	}TYPE;

	static CObject2D* Create(TYPE type);

private:
	TYPE m_type;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
};

#endif