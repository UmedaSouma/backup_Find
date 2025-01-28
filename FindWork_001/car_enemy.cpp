//===========================================================================================================================================================
// 
// 敵の車 [car_enemy.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "car_enemy.h"
#include "car_player.h"
#include "search.h"
#include "manager.h"
#include "collision.h"
#include "course_point.h"
#include "search.h"
#include "text.h"
#include "manager.h"
#include "calculation.h"
#include "backlight.h"
#include "countdown.h"
#include "game.h"
#include "bomb.h"
#include <random>

//========================================================================================================================
// コンストラクタ
//========================================================================================================================
CCarEnemy::CCarEnemy() :
	m_nCnt(0),
	m_bRouteClear(true),
	m_NextRoute({ 0.0f,0.0f,0.0f }),
	m_NextIdx(-1)
{
}

//========================================================================================================================
// デストラクタ
//========================================================================================================================
CCarEnemy::~CCarEnemy()
{
}

//========================================================================================================================
// 初期設定
//========================================================================================================================
HRESULT CCarEnemy::Init()
{
	InitRandTargetPoint();

	SetType(TYPE::CAR_ENEMY);
	SetSize({ 10.0f,10.0f,30.0f });
	SetGravity(true);
	CCar::Init();

	return S_OK;
}

//========================================================================================================================
// 終了処理
//========================================================================================================================
void CCarEnemy::Uninit()
{
	CCar::Uninit();
}

//========================================================================================================================
// 更新処理
//========================================================================================================================
void CCarEnemy::Update()
{
	CCountdown* pCD = CGame::GetCountDown();
	if (pCD != nullptr)
	{
		if (pCD->GetUse())
		{
			return;
		}
	}

	CCar::Update();

	// 車がダウン状態だったら以降の処理をしない
	if (GetActionState() == CCar::ACTION_STATE::DOWN) 
	{ return; }

	BlowAwayPtoE();
	//BlowAwayEtoE();

	if (GetDeath())
	{ return; }

	Route();

	TargetRouteUpdate();

}

//========================================================================================================================
// 描画処理
//========================================================================================================================
void CCarEnemy::Draw()
{
	CCar::Draw();
}

//===========================================================================================================
// ぶっ飛ばされる処理(プレイヤーと敵)
//===========================================================================================================
void CCarEnemy::BlowAwayPtoE()
{
	CCarPlayer* pCarP = nullptr;
	pCarP = CSearch::SearchObject(pCarP, CObject::TYPE::CAR_PLAYER);

	// プレイヤーが存在しなかったら処理は通さない
	if (pCarP == nullptr)
	{	return;	};
	
	// 当たったら
	//if (CCollision::BoxTrigger(pCarP->GetPos(), pCarP->GetSize(), GetPos(), GetSize()))
	if (CCollision::SphereTrigger(pCarP->GetPos(),30, GetPos(), 30))
	{
		D3DXVECTOR3 move = { 0,0,0 };

		// 現在のプレイヤーの速度
		float Speed = pCarP->GetAccumulationSpeed();
		float eSpeed = GetAccumulationSpeed();

		// プレイヤーと当たった車の位置で角度を算出する
		float ResultRot = 0.0f;		// 計算結果を入れる変数
		float Z = pCarP->GetPos().z - GetPos().z;	// Zの大きさを測る
		float X = pCarP->GetPos().x - GetPos().x;	// Xの大きさを測る
		ResultRot = atan2f(X, Z);	// 計算

		float R = Speed - eSpeed;

	
		if(R <= 0)
		{
			if (!GetDeath()) 
			{ return; }
			move = pCarP->GetMove();

			eSpeed *= 1.f;

			//// スピードの分飛ばす
			//pCarP->SetMove({
			//	(sinf(D3DX_PI - ResultRot) * -eSpeed) + -move.x,
			//	(eSpeed * 0.01f) + move.y ,
			//	(cosf(D3DX_PI - ResultRot) * eSpeed) + -move.z
			//	});
		}
		else
		{
			move = GetMove();

			Speed *= 0.5f;

			if (GetTypeCar() == CParamStorage::TYPE::CAR_BOMB)
			{
				pCarP->ActionDown();

				D3DXVECTOR3 pos = GetPos();
				pos.y += 100;

				CBomb::Create(pos, 1);
				Uninit();
			}

			// スピードの分飛ばす
			SetMove({
				(sinf(D3DX_PI - ResultRot) * -Speed) + move.x,
				(Speed * 1.f) + move.y ,
				(cosf(D3DX_PI - ResultRot) * Speed) + move.z
				});

			if (GetTypeCar() != CParamStorage::CAR_BOMB)
			{
				// 車変更
				pCarP->ChangeCar(GetTypeCar());
			}

			pCarP->ActionTurbo();

			pCarP->SetRecoveryGauge(1000);

			if (!GetDeath())
			{
				SetDeath();	// もう使わない！！
			}
		}
		

		
	}
}

