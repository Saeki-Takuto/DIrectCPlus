//==================================================================
//
//�J�������� [camera.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _CAMERA_H_					//���̃}�N����`������ĂȂ�������
#define _CAMERA_H_					//2�d�C���N���[�h�h�~�̃}�N����`

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
class CCamera
{
public:
	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);

	D3DXVECTOR3 GetRot(void) {return m_rot;}

private:
	D3DXMATRIX m_mtxView;
	D3DXMATRIX m_mtxProjection;
	D3DXVECTOR3 m_posV;
	D3DXVECTOR3 m_posR;
	D3DXVECTOR3 m_vecU;
	D3DXVECTOR3 m_rot;

	D3DXVECTOR3 m_posVDest;
	D3DXVECTOR3 m_posRDest;
	float m_Distance;

};

#endif