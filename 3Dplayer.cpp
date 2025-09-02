//==================================================================
//
//3Dプレイヤー処理 [3Dplayer.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//インクルード
//================================================
#include "3Dplayer.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"

//================================================
//静的メンバ変数
//================================================
D3DXVECTOR3 C3DPlayer::m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 C3DPlayer::m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 C3DPlayer::m_size   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//================================================
//コンストラクタ
//================================================
C3DPlayer::C3DPlayer()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		m_apModel[nCnt] = NULL; //モデルの初期化
	}

	m_nNumModel = NULL;

}

//================================================
//デストラクタ
//================================================
C3DPlayer::~C3DPlayer()
{
}

//================================================
//初期化処理
//================================================
HRESULT C3DPlayer::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//ファイルを開く
	FILE* pFile = NULL;

	//ファイルを開く
	pFile = fopen("data/PLAYER/motion.txt", "r");

	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nModel = 0;
	int nIdx = 0;
	int nCnt = 0;
	int nCntPos = 0;
	int nCntRot = 0;
	int nCntKey = 0;
	int nCntMotion = 0;
	int nLoop = 0;
	int nIdxNumKey = 0;
	int nKey = 0;


	if (pFile != NULL)
	{
		char aString[MAX_WORD];

		while (1)
		{
			fscanf(pFile, "%s", &aString[0]);

			if (strcmp(&aString[0], "SCRIPT") == 0)
			{//SCRIPT読み取り

				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "NUM_MODEL") == 0)
					{// NUM_MODEL読み取り
						fscanf(pFile, "%s", &aString[0]);

						if (strcmp(&aString[0], "=") == 0)
						{//値を代入
							fscanf(pFile, "%d", &nModel);
						}
					}
					else if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
					{
						// MODEL_FILENAME読み取り
						fscanf(pFile, "%s", &aString[0]);

						if (strcmp(&aString[0], "=") == 0)
						{// 代入

							//文字列を読み込む
							fscanf(pFile, "%s", &aString[0]);

							const char* MODEL_FILE = {};	//モデルファイル名格納変数

							//文字列を保存する
							MODEL_FILE = aString;

							m_apModel[nCnt] = CModel::Create(MODEL_FILE);

							nCnt++; //nCntをインクリメント
						}
					}
					else if (strcmp(&aString[0], "CHARACTERSET") == 0)
					{
						while (1)
						{
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "NUM_PARTS") == 0)
							{// NUM_PARTS読み込み

								fscanf(pFile, "%s", &aString[0]);

								if (strcmp(&aString[0], "=") == 0)
								{//値を代入
									fscanf(pFile, "%d", &m_nNumModel);
								}
							}
							else if (strcmp(&aString[0], "PARTSSET") == 0)
							{
								while (1)
								{
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(&aString[0], "INDEX") == 0)
									{//INDEXを読み取り

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{//代入
											fscanf(pFile, "%d", &nIdx);
										}
									}

									if (strcmp(&aString[0], "PARENT") == 0)
									{//PARENT読み取り

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{// 代入
											//親
											int nParent;
											fscanf(pFile, "%d", &nParent);
											if (nParent < 0)
											{//0以下(基本は-1)の場合(NULL)
												m_apModel[nIdx]->SetParent(NULL);
											}
											else
											{//親モデルが指定されている場合
												m_apModel[nIdx]->SetParent(m_apModel[nParent]);
											}
										}
									}

									if (strcmp(&aString[0], "POS") == 0)
									{//POS読み取り

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{//座標を代入
											D3DXVECTOR3 nIdxPos;
											fscanf(pFile, "%f", &nIdxPos.x);
											fscanf(pFile, "%f", &nIdxPos.y);
											fscanf(pFile, "%f", &nIdxPos.z);

											m_apModel[nIdx]->SetPos(nIdxPos);
										}
									}

									if (strcmp(&aString[0], "ROT") == 0)
									{//ROT読み取り

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{//角度を代入
											D3DXVECTOR3 nIdxRot;
											fscanf(pFile, "%f", &nIdxRot.x);
											fscanf(pFile, "%f", &nIdxRot.y);
											fscanf(pFile, "%f", &nIdxRot.z);

											m_apModel[nIdx]->SetRot(nIdxRot);
										}
									}

									if (strcmp(&aString[0], "END_PARTSSET") == 0)
									{// END_PARTSSET読み取り
										break;
									}

								}
							}
							else if (strcmp(&aString[0], "END_CHARACTERSET") == 0)
							{
								break;
							}
						}
					}
					else if (strcmp(&aString[0], "MOTIONSET") == 0)
					{
						//ループフラグとキー数の初期化
						while (1)
						{
							fscanf(pFile, "%s", &aString[0]);

							// ループフラグ
							if (strcmp(&aString[0], "LOOP") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								if (strcmp(&aString[0], "=") == 0)
								{
									fscanf(pFile, "%d", &nLoop);
									for (int i = 0; i < m_nNumModel; i++)
									{
										if (m_apModel[i]) m_apModel[i]->SetMotionLoop(nCntMotion, nLoop != 0);
									}
								}
							}
							//キー数
							else if (strcmp(&aString[0], "NUM_KEY") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								if (strcmp(&aString[0], "=") == 0)
								{
									fscanf(pFile, "%d", &nIdxNumKey);
									for (int i = 0; i < m_nNumModel; i++)
									{
										if (m_apModel[i]) m_apModel[i]->SetMotionNumKey(nCntMotion, nIdxNumKey);
									}
								}
							}
							//キーセット
							else if (strcmp(&aString[0], "KEYSET") == 0)
							{
								int nFrame = 0;
								//フレーム数
								while (1)
								{
									fscanf(pFile, "%s", &aString[0]);
									if (strcmp(&aString[0], "FRAME") == 0)
									{
										fscanf(pFile, "%s", &aString[0]);
										if (strcmp(&aString[0], "=") == 0)
										{
											fscanf(pFile, "%d", &nFrame);
											for (int i = 0; i < m_nNumModel; i++)
											{
												if (m_apModel[i]) m_apModel[i]->SetFrame(nCntMotion, nKey, nFrame);
											}
										}
										break;
									}
								}
								//ここからキーフレームごとに全パーツ分KEYを読む
								for (int partIdx = 0; partIdx < m_nNumModel; partIdx++)
								{
									fscanf(pFile, "%s", &aString[0]);
									if (strcmp(&aString[0], "KEY") == 0)
									{
										float posx = 0, posy = 0, posz = 0;
										float rotx = 0, roty = 0, rotz = 0;
										bool posSet = false, rotSet = false;
										while (1)
										{
											fscanf(pFile, "%s", &aString[0]);
											if (strcmp(&aString[0], "POS") == 0)
											{
												fscanf(pFile, "%s", &aString[0]);
												if (strcmp(&aString[0], "=") == 0)
												{
													fscanf(pFile, "%f", &posx);
													fscanf(pFile, "%f", &posy);
													fscanf(pFile, "%f", &posz);
													posSet = true;
												}
											}
											else if (strcmp(&aString[0], "ROT") == 0)
											{
												fscanf(pFile, "%s", &aString[0]);
												if (strcmp(&aString[0], "=") == 0)
												{
													fscanf(pFile, "%f", &rotx);
													fscanf(pFile, "%f", &roty);
													fscanf(pFile, "%f", &rotz);
													rotSet = true;
												}
											}
											else if (strcmp(&aString[0], "END_KEY") == 0)
											{
												if (posSet && m_apModel[partIdx])
													m_apModel[partIdx]->SetKeyPos(nCntMotion, nKey, posx, posy, posz);
												if (rotSet && m_apModel[partIdx])
													m_apModel[partIdx]->SetKeyRot(nCntMotion, nKey, rotx, roty, rotz);
												break;
											}
										}
									}
								}
								// END_KEYSET
								fscanf(pFile, "%s", &aString[0]);
								nKey++;
							}
							// モーションセット終了
							else if (strcmp(&aString[0], "END_MOTIONSET") == 0)
							{
								nKey = 0;
								nCntMotion++;
								break;
							}
						}
					}

					if (strcmp(&aString[0], "END_SCRIPT") == 0)
					{
						// ファイルを閉じる
						fclose(pFile);
						break;
					}
				}
				break;
			}
		}
	}

	int nNumVtx;//頂点数
	DWORD sizeFVF;//頂点フォーマットのサイズ
	BYTE* pVtxBuff;//頂点バッファへのポインタ

	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		D3DXMATERIAL* pMat;//マテリアルへのポインタ

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)m_apModel[nCntModel]->GetBuffMat()->GetBufferPointer();

		//頂点数の取得
		nNumVtx = m_apModel[nCntModel]->GetMesh()->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(m_apModel[nCntModel]->GetMesh()->GetFVF());
		
		//頂点バッファのロック
		m_apModel[nCntModel]->GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//xの最大値比較
			if (vtx.x > m_vtxMax.x)
			{
				m_vtxMax.x = vtx.x;
			}

			//yの最大値比較
			if (vtx.y > m_vtxMax.y)
			{
				m_vtxMax.y = vtx.y;
			}

			//xの最大値比較
			if (vtx.z > m_vtxMax.z)
			{
				m_vtxMax.z = vtx.z;
			}

			//xの最小値比較
			if (vtx.x < m_vtxMin.x)
			{
				m_vtxMin.x = vtx.x;
			}

			//yの最小値比較
			if (vtx.y < m_vtxMin.y)
			{
				m_vtxMin.y = vtx.y;
			}

			//xの最小値比較
			if (vtx.z < m_vtxMin.z)
			{
				m_vtxMin.z = vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		//頂点バッファのアンロック
		m_apModel[nCntModel]->GetMesh()->UnlockVertexBuffer();
	}

	m_size = m_vtxMax - m_vtxMin;

	return S_OK;
}

