	#include "result.h"
#include "manager.h"
#include "background.h"
//CPlayer* CResult::m_pPlayer = NULL;
CWall* CResult::m_pWall = NULL;
CRock* CResult::m_pRock = NULL;
CScene* CResult::m_pScene = NULL;
C3DPlayer* CResult::m_p3DPlayer = NULL;
CBackground* CResult::m_pBackground = NULL;
CObject2D* CResult::m_pObject2D = NULL;
CScore* CResult::m_pScore = NULL;


CResult::CResult()
{
}

CResult::~CResult()
{
}

HRESULT CResult::Init()
{
	//CPlayer::Load();
	CRock::Load();
	m_pWall = CWall::Create();
	CBackground::Load();
	CScore::Load();

	int elapsedTime = CManager::GetResultTime();
	m_pScore = CScore::Create(
		CScore::SCORE_TYPE_NORMAL_01,
		3, // 桁数
		elapsedTime,
		D3DXVECTOR3(750, 590, 0), // 表示位置
		75.0f, 90.0f, 4.0f
	);

	//CObjectX::Create();
	//m_pRock = CRock::Create(40, 10, 150);
	//m_pRock = CRock::Create(-40, 50, 150);
	//m_pRock = CRock::Create(40, 90, 150);
	//m_pRock = CRock::Create(-40, 130, 150);


	//m_p3DPlayer = C3DPlayer::Create();

	m_pBackground = CBackground::Create(
		CBackground::BACKGROUND_TYPE_RESULT,
		CObject2D::TYPE_NORMAL,
		1280, 720,
		0.01f, 0.0f,
		1, 1, 0,
		1280 * 0.5f, 720 * 0.5f, 0.0f,
		0.0f
	);

	m_pBackground=CBackground::Create(
	CBackground::BACKGROUND_TYPE_GOAL,
	CObject2D::TYPE_SCROLL,
	1280, 400,
	0.01f, 0.0f,
	1, 1, 0,
	1280 * 0.5f, 600 * 0.5f,0.0f,
	0.0f
);

	CSound* pSound = CManager::GetSound();
	if (pSound != nullptr)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_BGM04);
	}

	return S_OK;
}

void CResult::Uninit()
{
	CRock::Unload();
	CBackground::Unload();
	CScore::Unload();

	m_p3DPlayer = nullptr;
	m_pScore = nullptr;
	m_pWall = nullptr;
	m_pRock = nullptr;
	m_pScene = nullptr;
	//m_pPlayer = nullptr;
	m_pBackground = nullptr;

}

void CResult::Update()
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
			pFade->SetFade(MODE_TITLE);
		}
	}

}

void CResult::Draw()
{
}

CResult* CResult::Create()
{
	//メモリを動的確保
	CResult* pResult = new CResult();

	//初期化処理
	pResult->Init();

	return pResult;
}

//CPlayer* CResult::GetPlayer(void)
//{
//	//return m_pPlayer;
//}

CWall* CResult::GetWall(void)
{
	return m_pWall;
}

CRock* CResult::GetRock(void)
{
	return m_pRock;
}

C3DPlayer* CResult::Get3DPlayer(void)
{
	return m_p3DPlayer;
}
