#include "object3D.h"
#include "renderer.h"
#include "manager.h"

CObject3D::CObject3D()
{
}

CObject3D::~CObject3D()
{
}

HRESULT CObject3D::Init(void)
{
	//デバイスの取得
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/mouse.png",
		&m_pTexturePolygon);

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffPolygon, NULL);

	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロック
	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標を設定
	pVtx[0].pos = D3DXVECTOR3(-150.0f, 0.0f, 150.0f);
	pVtx[1].pos = D3DXVECTOR3(150.0f, 0.0f, 150.0f);
	pVtx[2].pos = D3DXVECTOR3(-150.0f, 0.0f, -150.0f);
	pVtx[3].pos = D3DXVECTOR3(150.0f, 0.0f, -150.0f);

	//各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
	pVtx[0].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	pVtx[1].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	pVtx[2].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	pVtx[3].nor = D3DXVECTOR3(0.0, 1.0, 0.0);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuffPolygon->Unlock();

	return S_OK;
}

void CObject3D::Uninit(void)
{
	if (m_pVtxBuffPolygon != NULL)
	{
		m_pVtxBuffPolygon->Release();
		m_pVtxBuffPolygon = NULL;
	}

	if (m_pTexturePolygon != NULL)
	{
		m_pTexturePolygon->Release();
		m_pTexturePolygon = NULL;
	}
}

void CObject3D::Update(void)
{
}

void CObject3D::Draw(void)
{
	//デバイスの取得
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorldPolygon);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotPolygon.y, m_rotPolygon.x, m_rotPolygon.z);
	D3DXMatrixMultiply(&m_mtxWorldPolygon, &m_mtxWorldPolygon, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_posPolygon.x, m_posPolygon.y, m_posPolygon.z);
	D3DXMatrixMultiply(&m_mtxWorldPolygon, &m_mtxWorldPolygon, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldPolygon);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexturePolygon);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

CObject3D* CObject3D::Create(void)
{
	CObject3D* pObject3D = new CObject3D;
	pObject3D->Init();

	return pObject3D;
}

D3DXVECTOR2 CObject3D::GetPos(void)
{
	// 3D座標のx, zを2D座標に変換（用途に応じて調整）
	return D3DXVECTOR2(m_posPolygon.x, m_posPolygon.z);
}

int CObject3D::GetWidth(void)
{
	// 必要に応じて適切な値を返す（例: 300）
	return 300;
}

int CObject3D::GetHeight(void)
{
	// 必要に応じて適切な値を返す（例: 300）
	return 300;
}

