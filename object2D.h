//==================================================================
//
//�I�u�W�F�N�g2D���� [object2D.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _OBJECT2D_H_					//���̃}�N����`������ĂȂ�������
#define _OBJECT2D_H_					//2�d�C���N���[�h�h�~�̃}�N����`

//================================================
//�C���N���[�h
//================================================
#include "object.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X
//================================================
class CObject2D :public CObject
{
public:
	CObject2D();
	~CObject2D();

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

	typedef enum
	{
		TYPE_NONE=0,
		TYPE_ONE,
		TYPE_TWO,
		TYPE_MAX
	}TYPE;

	static CObject2D* Create(TYPE type);

private:
	TYPE m_type;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
};

#endif