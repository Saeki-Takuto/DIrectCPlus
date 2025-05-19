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

//================================================
//静的
//================================================
int CObject::m_nNumAll = 0;//オブジェクト総数
CObject* CObject::m_apObject[10] = {};//オブジェクトのポインタ配列

//================================================
//コンストラクタ
//================================================
CObject::CObject()
{
	for (int nCntObject = 0; nCntObject < 10; nCntObject++)
	{
		if (m_apObject[nCntObject] == NULL)
		{
			m_apObject[nCntObject] = this;//自分自身の代入
			m_nID = nCntObject;//自分自身のIDを保存
			m_nNumAll++;//総数をカウントアップ
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
//全体破棄処理
//================================================
void CObject::ReleaseAll(void)
{
	for (int nCntObject = 0; nCntObject < 10; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			m_apObject[nCntObject]->Uninit();
		}
	}
}

//================================================
//全体更新処理
//================================================
void CObject::UpdateAll(void)
{
	for (int nCntObject = 0; nCntObject < 10; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			m_apObject[nCntObject]->Update();
		}
	}

}

//================================================
//全体描画処理
//================================================
void CObject::DrawAll(void)
{
	for (int nCntObject = 0; nCntObject < 10; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			m_apObject[nCntObject]->Draw();
		}
	}
}