//================================================
//終了処理
//================================================
void C3DPlayer::Uninit(void)
{
	//モデルの解放
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			m_apModel[nCnt]->Uninit();
			delete m_apModel[nCnt];
			m_apModel[nCnt] = nullptr;
		}
	}
}

//================================================
//更新処理
//================================================
void C3DPlayer::Update(void)
{
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	D3DXVECTOR3 CamRot;
	//カメラの取得
	CCamera* pCamera = CManager::GetCamera();

	CamRot = pCamera->GetRot();

	m_posOld = m_pos;

	if (pInputKeyboard->Repeat(DIK_DOWN) == true)
	{
		m_move.x += sinf(CamRot.y);
		m_move.z += cosf(CamRot.y);
		m_rotDest.y = CamRot.y - D3DX_PI;
	}
	else if (pInputKeyboard->Repeat(DIK_UP) == true)
	{
		m_move.x -= sinf(CamRot.y);
		m_move.z -= cosf(CamRot.y);
		m_rotDest.y = CamRot.y;

	}
	else if (pInputKeyboard->Repeat(DIK_RIGHT) == true)
	{
		m_move.z += sinf(CamRot.y);
		m_move.x -= cosf(CamRot.y);
		m_rotDest.y = CamRot.y + D3DX_PI * 0.5f;
	}
	else if (pInputKeyboard->Repeat(DIK_LEFT) == true)
	{
		m_move.z -= sinf(CamRot.y);
		m_move.x += cosf(CamRot.y);
		m_rotDest.y = CamRot.y - D3DX_PI * 0.5f;
	}

	//gameのRockとObject3Dを取得
	CRock* pRock = CGame::GetRock();

	//Object3Dを取得
	CObject3D* pObject3D = CManager::GetObject3D();

	// ジャンプ処理
	if (pInputKeyboard->Trigger(DIK_SPACE) == true)
	{
		// 足場の上にいるときだけジャンプ可能
		if (!m_bJump)
		{
			m_move.y += 4.0f;
			m_bJump = true;
		}
	}


	m_pos += m_move;

	//移動量を更新(減衰させる)
	m_move.x += (0.0f - m_move.x) * 0.17f;
	m_move.z += (0.0f - m_move.z) * 0.17f;

	m_pos = pRock->Colision(m_pos, m_posOld, m_size);


	//// 現在座標の地面の高さを取得
	//float groundY = 0.0f;
	//if (pObject3D) {
	//	groundY = pObject3D->GetHeightMesh(m_pos.x, m_pos.z);
	//}

	//float rockY = 0.0f;
	//if (pRock) {
	//	rockY = pRock->GetHeight(m_pos.x, m_pos.z);
	//}

	// 足場の高さを決定（地面と岩のうち高い方）
	//float platformY = (groundY > rockY) ? groundY : rockY;

	//// 現在座標の地面の高さを取得
	//float groundY = 0.0f;
	//if (pObject3D) {
	//	groundY = pObject3D->GetHeightMesh(m_pos.x, m_pos.z);
	//}

	//float rockY = 0.0f;
	//if (pRock) {
	//	rockY = pRock->GetHeight(m_pos.x, m_pos.z);
	//}

	//// ジャンプ処理
	//if (pInputKeyboard->Trigger(DIK_SPACE) == true)
	//{
	//	// 地面またはobject3Dの上にいるときだけジャンプ可能
	//	if (!m_bJump && fabs(m_pos.y - groundY) < 0.15f)
	//	{
	//		m_move.y += 4.0f;
	//		m_bJump = true;
	//	}
	//}



	if (m_rotDest.y - m_rot.y >= D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
	else if (m_rotDest.y - m_rot.y <= -D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}

	m_rot.y += (m_rotDest.y - m_rot.y) * 0.1f;



	m_move.y -= 0.1f;

	// 着地判定
	if (m_pos.y <=  0.0f)
	{
		m_pos.y = 0.0f;
		m_move.y = 0.0f;
		m_bJump = false;
	}

	//// 着地判定
	//if (m_pos.y <= platformY + 0.05f)
	//{
	//	m_pos.y = platformY;
	//	m_move.y = 0.0f;
	//	m_bJump = false;
	//}
	 
	
	//モデルの解放
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			m_apModel[nCnt]->Update();
		}
	}

	if (pInputKeyboard->Repeat(DIK_1)) {
		for (int i = 0; i < m_nNumModel; i++) {
			if (m_apModel[i]) m_apModel[i]->SetMotionType(CModel::MOTION_TYPE_NEUTRAL);
		}
	}
	else if (pInputKeyboard->Repeat(DIK_2)) {
		for (int i = 0; i < m_nNumModel; i++) {
			if (m_apModel[i]) m_apModel[i]->SetMotionType(CModel::MOTION_TYPE_MOVE);
		}
	}
	else if (pInputKeyboard->Repeat(DIK_3)) {
		for (int i = 0; i < m_nNumModel; i++) {
			if (m_apModel[i]) m_apModel[i]->SetMotionType(CModel::MOTION_TYPE_ONE);
		}
	}
	else if (pInputKeyboard->Repeat(DIK_4)) {
		for (int i = 0; i < m_nNumModel; i++) {
			if (m_apModel[i]) m_apModel[i]->SetMotionType(CModel::MOTION_TYPE_TWO);
		}
	}
	else if (pInputKeyboard->Repeat(DIK_5)) {
		for (int i = 0; i < m_nNumModel; i++) {
			if (m_apModel[i]) m_apModel[i]->SetMotionType(CModel::MOTION_TYPE_THREE);
		}
	}


	////プレイヤーがobject3Dの内側にいるとき
	//m_pos.y = pObject3D->GetHeightMesh(m_pos.x, m_pos.z);
}

