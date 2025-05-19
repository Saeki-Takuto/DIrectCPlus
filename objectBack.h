//==================================================================
//
//オブジェクト背景処理 [objectBack.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _OBJECTBACK_H_					//このマクロ定義がされてなかったら
#define _OBJECTBACK_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "object.h"

//================================================
//ライブラリのリンク
//================================================

//================================================
//マクロ定義
//================================================

//================================================
//クラス
//================================================
class CObjectBack :public CObject
{
public:
	CObjectBack();
	~CObjectBack();

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
		TYPE_NONE = 0,
		TYPE_ONE,
		TYPE_MAX
	}TYPE;

	static CObjectBack* Create(TYPE type);

private:
	TYPE m_type;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	float m_aPosTexU;
};

#endif