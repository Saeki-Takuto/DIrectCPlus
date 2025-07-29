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
#include "debugproc.h"

//================================================
//静的
//================================================
int CObject::m_nNumAll = 0;//オブジェクト総数
CObject* CObject::m_apObject[OBJECT_PRIORITY_MAX][OBJECT_MAX] = {};
CObject* CObject::m_pTop[OBJECT_PRIORITY_MAX] = {}; // オブジェクトのリストの先頭
CObject* CObject::m_pCur[OBJECT_PRIORITY_MAX] = {}; // 現在のオブジェクトのポインタ

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

//CObject::CObject(int nPriority)
//	: m_pPrev(nullptr), m_pNext(nullptr)
//{
//	// 配列管理（優先度ごとに登録）
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
//	// リスト管理
//	if (m_pTop == nullptr) {
//		m_pTop = this;
//		m_pCur = this;
//	}
//	else {
//		m_pPrev = m_pCur;
//		m_pCur->m_pNext = this;
//		m_pCur = this;
//	}
//}

CObject::CObject(int nPriority)
{
	m_type = TYPE_NONE;					//種類を初期化
	m_nPriority = nPriority;			//優先度を設定
	m_bDeath = false;					// 死亡フラグ無効化

	m_pNext = nullptr;					// 次のポインタを初期化
	m_pPrev = nullptr;					// 前のポインタを初期化

	m_pPrev = m_pCur[nPriority];		//現在の最後尾を前ポインタに設定

	if (m_pCur[nPriority])
	{

		m_pCur[nPriority]->m_pNext = this;
	}
	else
	{

		m_pTop[nPriority] = this;
	}

	m_pCur[nPriority] = this;
	m_nNumAll++;
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

CObject* CObject::GetTop(int nPriority)
{
	return nullptr;
}

CObject* CObject::GetNext(void)
{
	return nullptr;
}

void CObject::Release(void)
{
	m_bDeath = true;
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
//void CObject::ReleaseAll(void)
//{
//	for (int nCntPriority = 0; nCntPriority < OBJECT_PRIORITY_MAX; nCntPriority++)
//	{
//		for (int nCntObject = 0; nCntObject < OBJECT_MAX; nCntObject++)
//		{
//			if (m_apObject[nCntPriority][nCntObject] != NULL)
//			{
//				m_apObject[nCntPriority][nCntObject]->Uninit();
//			}
//		}
//	}
//	CCamera* pCamera = CManager::GetCamera();
//
//	pCamera->Uninit();
//
//}

void CObject::ReleaseAll(void)
{
	// 優先番号分回す
	for (int nCnt = 0; nCnt < OBJECT_PRIORITY_MAX; nCnt++)
	{
		// 先頭のアドレスを取得する
		CObject* pObj = m_pTop[nCnt];

		// 取得できたら
		while (pObj != nullptr)
		{
			// 次のオブジェクトを保存する
			CObject* pNext = pObj->m_pNext;

			// オブジェクト終了処理
			pObj->Uninit();

			// 前後を初期化
			pObj->m_pNext = nullptr;
			pObj->m_pPrev = nullptr;

			// オブジェクト自体をここで削除する
			delete pObj;

			// nullptrにする
			pObj = nullptr;

			// 次のオブジェクトに代入
			pObj = pNext;
		}

		// 先頭のポインタをnullptrにする
		m_pTop[nCnt] = nullptr;

		// 最後尾のポインタをnullptrにする
		m_pCur[nCnt] = nullptr;
	}

	// 総数をリセットする
	m_nNumAll = NULL;

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

//void CObject::UpdateAll(void)
//{
//	CObject* pObject = m_pTop;//先頭代入
//
//	while (pObject != nullptr) // リストの終端まで
//	{
//		//次のオブジェクトを保存
//		CObject* pObjectNext = pObject->m_pNext;
//
//		//更新
//		pObject->Update();
//
//		pObject = pObjectNext;//次のオブジェ代入
//	}
//
//	//各オブジェクトの死亡フラグをチェック
//	CObject* pCheck = m_pTop;
//	while (pCheck != nullptr) // リストの終端まで
//	{
//		CObject* pCheckNext = pCheck->m_pNext; // 次のオブジェクトを保存
//		if (pCheck->m_bDeath) // 死亡フラグが立っている場合
//		{
//			pCheck->Release(); // オブジェクトを解放
//		}
//		pCheck = pCheckNext; // 次のオブジェクトへ移動
//	}
//
//
//	CCamera* pCamera = CManager::GetCamera();
//
//	pCamera->Update();
//}

void CObject::UpdateAll(void)
{
	// 優先番号分回す
	for (int nPrio = 0; nPrio < OBJECT_PRIORITY_MAX; nPrio++)
	{
		// 先頭アドレス,優先番号を取得
		CObject* pObject = m_pTop[nPrio];

		// 取得できたら
		while (pObject != nullptr)
		{
			// 次のオブジェクト保存
			CObject* pObjeNext = pObject->m_pNext;

			// オブジェクト更新
			pObject->Update();

			// 次のオブジェクトを代入
			pObject = pObjeNext;
		}
	}

	// 死亡しているかフラグで判別し対象のオブジェクトを削除
	for (int nCnt = 0; nCnt < OBJECT_PRIORITY_MAX; nCnt++)
	{
		// 先頭アドレス,優先番号を取得
		CObject* pObject = m_pTop[nCnt];

		// 取得できたら
		while (pObject != nullptr)
		{
			// 次のオブジェクト保存
			CObject* pObjeNext = pObject->m_pNext;

			// フラグが有効の物を破棄する
			if (pObject->m_bDeath)
			{
				// 前のオブジェクトが存在する場合は、自分の次を前のオブジェクトに接続
				if (pObject->m_pPrev != nullptr)
				{
					pObject->m_pPrev->m_pNext = pObject->m_pNext;
				}
				else
				{
					// 自分がリストの先頭なら、トップを次のオブジェクトに更新
					m_pTop[nCnt] = pObject->m_pNext;
				}

				// 次のオブジェクトが存在する場合は、自分の前を次のオブジェクトに接続
				if (pObject->m_pNext != nullptr)
				{
					pObject->m_pNext->m_pPrev = pObject->m_pPrev;
				}
				else
				{
					// 自分がリストの最後尾なら、最後尾を前のオブジェクトに更新
					m_pCur[nCnt] = pObject->m_pPrev;
				}

				// 前後を初期化
				pObject->m_pNext = nullptr;
				pObject->m_pPrev = nullptr;

				// 総数減算
				m_nNumAll--;

				// オブジェクト自身破棄
				delete pObject;
			}

			// 次のオブジェクトを代入
			pObject = pObjeNext;
		}
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

//void CObject::DrawAll(void)
//{
//	CObject* pObject = m_pTop;//先頭代入
//
//	while (pObject != nullptr) // リストの終端まで
//	{
//		//次のオブジェクトを保存
//		CObject* pObjectNext = pObject->m_pNext;
//
//		//更新
//		pObject->Draw();
//
//		pObject = pObjectNext;//次のオブジェ代入
//	}
//
//	CCamera* pCamera = CManager::GetCamera();
//
//	pCamera->SetCamera();
//}

void CObject::DrawAll(void)
{
	// カメラの取得
	CCamera* pCamera = CManager::GetCamera();

	// カメラのセット
	pCamera->SetCamera();

	// 優先番号分回す
	for (int nPrio = 0; nPrio < OBJECT_PRIORITY_MAX; nPrio++)
	{
		// 先頭アドレス,優先番号を取得
		CObject* pObject = m_pTop[nPrio];

		// 取得できたら
		while (pObject != nullptr)
		{
			// 次のオブジェクト保存
			CObject* pObjeNext = pObject->m_pNext;

			// オブジェクト描画
			pObject->Draw();

			// 次のオブジェクトを代入
			pObject = pObjeNext;
		}
	}

	////// デバッグフォント
	////CDebugProc::Print("現在のオブジェクト数 : %d", m_nNumAll);
	////CDebugProc::Draw(0, 120);
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


