//==================================================================
//
//�I�u�W�F�N�g2D���� [object2D.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _OBJECT3D_H_					//���̃}�N����`������ĂȂ�������
#define _OBJECT3D_H_					//2�d�C���N���[�h�h�~�̃}�N����`

//================================================
//�C���N���[�h
//================================================
#include "object.h"
#include <string>

//================================================
//�}�N����`
//================================================

//================================================
//�N���X
//================================================
class CObject3D :public CObject
{
public:
	CObject3D();
	~CObject3D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	typedef struct
	{
		D3DXVECTOR3 pos;//���_���W
		D3DXVECTOR3 nor;//�@���x�N�g��
		D3DCOLOR col;//���_�J���[
		D3DXVECTOR2 tex;//�e�N�X�`�����W
	}VERTEX_3D;

	static CObject3D* Create(void);
	D3DXVECTOR2 GetPos(void) override;
	int GetWidth(void) override;
	int GetHeight(void) override;

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPolygon = NULL;//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexturePolygon = NULL;		//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_posPolygon;//�ʒu
	D3DXVECTOR3 m_rotPolygon;//����
	D3DXMATRIX m_mtxWorldPolygon;//���[���h�}�g���b�N�X
};

#endif