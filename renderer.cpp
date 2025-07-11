//==================================================================
//
//レンダラー処理 [renderer.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//インクルード
//================================================
#include "renderer.h"
#include "object.h"
#include "main.h"

//================================================
//静的メンバ変数
//================================================	
CDebugProc* CRenderer::m_pDebug = nullptr;
int CRenderer::m_fps = 0;

//================================================
//コンストラクタ
//================================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
	m_dwFrameCount = 0;
	m_dwFPSLastTime = timeGetTime();
}

//================================================
//デストラクタ
//================================================
CRenderer::~CRenderer()
{
}

//================================================
//初期化処理
//================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;							//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;					//プレゼンテーションパラメータ


	//Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							//パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;						//ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						//ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;						//バックバッファの形式
	d3dpp.BackBufferCount = 1;									//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;						//デブスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					//デブスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;									//ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//インターバル

	//Direct3Dデバイスの生成(描画処理と頂点処理をハードウェアで行う)
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{//Direct3Dデバイスの生成(描画処理はハードウェア、頂点処理はCPUで行う
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{//Direct3Dデバイスの生成(描画処理と頂点処理をCPUで行う
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//レンダリングターゲット用テクスチャの生成
		m_pD3DDevice->CreateTexture(SCREEN_WIDTH,
			SCREEN_HEIGHT,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&m_apTextureMT[nCnt],
			NULL);

		//テクスチャレンダリング用インタフェースの生成
		m_apTextureMT[nCnt]->GetSurfaceLevel(0, &m_apRenderMT[nCnt]);
	}

	////レンダリングターゲット用テクスチャの生成
	//m_pD3DDevice->CreateTexture(SCREEN_WIDTH,
	//	SCREEN_HEIGHT,
	//	1,
	//	D3DUSAGE_RENDERTARGET,
	//	D3DFMT_A8R8G8B8,
	//	D3DPOOL_DEFAULT,
	//	&m_pTextureMT,
	//	NULL);

	////テクスチャレンダリング用インタフェースの生成
	//m_pTextureMT->GetSurfaceLevel(0, &m_pRenderMT);

	//テクスチャレンダリング用Zバッファの生成
	m_pD3DDevice->CreateDepthStencilSurface(
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&m_pZBuffMT,
		NULL
	);

	////現在のレンダリングターゲットを取得
	//m_pD3DDevice->GetRenderTarget(0, &pRenderDef);

	////現在のZバッファを取得(保存)
	//m_pD3DDevice->GetDepthStencilSurface(&pZBuffDef);

	//for (int nCnt = 0; nCnt < 2; nCnt++)
	//{
	//	//レンダリングターゲットを生成したテクスチャに設定
	//	m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[2]);
	//}

	////Zバッファを生成したテクスチャに設定
	//m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	//レンダリングターゲット用テクスチャのクリア
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	////レンダリングターゲットをもとに戻す
	//m_pD3DDevice->SetRenderTarget(0, pRenderDef);

	////Zバッファをもとに戻す
	//m_pD3DDevice->SetDepthStencilSurface(pZBuffDef);

	//テクスチャレンダリング用ビューポートの設定
	m_viewportMT.X = 0;
	m_viewportMT.Y = 0;
	m_viewportMT.Width = 40;
	m_viewportMT.Height = 80;
	m_viewportMT.MinZ = 0.0f;
	m_viewportMT.MaxZ = 0.0f;




	//レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pDebug->Init();

	return S_OK;
}

//================================================
//終了処理
//================================================
void CRenderer::Uninit(void)
{
	m_pDebug->Uninit();

	CObject::ReleaseAll();

	//Direct3Dデバイスの破棄
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの破棄
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//================================================
//更新処理
//================================================
void CRenderer::Update(void)
{
	CObject::UpdateAll();

	DWORD dwCurrentTime = timeGetTime();

	m_dwFrameCount++;

	if ((dwCurrentTime - m_dwFPSLastTime) >= 500) //0.5秒ごとに計測
	{
		m_fps = (m_dwFrameCount * 1000) / (dwCurrentTime - m_dwFPSLastTime);
		m_dwFPSLastTime = dwCurrentTime;
		m_dwFrameCount = 0;
	}
}

//================================================
//描画処理
//================================================
void CRenderer::Draw(void)
{
	//画面クリア(バックバッファ&Zバッファのクリア)
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合

		CObject::DrawAll();

		m_pDebug->Print("FPS:%d",m_fps);

		m_pDebug->Draw();

		//描画終了
		m_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//================================================
//デバイス取得処理
//================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}

void CRenderer::ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU)
{
	D3DXMATRIX mtxView, mtxProjection;
	float fAspect;

	//レンダリングターゲットを生成したテクスチャに設定
	m_pD3DDevice->SetRenderTarget(0, m_pRenderMT);

	//Zバッファを生成したZバッファに設定
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	//テクスチャレンダリング用のビューポートを設定
	m_pD3DDevice->SetViewport(&m_viewportMT);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&mtxView,
		&posV,
		&posR,
		&vecU);

	//ビューマトリックスの設定
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&mtxProjection);

	fAspect = (float)m_viewportMT.Width / (float)m_viewportMT.Height;

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
		D3DXToRadian(45.0f),
		fAspect,
		10.0f,
		1000.0f);

	//プロジェクションマトリックスの設定
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);



}

LPDIRECT3DTEXTURE9 CRenderer::GetTextureMT(void)
{
	return m_pTextureMT;
}