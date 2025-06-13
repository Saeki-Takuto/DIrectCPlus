//==================================================================
//
//3D�v���C���[���� [3Dplayer.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//�C���N���[�h
//================================================
#include "3Dplayer.h"
#include "renderer.h"
#include "manager.h"

//================================================
//�ÓI�����o�ϐ�
//================================================

//================================================
//�R���X�g���N�^
//================================================
C3DPlayer::C3DPlayer()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		m_apModel[nCnt] = NULL; //���f���̏�����
	}

	m_nNumModel = NULL;

}

//================================================
//�f�X�g���N�^
//================================================
C3DPlayer::~C3DPlayer()
{
}

//================================================
//����������
//================================================
HRESULT C3DPlayer::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�t�@�C�����J��
	FILE* pFile = NULL;

	//�t�@�C�����J��
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
			{//SCRIPT�ǂݎ��

				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "NUM_MODEL") == 0)
					{// NUM_MODEL�ǂݎ��
						fscanf(pFile, "%s", &aString[0]);

						if (strcmp(&aString[0], "=") == 0)
						{//�l����
							fscanf(pFile, "%d", &nModel);
						}
					}
					else if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
					{
						// MODEL_FILENAME�ǂݎ��
						fscanf(pFile, "%s", &aString[0]);

						if (strcmp(&aString[0], "=") == 0)
						{// ���

							//�������ǂݍ���
							fscanf(pFile, "%s", &aString[0]);

							const char* MODEL_FILE = {};	//���f���t�@�C�����i�[�ϐ�

							//�������ۑ�����
							MODEL_FILE = aString;

							m_apModel[nCnt] = CModel::Create(MODEL_FILE);

							nCnt++; //nCnt���C���N�������g
						}
					}
					else if (strcmp(&aString[0], "CHARACTERSET") == 0)
					{
						while (1)
						{
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "NUM_PARTS") == 0)
							{// NUM_PARTS�ǂݍ���

								fscanf(pFile, "%s", &aString[0]);

								if (strcmp(&aString[0], "=") == 0)
								{//�l����
									fscanf(pFile, "%d", &m_nNumModel);
								}
							}
							else if (strcmp(&aString[0], "PARTSSET") == 0)
							{
								while (1)
								{
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(&aString[0], "INDEX") == 0)
									{//INDEX��ǂݎ��

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{//���
											fscanf(pFile, "%d", &nIdx);
										}
									}

									if (strcmp(&aString[0], "PARENT") == 0)
									{//PARENT�ǂݎ��

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{// ���
											//�e
											int nParent;
											fscanf(pFile, "%d", &nParent);
											if (nParent < 0)
											{//0�ȉ�(��{��-1)�̏ꍇ(NULL)
												m_apModel[nIdx]->SetParent(NULL);
											}
											else
											{//�e���f�����w�肳��Ă���ꍇ
												m_apModel[nIdx]->SetParent(m_apModel[nParent]);
											}
										}
									}

									if (strcmp(&aString[0], "POS") == 0)
									{//POS�ǂݎ��

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{//���W����
											D3DXVECTOR3 nIdxPos;
											fscanf(pFile, "%f", &nIdxPos.x);
											fscanf(pFile, "%f", &nIdxPos.y);
											fscanf(pFile, "%f", &nIdxPos.z);

											m_apModel[nIdx]->SetPos(nIdxPos);
										}
									}

									if (strcmp(&aString[0], "ROT") == 0)
									{//ROT�ǂݎ��

										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(&aString[0], "=") == 0)
										{//�p�x����
											D3DXVECTOR3 nIdxRot;
											fscanf(pFile, "%f", &nIdxRot.x);
											fscanf(pFile, "%f", &nIdxRot.y);
											fscanf(pFile, "%f", &nIdxRot.z);

											m_apModel[nIdx]->SetRot(nIdxRot);
										}
									}

									if (strcmp(&aString[0], "END_PARTSSET") == 0)
									{// END_PARTSSET�ǂݎ��
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
						//���[�v�t���O�ƃL�[���̏�����
						while (1)
						{
							fscanf(pFile, "%s", &aString[0]);

							// ���[�v�t���O
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
							//�L�[��
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
							//�L�[�Z�b�g
							else if (strcmp(&aString[0], "KEYSET") == 0)
							{
								int nFrame = 0;
								//�t���[����
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
								//��������L�[�t���[�����ƂɑS�p�[�c��KEY��ǂ�
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
							// ���[�V�����Z�b�g�I��
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
						// �t�@�C�������
						fclose(pFile);
						break;
					}
				}
				break;
			}
		}
	}
	return S_OK;
}

//================================================
//�I������
//================================================
void C3DPlayer::Uninit(void)
{
	//���f���̉��
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
//�X�V����
//================================================
void C3DPlayer::Update(void)
{
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	D3DXVECTOR3 CamRot;
	//�J�����̎擾
	CCamera* pCamera = CManager::GetCamera();

	CamRot = pCamera->GetRot();

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

	if (m_rotDest.y - m_rot.y >= D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
	else if (m_rotDest.y - m_rot.y <= -D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}

	m_rot.y += (m_rotDest.y - m_rot.y) * 0.1f;

	m_pos += m_move;

	//�ړ��ʂ��X�V(����������)
	m_move.x += (0.0f - m_move.x) * 0.17f;
	m_move.z += (0.0f - m_move.z) * 0.17f;

	//���f���̉��
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

}

//================================================
//�`�揈��
//================================================
void C3DPlayer::Draw(void)
{
	// �f�o�C�X�̎擾
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �e���f���̕`��
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			m_apModel[nCnt]->Draw();
		}
	}
}

//================================================
//��������
//================================================
C3DPlayer* C3DPlayer::Create()
{
	C3DPlayer* p3DPlayer = new C3DPlayer;

	p3DPlayer->Init();

	return p3DPlayer;
}

//================================================
//�e�N�X�`�����[�h����
//================================================

//================================================
//�e�N�X�`���A�����[�h����
//================================================


D3DXVECTOR2 C3DPlayer::GetPos(void)
{
	return D3DXVECTOR2();
}

int C3DPlayer::GetWidth(void)
{
	return 0;
}

int C3DPlayer::GetHeight(void)
{
	return 0;
}
