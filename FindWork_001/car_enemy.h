#pragma once
//===========================================================================================================================================================
// 
// car_enemy.cppのヘッダー [car_enemy.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _CAR_ENEMY_H_
#define _CAR_ENEMY_H_
#include "main.h"
#include "car.h"

class CCarEnemy:public CCar
{
public:
	CCarEnemy();
	~CCarEnemy()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画
	void BlowAwayPtoE();	// ぶっ飛ばされる(プレイヤーと敵の当たり判定
	void BlowAwayEtoE();	// ぶっ飛ばされる(敵と敵の当たり判定

	static CCarEnemy* Create(CParamStorage::TYPE cartype,D3DXVECTOR3 pos);   // 生成処理
	void Route();	// 車の道順
	void TargetRouteUpdate();
	void InitTargetPoint();	// 一番近くのターゲットポイントを設定する
	void InitRandTargetPoint();	// ランダムなターゲットポイントに車を配置

	void SetTargetRoute(D3DXVECTOR3 targetpos) { m_NextRoute = targetpos; }	// 次に通る道
	void SetNextIdx(int Idx) { m_NextIdx = Idx; }
	FLOAT* GetDistance() { return &m_Distance; }

private:
	FLOAT m_Distance = 0.0f;
	int m_nCnt;
	bool m_bRouteClear;	// その道を通ったかどうか判定
	D3DXVECTOR3 m_NextRoute;
	int m_NextIdx;
};



#endif // !CAR_ENEMY_H_
