#include "wall.h"
#include "renderer.h"
#include "manager.h"

CWall::CWall()
{
}

CWall::~CWall()
{
}

HRESULT CWall::Init(void)
{
	//デバイスの取得
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/WALL.png",
		&m_pTexturePolygon);

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffPolygon, NULL);

	m_posPolygon.z = 150.0f;
	m_posPolygon.y = 700.0f;

	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロック
	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標を設定
	pVtx[0].pos = D3DXVECTOR3(-WALL_WIDTH, +WALL_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+WALL_WIDTH, +WALL_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-WALL_WIDTH, -WALL_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+WALL_WIDTH, -WALL_HEIGHT, 0.0f);


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
	pVtx[1].tex = D3DXVECTOR2(2.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 8.0f);
	pVtx[3].tex = D3DXVECTOR2(2.0f, 8.0f);

	// 頂点座標
	D3DXVECTOR3 a = pVtx[0].pos;
	D3DXVECTOR3 b = pVtx[1].pos;
	D3DXVECTOR3 c = pVtx[2].pos;
	D3DXVECTOR3 d = pVtx[3].pos;

	D3DXVECTOR3 n1, n2;

	// 三角形1: a, b, c
	D3DXVECTOR3 vec1 = b - a;
	D3DXVECTOR3 vec2 = c - a;
	D3DXVec3Cross(&n1, &vec1, &vec2);
	D3DXVec3Normalize(&n1, &n1);

	// 三角形2: b, d, c
	D3DXVECTOR3 v3 = d - b;
	D3DXVECTOR3 v4 = c - b;
	D3DXVec3Cross(&n2, &v3, &v4);
	D3DXVec3Normalize(&n2, &n2);

	// 各頂点の法線（平均化）
	pVtx[0].nor = n1;
	pVtx[1].nor = D3DXVECTOR3((n1.x + n2.x) / 2, (n1.y + n2.y) / 2, (n1.z + n2.z) / 2);
	D3DXVec3Normalize(&pVtx[1].nor, &pVtx[1].nor);
	pVtx[2].nor = D3DXVECTOR3((n1.x + n2.x) / 2, (n1.y + n2.y) / 2, (n1.z + n2.z) / 2);
	D3DXVec3Normalize(&pVtx[2].nor, &pVtx[2].nor);
	pVtx[3].nor = n2;

	//頂点バッファのアンロック
	m_pVtxBuffPolygon->Unlock();

	return S_OK;
}

void CWall::Uninit(void)
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

void CWall::Update(void)
{
	//CInputKeyboard* pInputKeyboard;
	//pInputKeyboard = CManager::GetInputKeyboard();

	//if (pInputKeyboard->Repeat(DIK_5) == true)
	//{
	//	m_posPolygon.x += 10.0f;
	//}

	//VERTEX_3D* pVtx = NULL;
	////頂点バッファをロック
	//m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	////頂点座標を設定
	//pVtx[0].pos = D3DXVECTOR3(-WALL_WIDTH, +WALL_HEIGHT, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(+WALL_WIDTH, +WALL_HEIGHT, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(-WALL_WIDTH, -WALL_HEIGHT, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(+WALL_WIDTH, -WALL_HEIGHT, 0.0f);

	////各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
	//pVtx[0].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[1].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[2].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[3].nor = D3DXVECTOR3(0.0, 1.0, 0.0);

	////頂点カラーの設定
	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//////テクスチャ座標の設定
	////pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	////pVtx[1].tex = D3DXVECTOR2(5.0f, 0.0f);
	////pVtx[2].tex = D3DXVECTOR2(0.0f, 5.0f);
	////pVtx[3].tex = D3DXVECTOR2(5.0f, 5.0f);

	////頂点バッファのアンロック
	//m_pVtxBuffPolygon->Unlock();


}

void CWall::Draw(void)
{
	//デバイスの取得
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	// ライティング有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ディレクショナルライト設定
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Direction = D3DXVECTOR3(0.0f, -1.0f, 1.0f);
	light.Diffuse = D3DXCOLOR(1, 1, 1, 1);
	light.Ambient = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1);
	pDevice->SetLight(0, &light);
	pDevice->LightEnable(0, TRUE);

	// マテリアル設定
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(mtrl));
	mtrl.Diffuse = D3DXCOLOR(1, 1, 1, 1);
	mtrl.Ambient = D3DXCOLOR(1, 1, 1, 1);
	pDevice->SetMaterial(&mtrl);

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

	pDevice->SetTexture(0, NULL); // テクスチャステージ0をリセット
}

CWall* CWall::Create(void)
{
	CWall* pObject3D = new CWall;
	pObject3D->Init();
	pObject3D->SetType(TYPE_WALL);

	return pObject3D;
}

D3DXVECTOR3 CWall::GetPos(void)
{
	return D3DXVECTOR3(m_posPolygon.x, m_posPolygon.y, m_posPolygon.z);
}

int CWall::GetWidth(void)
{
	// 必要に応じて適切な値を返す（例: 300）
	return 300;
}

