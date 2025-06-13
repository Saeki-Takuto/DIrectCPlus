//==================================================================
//
//�G�t�F�N�g���� [effect.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _EFFECT_H_					//���̃}�N����`������ĂȂ�������
#define _EFFECT_H_					//2�d�C���N���[�h�h�~�̃}�N����`

//================================================
//�C���N���[�h
//================================================
#include "object2D.h"

//================================================
//�}�N����`
//================================================
#define EFFECT_PRIORITY (1)		//�e�̗D��x

//================================================
//�N���X
//================================================
class CEffect :public CObject2D
{
public:
    CEffect(int nPriority);
    ~CEffect();

    static CEffect* Create(
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
    }Effect;


private:
    static LPDIRECT3DTEXTURE9 m_pTexture;
    Effect m_Effect;
    D3DXCOLOR m_col;
    float m_fRadius;
    float m_fLength;
    float m_fAngle;
};

#endif