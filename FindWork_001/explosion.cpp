//===========================================================================================================================================================
// 
// 爆発の処理 [explosion.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "explosion.h"
#include "collision.h"
#include "car_player.h"
#include "search.h"
#include "manager.h"

//========================================================================================================================
// コンストラクタ
//========================================================================================================================
CExplosion::CExplosion() :
	m_nTargetCnt(0)
	, m_nExpansionCnt(0)
{
}

//========================================================================================================================
// デストラクタ
//========================================================================================================================
CExplosion::~CExplosion()
{
}

//========================================================================================================================
// 初期設定
//========================================================================================================================
HRESULT CExplosion::Init()
{
	SetModel("data\\MODEL\\sphere_000.x");
	SetSize({ 10.0f,10.0f,10.0f });

	CModel::Init();
	return S_OK;
}

//========================================================================================================================
// 終了処理
//========================================================================================================================
void CExplosion::Uninit()
{
	CModel::Uninit();
}

//========================================================================================================================
// 更新処理
//========================================================================================================================
void CExplosion::Update()
{
	CModel::Update();

	float nScale = 5;

	if (m_nTargetCnt <= m_nExpansionCnt)
	{// 設定した時間に達したら
		Uninit();	// 爆発を消す
	}
	else
	{// 設定した時間に達していない場合
		m_nExpansionCnt++;						// カウントを進める
		nScale += (1.0f* m_nExpansionCnt);		// カウントが増えるごとにスケールを多くしていく
		SetScale({ nScale ,nScale ,nScale });	// スケールを適用する
	}

	// プレイヤーを取得
	CCarPlayer* pPlayer = nullptr;
	pPlayer = CSearch::SearchObject(pPlayer, CObject::TYPE::CAR_PLAYER);

	// プレイヤーが存在しなかったらこの後ろの処理を飛ばす
	if(pPlayer==nullptr)
	{	return;	}

	// 爆発との当たり判定
	if (CCollision::SphereTrigger(					// 円の当たり判定 < memo > 今後球にする
		pPlayer->GetPos(), pPlayer->GetSize().x,	// プレイヤー
		GetPos(), GetSize().x * nScale))			// 爆発
	{
		pPlayer->ActionDown();
	}
}

//========================================================================================================================
// 描画処理
//========================================================================================================================
void CExplosion::Draw()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);	// 法線の正規化
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	// 両面描画

	CModel::Draw();

	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);	// 元に戻す
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	// 反時計回りを裏面とする(表面だけ描画
}

//========================================================================================================================
// 生成処理
//========================================================================================================================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, int Expantion)
{
	CExplosion* pExplosion = new CExplosion;

	pExplosion->m_nTargetCnt = Expantion;
	pExplosion->SetPos(pos);

	pExplosion->Init();

	return pExplosion;
}