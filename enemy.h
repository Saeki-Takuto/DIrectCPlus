//==================================================================
//
//�G���� [enemy.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _ENEMY_H_					//���̃}�N����`������ĂȂ�������
#define _ENEMY_H_					//2�d�C���N���[�h�h�~�̃}�N����`

//================================================
//�C���N���[�h
//================================================
#include "object2D.h"

//================================================
//�}�N����`
//================================================
#define ENEMY_PRIORITY (3)		//�G�̗D��x

//================================================
//�N���X
//================================================
class CEnemy :public CObject2D
{
public:
    CEnemy(int nPriority);
    ~CEnemy();

    typedef enum
    {
        ENEMY_TYPE_NONE = 0,
        ENEMY_TYPE_NORMAL_01,
        ENEMY_TYPE_NORMAL_02,
        ENEMY_TYPE_MAX
    }ENEMY_TYPE;

    static CEnemy* Create(
        ENEMY_TYPE enemytype,
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

    ENEMY_TYPE GetEnemyType() const { return m_enemyType; }
    void SetEnemyType(ENEMY_TYPE type) { m_enemyType = type; }

    typedef struct
    {
    }Enemy;


private:
    static LPDIRECT3DTEXTURE9 m_pTexture[ENEMY_TYPE_MAX];
    ENEMY_TYPE m_enemyType;
    Enemy m_Enemy;
};

#endif