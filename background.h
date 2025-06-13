//==================================================================
//
//�w�i���� [background.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _BACKGROUND_H_					//���̃}�N����`������ĂȂ�������
#define _BACKGROUND_H_					//2�d�C���N���[�h�h�~�̃}�N����`

//================================================
//�C���N���[�h
//================================================
#include "object2D.h"

//================================================
//�}�N����`
//================================================
#define BACKGROUND_PRIORITY (1)		//�w�i�̗D��x

//================================================
//�N���X
//================================================
class CBackground :public CObject2D
{
public:
    CBackground(int nPriority);
    ~CBackground();

    typedef enum
    {
        BACKGROUND_TYPE_NONE = 0,
        BACKGROUND_TYPE_CLOUD,
        BACKGROUND_TYPE_BACK,
        BACKGROUND_TYPE_MAX
    }BACKGROUND_TYPE;

    static CBackground* Create(
        BACKGROUND_TYPE backgroundtype,
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


    typedef struct
    {
    }Background;


private:
    static LPDIRECT3DTEXTURE9 m_pTexture[BACKGROUND_TYPE_MAX];
    Background m_Background;
};

#endif