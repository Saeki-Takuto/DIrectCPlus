//==================================================================
//
//弾処理 [bullet.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//インクルード
//================================================
#include "bullet.h"
#include "input.h"
#include "manager.h"
#include "explosion.h"
#include "effect.h"
#include "particle.h"

//================================================
//静的メンバ変数
//================================================
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

//================================================
//コンストラクタ
//================================================
CBullet::CBullet(int nPriority) : CObject2D(nPriority)
{
	m_Life = 0; // 初期ライフ
}

//================================================
//デストラクタ
//================================================
CBullet::~CBullet()
{
}


//================================================
//初期化処理
//================================================
HRESULT CBullet::Init(void)
{
	CObject2D::Init();
	SetType(TYPE_BULLET);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CBullet::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================
//更新処理
//================================================
void CBullet::Update(void)
{
    m_Life--;

    if (m_Life<0)
    {
        // 爆発エフェクト
        D3DXVECTOR2 pos = GetPos();
        //CExplosion* pExplosion = CExplosion::Create(
        //    CExplosion::EXPLOSION_TYPE_NORMAL_01,
        //    TYPE_NORMAL,
        //    100, 100,
        //    0.0f, 0.0f,
        //    8, 1, 0,
        //    pos.x, pos.y,
        //    0.0f
        //);

        //パーティクル
        CParticle* pParticle = CParticle::Create(
            pos.x, pos.y, 10
        );
        Uninit();
        return;
    }

    D3DXVECTOR2 pos = GetPos();
    D3DXVECTOR3 move = GetMove();



    CEffect::Create(
        CObject2D::TYPE_NORMAL,
        30,         
        30,         
        0, 0,                
        0, 0,               
        0,                  
        pos.x, pos.y, 
        0.0f,           
        0.0f,                  
        10            
    );


    if (CollisionEnemy(pos) == true)
    {
        return;
    }

    pos.x += move.x;
    pos.y += move.y;
    SetPos(pos);

    CObject2D::Update();
}

//================================================
//描画処理
//================================================
void CBullet::Draw(void)
{
	CObject2D::Draw();
}

//================================================
//生成処理
//================================================
CBullet* CBullet::Create(
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
    float rotZ,
    float speed,
    int nLife
)
{
    CBullet* pBullet = new CBullet(BULLET_PRIORITY);
    pBullet->SetDrawType(drawtype);
    pBullet->SetWidth(width);
    pBullet->SetHeight(height);
    pBullet->SetAnimeFrameU(animeFrameU);
    pBullet->SetAnimeFrameV(animeFrameV);
    pBullet->SetAnimePattern(animePattern);
    pBullet->SetPos(D3DXVECTOR2(posX, posY));
    D3DXVECTOR3 rot = pBullet->GetRot();
    rot.z = rotZ;
    pBullet->SetRot(rot);
    D3DXVECTOR3 move(
        sinf(rotZ) * speed,
        -cosf(rotZ) * speed,
        0.0f
    );
    pBullet->SetMove(move);
    pBullet->m_Life = nLife; // 追加
    pBullet->BindTexture(m_pTexture);
    pBullet->Init();
    return pBullet;
}

//================================================
//敵との当たり判定処理
//================================================
bool CBullet::CollisionEnemy(D3DXVECTOR2 pos)
{
    for (int nPriority = 0; nPriority < OBJECT_PRIORITY_MAX; nPriority++)
    {
        for (int nCntOb = 0; nCntOb < OBJECT_MAX; nCntOb++)
        {
            CObject* pObj = NULL;

            // オブジェクトを取得
            pObj = GetObject(nPriority,nCntOb);

            if (pObj != NULL)
            {
                CObject::OBJECT_TYPE type;

                // 種類を取得
                type = pObj->GetType();

                if (type == CObject::TYPE_ENEMY)
                {// 種類が敵だった場合
                    D3DXVECTOR2 posEnemy = pObj->GetPos();
                    D3DXVECTOR2 posBullet = this->GetPos();
                    int fWidthObj = pObj->GetWidth();
                    int  fHeightObj = pObj->GetHeight();

                    if (posBullet.x >= posEnemy.x - fWidthObj && posBullet.x <= posEnemy.x + fWidthObj && posBullet.y >= posEnemy.y - fHeightObj && posBullet.y <= posEnemy.y + fHeightObj)
                    {
                        if (type == CObject::TYPE_ENEMY)
                        {
                            CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);
                            if (pEnemy && pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE_NORMAL_01)
                            {
                                CExplosion* pExplosion = CExplosion::Create(
                                    CExplosion::EXPLOSION_TYPE_NORMAL_01,
                                    TYPE_NORMAL,
                                    100, 100,
                                    0.0f, 0.0f,
                                    8, 1, 0,
                                    posEnemy.x, posEnemy.y,
                                    0.0f
                                );
                            }
                            else if (pEnemy && pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE_NORMAL_02)
                            {
                                CExplosion* pExplosion = CExplosion::Create(
                                    CExplosion::EXPLOSION_TYPE_NORMAL_02,
                                    TYPE_NORMAL,
                                    100, 100,
                                    0.0f, 0.0f,
                                    8, 1, 0,
                                    posEnemy.x, posEnemy.y,
                                    0.0f
                                );
                            }
                        }
                        pObj->Uninit();
                        this->Uninit();

                        return true;
                    }
                }
            }
        }
}

    return false;
}

//================================================
//テクスチャロード処理
//================================================
HRESULT CBullet::Load(void)
{
    // デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet001.png", &m_pTexture)))
    {
        return E_FAIL;
    }

    return S_OK;
}

//================================================
//テクスチャアンロード処理
//================================================
void CBullet::Unload(void)
{
    if (m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}
