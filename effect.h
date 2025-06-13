//==================================================================
//
//エフェクト処理 [effect.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _EFFECT_H_					//このマクロ定義がされてなかったら
#define _EFFECT_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "object2D.h"

//================================================
//マクロ定義
//================================================
#define EFFECT_PRIORITY (1)		//弾の優先度

//================================================
//クラス
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