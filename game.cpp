#include "game.h"
#include "manager.h"
#include "fade.h"
//CPlayer* CGame::m_pPlayer = NULL;
CWall* CGame::m_pWall = NULL;
CRock* CGame::m_pRock = NULL;
CScene* CGame::m_pScene = NULL;
C3DPlayer* CGame::m_p3DPlayer = NULL;
CGoal* CGame::m_pGoal = NULL;
CTime* CGame::m_pTime = NULL;
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
	CGoal::Load();
	CTime::Load();
	m_pWall = CWall::Create();


	//CObjectX::Create();
	m_pRock = CRock::Create(40, 40, 150);
	m_pRock = CRock::Create(-40, 100, 150);
	m_pRock = CRock::Create(40, 160, 150);
	m_pRock = CRock::Create(80, 220, 150);
	m_pRock = CRock::Create(20, 280, 150);
	m_pRock = CRock::Create(-10, 340, 150);
	m_pRock = CRock::Create(-80, 400, 150);
	m_pRock = CRock::Create(80, 460, 150);
	m_pRock = CRock::Create(10, 520, 150);
	m_pRock = CRock::Create(80, 580, 150);
	m_pRock = CRock::Create(-10, 640, 150);
	m_pRock = CRock::Create(-70, 700, 150);
	m_pRock = CRock::Create(-90, 760, 150);
	m_pRock = CRock::Create(0, 820, 150);
	m_pRock = CRock::Create(50, 880, 150);
	m_pRock = CRock::Create(100, 940, 150);


	m_pGoal = CGoal::Create(0, 1000, 150);
	m_pTime = CTime::Create(CTime::TIME_TYPE_NORMAL_01, 3, 0, D3DXVECTOR3(650, 50.0f, 0.0f), 30.0f, 50.0f, 4.0f);

	CSound* pSound = CManager::GetSound();
	if (pSound != nullptr)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_BGM03);
	}


	m_p3DPlayer = C3DPlayer::Create();

	return S_OK;
}
 
void CGame::Uninit()
{
	CPlayer::Unload();
	CRock::Unload();
	CGoal::Unload();
	CScore::Unload();
	CTime::Unload();

    m_p3DPlayer = nullptr;
	m_pWall = nullptr;
	m_pRock = nullptr;
	m_pScene = nullptr;
	m_pGoal = nullptr;
	m_pTime = nullptr;
	//m_pPlayer = nullptr;
}

void CGame::Update()
{
	bool goal = false;
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	for (int prio = 0; prio < OBJECT_PRIORITY_MAX; ++prio) {
		CObject* obj = CObject::GetTop(prio);
		while (obj != nullptr) {
			if (obj->GetType() == CObject::TYPE_PLAYER) {
				C3DPlayer* p3DPlayer = dynamic_cast<C3DPlayer*>(obj);
				if (p3DPlayer)
				{
					goal = p3DPlayer->GetonGoal();
				}
			}
			//else if (obj->GetType() == CObject::TYPE_TIME) {
			//	CTime* pTime = dynamic_cast<CTime*>(obj);
			//	if (pTime)
			//	{
			//		CManager::SetResultTime(pTime->GetValue());
			//	}
			//}

			obj = obj->GetNext();
		}
	}


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

	int time;


	if (goal)
	{
		for (int prio = 0; prio < OBJECT_PRIORITY_MAX; ++prio) {
			CObject* obj = CObject::GetTop(prio);
			while (obj != nullptr) {
				if (obj->GetType() == CObject::TYPE_TIME) {
					CTime* pTime = dynamic_cast<CTime*>(obj);
					if (pTime)
					{
						time = pTime->GetValue();
					}
				}

				obj = obj->GetNext();
			}
		}

		CManager::SetResultTime(time);

		CFade* pFade = CManager::GetFade();
		if (pFade != nullptr)
		{
			pFade->SetFade(MODE_RESULT);
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

//CPlayer* CGame::GetPlayer(void)
//{
//	//return m_pPlayer;
//}

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
