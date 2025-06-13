//==================================================================
//
//エフェクト処理 [effect.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//インクルード
//================================================
#include "effect.h"
#include "input.h"
#include "manager.h"
#include "explosion.h"

//================================================
//静的メンバ変数
//================================================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//================================================
//コンストラクタ
//================================================
CEffect::CEffect(int nPriority) : CObject2D(nPriority)
{
}

//================================================
//デストラクタ
//================================================
CEffect::~CEffect()
{
}


//================================================
//初期化処理
//================================================
HRESULT CEffect::Init(void)
{
    CObject2D::Init();

    SetType(TYPE_EFFECT);
        
    return S_OK;
}

//================================================
//終了処理
//================================================
void CEffect::Uninit(void)
{
    CObject2D::Uninit();
}

//================================================
//更新処理
//================================================
void CEffect::Update(void)
{
    m_Life--;

    if (m_Life < 0)
    {
        Uninit();
        return;
    }

    D3DXVECTOR2 pos = GetPos();
    D3DXVECTOR3 move = GetMove();

    pos.x += move.x;
    pos.y += move.y;
    SetPos(pos);

    CObject2D::Update();
}

//================================================
//描画処理
//================================================
void CEffect::Draw(void)
{
    // デバイス取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // αブレンディングを加算合成に設定
    pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

    CObject2D::Draw();

    // αブレンディングを元に戻す
    pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//================================================
//生成処理
//================================================
CEffect* CEffect::Create(
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
    CEffect* pEffect = new CEffect(EFFECT_PRIORITY);
    pEffect->SetDrawType(drawtype);
    pEffect->SetWidth(width);
    pEffect->SetHeight(height);
    pEffect->SetAnimeFrameU(animeFrameU);
    pEffect->SetAnimeFrameV(animeFrameV);
    pEffect->SetAnimePattern(animePattern);
    pEffect->SetPos(D3DXVECTOR2(posX, posY));
    D3DXVECTOR3 rot = pEffect->GetRot();
    rot.z = rotZ;
    pEffect->SetRot(rot);
    D3DXVECTOR3 move(
        sinf(rotZ) * speed,
        -cosf(rotZ) * speed,
        0.0f
    );
    pEffect->SetMove(move);
    pEffect->m_Life = nLife; // 追加
    pEffect->BindTexture(m_pTexture);
    pEffect->Init();
    return pEffect;
}

//================================================
//テクスチャロード処理
//================================================
HRESULT CEffect::Load(void)
{
    // デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &m_pTexture)))
    {
        return E_FAIL;
    }

    return S_OK;
}

//================================================
//テクスチャアンロード処理
//================================================
void CEffect::Unload(void)
{
    if (m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}
