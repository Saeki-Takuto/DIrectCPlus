//==================================================================
//
//爆発処理 [explosion.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//インクルード
//================================================
#include "explosion.h"
#include "input.h"
#include "manager.h"

//================================================
//静的メンバ変数
//================================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture[EXPLOSION_TYPE_MAX] = {};

//================================================
//コンストラクタ
//================================================
CExplosion::CExplosion(int nPriority) : CObject2D(nPriority)
{
}

//================================================
//デストラクタ
//================================================
CExplosion::~CExplosion()
{
}

//================================================
//初期化処理
//================================================
HRESULT CExplosion::Init(void)
{
    CObject2D::Init();
    SetType(CObject2D::TYPE_EXPLOSION);

    return S_OK;
}

//================================================
//終了処理
//================================================
void CExplosion::Uninit(void)
{
    CObject2D::Uninit();
}

//================================================
//更新処理
//================================================
void CExplosion::Update(void)
{
    // アニメーション進行
    SetAnimeCounter(GetAnimeCounter() + 1);
    if (GetAnimeFrameU() > 1 || GetAnimeFrameV() > 1) {
        if (GetAnimeCounter() % 5 == 0) {
            SetAnimePattern(GetAnimePattern() + 1);
            if (GetAnimePattern() >= GetAnimeFrameU() * GetAnimeFrameV()) {
                Uninit();
                return;
            }
        }
    }

    CObject2D::Update();
}

//================================================
//描画処理
//================================================
void CExplosion::Draw(void)
{
    CObject2D::Draw();
}

//================================================
//生成処理
//================================================
CExplosion* CExplosion::Create(
    EXPLOSION_TYPE explosiontype,
    DRAW_TYPE drawtype,
    int width,
    int height,
    float scrollX,
    float scrollY,
    int animeFrameU,
    int animeFrameV,
    int animePattern,
    float posX,
    float posY,
    float rotZ
)
{
    CExplosion* pExplosion = new CExplosion(EXPLOSION_PRIORITY);
    pExplosion->SetDrawType(drawtype);
    pExplosion->SetWidth(width);
    pExplosion->SetHeight(height);
    pExplosion->SetAnimeFrameU(animeFrameU);
    pExplosion->SetAnimeFrameV(animeFrameV);
    pExplosion->SetAnimePattern(animePattern);
    pExplosion->SetPos(D3DXVECTOR2(posX, posY));
    D3DXVECTOR3 rot = pExplosion->GetRot();
    rot.z = rotZ;
    pExplosion->SetRot(rot);
    pExplosion->BindTexture(m_pTexture[explosiontype]);
    pExplosion->Init();
    return pExplosion;
}

//================================================
//テクスチャロード処理
//================================================
HRESULT CExplosion::Load(void)
{
    // デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/explosion000.png", &m_pTexture[EXPLOSION_TYPE_NORMAL_01])))
    {
        return E_FAIL;
    }

    if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/explosion001.png", &m_pTexture[EXPLOSION_TYPE_NORMAL_02])))
    {
        return E_FAIL;
    }

    return S_OK;
}

//================================================
//テクスチャアンロード処理
//================================================
void CExplosion::Unload(void)
{
        for (int nCnt = 0; nCnt < EXPLOSION_TYPE_MAX; nCnt++)
        {
            if (m_pTexture[nCnt] != NULL)
            {
                m_pTexture[nCnt]->Release();
                m_pTexture[nCnt] = NULL;
            }
        }
}
