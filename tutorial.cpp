#include "tutorial.h"
#include "manager.h"
#include "background.h"
//CPlayer* CTutorial::m_pPlayer = NULL;
CWall* CTutorial::m_pWall = NULL;
CRock* CTutorial::m_pRock = NULL;
CScene* CTutorial::m_pScene = NULL;
C3DPlayer* CTutorial::m_p3DPlayer = NULL;
CBackground* CTutorial::m_pBackground = NULL;
CObject2D* CTutorial::m_pObject2D = NULL;


CTutorial::CTutorial()
{
}

CTutorial::~CTutorial()
{
}

HRESULT CTutorial::Init()
{
	//CPlayer::Load();
	CRock::Load();
	m_pWall = CWall::Create();
	CBackground::Load();



	//CObjectX::Create();
	//m_pRock = CRock::Create(40, 10, 150);
	//m_pRock = CRock::Create(-40, 50, 150);
	//m_pRock = CRock::Create(40, 90, 150);
	//m_pRock = CRock::Create(-40, 130, 150);


	//m_p3DPlayer = C3DPlayer::Create();

	m_pBackground = CBackground::Create(
		CBackground::BACKGROUND_TYPE_TUTORIAL,
		CObject2D::TYPE_NORMAL,
		1280, 720,
		0.01f, 0.0f,
		1, 1, 0,
		1280 * 0.5f, 720 * 0.5f, 0.0f,
		0.0f
	);


	CSound* pSound = CManager::GetSound();
	if (pSound != nullptr)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_BGM02);
	}

	return S_OK;
}

void CTutorial::Uninit()
{
	CRock::Unload();
	CBackground::Unload();

	m_p3DPlayer = nullptr;
	m_pWall = nullptr;
	m_pRock = nullptr;
	m_pScene = nullptr;
	//m_pPlayer = nullptr;
	m_pBackground = nullptr;

}

void CTutorial::Update()
{
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	if (pInputKeyboard->Trigger(DIK_SPACE))
	{
		//CManager::SetMode(MODE_TEMPLATE);
		// フェード取得
		CFade* pFade = CManager::GetFade();

		// 取得できたら
		if (pFade != nullptr)
		{
			// 画面遷移
			pFade->SetFade(MODE_GAME);
		}
	}

}

void CTutorial::Draw()
{
}

CTutorial* CTutorial::Create()
{
	//メモリを動的確保
	CTutorial* pTutorial = new CTutorial();

	//初期化処理
	pTutorial->Init();

	return pTutorial;
}

//CPlayer* CTutorial::GetPlayer(void)
//{
//	//return m_pPlayer;
//}

CWall* CTutorial::GetWall(void)
{
	return m_pWall;
}

CRock* CTutorial::GetRock(void)
{
	return m_pRock;
}

C3DPlayer* CTutorial::Get3DPlayer(void)
{
	return m_p3DPlayer;
}
