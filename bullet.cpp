//==================================================================
//
//�e���� [bullet.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//�C���N���[�h
//================================================
#include "bullet.h"
#include "input.h"
#include "manager.h"
#include "explosion.h"
#include "effect.h"
#include "particle.h"

//================================================
//�ÓI�����o�ϐ�
//================================================
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

//================================================
//�R���X�g���N�^
//================================================
CBullet::CBullet(int nPriority) : CObject2D(nPriority)
{
	m_Life = 0; // �������C�t
}

//================================================
//�f�X�g���N�^
//================================================
CBullet::~CBullet()
{
}


//================================================
//����������
//================================================
HRESULT CBullet::Init(void)
{
	CObject2D::Init();
	SetType(TYPE_BULLET);

	return S_OK;
}

//================================================
//�I������
//================================================
void CBullet::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================
//�X�V����
//================================================
void CBullet::Update(void)
{
    m_Life--;

    if (m_Life<0)
    {
        // �����G�t�F�N�g
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

        //�p�[�e�B�N��
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
//�`�揈��
//================================================
void CBullet::Draw(void)
{
	CObject2D::Draw();
}

//================================================
//��������
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
    pBullet->m_Life = nLife; // �ǉ�
    pBullet->BindTexture(m_pTexture);
    pBullet->Init();
    return pBullet;
}

//================================================
//�G�Ƃ̓����蔻�菈��
//================================================
bool CBullet::CollisionEnemy(D3DXVECTOR2 pos)
{
    for (int nPriority = 0; nPriority < OBJECT_PRIORITY_MAX; nPriority++)
    {
        for (int nCntOb = 0; nCntOb < OBJECT_MAX; nCntOb++)
        {
            CObject* pObj = NULL;

            // �I�u�W�F�N�g���擾
            pObj = GetObject(nPriority,nCntOb);

            if (pObj != NULL)
            {
                CObject::OBJECT_TYPE type;

                // ��ނ��擾
                type = pObj->GetType();

                if (type == CObject::TYPE_ENEMY)
                {// ��ނ��G�������ꍇ
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
//�e�N�X�`�����[�h����
//================================================
HRESULT CBullet::Load(void)
{
    // �f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet001.png", &m_pTexture)))
    {
        return E_FAIL;
    }

    return S_OK;
}

//================================================
//�e�N�X�`���A�����[�h����
//================================================
void CBullet::Unload(void)
{
    if (m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}
