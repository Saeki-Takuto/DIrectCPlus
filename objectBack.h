//==================================================================
//
//�I�u�W�F�N�g�w�i���� [objectBack.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _OBJECTBACK_H_					//���̃}�N����`������ĂȂ�������
#define _OBJECTBACK_H_					//2�d�C���N���[�h�h�~�̃}�N����`

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

//================================================
//�N���X
//================================================
class CObjectBack :public CObject
{
public:
	CObjectBack();
	~CObjectBack();

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
		TYPE_NONE = 0,
		TYPE_ONE,
		TYPE_MAX
	}TYPE;

	static CObjectBack* Create(TYPE type);

private:
	TYPE m_type;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	float m_aPosTexU;
};

#endif