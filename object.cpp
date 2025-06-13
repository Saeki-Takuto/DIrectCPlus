//==================================================================
//
//オブジェクト処理 [object.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//インクルード
//================================================
#include "object.h"
#include "camera.h"
#include "manager.h"

//================================================
//静的
//================================================
int CObject::m_nNumAll = 0;//オブジェクト総数
CObject* CObject::m_apObject[OBJECT_PRIORITY_MAX][OBJECT_MAX] = {};

//================================================
//コンストラクタ
//================================================
CObject::CObject(int nPriority)
{
	for (int nCntObject = 0; nCntObject < OBJECT_MAX; nCntObject++)
	{
		if (m_apObject[nPriority][nCntObject] == NULL)
		{
			m_nPriority = nPriority;
			m_apObject[m_nPriority][nCntObject] = this;
			m_nID = nCntObject;
			m_nNumAll++;
			break;
		}
	}
}

//================================================
//デストラクタ
//================================================
CObject::~CObject()
{
}

//================================================
//破棄処理
//================================================
void CObject::Release(void)
{
	int nIdx = this->m_nID;
	int nPriority = this->m_nPriority;

	if (m_apObject[nPriority][nIdx] != NULL)
	{
		delete m_apObject[nPriority][nIdx];
		m_apObject[nPriority][nIdx] = NULL;
		m_nNumAll--;
	}
}

//================================================
//全体破棄処理
//================================================
void CObject::ReleaseAll(void)
{

	for (int nCntPriority = 0; nCntPriority < OBJECT_PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < OBJECT_MAX; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				m_apObject[nCntPriority][nCntObject]->Uninit();
			}
		}
	}
	CCamera* pCamera = CManager::GetCamera();

	pCamera->Uninit();

}

//================================================
//全体更新処理
//================================================
void CObject::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < OBJECT_PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < OBJECT_MAX; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				m_apObject[nCntPriority][nCntObject]->Update();
			}
		}
	}
	CCamera* pCamera = CManager::GetCamera();

	pCamera->Update();

}

//================================================
//全体描画処理
//================================================
void CObject::DrawAll(void)
{

	for (int nCntPriority = 0; nCntPriority < OBJECT_PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < OBJECT_MAX; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				m_apObject[nCntPriority][nCntObject]->Draw();
			}
		}
	}

	CCamera* pCamera = CManager::GetCamera();

	pCamera->SetCamera();

}

//================================================
//タイプセット処理
//================================================
void CObject::SetType(OBJECT_TYPE type)
{
	m_type = type;
}

//================================================
//タイプ取得処理
//================================================
CObject::OBJECT_TYPE CObject::GetType(void)
{
	return m_type;
}


