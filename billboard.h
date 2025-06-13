//==================================================================
//
//�r���{�[�h���� [billboard.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _BILLBOARD_H_					//���̃}�N����`������ĂȂ�������
#define _BILLBOARD_H_					//2�d�C���N���[�h�h�~�̃}�N����`

//================================================
//�C���N���[�h
//================================================
#include "object.h"
#include <string>

//================================================
//�}�N����`
//================================================
#define BILL_SIZE (15.0f)

//================================================
//�N���X
//================================================
class CBillboard :public CObject
{
public:
	CBillboard();
	~CBillboard();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBillboard* Create(void);

	D3DXVECTOR2 GetPos(void) override;
	int GetWidth(void) override;
	int GetHeight(void) override;

	typedef struct
	{
		D3DXVECTOR3 pos;//���_���W
		D3DXVECTOR3 nor;//�@���x�N�g��
		D3DCOLOR col;//���_�J���[
		D3DXVECTOR2 tex;//�e�N�X�`�����W
	}VERTEX_3D;

private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;

	//LPD3DXMESH m_pMesh;
	//LPD3DXBUFFER m_pBuffMat;
	//DWORD m_dwNumMat;

	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
};

#endif