//==================================================================
//
//�I�u�W�F�N�g���� [object.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _OBJECT_H_					//���̃}�N����`������ĂȂ�������
#define _OBJECT_H_					//2�d�C���N���[�h�h�~�̃}�N����`

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

//================================================
//�I�u�W�F�N�g�N���X
//================================================
class CObject
{
public:
	CObject();
	virtual ~CObject();

	virtual HRESULT Init(void)=0;
	virtual void Uninit(void)=0;
	virtual void Update(void)=0;
	virtual void Draw(void)=0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

protected:

private:
	static CObject* m_apObject[10];
	static int m_nNumAll;//�I�u�W�F�N�g����
	int m_nID;//�������g��ID
};

#endif