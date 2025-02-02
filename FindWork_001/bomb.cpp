//===========================================================================================================================================================
// 
// 爆弾の処理 [bomb.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "bomb.h"
#include "explosion.h"
#include "manager.h"

//========================================================================================================================
// コンストラクタ
//========================================================================================================================
CBomb::CBomb() :
	m_nExplCnt(0)
	, m_nExplTargetTime(0)
{
}

//========================================================================================================================
// デストラクタ
//========================================================================================================================
CBomb::~CBomb()
{
}

//========================================================================================================================
// 初期設定
//========================================================================================================================
HRESULT CBomb::Init()
{
	CFixedValue* pFix = CManager::GetFixValue();
	const char* pass = nullptr;	// モデルのパス

	if (pFix != nullptr) 
	{ 
		pass = pFix->GetBomb()->MODEL_PASS;	// パスを持ってくる
	}

	SetModel(pass);	// モデルを設定
	SetSize({ 10.0f,10.0f,30.0f });

	CModel::Init();
	
	return S_OK;
}

//========================================================================================================================
// 終了処理
//========================================================================================================================
void CBomb::Uninit()
{
	CModel::Uninit();
}

//========================================================================================================================
// 更新処理
//========================================================================================================================
void CBomb::Update()
{
	CModel::Update();

	CFixedValue* pFix = CManager::GetFixValue();
	int time = 0;	// 爆発持続時間

	if (pFix != nullptr)
	{
		time = pFix->GetBomb()->EXPLOSION_TIME;
	}

	if (m_nExplTargetTime <= m_nExplCnt)
	{// 設定した時間に達したら

		// memo :: ここで爆発を生成する
		CExplosion::Create(GetPos(), time);

		Uninit();	// 爆弾を消す
	}
	else
	{// 設定した時間に達していない場合
		m_nExplCnt++;	// カウントを進める
	}
}

//========================================================================================================================
// 描画処理
//========================================================================================================================
void CBomb::Draw()
{
	MeshColl();

	CModel::Draw();
}

//========================================================================================================================
// 生成処理
//========================================================================================================================
CBomb* CBomb::Create(D3DXVECTOR3 pos, int time)
{
	CBomb* pBomb = new CBomb;

	pBomb->m_nExplTargetTime = time;	// 爆発時間を設定する
	pBomb->SetPos(pos);

	pBomb->Init();

	return pBomb;
}