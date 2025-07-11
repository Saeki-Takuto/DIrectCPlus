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
	void ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU);
	LPDIRECT3DTEXTURE9 GetTextureMT(void);

	typedef struct
	{
		D3DXVECTOR3 pos;//頂点座標
		D3DXVECTOR3 nor;//法線ベクトル
		D3DCOLOR col;//頂点カラー
		D3DXVECTOR2 tex;//テクスチャ座標
	}VERTEX_3D;


private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	static CDebugProc* m_pDebug;
	static int m_fps;
	DWORD m_dwFrameCount;
	DWORD m_dwFPSLastTime;

	LPDIRECT3DTEXTURE9 m_pTextureMT;//レンダリングターゲット用テクスチャ
	LPDIRECT3DSURFACE9 m_pRenderMT;//テクスチャレンダリング用インタフェース

	LPDIRECT3DTEXTURE9 m_apTextureMT[2];//レンダリングターゲット用テクスチャ
	LPDIRECT3DSURFACE9 m_apRenderMT[2];//テクスチャレンダリング用インタフェース


	LPDIRECT3DSURFACE9 m_pZBuffMT;//テクスチャレンダリング用Zバッファ
	D3DVIEWPORT9 m_viewportMT;//テクスチャレンダリング用ビューポート

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMT;//フィードバック用ポリゴンの頂点バッファ



};

#endif