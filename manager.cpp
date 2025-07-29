//==================================================================
//
//マネージャー処理 [manager.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//インクルード
//================================================
#include "manager.h"
#include "input.h"
#include "background.h".
#include "effect.h"
#include "particle.h"
#include "objectX.h"
#include "billboard.h"
#include "3Dplayer.h"
#include "shadowS.h"

//================================================
//静的
//================================================
CRenderer* CManager::m_pRenderer = NULL;
CInputKeyboard* CManager::m_pInputKeyboard = NULL;
CPlayer* CManager::m_pPlayer = NULL;
CObject3D* CManager::m_pObject3D = NULL;
CCamera* CManager::m_pCamera = NULL;
CLight* CManager::m_pLight = NULL;
C3DPlayer* CManager::m_p3DPlayer = NULL;
CWall* CManager::m_pWall = NULL;
CRock* CManager::m_pRock = NULL;
CShadowS* CManager::m_pShadowS = NULL;
CScene* CManager::m_pScene = NULL;
CFade* CManager::m_pFade = NULL;

//================================================
//コンストラクタ
//================================================
CManager::CManager()
{
	m_pRenderer = NULL;
}

//================================================
//デストラクタ
//================================================
CManager::~CManager()
{
}

//================================================
//初期化処理
//================================================
HRESULT CManager::Init(HWND hWnd, BOOL bWindow)
{
	//レンダラーの設定
	m_pRenderer = new CRenderer;
	//初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		delete m_pRenderer;
		m_pRenderer = NULL;
		return -1;
	}

	m_pInputKeyboard = new CInputKeyboard;
	if (FAILED(m_pInputKeyboard->Init(GetModuleHandle(NULL), hWnd)))
	{
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
		return -1;
	}

	//カメラの設定
	m_pCamera = new CCamera;
	m_pCamera->Init();

	//ライトの設定
	m_pLight = new CLight;
	m_pLight->Init();

	m_pFade = new CFade;
	m_pFade->Init();


	SetMode(CScene::MODE_TITLE);

	CPlayer::Load();
	CBullet::Load();	
	CExplosion::Load();
	CEnemy::Load();
	CBackground::Load();
	CScore::Load();
	CEffect::Load();
	CRock::Load();
	CShadowS::Load();

	//CObject3D::Create();

	//m_pObject3D = CObject3D::Create();
	//m_pWall = CWall::Create();

	//// スコア生成
	//CScore::Create(
	//	CScore::SCORE_TYPE_NORMAL_01,
	//	4, 0, // 桁数と初期値
	//	D3DXVECTOR3(1200, 50,0), // 中心座標
	//	30.0f, 50.0f, 4.0f // 幅、高さ、スペース
	//);

	//CBillboard::Create();

	////CObjectX::Create();
	//m_pRock=CRock::Create(40, 10, 150);
	//m_pRock = CRock::Create(-40, 50, 150);
	//m_pRock = CRock::Create(40, 90, 150);
	//m_pRock = CRock::Create(-40, 130, 150);

	//m_pShadowS = CShadowS::Create(0, 100, 0);

	//m_p3DPlayer = C3DPlayer::Create();

	return S_OK;
}

//================================================
//終了処理
//================================================
void CManager::Uninit(void)
{
	//オブジェクトの破棄
	CObject::ReleaseAll();
	CObject2D::ReleaseAll();

	//入力デバイスの破棄
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		//レンダラーの終了処理
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}

	if (m_pScene != NULL)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = NULL;
	}


	CEffect::Unload();
	CBackground::Unload();
	CEnemy::Unload();
	CExplosion::Unload();
	CBullet::Unload();
	CPlayer::Unload();
	CScore::Unload();
	CRock::Unload();
	CShadowS::Unload();
}

//================================================
//更新処理
//================================================
void CManager::Update(void)
{
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

	//入力デバイスの更新
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	if (m_pScene != NULL)
	{
		m_pScene->Update();
	}
}

//================================================
//描画処理
//================================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();
}

//================================================
//レンダラー取得処理
//================================================
CRenderer* CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//================================================
//キーボード取得処理
//================================================
CInputKeyboard* CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//================================================
//プレイヤー取得処理
//================================================
CPlayer* CManager::GetPlayer(void)
{
	return m_pPlayer;
}

//================================================
//カメラ取得処理
//================================================
CCamera* CManager::GetCamera(void)
{
	return m_pCamera;
}

//================================================
//ライト取得処理
//================================================
CLight* CManager::GetLight(void)
{
	return m_pLight;
}

CObject3D* CManager::GetObject3D(void)
{
	return m_pObject3D;
}

C3DPlayer* CManager::Get3DPlayer(void)
{
	return m_p3DPlayer;
}

CWall* CManager::GetWall(void)
{
	return m_pWall;
}

CRock* CManager::GetRock(void)
{
	return m_pRock;
}

void CManager::SetMode(CScene::MODE mode)
{
	//シーン情報が存在する場合
	if (m_pScene != NULL)
	{
		//終了処理
		m_pScene->Uninit();

		CObject::ReleaseAll();

		delete m_pScene;
		m_pScene = NULL;
	}

	//新たなシーンを生成
	m_pScene = CScene::Create(mode);
}