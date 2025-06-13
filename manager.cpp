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
#include "background.h"
#include "effect.h"
#include "particle.h"
#include "objectX.h"
#include "billboard.h"
#include "3Dplayer.h"

//================================================
//静的
//================================================
CRenderer* CManager::m_pRenderer = NULL;
CInputKeyboard* CManager::m_pInputKeyboard = NULL;
CPlayer* CManager::m_pPlayer = NULL;
CCamera* CManager::m_pCamera = NULL;
CLight* CManager::m_pLight = NULL;

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

	//if (FAILED(m_pCamera->Init()))
	//{
	//	delete m_pCamera;
	//	m_pCamera = NULL;
	//	return -1;
	//}

	//ライトの設定
	m_pLight = new CLight;
	m_pLight->Init();
	//if (FAILED(m_pLight->Init()))
	//{
	//	delete m_pLight;
	//	m_pLight = NULL;
	//	return -1;
	//}

	CPlayer::Load();
	CBullet::Load();	
	CExplosion::Load();
	CEnemy::Load();
	CBackground::Load();
	CScore::Load();
	CEffect::Load();

	CObject3D::Create();

	//CBackground::Create(
	//	CBackground::BACKGROUND_TYPE_BACK,
	//	CObject2D::TYPE_NORMAL,
	//	1280, 720,
	//	0.0f, 0.0f,
	//	1, 1, 0,
	//	1280 * 0.5f, 720 * 0.5f,
	//	0.0f
	//);

	//CBackground::Create(
	//	CBackground::BACKGROUND_TYPE_CLOUD,
	//	CObject2D::TYPE_SCROLL,
	//	1280, 720,
	//	0.01f, 0.0f,
	//	1, 1, 0,
	//	1280 * 0.5f, 720 * 0.5f,
	//	0.0f
	//);


	//CPlayer::Create(
	//	CPlayer::TYPE_NORMAL,
	//	150, 250,
	//	0.0f, 0.0f,
	//	1, 1, 0, // アニメーション
	//	250 * 0.5f, 500 * 0.5f, // 中心座標X, Y
	//	0.0f);

	//CEnemy::Create(
	//	CEnemy::ENEMY_TYPE_NORMAL_01,
	//	CObject2D::TYPE_NORMAL,
	//	100, 100,
	//	0.0f, 0.0f,
	//	1, 1, 0,
	//	50, 50,
	//	0.0f
	//);

	//CEnemy::Create(
	//	CEnemy::ENEMY_TYPE_NORMAL_02,
	//	CObject2D::TYPE_NORMAL,
	//	100, 100,
	//	0.0f, 0.0f,
	//	1, 1, 0,
	//	200, 50,
	//	0.0f
	//);

	// スコア生成
	CScore::Create(
		CScore::SCORE_TYPE_NORMAL_01,
		4, 0, // 桁数と初期値
		D3DXVECTOR2(1200, 50), // 中心座標
		30.0f, 50.0f, 4.0f // 幅、高さ、スペース
	);

	CBillboard::Create();

	//CObjectX::Create();

	C3DPlayer::Create();

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

	CEffect::Unload();
	CBackground::Unload();
	CEnemy::Unload();
	CExplosion::Unload();
	CBullet::Unload();
	CPlayer::Unload();
	CScore::Unload();
}

//================================================
//更新処理
//================================================
void CManager::Update(void)
{
	//入力デバイスの更新
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
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