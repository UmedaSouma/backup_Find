//===========================================================================================================================================================
// 
// エフェクトの処理 [effect.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "effect.h"
#include "manager.h"
#include "billboard.h"

//========================================================================================================================
// コンストラクタ
//========================================================================================================================
CEffect::CEffect(int nPrio):CBillboard(nPrio)
{
}

//========================================================================================================================
// デストラクタ
//========================================================================================================================
CEffect::~CEffect()
{
}

//========================================================================================================================
// 初期設定
//========================================================================================================================
HRESULT CEffect::Init()
{
	int Idx = 0;
	Idx = CManager::GetTexture()->Regist("data\\TEXTURE\\shadow000.jpg");
	BindTexture(CManager::GetTexture()->GetAddress(Idx));

	// 寿命設定
	m_nLife = m_nMaxLife;

	CBillboard::Init();
	return S_OK;
}

//========================================================================================================================
// 終了処理
//========================================================================================================================
void CEffect::Uninit()
{
	CBillboard::Uninit();
}

//========================================================================================================================
// 更新処理
//========================================================================================================================
void CEffect::Update()
{
	if (m_nLife == -1)
	{
	}
	else if (m_nLife <= 0)
	{
		Uninit();
	}
	else
	{
		m_nLife--;
	}

	CBillboard::Update();
}

//========================================================================================================================
// 描画処理
//========================================================================================================================
void CEffect::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// Zの比較方法
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// Zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	CBillboard::Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// Zの比較方法
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// Zバッファに書き込む
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//========================================================================================================================
// 生成処理
//========================================================================================================================
CEffect* CEffect::Create(D3DXVECTOR3 pos, int nLife)
{
	CEffect* pEffect = new CEffect;
	pEffect->SetPos(pos);
	pEffect->m_nMaxLife = nLife;

	pEffect->Init();

	return pEffect;
}