//===========================================================================================================
// ぶっ飛ばされる処理(敵と敵)
//===========================================================================================================
void CCarEnemy::BlowAwayEtoE()
{
	std::vector<CCarEnemy*>pEnemy;
	pEnemy.clear();

	pEnemy = CSearch::SearchMultiObject(pEnemy, CObject::CAR_ENEMY);
	if (pEnemy.empty()) { return; }

	unsigned int eSize = pEnemy.size();
	for (unsigned int i = 0; i < eSize; i++)
	{
		if(pEnemy[i]==this)
		{// 同じオブジェクトだったら判定しない
			return;
		}

		if (CCollision::BoxTrigger(pEnemy[i]->GetPos(), pEnemy[i]->GetSize(), GetPos(), GetSize()))
		{
			D3DXVECTOR3 move = GetMove();

			// 現在のプレイヤーの速度
			float Speed = pEnemy[i]->GetAccumulationSpeed();

			// プレイヤーと当たった車の位置で角度を算出する
			float ResultRot = 0.0f;		// 計算結果を入れる変数
			float Z = pEnemy[i]->GetPos().z - GetPos().z;	// Zの大きさを測る
			float X = pEnemy[i]->GetPos().x - GetPos().x;	// Xの大きさを測る
			ResultRot = atan2f(X, Z);	// 計算

			Speed *= 0.1f;

			// スピードの分飛ばす
			SetMove({
				(sinf(D3DX_PI - ResultRot) * -Speed) + move.x,
				(Speed * 0.1f) + move.y ,
				(cosf(D3DX_PI - ResultRot) * Speed) + move.z
				});

			pEnemy[i]->SetMove({
				(sinf(D3DX_PI - ResultRot) * -Speed) + -move.x,
				(Speed * 0.1f) + move.y ,
				(cosf(D3DX_PI - ResultRot) * Speed) + -move.z
				});
		}
	}

}

//========================================================================================================================
// 生成処理
//========================================================================================================================
CCarEnemy* CCarEnemy::Create(CParamStorage::TYPE cartype, D3DXVECTOR3 pos)
{
	CCarEnemy* pCarEnemy = new CCarEnemy;

	//pCarEnemy->SetPos(pos);
	pCarEnemy->InitType(cartype);

	pCarEnemy->Init();

	return pCarEnemy;
}

//===========================================================================================================
// 次のルートを設定する
//===========================================================================================================
void CCarEnemy::Route()
{
	// まだ次のターゲットまで到達していなかったら
	if (!m_bRouteClear) 
	{ return; }

	using namespace std;
	vector<CCoursePoint*>pCoursePoint;
	int nCnt = m_nCnt;

	// 道順のポイントを探す
	pCoursePoint.clear();
	pCoursePoint = CSearch::SearchMultiObject(pCoursePoint, CObject::POINT);

	// vectorの中身が空だったら処理を行わない
	if (pCoursePoint.empty()) { return; }

	// サイズをあらかじめ別の変数に入れておく
	unsigned int coursesize = pCoursePoint.size();

	for (unsigned int i = 0; i < coursesize; i++)
	{
		if (pCoursePoint[i]->GetIdx() == m_nCnt)
		{// インデックス順になるようにする
			// 次のターゲットを設定する
			SetTargetRoute(pCoursePoint[i]->GetPos());
			SetNextIdx(pCoursePoint[i]->GetIdx());
			break;
		}
	}

	// カウントを進める
	m_nCnt++;
	m_nCnt %= coursesize;	// サイズで剰余算しておく

	// 次のターゲットに到達していないに設定する
	m_bRouteClear = false;
}

