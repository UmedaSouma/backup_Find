#pragma once
//===========================================================================================================================================================
// 
// goal.cppのヘッダー [goal.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _GOAL_H_
#define _GOAL_H_
#include "main.h"
#include "model.h"
#include "car_player.h"

class CGoal :public CModel
{
	// ゴールと衝突時の進行方向
	typedef enum
	{
		RUN_BACK = -1,
		RUN_NONE,
		RUN_FRONT,
		RUN_MAX
	}RUNTYPE;

	// ゴールポイントを示す数値
	// 何を踏んだか判定するときに使う
	typedef enum
	{
		POINT_IN_FRONT=0,	// 最初の角度から見て手前のポイント
		POINT_IN_BACK,		// 奥のポイント
		POINT_IN_MAX
	}GOAL_POINT;

	typedef enum
	{
		ORDER_FIRST=0,
		ORDER_LAST,
		ORDER_MAX
	}ORDER;

public:
	CGoal(int nPrio = PRIORITY_DEFAULT - 1);
	~CGoal()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画
	RUNTYPE CollisionGoalPlayer(CCarPlayer*pPlayer);	// 
	void GoalPointOrder(GOAL_POINT point);	// ポイントに着いた順番の結果を出す関数

	int GetDierTrvel() { return m_DireTravel; }

	static CGoal* Create();   // 生成処理
private:
	const int GOAL_LAPS = 2;

	RUNTYPE m_runtype;	// ゴール衝突時の進行方向
	int m_nOrder[ORDER_MAX];	// ポイントを踏んだ順番
	int m_DireTravel;	// 進行方向
	int m_nLaps;	 // 周回数
};

#endif // !GOAL_H_