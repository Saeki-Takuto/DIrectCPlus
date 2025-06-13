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
#include <string>

//================================================
//マクロ定義
//================================================

//================================================
//クラス
//================================================
class CObject2D :public CObject
{
public:
	CObject2D(int nPriority = 3);
	~CObject2D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

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
		TYPE_NORMAL,
		TYPE_ANIME,
		TYPE_SCROLL,
		TYPE_MAX
	}DRAW_TYPE;

	static CObject2D* Create(
		DRAW_TYPE type,
		int width,
		int height,
		float scrollX = 0.0f,
		float scrollY = 0.0f,
		int animeFrameU = 1,
		int animeFrameV = 1,
		int animePattern = 0,
		float posX = 0.0f,
		float posY = 0.0f,
		float rotZ = 0.0f
	);

	DRAW_TYPE GetDrawType() const { return m_drawtype; }
	D3DXVECTOR3 GetRot() const { return m_rot; }
	D3DXVECTOR3 GetMove() const { return m_move; }
	D3DXVECTOR2 GetPos(void) override { return m_pos; }
	int GetWidth(void) override { return m_width; }
	int GetHeight(void) override { return m_height; }	int GetAnimePattern() const { return m_animePattern; }
	LPDIRECT3DTEXTURE9 GetTexture() const { return m_pTexture; }
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff() const { return m_pVtxBuff; }
	float GetScrollPosX() const { return m_scrollPosX; }
	float GetScrollPosY() const { return m_scrollPosY; }
	float GetScrollSpeedX() const { return m_scrollSpeedX; }
	float GetScrollSpeedY() const { return m_scrollSpeedY; }
	int GetAnimeFrameU() const { return m_animeFrameU; }
	int GetAnimeFrameV() const { return m_animeFrameV; }
	int GetAnimeCounter() const { return m_animeCounter; }

	void SetDrawType(DRAW_TYPE drawtype) { m_drawtype = drawtype; }
	void SetPos(const D3DXVECTOR2& pos) { m_pos = pos; }
	void SetRot(const D3DXVECTOR3& rot) { m_rot = rot; }
	void SetMove(const D3DXVECTOR3& move) { m_move = move; }
	void SetWidth(int width) { m_width = width; }
	void SetHeight(int height) { m_height = height; }
	void SetAnimePattern(int pattern) { m_animePattern = pattern; }
	void SetTexture(LPDIRECT3DTEXTURE9 tex) { m_pTexture = tex; }
	void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 vtxBuff) { m_pVtxBuff = vtxBuff; }
	void SetScrollPosX(float x) { m_scrollPosX = x; }
	void SetScrollPosY(float y) { m_scrollPosY = y; }
	void SetScrollSpeedX(float x) { m_scrollSpeedX = x; }
	void SetScrollSpeedY(float y) { m_scrollSpeedY = y; }
	void SetAnimeFrameU(int u) { m_animeFrameU = u; }
	void SetAnimeFrameV(int v) { m_animeFrameV = v; }
	void SetAnimeCounter(int c) { m_animeCounter = c; }

private:
	DRAW_TYPE m_drawtype;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR2 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_move;
	int m_width;
	int m_height;
	float m_scrollPosX;
	float m_scrollPosY;
	float m_scrollSpeedX;
	float m_scrollSpeedY;
	int m_animeFrameU;
	int m_animeFrameV;
	int m_animePattern;
	int m_animeCounter;
	LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif