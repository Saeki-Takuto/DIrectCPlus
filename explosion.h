//==================================================================
//
//�������� [explosion.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _EXPLOSION_H_					//���̃}�N����`������ĂȂ�������
#define _EXPLOSION_H_					//2�d�C���N���[�h�h�~�̃}�N����`

//================================================
//�C���N���[�h
//================================================
#include "object2D.h"

//================================================
//�}�N����`
//================================================
#define EXPLOSION_PRIORITY (5)		//�����̗D��x

//================================================
//�N���X
//================================================
class CExplosion :public CObject2D
{
public:
    CExplosion(int nPriority);
    ~CExplosion();

    typedef enum
    {
        EXPLOSION_TYPE_NONE = 0,
        EXPLOSION_TYPE_NORMAL_01,
        EXPLOSION_TYPE_NORMAL_02,
        EXPLOSION_TYPE_MAX
    }EXPLOSION_TYPE;

    static CExplosion* Create(
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
    );
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    static HRESULT Load(void);
    static void Unload(void);

    int m_Life;

    typedef struct
    {
    }Explosion;


private:
    static LPDIRECT3DTEXTURE9 m_pTexture[EXPLOSION_TYPE_MAX];
    Explosion m_Explosion;
};

#endif