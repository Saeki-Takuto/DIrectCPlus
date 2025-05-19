//==================================================================
//
//�����_���[���� [renderer.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _RENDERER_H_					//���̃}�N����`������ĂȂ�������
#define _RENDERER_H_					//2�d�C���N���[�h�h�~�̃}�N����`

//================================================
//�C���N���[�h
//================================================
#include "d3dx9.h"

//================================================
//���C�u�����̃����N
//================================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")

//================================================
//�}�N����`
//================================================
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//================================================
//�����_���[�N���X
//================================================
class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd,
				 BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	LPDIRECT3DDEVICE9 GetDevice(void);

private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
};

#endif