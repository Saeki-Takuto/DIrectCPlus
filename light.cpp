#include "light.h"
#include "renderer.h"
#include "manager.h"

CLight::CLight()
{
}

CLight::~CLight()
{
}

HRESULT CLight::Init(void)
{
	// Direct3D�f�o�C�X�̎擾
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	D3DXVECTOR3 vecDir;//���C�g�̕����x�N�g��

	//���C�g���N���A����
	ZeroMemory(&m_aLight[0], sizeof(D3DLIGHT9));

	//���C�g�̎�ނ�ݒ�
	m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U����ݒ�
	m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);

	//���K������(�傫��1�̃x�N�g���ɂ���)
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_aLight[0].Direction = vecDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(0, &m_aLight[0]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);


	return E_NOTIMPL;
}

void CLight::Uninit(void)
{
}

void CLight::Update(void)
{
}
