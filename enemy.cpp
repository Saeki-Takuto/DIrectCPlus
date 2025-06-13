//==================================================================
//
//敵処理 [enemy.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//インクルード
//================================================
#include "enemy.h"
#include "input.h"
#include "manager.h"
#include "bullet.h"

//================================================
//静的メンバ変数
//================================================
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[ENEMY_TYPE_MAX] = {};

//================================================
//コンストラクタ
//================================================
CEnemy::CEnemy(int nPriority) : CObject2D(nPriority)
{
}


//================================================
//デストラクタ
//================================================
CEnemy::~CEnemy()
{
}

//================================================
//初期化処理
//================================================
HRESULT CEnemy::Init(void)
{
	CObject2D::Init();
	SetType(TYPE_ENEMY);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CEnemy::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================
//更新処理
//================================================
void CEnemy::Update(void)
{
	CObject2D::Update();
}

//================================================
//描画処理
//================================================
void CEnemy::Draw(void)
{
	CObject2D::Draw();
}

//================================================
//生成処理
//================================================
CEnemy* CEnemy::Create(ENEMY_TYPE enemytype, DRAW_TYPE drawtype, int width, int height, float scrollX, float scrollY, int animeFrameU, int animeFrameV, int animePattern, float posX, float posY, float rotZ)
{
	CEnemy* pEnemy = new CEnemy(ENEMY_PRIORITY);
	pEnemy->SetEnemyType(enemytype);
	pEnemy->SetDrawType(drawtype);
	pEnemy->SetWidth(width);
	pEnemy->SetHeight(height);
	pEnemy->SetAnimeFrameU(animeFrameU);
	pEnemy->SetAnimeFrameV(animeFrameV);
	pEnemy->SetAnimePattern(animePattern);
	pEnemy->SetPos(D3DXVECTOR2(posX, posY));
	D3DXVECTOR3 rot = pEnemy->GetRot();
	rot.z = rotZ;
	pEnemy->SetRot(rot);
	pEnemy->Init();
	pEnemy->BindTexture(m_pTexture[enemytype]);
	return pEnemy;
}

//================================================
//テクスチャロード処理
//================================================
HRESULT CEnemy::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy000.jpg", &m_pTexture[ENEMY_TYPE_NORMAL_01])))
	{
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/virus.png", &m_pTexture[ENEMY_TYPE_NORMAL_02])))
	{
		return E_FAIL;
	}


	return S_OK;
}

//================================================
//テクスチャアンロード処理
//================================================
void CEnemy::Unload(void)
{
	for (int nCnt = 0; nCnt < ENEMY_TYPE_MAX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

