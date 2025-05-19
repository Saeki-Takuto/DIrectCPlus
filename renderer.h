//==================================================================
//
//レンダラー処理 [renderer.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _RENDERER_H_					//このマクロ定義がされてなかったら
#define _RENDERER_H_					//2重インクルード防止のマクロ定義

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
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//================================================
//レンダラークラス
//================================================
class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd,
				 BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	LPDIRECT3DDEVICE9 GetDevice(void);

private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
};

#endif