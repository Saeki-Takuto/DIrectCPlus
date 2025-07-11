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
CObject* CObject::m_pTop = nullptr; // オブジェクトのリストの先頭
CObject* CObject::m_pCur = nullptr; // 現在のオブジェクトのポインタ


//================================================
//コンストラクタ
//================================================
//CObject::CObject(int nPriority)
//{
//	for (int nCntObject = 0; nCntObject < OBJECT_MAX; nCntObject++)
//	{
//		if (m_apObject[nPriority][nCntObject] == NULL)
//		{
//			m_nPriority = nPriority;
//			m_apObject[m_nPriority][nCntObject] = this;
//			m_nID = nCntObject;
//			m_nNumAll++;
//			break;
//		}
//	}
//
//
//}

CObject::CObject(int nPriority)
	: m_pPrev(nullptr), m_pNext(nullptr)
{
	// 配列管理（優先度ごとに登録）
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

	// リスト管理
	if (m_pTop == nullptr) {
		m_pTop = this;
		m_pCur = this;
	}
	else {
		m_pPrev = m_pCur;
		m_pCur->m_pNext = this;
		m_pCur = this;
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
//void CObject::Release(void)
//{
//	int nIdx = this->m_nID;
//	int nPriority = this->m_nPriority;
//
//	if (m_apObject[nPriority][nIdx] != NULL)
//	{
//		delete m_apObject[nPriority][nIdx];
//		m_apObject[nPriority][nIdx] = NULL;
//		m_nNumAll--;
//	}
//}

//void CObject::Release(void)
//{
//	int nIdx = this->m_nID;
//	int nPriority = this->m_nPriority;
//
//	if (m_pPrev) 
//	{ 
//		m_pPrev->m_pNext = m_pNext; 
//	}
//
//	if (m_pNext) 
//	{
//		m_pNext->m_pPrev = m_pPrev; 
//	}
//
//
//	if (m_pTop == this) 
//	{ 
//		m_pTop = m_pNext; 
//	}
//
//	if (m_pCur == this)
//	{
//		m_pCur = m_pPrev;
//	}
//
//	// --- 配列から外す ---
//	if (m_apObject[nPriority][nIdx] != NULL)
//	{
//		// deleteは呼び出し元で行う場合はここでは不要
//		m_apObject[nPriority][nIdx] = NULL;
//		m_nNumAll--;
//	}
//
//	// ポインタを切る
//	m_pPrev = nullptr;
//	m_pNext = nullptr;
//}

void CObject::Release(void)
{
	int nIdx = this->m_nID;
	int nPriority = this->m_nPriority;

	if (m_pPrev)
	{
		m_pPrev->m_pNext = m_pNext;
	}

	if (m_pNext)
	{
		m_pNext->m_pPrev = m_pPrev;
	}


	if (m_pTop == this)
	{
		m_pTop = m_pNext;
	}

	if (m_pCur == this)
	{
		m_pCur = m_pPrev;
	}

	// --- 配列から外す ---
	if (m_apObject[nPriority][nIdx] != NULL)
	{
		// deleteは呼び出し元で行う場合はここでは不要
		m_apObject[nPriority][nIdx]->m_bDeath=false;
		//m_nNumAll--;
	}

	//// ポインタを切る
	//m_pPrev = nullptr;
	//m_pNext = nullptr;
}


// デストラクタでも念のためリストから外す
//CObject::~CObject()
//{
//	// ここでRelease()を呼ぶと二重解放になる場合があるので、
//	// リストから外す処理だけを記述
//	if (m_pPrev) m_pPrev->m_pNext = m_pNext;
//	if (m_pNext) m_pNext->m_pPrev = m_pPrev;
//	if (m_pTop == this) m_pTop = m_pNext;
//	if (m_pCur == this) m_pCur = m_pPrev;
//	m_pPrev = nullptr;
//	m_pNext = nullptr;
//}

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
//void CObject::UpdateAll(void)
//{
//	for (int nCntPriority = 0; nCntPriority < OBJECT_PRIORITY_MAX; nCntPriority++)
//	{
//		for (int nCntObject = 0; nCntObject < OBJECT_MAX; nCntObject++)
//		{
//			if (m_apObject[nCntPriority][nCntObject] != NULL)
//			{
//				m_apObject[nCntPriority][nCntObject]->Update();
//			}
//		}
//	}
//	CCamera* pCamera = CManager::GetCamera();
//
//	pCamera->Update();
//
//}

void CObject::UpdateAll(void)
{
	CObject* pObject = m_pTop;//先頭代入

	while (pObject != nullptr) // リストの終端まで
	{
		//次のオブジェクトを保存
		CObject* pObjectNext = pObject->m_pNext;

		//更新
		pObject->Update();

		pObject = pObjectNext;//次のオブジェ代入
	}

	//各オブジェクトの死亡フラグをチェック
	CObject* pCheck = m_pTop;
	while (pCheck != nullptr) // リストの終端まで
	{
		CObject* pCheckNext = pCheck->m_pNext; // 次のオブジェクトを保存
		if (pCheck->m_bDeath) // 死亡フラグが立っている場合
		{
			pCheck->Release(); // オブジェクトを解放
		}
		pCheck = pCheckNext; // 次のオブジェクトへ移動
	}


	CCamera* pCamera = CManager::GetCamera();

	pCamera->Update();
}


//================================================
//全体描画処理
//================================================
//void CObject::DrawAll(void)
//{
//
//	for (int nCntPriority = 0; nCntPriority < OBJECT_PRIORITY_MAX; nCntPriority++)
//	{
//		for (int nCntObject = 0; nCntObject < OBJECT_MAX; nCntObject++)
//		{
//			if (m_apObject[nCntPriority][nCntObject] != NULL)
//			{
//				m_apObject[nCntPriority][nCntObject]->Draw();
//			}
//		}
//	}
//
//	CCamera* pCamera = CManager::GetCamera();
//
//	pCamera->SetCamera();
//
//}

void CObject::DrawAll(void)
{
	CObject* pObject = m_pTop;//先頭代入

	while (pObject != nullptr) // リストの終端まで
	{
		//次のオブジェクトを保存
		CObject* pObjectNext = pObject->m_pNext;

		//更新
		pObject->Draw();

		pObject = pObjectNext;//次のオブジェ代入
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


