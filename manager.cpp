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
#include "objectAnim.h"
#include "objectBack.h"
#include "input.h"

//================================================
//静的
//================================================
CRenderer* CManager::m_pRenderer = NULL;
CInputKeyboard* CManager::m_pInputKeyboard = NULL;

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

	//オブジェクトの初期化
	CObjectBack::Create(CObjectBack::TYPE_ONE);

	//オブジェクトの初期化
	CObject2D::Create(CObject2D::TYPE_ONE);

	//オブジェクトの初期化
	CObject2D::Create(CObject2D::TYPE_TWO);

	//オブジェクトの初期化
	CObjectAnim::Create(CObjectAnim::TYPE_ONE);

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
	CObjectAnim::ReleaseAll();
	CObjectBack::ReleaseAll();

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

CInputKeyboard* CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}
