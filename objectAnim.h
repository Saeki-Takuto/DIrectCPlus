//==================================================================
//
//オブジェクトアニメ処理 [objectAnim.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _OBJECTANIM_H_					//このマクロ定義がされてなかったら
#define _OBJECTANIM_H_					//2重インクルード防止のマクロ定義

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
#define WIDTH (50)			//幅
#define HEIGHT (100)			//高さ

#define ANIME_FRAME_U_NUM (8)
#define ANIME_FRAME_V_NUM (1)

#define ANIME_U(index) ((float)((index) % ANIME_FRAME_U_NUM) / (ANIME_FRAME_U_NUM))
#define ANIME_V(index) ((float)((index) / ANIME_FRAME_U_NUM) / (ANIME_FRAME_V_NUM))
#define ANIME_UW      (1.0f / ANIME_FRAME_U_NUM)
#define ANIME_VH      (1.0f / ANIME_FRAME_V_NUM)

//================================================
//クラス
//================================================
class CObjectAnim :public CObject
{
public:
	CObjectAnim();
	~CObjectAnim();

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

	typedef struct
	{
		D3DXVECTOR3 pos;//現在の位置
		D3DXVECTOR3 posOld;//前回の位置
		D3DXVECTOR3 rot;//向き
		D3DXVECTOR3 move;//移動量
		int nCounterState;//状態管理カウンター
		int nLife;//体力
		float nStamina;//スタミナ
		bool bDisp;//表示するかしないか
		bool bUse;
		bool bJump;
		bool bRightMove;
		bool bGoal;
		bool bFall;
		bool bClear;
	}Player;



	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_ONE,
		TYPE_MAX
	}TYPE;

	static CObjectAnim* Create(TYPE type);

private:
	TYPE m_type;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	int m_CounterAnim;
	int m_nPatternAnim;
	Player m_Player;
};

#endif