//==================================================================
//
//モデル処理 [model.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//インクルード
//================================================
#include "model.h"
#include "renderer.h"
#include "manager.h"

//================================================
//静的メンバ変数
//================================================

//================================================
//コンストラクタ
//================================================
CModel::CModel()
{
	m_nNumKey = 2;
	m_MotionType = MOTION_TYPE_NEUTRAL;
}

//================================================
//デストラクタ
//================================================
CModel::~CModel()
{
}

//================================================
//初期化処理
//================================================
HRESULT CModel::Init(const char* XFilePass)
{
	//デバイスの取得
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX(XFilePass,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	D3DXMATERIAL* pMat;//マテリアルへのポインタ

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_apTexture[nCntMat]);
		}
	}

	return S_OK;
}

//================================================
//終了処理
//================================================
void CModel::Uninit(void)
{
	//テクスチャの解放
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//頂点バッファの解放
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	for (int nCnt = 0; nCnt < 128; nCnt++)
	{
		//テクスチャの破棄
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

//================================================
//更新処理
//================================================
void CModel::Update(void)
{
	// キー数が0なら何もしない
	int numKey = m_MotionInfo[m_MotionType].nNumKey;
	if (numKey <= 0) return;

	if (m_nKey >= numKey)
	{
		m_nKey = 0;
	}

	int nDis = (m_nKey + 1) % numKey;

	int nFrame = m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].nFrame;
	if (nFrame <= 0) nFrame = 1; // 0除算防止

	D3DXVECTOR3 fPosB, fRotB;
	fPosB.x = m_MotionInfo[m_MotionType].aKeyInfo[nDis].aKey.fPosX - m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fPosX;
	fPosB.y = m_MotionInfo[m_MotionType].aKeyInfo[nDis].aKey.fPosY - m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fPosY;
	fPosB.z = m_MotionInfo[m_MotionType].aKeyInfo[nDis].aKey.fPosZ - m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fPosZ;

	fRotB.x = m_MotionInfo[m_MotionType].aKeyInfo[nDis].aKey.fRotX - m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fRotX;
	fRotB.y = m_MotionInfo[m_MotionType].aKeyInfo[nDis].aKey.fRotY - m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fRotY;
	fRotB.z = m_MotionInfo[m_MotionType].aKeyInfo[nDis].aKey.fRotZ - m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fRotZ;

	float fDis = (float)m_nCounterMotion / nFrame;

	D3DXVECTOR3 fPosA, fRotA;
	fPosA.x = m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fPosX + fPosB.x * fDis;
	fPosA.y = m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fPosY + fPosB.y * fDis;
	fPosA.z = m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fPosZ + fPosB.z * fDis;

	fRotA.x = m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fRotX + fRotB.x * fDis;
	fRotA.y = m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fRotY + fRotB.y * fDis;
	fRotA.z = m_MotionInfo[m_MotionType].aKeyInfo[m_nKey].aKey.fRotZ + fRotB.z * fDis;

	m_rot = fRotA;

	m_nCounterMotion++;

	if (m_nCounterMotion >= nFrame)
	{
		m_nCounterMotion = 0;
		m_nKey++;
		if (m_nKey >= numKey)
		{
			m_nKey = 0;
		}
	}
}


//================================================
//描画処理
//================================================
void CModel::Draw(void)
{
	// デバイスの取得
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//親のマトリックスと掛け合わせる
	D3DXMATRIX mtxParent;//親モデルのマトリックス
	if (m_pParent != NULL)
	{//親が存在する
		//親モデルのマトリックスを取得する
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{//親が存在しない
		//現在(最新)のマトリックスを取得する[=プレイヤーのマトリックス]
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}
	//親のマトリックスと掛け合わせる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_apTexture[nCntMat]);

		//モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//================================================
//生成処理
//================================================
CModel* CModel::Create(const char* XFilePass)
{
	CModel* pCModel = new CModel;
	pCModel->Init(XFilePass);
	return pCModel;
}

void CModel::SetParent(CModel* pModel)
{
	m_pParent = pModel;
}

D3DXMATRIX CModel::GetMtxWorld(void)
{
	return m_mtxWorld;
}

void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

void CModel::SetKeyFrame0(KEY aKey)
{
	m_aKey[0] = aKey;
}

void CModel::SetKeyFrame1(KEY aKey)
{
	m_aKey[1] = aKey;
}

void CModel::SetFrame(int Frame)
{
	m_nFrame = Frame;
}

void CModel::SetMotionNumKey(int nIdx, int nNumKey)
{
	m_MotionInfo[nIdx].nNumKey = nNumKey;
}

int CModel::GetMotionNumKey(int nIdx)
{
	return m_MotionInfo[nIdx].nNumKey;
}

void CModel::SetFrame(int nIdx, int nIdx1,int nFrame)
{
	m_MotionInfo[nIdx].aKeyInfo[nIdx1].nFrame = nFrame;
}

void CModel::SetKeyPos(int nIdx, int nIdx1, float x, float y, float z)
{
	m_MotionInfo[nIdx].aKeyInfo[nIdx1].aKey.fPosX = x;
	m_MotionInfo[nIdx].aKeyInfo[nIdx1].aKey.fPosY = y;
	m_MotionInfo[nIdx].aKeyInfo[nIdx1].aKey.fPosZ = z;
}

void CModel::SetKeyRot(int nIdx, int nIdx1, float x, float y, float z)
{
	m_MotionInfo[nIdx].aKeyInfo[nIdx1].aKey.fRotX = x;
	m_MotionInfo[nIdx].aKeyInfo[nIdx1].aKey.fRotY = y;
	m_MotionInfo[nIdx].aKeyInfo[nIdx1].aKey.fRotZ = z;
}

void CModel::SetMotionLoop(int nIdx, bool bLoop)
{
	m_MotionInfo[nIdx].bLoop = bLoop;
}

void CModel::SetMotionType(MOTION_TYPE motion)
{
	m_MotionType = motion;
}

