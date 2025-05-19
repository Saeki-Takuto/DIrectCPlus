//==================================================================
//
//�I�u�W�F�N�g�A�j������ [objectAnim.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _OBJECTANIM_H_					//���̃}�N����`������ĂȂ�������
#define _OBJECTANIM_H_					//2�d�C���N���[�h�h�~�̃}�N����`

//================================================
//�C���N���[�h
//================================================
#include "object.h"

//================================================
//���C�u�����̃����N
//================================================

//================================================
//�}�N����`
//================================================
#define WIDTH (50)			//��
#define HEIGHT (100)			//����

#define ANIME_FRAME_U_NUM (8)
#define ANIME_FRAME_V_NUM (1)

#define ANIME_U(index) ((float)((index) % ANIME_FRAME_U_NUM) / (ANIME_FRAME_U_NUM))
#define ANIME_V(index) ((float)((index) / ANIME_FRAME_U_NUM) / (ANIME_FRAME_V_NUM))
#define ANIME_UW      (1.0f / ANIME_FRAME_U_NUM)
#define ANIME_VH      (1.0f / ANIME_FRAME_V_NUM)

//================================================
//�N���X
//================================================
class CObjectAnim :public CObject
{
public:
	CObjectAnim();
	~CObjectAnim();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	typedef struct
	{
		D3DXVECTOR3 pos;				//���_���W
		float rhw;						//���W�ϊ��p�W��(1.0f�ŌŒ�)
		D3DCOLOR col;					//���_�J���[
		D3DXVECTOR2 tex;				//�e�N�X�`�����W
	}VERTEX_2D;

	typedef struct
	{
		D3DXVECTOR3 pos;//���݂̈ʒu
		D3DXVECTOR3 posOld;//�O��̈ʒu
		D3DXVECTOR3 rot;//����
		D3DXVECTOR3 move;//�ړ���
		int nCounterState;//��ԊǗ��J�E���^�[
		int nLife;//�̗�
		float nStamina;//�X�^�~�i
		bool bDisp;//�\�����邩���Ȃ���
		bool bUse;
		bool bJump;
		bool bRightMove;
		bool bGoal;
		bool bFall;
		bool bClear;
	}Player;



	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_ONE,
		TYPE_MAX
	}TYPE;

	static CObjectAnim* Create(TYPE type);

private:
	TYPE m_type;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	int m_CounterAnim;
	int m_nPatternAnim;
	Player m_Player;
};

#endif