//==================================================================
//
//�������� [explosion.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//�C���N���[�h
//================================================
#include "explosion.h"
#include "input.h"
#include "manager.h"

//================================================
//�ÓI�����o�ϐ�
//================================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture[EXPLOSION_TYPE_MAX] = {};

//================================================
//�R���X�g���N�^
//================================================
CExplosion::CExplosion(int nPriority) : CObject2D(nPriority)
{
}

//================================================
//�f�X�g���N�^
//================================================
CExplosion::~CExplosion()
{
}

//================================================
//����������
//================================================
HRESULT CExplosion::Init(void)
{
    CObject2D::Init();
    SetType(CObject2D::TYPE_EXPLOSION);

    return S_OK;
}

//================================================
//�I������
//================================================
void CExplosion::Uninit(void)
{
    CObject2D::Uninit();
}

//================================================
//�X�V����
//================================================
void CExplosion::Update(void)
{
    // �A�j���[�V�����i�s
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
//�`�揈��
//================================================
void CExplosion::Draw(void)
{
    CObject2D::Draw();
}

//================================================
//��������
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
//�e�N�X�`�����[�h����
//================================================
HRESULT CExplosion::Load(void)
{
    // �f�o�C�X�̎擾
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
//�e�N�X�`���A�����[�h����
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