int CWall::GetHeight(void)
{
	// 必要に応じて適切な値を返す（例: 300）
	return 300;
}

float CWall::GetHeightMesh(float posx, float posz)
{
	float X = posx - m_posPolygon.x;
	float Z = posz - m_posPolygon.z;

	D3DXVECTOR3 vec1, vec2, nor;
	float fHeight;

	VERTEX_3D* pVtx = NULL;
	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//XとZがポリゴンの内側にいる
	if ((X >= -WALL_WIDTH && X <= WALL_WIDTH) && (Z >= -WALL_HEIGHT && Z <= WALL_HEIGHT))
	{
		float s1 = ((pVtx[1].pos.x - pVtx[0].pos.x) * (Z - pVtx[0].pos.z) - (pVtx[1].pos.z - pVtx[0].pos.z) * (X - pVtx[0].pos.x));
		float s2 = ((pVtx[2].pos.x - pVtx[1].pos.x) * (Z - pVtx[1].pos.z) - (pVtx[2].pos.z - pVtx[1].pos.z) * (X - pVtx[1].pos.x));
		float s3 = ((pVtx[0].pos.x - pVtx[2].pos.x) * (Z - pVtx[2].pos.z) - (pVtx[0].pos.z - pVtx[2].pos.z) * (X - pVtx[2].pos.x));

		if ((s1 >= 0 && s2 >= 0 && s3 >= 0) || (s1 <= 0 && s2 <= 0 && s3 <= 0))
		{//乗っているポリゴンが1枚目なら
			vec1 = pVtx[1].pos - pVtx[0].pos;
			vec2 = pVtx[2].pos - pVtx[0].pos;
			D3DXVec3Cross(&nor, &vec1, &vec2);
			D3DXVec3Normalize(&nor, &nor);

			fHeight = pVtx[0].pos.y - (nor.x * (X - pVtx[0].pos.x) + nor.z * (Z - pVtx[0].pos.z)) / nor.y;
		}
		else
		{//乗っているポリゴンが2枚目なら
			vec1 = pVtx[3].pos - pVtx[1].pos;
			vec2 = pVtx[2].pos - pVtx[1].pos;
			D3DXVec3Cross(&nor, &vec1, &vec2);
			D3DXVec3Normalize(&nor, &nor);

			fHeight = pVtx[1].pos.y - (nor.x * (X - pVtx[1].pos.x) + nor.z * (Z - pVtx[1].pos.z)) / nor.y;
		}
		m_pVtxBuffPolygon->Unlock();
		return fHeight + m_posPolygon.y;
	}
	m_pVtxBuffPolygon->Unlock();
	return 0;
}

D3DXVECTOR3 CWall::Colision(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 size)
{
	// 壁のAABB
	D3DXVECTOR3 wallPos = m_posPolygon;
	float wallHalfW = WALL_WIDTH;
	float wallHalfH = WALL_HEIGHT;

	// プレイヤーのAABB
	float playerHalfW = size.x * 0.5f;
	float playerHalfH = size.y * 0.5f;
	float playerHalfD = size.z * 0.5f;

	// XZ平面での判定
	float wallMinX = wallPos.x - wallHalfW;
	float wallMaxX = wallPos.x + wallHalfW;
	float wallMinZ = wallPos.z - wallHalfH;
	float wallMaxZ = wallPos.z + wallHalfH;

	float playerMinX = pos.x - playerHalfW;
	float playerMaxX = pos.x + playerHalfW;
	float playerMinZ = pos.z - playerHalfD;
	float playerMaxZ = pos.z + playerHalfD;

	// AABB衝突判定
	if (playerMaxX > wallMinX && playerMinX < wallMaxX &&
		playerMaxZ > wallMinZ && playerMinZ < wallMaxZ)
	{
		// めり込み補正（最も近い方向に押し戻す）
		float dx1 = wallMaxX - playerMinX; // 左から押し戻す量
		float dx2 = playerMaxX - wallMinX; // 右から押し戻す量
		float dz1 = wallMaxZ - playerMinZ; // 上から押し戻す量
		float dz2 = playerMaxZ - wallMinZ; // 下から押し戻す量

		float minDx = (dx1 < dx2) ? dx1 : -dx2;
		float minDz = (dz1 < dz2) ? dz1 : -dz2;

		if (fabs(minDx) < fabs(minDz)) {
			pos.x += minDx;
		}
		else {
			pos.z += minDz;
		}
	}
	return pos;
}
//float CWall::GetHeightMesh(float posx, float posz)
//{
//	float X = posx - m_posPolygon.x;
//	float Z = posz - m_posPolygon.z;
//
//	VERTEX_3D* pVtx = NULL;
//	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
//
//	if ((X >= -WALL_WIDTH && X <= WALL_WIDTH) && (Z >= -WALL_HEIGHT && Z <= WALL_HEIGHT))
//	{
//		D3DXVECTOR3 a = pVtx[0].pos;
//		D3DXVECTOR3 b = pVtx[1].pos;
//		D3DXVECTOR3 c = pVtx[2].pos;
//		D3DXVECTOR3 d = pVtx[3].pos;
//
//		float fHeight = 0.0f;
//
//		float s1 = ((b.x - a.x) * (Z - a.z) - (b.z - a.z) * (X - a.x));
//		float s2 = ((c.x - b.x) * (Z - b.z) - (c.z - b.z) * (X - b.x));
//		float s3 = ((a.x - c.x) * (Z - c.z) - (a.z - c.z) * (X - c.x));
//
//		if ((s1 >= 0 && s2 >= 0 && s3 >= 0) || (s1 <= 0 && s2 <= 0 && s3 <= 0))
//		{
//			D3DXVECTOR3 vec1 = b - a;
//			D3DXVECTOR3 vec2 = c - a;
//			D3DXVECTOR3 nor;
//			D3DXVec3Cross(&nor, &vec1, &vec2);
//			D3DXVec3Normalize(&nor, &nor);
//
//			fHeight = a.y - (nor.x * (X - a.x) + nor.z * (Z - a.z)) / nor.y;
//			m_pVtxBuffPolygon->Unlock();
//			return fHeight + m_posPolygon.y;
//		}
//		else
//		{
//			D3DXVECTOR3 vec1 = d - b;
//			D3DXVECTOR3 vec2 = c - b;
//			D3DXVECTOR3 nor;
//			D3DXVec3Cross(&nor, &vec1, &vec2);
//			D3DXVec3Normalize(&nor, &nor);
//
//			fHeight = b.y - (nor.x * (X - b.x) + nor.z * (Z - b.z)) / nor.y;
//			m_pVtxBuffPolygon->Unlock();
//			return fHeight + m_posPolygon.y;
//		}
//	}
//	m_pVtxBuffPolygon->Unlock();
//	return 0;
//}



