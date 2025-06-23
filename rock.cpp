#include "rock.h"
#include "manager.h"

LPD3DXMESH CRock::m_pMesh = NULL;
LPD3DXBUFFER CRock::m_pBuffMat = NULL;
DWORD CRock::m_dwNumMat = NULL;

CRock::CRock()
{
}

CRock::~CRock()
{
}

HRESULT CRock::Init(void)
{
	CObjectX::Init();

	return S_OK;
}

void CRock::Uninit(void)
{
	CObjectX::Uninit();
}

void CRock::Update(void)
{
	
}

void CRock::Draw(void)
{
	CObjectX::Draw();
}

//CRock* CRock::Create()
//{
//	CRock* pRock = new CRock();
//	pRock->BindX(m_pBuffMat, m_dwNumMat, m_pMesh);
//	pRock->Init();
//	return pRock;
//}

CRock* CRock::Create(float X, float Y, float Z)
{
	CRock* pRock = new CRock();
	pRock->BindX(m_pBuffMat, m_dwNumMat, m_pMesh);
	pRock->Init();
	pRock->SetPos(X, Y, Z);
	return pRock;
}

HRESULT CRock::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	HRESULT hr = D3DXLoadMeshFromX("data/MODEL/privacy.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	if (FAILED(hr))
	{
		m_pMesh = NULL;
		m_pBuffMat = NULL;
		m_dwNumMat = 0;
		return E_FAIL;
	}

	return S_OK;
}

void CRock::Unload(void)
{
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	if (m_dwNumMat != NULL)
	{
		//m_dwNumMat->Release();
		m_dwNumMat = NULL;
	}

	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

}
