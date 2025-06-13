//==================================================================
//
//パーティクル処理 [particle.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _PARTICLE_H_					//このマクロ定義がされてなかったら
#define _PARTICLE_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "d3dx9.h"
#include "object.h"

//================================================
//ライブラリのリンク
//================================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")

//================================================
//マクロ定義
//================================================

//================================================
//クラス
//================================================
class CParticle : public CObject
{
public:
    CParticle(int nPriority = 3);
    ~CParticle();

    static CParticle* Create(
        //DRAW_TYPE drawtype,
        //int width,
        //int height,
        //float scrollX,
        //float scrollY,
        //int animeFrameU,
        //int animeFrameV,
        //int animePattern,
        float posX,
        float posY,
		int ParticleCount
        //float rotZ,
        //float speed,
        //int nLife
    );
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

	static void SetPosition(float x, float y, float z);
	static void SetMove(float x, float y, float z);
	static void SetLife(int life);
	static void SetColor(float r, float g, float b, float a);
	static void SetRadius(float radius);
	static void SetParticleCount(int count);

	static D3DXVECTOR3 GetPosition(void);
	static D3DXVECTOR3 GetMove(void);
	static int GetLife(void);
	static D3DXCOLOR GetColor(void);
	static float GetRadius(void);
	static int GetParticleCount(void);

    D3DXVECTOR2 GetPos(void) override;
    int GetWidth(void) override;
    int GetHeight(void) override;


private:
    static LPDIRECT3DTEXTURE9 m_pTexture;

	static int m_ParticleCount;
    static D3DXVECTOR3 m_pos;
    static D3DXVECTOR3 m_move;
    static int m_Life;
    static float fRadius;
	static D3DXCOLOR m_col;

};

#endif