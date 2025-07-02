//==================================================================
//
//石処理 [rock.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _ROCK_H_					//このマクロ定義がされてなかったら
#define _ROCK_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "objectX.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラス
//================================================
class CRock :public CObjectX
{
public:
    CRock();
    ~CRock();

    //static CPlayer* Create(
    //    DRAW_TYPE drawtype,
    //    int width,
    //    int height,
    //    float scrollX,
    //    float scrollY,
    //    int animeFrameU,
    //    int animeFrameV,
    //    int animePattern,
    //    float posX,
    //    float posY,
    //    float posZ,
    //    float rotZ
    //);

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    //static CRock* Create();
    static CRock* Create(float X,float Y,float Z);


    static HRESULT Load(void);
    static void Unload(void);
    float GetHeight(float posx, float posz);


private:
    static LPD3DXMESH m_pMesh;
    static LPD3DXBUFFER m_pBuffMat;
    static DWORD m_dwNumMat;

    static D3DXVECTOR3 m_vtxMin;
    static D3DXVECTOR3 m_vtxMax;
    static D3DXVECTOR3 m_size;
};

#endif