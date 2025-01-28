//===========================================================================================================================================================
// 
// ゴールのモデルとゴール処理 [goal.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "goal.h"
#include "search.h"
#include "collision.h"
#include "manager.h"

std::vector<int> g_aa;

//========================================================================================================================
// コンストラクタ
//========================================================================================================================
CGoal::CGoal(int nPrio) :CModel(nPrio),
m_runtype(RUN_NONE)
, m_nOrder{ -1,-1 }
, m_DireTravel(0)
, m_nLaps(0)
{
	g_aa.clear();
}

//========================================================================================================================
// デストラクタ
//========================================================================================================================
CGoal::~CGoal()
{
}

//========================================================================================================================
// 初期設定
//========================================================================================================================
HRESULT CGoal::Init()
{
	SetModel("data\\MODEL\\goal.x");
	SetPos({ 200,0,0 });


	SetScale(GetScale() * 1.2f);

	CModel::Init();

	SetType(GOAL);

	return S_OK;
}

//========================================================================================================================
// 終了処理
//========================================================================================================================
void CGoal::Uninit()
{
	CModel::Uninit();
}

//========================================================================================================================
// 更新処理
//========================================================================================================================
void CGoal::Update()
{
	CCarPlayer* pPlayer = nullptr;
	pPlayer = CSearch::SearchObject(pPlayer, CObject::CAR_PLAYER);

	if (pPlayer == nullptr)
	{ return; }

	D3DXVECTOR3 Fpos = GetPos();
	D3DXVECTOR3 Lpos = GetPos();
	D3DXVECTOR3 RePos = GetPos();
	D3DXVECTOR3 size = { 500.0f,500.0f,50.0f };
	Fpos.z -= 300.0f;	// ゴールから見て一番手前のポイント
	Lpos.z -= 100.0f;	// ゴールに近い手前
	RePos.z += 100.0f;	// ポイントに着いた履歴をリセットする

	// それぞれのポイントに到達したとき
	if (CCollision::BoxTrigger(Fpos, size, pPlayer->GetPos(), pPlayer->GetSize()))
	{
		GoalPointOrder(POINT_IN_FRONT);
	}
	if (CCollision::BoxTrigger(Lpos, size, pPlayer->GetPos(), pPlayer->GetSize()))
	{
		GoalPointOrder(POINT_IN_BACK);
	}
	if (CCollision::BoxTrigger(RePos, size, pPlayer->GetPos(), pPlayer->GetSize()))
	{
		for (int i = 0; i < ORDER_MAX; i++)
		{
			m_nOrder[i] = -1;	// 順番リセット
		}
	}

	if (m_DireTravel == RUN_FRONT)
	{// 正しく走行した時
		m_DireTravel = RUN_NONE;	// リセットする
		m_nLaps += 1;	// 周回数を増やす
	}

	// 回数分ゴールまで到達したら
	if (m_nLaps == GOAL_LAPS)
	{
		CFade* pFade = CManager::GetFade();
		pFade->SetFade(CScene::MODE_RESULT);
	}
	
	
	//if (CCollision::BoxTrigger(Fpos, size, pPlayer->GetPos(), pPlayer->GetSize()))
	//{
	//	g_aa.push_back(1);

	//	/*RUNTYPE runtype = RUN_NONE;
	//	runtype = CollisionGoalPlayer(pPlayer);

	//	switch (runtype)
	//	{
	//	case RUN_BACK:

	//		break;

	//	case RUN_FRONT:
	//	case RUN_NONE:

	//		CFade* pFade = CManager::GetFade();
	//		pFade->SetFade(CScene::MODE_RESULT);

	//		break;
	//	}	*/
	//}

	//if (CCollision::BoxTrigger(Lpos, size, pPlayer->GetPos(), pPlayer->GetSize()))
	//{
	//	g_aa.push_back(2);
	//}

	//int bb = 0;
	//int b = 0;
	//int i = 0;
	//for (auto itr = g_aa.rbegin(); itr != g_aa.rend(); ++itr)
	//{
	//	if (i == 0)
	//	{
	//		bb = *itr;
	//	}
	//	if (i == 1)
	//	{
	//		b = *itr;
	//	}
	//	i++;
	//}

	//if (bb == 2 && b == 1)
	//{
	//	CFade* pFade = CManager::GetFade();
	//	pFade->SetFade(CScene::MODE_RESULT);
	//}


	CModel::Update();
}

//========================================================================================================================
// 描画処理
//========================================================================================================================
void CGoal::Draw()
{
	CModel::Draw();
}

//========================================================================================================================
// ゴールとプレイヤーの当たり判定
//========================================================================================================================
CGoal::RUNTYPE CGoal::CollisionGoalPlayer(CCarPlayer* pPlayer)
{
	D3DXVECTOR3 oldpos = pPlayer->GetOldPos();
	RUNTYPE runtype = RUN_NONE;

	if (oldpos.z > pPlayer->GetPos().z)
	{
		runtype = RUN_BACK;
	}
	else if (oldpos.z < pPlayer->GetPos().z)
	{
		runtype = RUN_FRONT;
	}

	return runtype;
}

//===========================================================================================================
// ゴールポイントの順番を出す関数
//===========================================================================================================
void CGoal::GoalPointOrder(GOAL_POINT point)
{
	// ラストが同じであればここは通さない
	// ずっと同じ所を押すのを回避するため
	if (m_nOrder[ORDER_LAST] == point)
	{ return; }

	// 順番を更新する
	m_nOrder[ORDER_FIRST] = m_nOrder[ORDER_LAST];
	m_nOrder[ORDER_LAST] = point;
	
	{// 順番による計算結果を反映
		if (m_nOrder[ORDER_FIRST] == POINT_IN_FRONT
			&& m_nOrder[ORDER_LAST] == POINT_IN_BACK)
		{
			m_DireTravel += 1;
		}

		if (m_nOrder[ORDER_FIRST] == POINT_IN_BACK
			&& m_nOrder[ORDER_LAST] == POINT_IN_FRONT)
		{
			m_DireTravel -= 1;
		}
	}
}

//========================================================================================================================
// 生成処理
//========================================================================================================================
CGoal* CGoal::Create()
{
	CGoal* pGoal = new CGoal;
	pGoal->Init();

	return pGoal;
}