//================================================
//描画処理
//================================================
void C3DPlayer::Draw(void)
{
	// デバイスの取得
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;
	D3DVIEWPORT9 viewportDef;
	D3DXMATRIX mtxViewDef, mtxProjectionDef;

	//現在のレンダリングターゲットを取得(保存)
	pDevice->GetRenderTarget(0, &pRenderDef);

	//現在のZバッファを取得(保存)
	pDevice->GetDepthStencilSurface(&pZBuffDef);

	//現在のビューポートを取得(保存)
	pDevice->GetViewport(&viewportDef);

	//現在のビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxViewDef);

	//現在のプロジェクションマトリックスを取得(保存)
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjectionDef);



	// プレイヤーの後方上空からプレイヤーを見るカメラ
	//D3DXVECTOR3 posV = m_pos + D3DXVECTOR3(-sinf(m_rot.y) * 200.0f, 100.0f, -cosf(m_rot.y) * 200.0f); // カメラ位置
	//D3DXVECTOR3 posR = m_pos; // 注視点（プレイヤーの位置）
	//D3DXVECTOR3 vecU = D3DXVECTOR3(0, 1, 0); // 上方向

	D3DXVECTOR3 posV = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	D3DXVECTOR3 posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	CManager::GetRenderer()->ChangeTarget(posV, posR, vecU);

	//レンダリングターゲット用のテクスチャのクリア