//float CWall::GetHeightMesh(float posx, float posz)
//{
//
//	VERTEX_3D* pVtx = NULL;
//	//頂点バッファをロック
//	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
//
//	// ポリゴンの範囲内か判定
//	if ((posx >= m_posPolygon.x - WALL_WIDTH && posx <= m_posPolygon.x + WALL_WIDTH) && (posz >= m_posPolygon.z - WALL_HEIGHT && posz <= m_posPolygon.z + WALL_HEIGHT))
//	{
//		D3DXVECTOR3 a = pVtx[0].pos;
//		D3DXVECTOR3 b = pVtx[1].pos;
//		D3DXVECTOR3 c = pVtx[2].pos;
//		D3DXVECTOR3 d = pVtx[3].pos;
//
//		float y = 0.0f;
//
//		// どちらの三角形に含まれるか判定
//		// 三角形abc
//		float s1 = ((pVtx[1].pos.x - pVtx[0].pos.x) * (posz - pVtx[0].pos.z) - (pVtx[1].pos.z - pVtx[0].pos.z) * (posx - pVtx[0].pos.x));
//		float s2 = ((pVtx[2].pos.x - pVtx[1].pos.x) * (posz - pVtx[1].pos.z) - (pVtx[2].pos.z - pVtx[1].pos.z) * (posx - pVtx[1].pos.x));
//		float s3 = ((pVtx[0].pos.x - pVtx[2].pos.x) * (posz - pVtx[2].pos.z) - (pVtx[0].pos.z - pVtx[2].pos.z) * (posx - pVtx[2].pos.x));
//
//		if ((s1 >= 0 && s2 >= 0 && s3 >= 0) || (s1 <= 0 && s2 <= 0 && s3 <= 0))
//		{
//			// 三角形abcの平面方程式
//			D3DXVECTOR3 vec1 = pVtx[1].pos - pVtx[0].pos;
//			D3DXVECTOR3 vec2 = pVtx[2].pos - pVtx[0].pos;
//			D3DXVECTOR3 nor;
//			D3DXVec3Cross(&nor, &vec1, &vec2);
//			D3DXVec3Normalize(&nor, &nor);
//
//			// 平面方程式: nor.x*(x-a.x) + nor.y*(y-a.y) + nor.z*(z-a.z) = 0
//			// y = a.y - (nor.x*(x-a.x) + nor.z*(z-a.z)) / nor.y
//			y = pVtx[0].pos.y - (nor.x * (posx - pVtx[0].pos.x) + nor.z * (posz - pVtx[0].pos.z)) / nor.y;
//			return y;
//		}
//		else
//		{
//			// 三角形bdc
//			D3DXVECTOR3 vec1 = pVtx[3].pos - pVtx[1].pos;
//			D3DXVECTOR3 vec2 = pVtx[2].pos - pVtx[1].pos;
//			D3DXVECTOR3 nor;
//			D3DXVec3Cross(&nor, &vec1, &vec2);
//			D3DXVec3Normalize(&nor, &nor);
//
//			// 平面方程式
//			y = pVtx[1].pos.y - (nor.x * (posx - pVtx[1].pos.x) + nor.z * (posz - pVtx[1].pos.z)) / nor.y;
//			return y;
//		}
//	}
//	//頂点バッファのアンロック
//	m_pVtxBuffPolygon->Unlock();
//
//	return 0;
//}
//