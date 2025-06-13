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
	// Direct3Dデバイスの取得
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	D3DXVECTOR3 vecDir;//ライトの方向ベクトル

	//ライトをクリアする
	ZeroMemory(&m_aLight[0], sizeof(D3DLIGHT9));

	//ライトの種類を設定
	m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	//ライトの拡散光を設定
	m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライトの方向を設定
	vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);

	//正規化する(大きさ1のベクトルにする)
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_aLight[0].Direction = vecDir;

	//ライトを設定する
	pDevice->SetLight(0, &m_aLight[0]);

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);


	return E_NOTIMPL;
}

void CLight::Uninit(void)
{
}

void CLight::Update(void)
{
}
