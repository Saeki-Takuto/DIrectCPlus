//==================================================================
//
//�G�t�F�N�g���� [effect.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//�C���N���[�h
//================================================
#include "effect.h"
#include "input.h"
#include "manager.h"
#include "explosion.h"

//================================================
//�ÓI�����o�ϐ�
//================================================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//================================================
//�R���X�g���N�^
//================================================
CEffect::CEffect(int nPriority) : CObject2D(nPriority)
{
}

//================================================
//�f�X�g���N�^
//================================================
CEffect::~CEffect()
{
}


//================================================
//����������
//================================================
HRESULT CEffect::Init(void)
{
    CObject2D::Init();

    SetType(TYPE_EFFECT);
        
    return S_OK;
}

//================================================
//�I������
//================================================
void CEffect::Uninit(void)
{
    CObject2D::Uninit();
}

//================================================
//�X�V����
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
//�`�揈��
//================================================
void CEffect::Draw(void)
{
    // �f�o�C�X�擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // ���u�����f�B���O�����Z�����ɐݒ�
    pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

    CObject2D::Draw();

    // ���u�����f�B���O�����ɖ߂�
    pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//================================================
//��������
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
    pEffect->m_Life = nLife; // �ǉ�
    pEffect->BindTexture(m_pTexture);
    pEffect->Init();
    return pEffect;
}

//================================================
//�e�N�X�`�����[�h����
//================================================
HRESULT CEffect::Load(void)
{
    // �f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &m_pTexture)))
    {
        return E_FAIL;
    }

    return S_OK;
}

//================================================
//�e�N�X�`���A�����[�h����
//================================================
void CEffect::Unload(void)
{
    if (m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}
