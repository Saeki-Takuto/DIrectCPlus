#include "shadowS.h"
#include "manager.h"

D3DXVECTOR3 CShadowS::m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CShadowS::m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CShadowS::m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

LPD3DXMESH CShadowS::m_pMesh = NULL;
LPD3DXBUFFER CShadowS::m_pBuffMat = NULL;
DWORD CShadowS::m_dwNumMat = NULL;

CShadowS::CShadowS()
{
}

CShadowS::~CShadowS()
{
}

HRESULT CShadowS::Init(void)
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

void CShadowS::Uninit(void)
{
	CObjectX::Uninit();
}

void CShadowS::Update(void)
{

}

void CShadowS::Draw(void)
{
	CObjectX::Draw();

	//ステンシルテストを有効にする
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	//Zバッファの書き込みを無効にする
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//カラーバッファの書き込みを無効にする
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000);

	//ステンシルバッファの比較パラメータを設定
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);

	//表面をカリング
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//影モデルの描画
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	m_pMesh->DrawSubset(0);

	//ステンシルバッファの参照値を設定("1"にする)
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

	//ステンシルバッファの比較パラメータを設定
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);

	//裏面をカリング
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//影モデルの描画
	m_pMesh->DrawSubset(0);

	//カラーバッファへの書き込みを有効にする
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0000000F);
	//ステンシルバッファの参照値を設定("2"にする)
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x02);

	//ステンシルバッファの比較パラメータを設定
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);

	//画面の大きさのポリゴンを描画
	D3DXMATRIX mtxTrans;
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	pDevice->SetTransform(D3DTS_WORLD, &mtxTrans);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	m_pMesh->DrawSubset(0);
	
	// すべてもとに戻す
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// 追加: レンダーステートを元に戻す
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // 通常はTRUE
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0000000F); // 全色書き込み
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE); // Zバッファ有効


}


CShadowS* CShadowS::Create(float X, float Y, float Z)
{
	CShadowS* pShadowS = new CShadowS();
	pShadowS->BindX(m_pBuffMat, m_dwNumMat, m_pMesh);
	pShadowS->Init();
	pShadowS->SetPos(X, Y, Z);
	//CObject::Add(pShadowS); // ★これを追加
	return pShadowS;
}

HRESULT CShadowS::Load(void)
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

void CShadowS::Unload(void)
{
	if (m_pBuffMat != NULL)
	{
		//m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	if (m_dwNumMat != NULL)
	{
		//m_dwNumMat->Release();
		m_dwNumMat = NULL;
	}

	if (m_pMesh != NULL)
	{
		//m_pMesh->Release();
		m_pMesh = NULL;
	}
}

float CShadowS::GetHeight(float posx, float posz)
{
	D3DXVECTOR3 shadowsPos = GetPos();

	float minX = shadowsPos.x + m_vtxMin.x;
	float maxX = shadowsPos.x + m_vtxMax.x;
	float minZ = shadowsPos.z + m_vtxMin.z;
	float maxZ = shadowsPos.z + m_vtxMax.z;
	float topY = shadowsPos.y + m_vtxMax.y;

	if (posx >= minX && posx <= maxX &&
		posz >= minZ && posz <= maxZ)
	{
		return topY;
	}

	return -1.0f;
}
