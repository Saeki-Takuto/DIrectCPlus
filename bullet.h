//==================================================================
//
//弾処理 [bullet.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _BULLET_H_					//このマクロ定義がされてなかったら
#define _BULLET_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "object2D.h"

//================================================
//マクロ定義
//================================================
#define BULLET_PRIORITY (2)		//弾の優先度

//================================================
//クラス
//================================================
class CBullet :public CObject2D
{
public:
    CBullet(int nPriority);
    ~CBullet();

    static CBullet* Create(
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
    bool CollisionEnemy(D3DXVECTOR2 pos);

    static HRESULT Load(void);
    static void Unload(void);

    int m_Life;

    typedef struct
    {
    }Bullet;


private:
    static LPDIRECT3DTEXTURE9 m_pTexture;
    Bullet m_Bullet;
};

#endif