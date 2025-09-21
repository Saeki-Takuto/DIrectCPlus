#include "TemplateScene.h"
#include "manager.h"
#include "background.h"
//CPlayer* CTemplateScene::m_pPlayer = NULL;
CWall* CTemplateScene::m_pWall = NULL;
CRock* CTemplateScene::m_pRock = NULL;
CScene* CTemplateScene::m_pScene = NULL;
C3DPlayer* CTemplateScene::m_p3DPlayer = NULL;
CBackground* CTemplateScene::m_pBackground = NULL;
CObject2D* CTemplateScene::m_pObject2D = NULL;


CTemplateScene::CTemplateScene()
{
}

CTemplateScene::~CTemplateScene()
{
}

HRESULT CTemplateScene::Init()
{
	//CPlayer::Load();
	//CRock::Load();
	m_pWall = CWall::Create();
	CBackground::Load();



	//CObjectX::Create();
	//m_pRock = CRock::Create(40, 10, 150);
	//m_pRock = CRock::Create(-40, 50, 150);
	//m_pRock = CRock::Create(40, 90, 150);
	//m_pRock = CRock::Create(-40, 130, 150);


	m_p3DPlayer = C3DPlayer::Create();

	m_pBackground=CBackground::Create(
	CBackground::BACKGROUND_TYPE_TITLE,
	CObject2D::TYPE_SCROLL,
	1280, 300,
	0.01f, 0.0f,
	1, 1, 0,
	1280 * 0.5f, 720 * 0.5f,0.0f,
	0.0f
);

	//CSound* pSound = CManager::GetSound();
	//if (pSound != nullptr)
	//{
	//	pSound->PlaySound(CSound::SOUND_LABEL_BGM01);
	//}

	return S_OK;
}

void CTemplateScene::Uninit()
{
	CBackground::Unload();
	m_p3DPlayer = nullptr;
	m_pWall = nullptr;
	//m_pRock = nullptr;
	//m_pScene = nullptr;
	//m_pPlayer = nullptr;
	m_pBackground = nullptr;

}

void CTemplateScene::Update()
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
			pFade->SetFade(MODE_TEMPLATE);
		}
	}

}

void CTemplateScene::Draw()
{
}

CTemplateScene* CTemplateScene::Create()
{
	//メモリを動的確保
	CTemplateScene* pTitle = new CTemplateScene();

	//初期化処理
	pTitle->Init();

	return pTitle;
}

//CPlayer* CTemplateScene::GetPlayer(void)
//{
//	return m_pPlayer;
//}

CWall* CTemplateScene::GetWall(void)
{
	return m_pWall;
}

CRock* CTemplateScene::GetRock(void)
{
	return m_pRock;
}

C3DPlayer* CTemplateScene::Get3DPlayer(void)
{
	return m_p3DPlayer;
}
