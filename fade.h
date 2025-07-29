//==================================================================
//
//フェード処理 [fade.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _FADE_H_					//このマクロ定義がされてなかったら
#define _FADE_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "main.h"
#include <d3dx9.h>
#include "scene.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラス
//================================================
class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,//何もしていない状態
		FADE_IN,//フェードイン状態
		FADE_OUT,//フェードアウト状態
		FADE_MAX
	}FADE;

	typedef struct
	{
		D3DXVECTOR3 pos;				//頂点座標
		float rhw;						//座標変換用係数(1.0fで固定)
		D3DCOLOR col;					//頂点カラー
		D3DXVECTOR2 tex;				//テクスチャ座標
	}VERTEX_2D;

	CFade();
	~CFade();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	static CFade* Create();

	FADE GetFade() { return m_fade; }//現在のモード
	void SetFade(CScene::MODE pmode);

private:
	static FADE m_fade;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXCOLOR m_color;
	CScene* m_pScene;
	CScene::MODE m_mode;
};


#endif