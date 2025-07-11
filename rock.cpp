#include "rock.h"
#include "manager.h"

D3DXVECTOR3 CRock::m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CRock::m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CRock::m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

	int nNumVtx;//頂点数
	DWORD sizeFVF;//頂点フォーマットのサイズ
	BYTE* pVtxBuff;//頂点バッファへのポインタ

	nNumVtx = m_pMesh->GetNumVertices();
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//xの最小値比較
		if (vtx.x < m_vtxMin.x)
		{
			m_vtxMin.x = vtx.x;
		}

		//xの最大値比較
		if (vtx.x > m_vtxMax.x)
		{
			m_vtxMax.x = vtx.x;
		}

		//yの最小値比較
		if (vtx.y < m_vtxMin.y)
		{
			m_vtxMin.y = vtx.y;
		}

		//yの最大値比較
		if (vtx.y > m_vtxMax.y)
		{
			m_vtxMax.y = vtx.y;
		}

		//zの最小値比較
		if (vtx.z < m_vtxMin.z)
		{
			m_vtxMin.z = vtx.z;
		}

		//zの最大値比較
		if (vtx.z > m_vtxMax.z)
		{
			m_vtxMax.z = vtx.z;
		}

		//頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	//頂点バッファのアンロック
	m_pMesh->UnlockVertexBuffer();

	m_size = m_vtxMax - m_vtxMin;

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

float CRock::GetHeight(float posx, float posz)
{
	D3DXVECTOR3 rockPos = GetPos();

	float minX = rockPos.x + m_vtxMin.x;
	float maxX = rockPos.x + m_vtxMax.x;
	float minZ = rockPos.z + m_vtxMin.z;
	float maxZ = rockPos.z + m_vtxMax.z;
	float topY = rockPos.y + m_vtxMax.y;

	if (posx >= minX && posx <= maxX &&
		posz >= minZ && posz <= maxZ)
	{
		return topY;
	}

	return -1.0f;
}
