#include "game.h"
#include "manager.h"
#include "fade.h"
CPlayer* CGame::m_pPlayer = NULL;
CWall* CGame::m_pWall = NULL;
CRock* CGame::m_pRock = NULL;
CScene* CGame::m_pScene = NULL;
C3DPlayer* CGame::m_p3DPlayer = NULL;

//================================================
//静的メンバ変数
//================================================


CGame::CGame()
{
}

CGame::~CGame()
{
}

HRESULT CGame::Init()
{
	CPlayer::Load();
	CRock::Load();
	m_pWall = CWall::Create();


	//CObjectX::Create();
	m_pRock = CRock::Create(40, 10, 150);
	m_pRock = CRock::Create(-40, 50, 150);
	m_pRock = CRock::Create(40, 90, 150);
	m_pRock = CRock::Create(-40, 130, 150);


	m_p3DPlayer = C3DPlayer::Create();

	return S_OK;
}

void CGame::Uninit()
{
    m_p3DPlayer = nullptr;
	CPlayer::Unload();
	CRock::Unload();
}

void CGame::Update()
{
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	if (pInputKeyboard->Trigger(DIK_L))
	{
		//CManager::SetMode(MODE_TITLE);
		// フェード取得
		CFade* pFade = CManager::GetFade();

		// 取得できたら
		if (pFade != nullptr)
		{
			// 画面遷移
			pFade->SetFade(MODE_TITLE);
		}
	}
}

void CGame::Draw()
{
}

CGame* CGame::Create()
{
	//メモリを動的確保
	CGame* pGame = new CGame();

	//初期化処理
	pGame->Init();

	return pGame;
}

CPlayer* CGame::GetPlayer(void)
{
	return m_pPlayer;
}

CWall* CGame::GetWall(void)
{
	return m_pWall;
}

CRock* CGame::GetRock(void)
{
	return m_pRock;
}

C3DPlayer* CGame::Get3DPlayer(void)
{
	return m_p3DPlayer;
}
