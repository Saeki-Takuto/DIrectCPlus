//==================================================================
//
//石処理 [goal.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _GOAL_H_					//このマクロ定義がされてなかったら
#define _GOAL_H_					//2重インクルード防止のマクロ定義

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
class CGoal :public CObjectX
{
public:
    CGoal();
    ~CGoal();

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

    //static CGoal* Create();
    static CGoal* Create(float X,float Y,float Z);


    static HRESULT Load(void);
    static void Unload(void);
    float GetHeight(float posx, float posz);
	static D3DXVECTOR3 GetSize(void) { return m_size; }

	D3DXVECTOR3 Colision(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 size);
    bool IsOnTop(const D3DXVECTOR3& playerPos, const D3DXVECTOR3& playerSize);

private:
    static LPD3DXMESH m_pMesh;
    static LPD3DXBUFFER m_pBuffMat;
    static DWORD m_dwNumMat;

    static D3DXVECTOR3 m_vtxMin;
    static D3DXVECTOR3 m_vtxMax;
    static D3DXVECTOR3 m_size;
};

#endif