//==================================================================
//
//�v���C���[���� [player.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _PLAYER_H_					//���̃}�N����`������ĂȂ�������
#define _PLAYER_H_					//2�d�C���N���[�h�h�~�̃}�N����`

//================================================
//�C���N���[�h
//================================================
#include "object2D.h"

//================================================
//�}�N����`
//================================================
#define PLAYER_PRIORITY (4)		//�v���C���[�̗D��x

//================================================
//�N���X
//================================================
class CPlayer :public CObject2D
{
public:
    CPlayer(int nPriority);
	~CPlayer();

    static CPlayer* Create(
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
	}Player;


private:
    static LPDIRECT3DTEXTURE9 m_pTexture;
	Player m_Player;
};

#endif