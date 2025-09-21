#include "fade.h"
#include "renderer.h"
#include "manager.h"

CFade::FADE CFade::m_fade = CFade::FADE_NONE; // 初期状態は何もしていない状態


CFade::CFade()
{
	m_fade = FADE_NONE;
	m_pVtxBuff = nullptr;
	m_color = D3DXCOLOR(0, 0, 0, 0);
	m_pScene = nullptr;
	m_mode = CScene::MODE_NONE; // 初期モードはNONE
}

CFade::~CFade()
{
	Uninit();
}

HRESULT CFade::Init()
{
	VERTEX_2D* pVtx;							//頂点情報へのポインタ

	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(m_color);
	pVtx[1].col = D3DXCOLOR(m_color);
	pVtx[2].col = D3DXCOLOR(m_color);
	pVtx[3].col = D3DXCOLOR(m_color);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

void CFade::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	if (m_pScene != nullptr)
	{
		delete m_pScene;
		m_pScene = nullptr;
	}
	m_fade = FADE_NONE;
}

void CFade::Update()
{
	VERTEX_2D* pVtx;							//頂点情報へのポインタ

	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN) 
		{//フェードイン状態
			m_color.a -= 0.11f;//ポリゴンを透明にしていく
			if (m_color.a <= 0.0f)
			{
				m_color.a = 0.0f;
				m_fade = FADE_NONE;//何もしていない状態に
			}
		}
		else if (m_fade == FADE_OUT)
		{//フェードアウト状態
			m_color.a += 0.11f;//ポリゴンを不透明にしていく
			if (m_color.a >= 1.0f)
			{
				m_color.a = 1.0f;
				//モード設定(次の画面に移行)
				CManager::SetMode(m_mode);
				m_fade = FADE_IN;//フェードイン状態に
			}
		}

		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(m_color);
		pVtx[1].col = D3DXCOLOR(m_color);
		pVtx[2].col = D3DXCOLOR(m_color);
		pVtx[3].col = D3DXCOLOR(m_color);

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}

}

void CFade::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ解除
	pDevice->SetTexture(0, nullptr);

	// テクスチャステージをカラーのみ（頂点カラー）に設定
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);

	// 頂点バッファ・FVF・カラー設定は従来通り
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// 必要なら、描画後にテクスチャステージを元に戻す
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
}

CFade* CFade::Create()
{
	return nullptr;
}

void CFade::SetFade(CScene::MODE pmode)
{
	if (GetFade() != FADE_OUT)
	{
		m_fade = FADE_OUT;//フェードアウト状態に
		m_mode = pmode;//次の画面(モード)を設定
		m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//黒いポリゴン(透明)にしておく
	}
}