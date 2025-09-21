#include "goal.h"
#include "manager.h"

D3DXVECTOR3 CGoal::m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CGoal::m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CGoal::m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

LPD3DXMESH CGoal::m_pMesh = NULL;
LPD3DXBUFFER CGoal::m_pBuffMat = NULL;
DWORD CGoal::m_dwNumMat = NULL;

CGoal::CGoal()
{
}

CGoal::~CGoal()
{
}

HRESULT CGoal::Init(void)
{
	if (!m_pMesh) {
		// メッシュが未ロード
		return E_FAIL;
	}
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

void CGoal::Uninit(void)
{
	CObjectX::Uninit();
}

void CGoal::Update(void)
{
	
}

void CGoal::Draw(void)
{
	CObjectX::Draw();
}


CGoal* CGoal::Create(float X, float Y, float Z)
{
	CGoal* pGoal = new CGoal();
	pGoal->BindX(m_pBuffMat, m_dwNumMat, m_pMesh);
	pGoal->Init();
	pGoal->SetType(CObject::TYPE_GOAL);
	pGoal->SetPos(X, Y, Z);
	return pGoal;
}

//
//いらない(Createに渡す)
//
HRESULT CGoal::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	HRESULT hr = D3DXLoadMeshFromX("data/MODEL/goal.x",
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

//
//いらない
//

void CGoal::Unload(void)
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

float CGoal::GetHeight(float posx, float posz)
{
	D3DXVECTOR3 goalPos = GetPos();

	float minX = goalPos.x + m_vtxMin.x;
	float maxX = goalPos.x + m_vtxMax.x;
	float minZ = goalPos.z + m_vtxMin.z;
	float maxZ = goalPos.z + m_vtxMax.z;
	float topY = goalPos.y + m_vtxMax.y;

	if (posx >= minX && posx <= maxX &&
		posz >= minZ && posz <= maxZ)
	{
		return topY;
	}

	return -1.0f;
}

D3DXVECTOR3 CGoal::Colision(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 size)
{
	D3DXVECTOR3 goalPos = GetPos();
	D3DXVECTOR3 returnPos = pos;

	// 下から当たった場合
	if (posOld.y + size.y <= goalPos.y - m_size.y * 0.5f && pos.y + size.y >= goalPos.y - m_size.y * 0.5f)
	{
		if (pos.z - size.z * 0.5f < goalPos.z + m_size.z * 0.5f && pos.z + size.z * 0.5f > goalPos.z - m_size.z * 0.5f &&
			pos.x - size.x * 0.5f < goalPos.x + m_size.x * 0.5f && pos.x + size.x * 0.5f > goalPos.x - m_size.x * 0.5f)
		{
			returnPos.y = goalPos.y - m_size.y * 0.5f - size.y;
		}
	}

	// 上から当たった場合
	if (posOld.y >= goalPos.y + m_size.y && pos.y <= goalPos.y + m_size.y)
	{
		if (pos.z - size.z * 0.5f < goalPos.z + m_size.z * 0.5f && pos.z + size.z * 0.5f > goalPos.z - m_size.z * 0.5f &&
			pos.x - size.x * 0.5f < goalPos.x + m_size.x * 0.5f && pos.x + size.x * 0.5f > goalPos.x - m_size.x * 0.5f)
		{
			returnPos.y = goalPos.y + m_size.y; // ← プレイヤーの底面が岩の上面に来る
		}
	}
	// Z軸前後
	if (posOld.z + size.z * 0.5f <= goalPos.z - m_size.z * 0.5f && pos.z + size.z * 0.5f >= goalPos.z - m_size.z * 0.5f)
	{
		if (pos.y - size.y * 0.5f < goalPos.y + m_size.y * 0.5f && pos.y + size.y * 0.5f > goalPos.y - m_size.y * 0.5f &&
			pos.x - size.x * 0.5f < goalPos.x + m_size.x * 0.5f && pos.x + size.x * 0.5f > goalPos.x - m_size.x * 0.5f)
		{
			returnPos.z = goalPos.z - m_size.z * 0.5f - size.z * 0.5f;
		}
	}

	if (posOld.z - size.z * 0.5f >= goalPos.z + m_size.z * 0.5f && pos.z - size.z * 0.5f <= goalPos.z + m_size.z * 0.5f)
	{
		if (pos.y - size.y * 0.5f < goalPos.y + m_size.y * 0.5f && pos.y + size.y * 0.5f > goalPos.y - m_size.y * 0.5f &&
			pos.x - size.x * 0.5f < goalPos.x + m_size.x * 0.5f && pos.x + size.x * 0.5f > goalPos.x - m_size.x * 0.5f)
		{
			returnPos.z = goalPos.z + m_size.z * 0.5f + size.z * 0.5f;
		}
	}

	// X軸左右
	if (posOld.x + size.x * 0.5f <= goalPos.x - m_size.x * 0.5f && pos.x + size.x * 0.5f >= goalPos.x - m_size.x * 0.5f)
	{
		if (pos.y - size.y < goalPos.y + m_size.y * 0.5f && pos.y + size.y > goalPos.y - m_size.y * 0.5f &&
			pos.z - size.z * 0.5f < goalPos.z + m_size.z * 0.5f && pos.z + size.z * 0.5f > goalPos.z - m_size.z * 0.5f)
		{
			returnPos.x = goalPos.x - m_size.x * 0.5f - size.x * 0.5f;
		}
	}

	if (posOld.x - size.x * 0.5f >= goalPos.x + m_size.x * 0.5f && pos.x - size.x * 0.5f <= goalPos.x + m_size.x * 0.5f)
	{
		if (pos.y - size.y < goalPos.y + m_size.y * 0.5f && pos.y + size.y > goalPos.y - m_size.y * 0.5f &&
			pos.z - size.z * 0.5f < goalPos.z + m_size.z * 0.5f && pos.z + size.z * 0.5f > goalPos.z - m_size.z * 0.5f)
		{
			returnPos.x = goalPos.x + m_size.x * 0.5f + size.x * 0.5f;
		}
	}

	return returnPos;
}

//bool CGoal::IsOnTop(const D3DXVECTOR3& playerPos, const D3DXVECTOR3& playerSize)
//{
//	D3DXVECTOR3 goalPos = GetPos();
//	D3DXVECTOR3 goalSize = m_size;
//
//	// XZ平面で重なっているか
//	bool overlapX = fabs(playerPos.x - goalPos.x) < (playerSize.x + goalSize.x) * 0.5f;
//	bool overlapZ = fabs(playerPos.z - goalPos.z) < (playerSize.z + goalSize.z) * 0.5f;
//
//	// プレイヤーの足元と岩の上面の高さが近いか
//	float playerFootY = playerPos.y;
//	float goalTopY = goalPos.y + goalSize.y * 0.5f;
//	bool onTopY = fabs(playerFootY - goalTopY) < 0.15f;
//
//	return overlapX && overlapZ && onTopY;
//}

bool CGoal::IsOnTop(const D3DXVECTOR3& playerPos, const D3DXVECTOR3& playerSize)
{
	D3DXVECTOR3 goalPos = GetPos();
	D3DXVECTOR3 goalSize = m_size;

	bool overlapX = fabs(playerPos.x - goalPos.x) < (playerSize.x + goalSize.x) * 0.5f;
	bool overlapZ = fabs(playerPos.z - goalPos.z) < (playerSize.z + goalSize.z) * 0.5f;

	float playerFootY = playerPos.y;
	float goalTopY = goalPos.y + goalSize.y;
	bool onTopY = fabs(playerFootY - goalTopY) < 0.2f; // ← 0.2fに拡大

	return overlapX && overlapZ && onTopY;
}

//bool CGoal::IsOnTop(const D3DXVECTOR3& playerPos, const D3DXVECTOR3& playerSize)
//{
//	D3DXVECTOR3 goalPos = GetPos();
//	D3DXVECTOR3 goalSize = m_size;
//
//	bool overlapX = fabs(playerPos.x - goalPos.x) < (playerSize.x + goalSize.x) * 0.5f;
//	bool overlapZ = fabs(playerPos.z - goalPos.z) < (playerSize.z + goalSize.z) * 0.5f;
//
//	float playerFootY = playerPos.y;
//	float goalTopY = goalPos.y + goalSize.y; // ← ここを修正
//	bool onTopY = fabs(playerFootY - goalTopY) < 0.2f;
//
//	return overlapX && overlapZ && onTopY;
//}