//===========================================================================================================
// 次のターゲットに到達するまでの更新処理
//===========================================================================================================
void CCarEnemy::TargetRouteUpdate()
{
	// 次のターゲットに到達していたら
	if (m_bRouteClear)
	{ return; }

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size= GetSize();
	
	D3DXVECTOR3 targetsize = { 100.0f,10.0f,100.0f };

	// 現在のプレイヤーの速度
	float Speed = 3.0f;

	// 次のポイントまでの角度を算出する
	float ResultRot = 0.0f;		// 計算結果を入れる変数
	float Z = m_NextRoute.z - pos.z;	// Zの大きさを測る
	float X = m_NextRoute.x - pos.x;	// Xの大きさを測る
	ResultRot = atan2f(X, Z);	// 計算

	float rotY = GetRot().y;	// 現在の角度

	// 角度補正の計算
	ResultRot = CCalculation::FixAngle(rotY, ResultRot);

	if (rotY - ResultRot >= -0.15f && rotY - ResultRot <= 0.15f)
	{// 角度がある程度あっていたら
		// 何もしないでまっすぐ走る
	}
	else if (rotY < ResultRot)
	{// 目的の角度より小さかったら
		ActionBend_R();		// 右に曲がる
	}
	else if(rotY > ResultRot)
	{// 目的の角度より大きかったら
		ActionBend_L();		// 左に曲がる
	}

	// 前進させる
	ActionAccele();

	// 次のポイントへ移動する
	//D3DXVECTOR3 move = { sinf(D3DX_PI - ResultRot) * -Speed,0.0f,cosf(D3DX_PI - ResultRot) * Speed };
	//pos += move;
	//SetPos(pos);

	D3DXVECTOR3 move = { 0.0f,0.0f ,0.0f };

	//if (CCollision::BoxTrigger(pos, size, m_NextRoute, targetsize))
	if (CCollision::CircleTrigger(pos, size.z, m_NextRoute, targetsize.x))
	{// ポイントに到達したら
		m_bRouteClear = true;
	}

	// デバッグ表示
	CManager::GetRenderer()->SetDebugRoutePoint(pos, move, m_NextRoute,m_NextIdx, m_bRouteClear);
}

void CCarEnemy::InitTargetPoint()
{
	using namespace std;
	vector<CCoursePoint*>pCoursePoint;
	int nCnt = m_nCnt;

	// 道順のポイントを探す
	pCoursePoint.clear();
	pCoursePoint = CSearch::SearchMultiObject(pCoursePoint, CObject::POINT);

	// vectorの中身が空だったら処理を行わない
	if (pCoursePoint.empty()) { return; }

	// サイズをあらかじめ別の変数に入れておく
	unsigned int coursesize = pCoursePoint.size();
	float Curr, Prev, Near=0.0f;	// 比較用(現在、ひとつ前、近かった方

	for (unsigned int i = 0; i < coursesize; i++)
	{
		if (i == 0) 
		{ continue; }

		if (Near == 0.0f)
		{
			D3DXVECTOR3 currpos, prevpos;	// 比較用
			currpos = pCoursePoint[i]->GetPos();
			prevpos = pCoursePoint[i - 1]->GetPos();

			Curr = CCalculation::TwoPointDistance(currpos, GetPos());
			Prev = CCalculation::TwoPointDistance(prevpos, GetPos());
		}
		else
		{

		}

		
	}
}

//===========================================================================================================
// ランダムなターゲットポイントに配置する
//===========================================================================================================
void CCarEnemy::InitRandTargetPoint()
{
	using namespace std;
	vector<CCoursePoint*>pCoursePoint;
	int nCnt = m_nCnt;
	mt19937_64 mt_64(0);

	// 道順のポイントを探す
	pCoursePoint.clear();
	pCoursePoint = CSearch::SearchMultiObject(pCoursePoint, CObject::POINT);

	// vectorの中身が空だったら処理を行わない
	if (pCoursePoint.empty())
	{ return; }

	// サイズをあらかじめ別の変数に入れておく
	unsigned int coursesize = pCoursePoint.size();

	uint64_t Idx = CCalculation::RandomInt((uint64_t)0, (uint64_t)coursesize);

	for (unsigned int i = 0; i < coursesize; i++)
	{
		if (pCoursePoint[i]->GetIdx() == Idx)
		{// インデックス順になるようにする

			int plus = 1;

			if (i >= coursesize-1)
			{// 配列オーバーにならないように
				plus = -1 * i;
			}

			SetPos(pCoursePoint[i]->GetPos());
			SetRot(pCoursePoint[i]->GetRot());
			SetNextIdx((int)Idx + plus);
			SetTargetRoute(pCoursePoint[i + plus]->GetPos());

			m_nCnt = (int)Idx;
			m_nCnt %= coursesize;	// サイズで剰余算しておく
		}
	}

	
}