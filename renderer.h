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
#include "debugproc.h"

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
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)//座標・法線・カラー・テクスチャ


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
	static CDebugProc* GetDebug(void) { return m_pDebug; }
	LPDIRECT3DDEVICE9 GetDevice(void);
	static int GetFPS(void) { return m_fps; }

private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	static CDebugProc* m_pDebug;
	static int m_fps;
	DWORD m_dwFrameCount;
	DWORD m_dwFPSLastTime;

};

#endif