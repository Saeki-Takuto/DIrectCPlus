#include "title.h"
#include "manager.h"
#include "background.h"
CPlayer* CTitle::m_pPlayer = NULL;
CWall* CTitle::m_pWall = NULL;
CRock* CTitle::m_pRock = NULL;
CScene* CTitle::m_pScene = NULL;
C3DPlayer* CTitle::m_p3DPlayer = NULL;


CTitle::CTitle()
{
}

CTitle::~CTitle()
{
}

HRESULT CTitle::Init()
{
	CPlayer::Load();
	CRock::Load();
	CBackground::Load();
	m_pWall = CWall::Create();


	//CObjectX::Create();
	//m_pRock = CRock::Create(40, 10, 150);
	//m_pRock = CRock::Create(-40, 50, 150);
	//m_pRock = CRock::Create(40, 90, 150);
	//m_pRock = CRock::Create(-40, 130, 150);


	//m_p3DPlayer = C3DPlayer::Create();

	CBackground::Create(
	CBackground::BACKGROUND_TYPE_CLOUD,
	CObject2D::TYPE_SCROLL,
	1280, 720,
	0.01f, 0.0f,
	1, 1, 0,
	1280 * 0.5f, 720 * 0.5f,0.0f,
	0.0f
);

	return S_OK;
}

void CTitle::Uninit()
{
	CPlayer::Unload();
	CRock::Unload();
	CBackground::Unload();
}

void CTitle::Update()
{
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	if (pInputKeyboard->Trigger(DIK_SPACE))
	{
		//CManager::SetMode(MODE_TITLE);
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

void CTitle::Draw()
{
}

CTitle* CTitle::Create()
{
	//メモリを動的確保
	CTitle* pTitle = new CTitle();

	//初期化処理
	pTitle->Init();

	return pTitle;
}

CPlayer* CTitle::GetPlayer(void)
{
	return m_pPlayer;
}

CWall* CTitle::GetWall(void)
{
	return m_pWall;
}

CRock* CTitle::GetRock(void)
{
	return m_pRock;
}

C3DPlayer* CTitle::Get3DPlayer(void)
{
	return m_p3DPlayer;
}