// 3DPlayer::Draw()の最初で
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(255, 0, 0, 255), 1.0f, 0);

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//// ワールドマトリックスの初期化
	//D3DXMatrixIdentity(&m_mtxWorld);

	////向きを反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	////位置を反映
	//D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	////ワールドマトリックスの設定
	//pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//// 各モデルの描画
	//for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	//{
	//	if (m_apModel[nCnt] != nullptr)
	//	{
	//		m_apModel[nCnt]->Draw();
	//	}
	//}

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 各モデルの描画
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			m_apModel[nCnt]->Draw();
		}
	}

	//レンダリングターゲットを元に戻す
	pDevice->SetRenderTarget(0, pRenderDef);
	//Zバッファを元に戻す
	pDevice->SetDepthStencilSurface(pZBuffDef);
	//ビューポートを元に戻す
	pDevice->SetViewport(&viewportDef);
	//ビューマトリックスを元に戻す
	pDevice->SetTransform(D3DTS_VIEW, &mtxViewDef);
	//プロジェクションマトリックスを元に戻す
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjectionDef);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 各モデルの描画
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			m_apModel[nCnt]->Draw();
		}
	}

}

//================================================
//生成処理
//================================================
C3DPlayer* C3DPlayer::Create()
{
	C3DPlayer* p3DPlayer = new C3DPlayer;

	p3DPlayer->Init();

	return p3DPlayer;
}

//================================================
//テクスチャロード処理
//================================================

//================================================
//テクスチャアンロード処理
//================================================


D3DXVECTOR3 C3DPlayer::GetPos(void)
{
	return m_pos;
}

D3DXVECTOR3 C3DPlayer::GetRot(void)
{
	return m_rot;
}

D3DXVECTOR3 C3DPlayer::GetMove(void)
{
	return m_move;
}

int C3DPlayer::GetWidth(void)
{
	return 0;
}

int C3DPlayer::GetHeight(void)
{
	return 0;
}
