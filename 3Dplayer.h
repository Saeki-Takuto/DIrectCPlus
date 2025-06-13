//==================================================================
//
//3Dプレイヤー処理 [3Dplayer.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _3DPLAYER_H_					//このマクロ定義がされてなかったら
#define _3DPLAYER_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "object.h"
#include "model.h"

//================================================
//マクロ定義
//================================================
#define MAX_PARTS (20)

//================================================
//クラス
//================================================
class C3DPlayer:public CObject
{
public:
    C3DPlayer();
    ~C3DPlayer();
    static C3DPlayer* Create();

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    D3DXVECTOR2 GetPos(void) override;
    int GetWidth(void) override;
    int GetHeight(void) override;

private:
    D3DXVECTOR3 m_pos;
    D3DXVECTOR3 m_rot;
    D3DXMATRIX m_mtxWorld;
    D3DXVECTOR3 m_rotDest;
    D3DXVECTOR3 m_move;
    CModel* m_apModel[MAX_PARTS];
    int m_nNumModel;
};

#endif