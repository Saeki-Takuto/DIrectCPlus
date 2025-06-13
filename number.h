//==================================================================
//
//数字処理 [number.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _NUMBER_H_					//このマクロ定義がされてなかったら
#define _NUMBER_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "object.h"
#include <string>

//================================================
//マクロ定義
//================================================
#define MAX_DIGIT (8)
#define NUMBER_PRIORITY (7)

//================================================
//クラス
//================================================
class CNumber :public CObject
{
public:
	CNumber(int nPriority = 3);
	~CNumber();

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
		TYPE_NONE = 0,
		TYPE_NORMAL,
		TYPE_ANIME,
		TYPE_SCROLL,
		TYPE_MAX
	}DRAW_TYPE;

	void Create(
		int digit,
		int value,
		const D3DXVECTOR2& center,
		LPDIRECT3DTEXTURE9 tex,
		float width,      // 桁の幅
		float height,     // 桁の高さ
		float spacing     // 桁の間隔
	);

	D3DXVECTOR2 GetPos(void) const { return m_pos; }
	int GetWidth(void) override { return m_width; }
	int GetHeight(void) override { return m_height; }
	D3DXVECTOR2 GetPos(void) override { return m_pos; }
	int GetSpacing(void) const { return m_spacing; }
	int GetDigit(void) const { return m_digit; }
	int GetValue(void) const { return m_value; }
	LPDIRECT3DTEXTURE9 GetTexture() const { return m_pTexture; }
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff() const { return m_pVtxBuff; }

	void SetPos(const D3DXVECTOR2& pos) { m_pos = pos; }
	void SetWidth(int width) { m_width = width; }
	void SetHeight(int height) { m_height = height; }
	void SetSpacing(int spacing) { m_spacing = spacing; }
	void SetDigit(int digit) { m_digit = digit; }
	void SetValue(int value) { m_value = value; }
	void SetTexture(LPDIRECT3DTEXTURE9 tex) { m_pTexture = tex; }
	void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 vtxBuff) { m_pVtxBuff = vtxBuff; }
	void AddValue(int value) { SetValue(GetValue() + value); }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR2 m_pos;
	int m_width;
	int m_height;
	int m_spacing;
	int m_digit;
	int m_value;
	LPDIRECT3DTEXTURE9 m_pTexture;

};

#endif