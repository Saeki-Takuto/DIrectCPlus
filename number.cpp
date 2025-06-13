//==================================================================
//
//�������� [number.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//�C���N���[�h
//================================================
#include "number.h"
#include "renderer.h"
#include "manager.h"

//================================================
//�R���X�g���N�^
//================================================
CNumber::CNumber(int nPriority) : CObject(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
}

//================================================
//�f�X�g���N�^
//================================================
CNumber::~CNumber()
{
}

//================================================
// ����������
//================================================
HRESULT CNumber::Init(void)
{
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	// ���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DIGIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	CNumber::BindTexture(m_pTexture);

	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < MAX_DIGIT; nCntTime++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//�I������
//================================================
void CNumber::Uninit(void)
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
void CNumber::Update(void)
{
	int digit = GetDigit();
	int value = GetValue();

	// �e���̐������E���珇�Ɏ擾
	int tempValue = value;
	int digits[16] = { 0 };
	for (int i = digit - 1; i >= 0; --i) {
		digits[i] = tempValue % 10;
		tempValue /= 10;
	}

	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < digit; ++i)
	{
		// UV�̂ݍĐݒ�i���W��T�C�Y��Create�ŌŒ�ς݁j
		float tu = 0.1f * digits[i];
		pVtx[0].tex = D3DXVECTOR2(tu, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(tu + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(tu, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(tu + 0.1f, 1.0f);

		pVtx += 4;
	}
	m_pVtxBuff->Unlock();
}

//================================================
//�`�揈��
//================================================
void CNumber::Draw(void)
{
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0, m_pTexture);

	// �e�����`��
	for (int i = 0; i < GetDigit(); ++i) {
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * i, 2);
	}
}

//================================================
//�e�N�X�`����������
//================================================
void CNumber::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//================================================
// ��������
//================================================
void CNumber::Create(
	int digit,
	int value,
	const D3DXVECTOR2& center,
	LPDIRECT3DTEXTURE9 tex,
	float width,
	float height,
	float spacing
)
{
	SetDigit(digit);
	SetValue(value);
	SetPos(center);
	SetTexture(tex);
	SetWidth(width);
	SetHeight(height);
	SetSpacing(spacing);

	float totalWidth = digit * width + (digit - 1) * spacing;
	float leftX = center.x - totalWidth / 2.0f;
	float y = center.y - height / 2.0f;

	// �e���̐������E���珇�Ɏ擾
	int tempValue = value;
	int digits[16] = { 0 };
	for (int i = digit - 1; i >= 0; --i) {
		digits[i] = tempValue % 10;
		tempValue /= 10;
	}

	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < digit; ++i)
	{
		float x = leftX + i * (width + spacing);

		pVtx[0].pos = D3DXVECTOR3(x, y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(x + width, y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(x, y + height, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(x + width, y + height, 0.0f);

		pVtx[0].rhw = pVtx[1].rhw = pVtx[2].rhw = pVtx[3].rhw = 1.0f;
		pVtx[0].col = pVtx[1].col = pVtx[2].col = pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		float tu = 0.1f * digits[i];
		pVtx[0].tex = D3DXVECTOR2(tu, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(tu + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(tu, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(tu + 0.1f, 1.0f);

		pVtx += 4;
	}
	m_pVtxBuff->Unlock();
}
