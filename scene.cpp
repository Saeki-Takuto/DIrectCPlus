//==================================================================
//
//シーン処理 [scene.cpp]
//Author:Takuto Saeki
//
//==================================================================
#include "scene.h"
#include "object.h"
#include "game.h"
#include "title.h"
CScene::MODE CScene::m_mode = CScene::MODE_NONE; //初期モードはNONE

CScene::CScene()
{
}

CScene::~CScene()
{
}

HRESULT CScene::Init()
{
	return S_OK;
}

void CScene::Uninit()
{
	//CObject::ReleaseAll();
}

void CScene::Update()
{
}

void CScene::Draw()
{
}

CScene* CScene::Create(MODE mode)
{
	//ローカル変数宣言
	CScene* pScene = new CScene();//シーン情報へのポインタ

	//モードの設定
	m_mode = mode;

	//モード別に動的確保
	switch (mode)
	{
	case MODE_TITLE://タイトル
		pScene = CTitle::Create();
		break;

	case MODE_GAME://ゲーム
		pScene = CGame::Create();
		break;

	case MODE_RESULT://リザルト
		//pScene = CResult::Create();
		break;

	default:
		break;
	}

	return pScene;
}
