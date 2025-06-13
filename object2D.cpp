//==================================================================
//
//�I�u�W�F�N�g2D���� [object2D.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//�C���N���[�h
//================================================
#include "object2D.h"
#include "renderer.h"
#include "manager.h"

//================================================
//�R���X�g���N�^
//================================================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
}

//================================================
//�f�X�g���N�^
//================================================
CObject2D::~CObject2D()
{
}

//================================================
// ����������
//================================================
HRESULT CObject2D::Init(void)
{
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	// ���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	CObject2D::BindTexture(m_pTexture);

	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ��]�Ή��̒��_���W�v�Z
	float halfW = m_width * 0.5f;
	float halfH = m_height * 0.5f;
	float angle = m_rot.z;

	D3DXVECTOR2 local[4] = {
		D3DXVECTOR2(-halfW, -halfH), // ����
		D3DXVECTOR2(halfW, -halfH), // �E��
		D3DXVECTOR2(-halfW,  halfH), // ����
		D3DXVECTOR2(halfW,  halfH)  // �E��
	};

	for (int i = 0; i < 4; ++i) {
		float x = local[i].x * cosf(angle) - local[i].y * sinf(angle);
		float y = local[i].x * sinf(angle) + local[i].y * cosf(angle);
		pVtx[i].pos = D3DXVECTOR3(m_pos.x + x, m_pos.y + y, 0.0f);
	}

	// rhw�̐ݒ�
	for (int i = 0; i < 4; ++i) pVtx[i].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	for (int i = 0; i < 4; ++i) pVtx[i].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �A�j���[�V�����p�e�N�X�`�����W�̌v�Z
	float u = 0.0f, v = 0.0f, uw = 1.0f, vh = 1.0f;
	if (m_animeFrameU > 1 || m_animeFrameV > 1) {
		int index = m_animePattern;
		u = (float)(index % m_animeFrameU) / m_animeFrameU;
		v = (float)(index / m_animeFrameU) / m_animeFrameV;
		uw = 1.0f / m_animeFrameU;
		vh = 1.0f / m_animeFrameV;
	}

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(u, v);
	pVtx[1].tex = D3DXVECTOR2(u + uw, v);
	pVtx[2].tex = D3DXVECTOR2(u, v + vh);
	pVtx[3].tex = D3DXVECTOR2(u + uw, v + vh);

	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//�I������
//================================================
void CObject2D::Uninit(void)
{
	m_pTexture = NULL;

	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CObject::Release();
}

//================================================
// �X�V����
//================================================
void CObject2D::Update(void)
{
	bool needUpdateVertex = false;

	if (m_drawtype == TYPE_SCROLL) {
		// UV�X�N���[���l�����Z
		m_scrollPosX += m_scrollSpeedX;
		m_scrollPosY += m_scrollSpeedY;

		// 0.0�`1.0�͈̔͂Ń��[�v
		if (m_scrollPosX >= 1.0f) m_scrollPosX -= 1.0f;
		if (m_scrollPosX < 0.0f) m_scrollPosX += 1.0f;
		if (m_scrollPosY >= 1.0f) m_scrollPosY -= 1.0f;
		if (m_scrollPosY < 0.0f) m_scrollPosY += 1.0f;

		needUpdateVertex = true;
	}

	if (m_drawtype == TYPE_ANIME) {
		m_animeCounter++;
		if (m_animeFrameU > 1 || m_animeFrameV > 1) {
			if (m_animeCounter % 5 == 0) {
				m_animePattern = (m_animePattern + 1) % (m_animeFrameU * m_animeFrameV);
				needUpdateVertex = true;
			}
		}
	}

	needUpdateVertex = true;

	if (needUpdateVertex) {
		VERTEX_2D* pVtx;
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ��]�Ή��̒��_���W�v�Z
		float halfW = m_width * 0.5f;
		float halfH = m_height * 0.5f;
		float angle = m_rot.z;

		D3DXVECTOR2 local[4] = {
			D3DXVECTOR2(-halfW, -halfH),
			D3DXVECTOR2(halfW, -halfH),
			D3DXVECTOR2(-halfW,  halfH),
			D3DXVECTOR2(halfW,  halfH)
		};

		for (int i = 0; i < 4; ++i) {
			float x = local[i].x * cosf(angle) - local[i].y * sinf(angle);
			float y = local[i].x * sinf(angle) + local[i].y * cosf(angle);
			pVtx[i].pos = D3DXVECTOR3(m_pos.x + x, m_pos.y + y, 0.0f);
		}

		// UV�X�N���[��
		float u = m_scrollPosX;
		float v = m_scrollPosY;
		float uw = 1.0f, vh = 1.0f;
		if (m_animeFrameU > 1 || m_animeFrameV > 1) {
			int index = m_animePattern;
			u += (float)(index % m_animeFrameU) / m_animeFrameU;
			v += (float)(index / m_animeFrameU) / m_animeFrameV;
			uw = 1.0f / m_animeFrameU;
			vh = 1.0f / m_animeFrameV;
		}
		pVtx[0].tex = D3DXVECTOR2(u, v);
		pVtx[1].tex = D3DXVECTOR2(u + uw, v);
		pVtx[2].tex = D3DXVECTOR2(u, v + vh);
		pVtx[3].tex = D3DXVECTOR2(u + uw, v + vh);

		m_pVtxBuff->Unlock();
	}
}

//================================================
//�`�揈��
//================================================
void CObject2D::Draw(void)
{
	CRenderer* renderer;

	renderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = renderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//================================================
//�e�N�X�`����������
//================================================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//================================================
// ��������
//================================================
CObject2D* CObject2D::Create(
	DRAW_TYPE type,
	int width,
	int height,
	float scrollX,
	float scrollY,
	int animeFrameU,
	int animeFrameV,
	int animePattern,
	float posX,
	float posY,
	float rotZ
)
{
	CObject2D* pObject2D = new CObject2D;
	pObject2D->m_drawtype = type;
	pObject2D->m_width = width;
	pObject2D->m_height = height;
	pObject2D->m_scrollSpeedX = scrollX;
	pObject2D->m_scrollSpeedY = scrollY;
	pObject2D->m_scrollPosX = 0.0f;
	pObject2D->m_scrollPosY = 0.0f;
	pObject2D->m_animeFrameU = animeFrameU;
	pObject2D->m_animeFrameV = animeFrameV;
	pObject2D->m_animePattern = animePattern;
	pObject2D->m_pos = D3DXVECTOR2(posX, posY);
	pObject2D->m_rot.z = rotZ;
	pObject2D->Init();
	return pObject2D;
}



