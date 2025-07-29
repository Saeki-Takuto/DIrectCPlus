//==================================================================
//
//石処理 [shadows.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _SHADOWS_H_					//このマクロ定義がされてなかったら
#define _SHADOWS_H_					//2重インクルード防止のマクロ定義

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
class CShadowS :public CObjectX
{
public:
    CShadowS();
    ~CShadowS();

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

    //static CShadowS* Create();
    static CShadowS* Create(float X, float Y, float Z);


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

    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
    D3DXVECTOR3 m_pos;
    D3DXVECTOR3 m_rot;
    D3DXVECTOR3 m_move;
    int m_width;
    int m_height;
    LPDIRECT3DTEXTURE9 m_pTexture;

};

#endif