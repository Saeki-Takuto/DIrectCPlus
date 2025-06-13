//==================================================================
//
//背景処理 [background.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _BACKGROUND_H_					//このマクロ定義がされてなかったら
#define _BACKGROUND_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "object2D.h"

//================================================
//マクロ定義
//================================================
#define BACKGROUND_PRIORITY (1)		//背景の優先度

//================================================
//クラス
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