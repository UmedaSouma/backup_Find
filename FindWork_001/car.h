#pragma once
//===========================================================================================================================================================
// 
// car.cppのヘッダー [car.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _CAR_H_
#define _CAR_H_
#include "main.h"
#include "param_storage.h"
#include "actor.h"
#include "sphere.h"

class CCar:public CActor
{
private:

	// 現在のパラメーター
	struct CurrParam
	{
		int nLife;
		int nGear;
		float Speed;
	};

	// レイの始点の位置
	typedef enum
	{
		CENTER = 0,
		FRONT_RIGHT,
		FRONT_LEFT,
		BACK_RIGHT,
		BACK_LEFT,
	}START_POINT;

public:
	// 車のアクション
	typedef enum
	{
		NONE = 0,	// 普通の状態
		ACCELE,		// 前進
		BRAKE,		// 後進
		TURBO,		// 突進
		DOWN,		// 衰退
		DRIFTR,		// ドリフト
		DRIFTL,		// ドリフト
		MAX
	}ACTION_STATE;

	// ドリフトに必要な要素
	typedef struct
	{
		float Force;	// ドリフトした瞬間の前進する力
		float Angle;	// ドリフトした瞬間の角度
	}Forward;

	CCar();
	~CCar()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	void MeshCollision(START_POINT point);	// メッシュとの当たり判定
	void ViewSetting();	// 表示スピードの設定
	void InitType(CParamStorage::TYPE type);		// タイプごとの初期設定
	void PramSet();
	void TarboCamera();	// ターボ使用時のカメラの挙動
	void HitObstacle();	// 障害物と当たるまで
	void DrawDistance();	// 描画の範囲設定

	static CCar* Create();   // 生成処理

	//-------------------------------------------------------
	// 車のアクション
	//-------------------------------------------------------
	void ActionAccele();	// アクセル(加速
	void ActionBrake();		// ブレーキ(減速
	float ActionBend();		// 曲がる
	void ActionBend_R();	// 右に曲がる
	void ActionBend_L();	// 左に曲がる
	void ActionTurbo();		// ブースト(急加速
	void ActionAttack();	// 攻撃(突進
	void ActionDown();		// 衰退
	void ActionDrift();		// ドリフト処理
	void ActionDriftR();		// ドリフト処理
	void ActionDriftL();		// ドリフト処理

	void ActionUpdate();	// アクション毎の更新処理(以降 ActionUpdate = AU と略す
	void AUdown();			// ダウン時の更新処理
	//===================================================================

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//======================================================================
	// ドリフトお試し用
	//======================================================================
public:
	typedef struct
	{
		float Current;	// 現在の角度
		float Target;	// 目的の角度
	}Drift_Direction;
private:
	void StartDrift();	// ドリフトを開始
	bool m_IsDrift;	// ドリフトをしているかどうか
	float m_ChargeTime;	// ドリフトチャージ時間
	Drift_Direction m_DDire;	// ドリフトの角度
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
private:
	CurrParam m_CurrParam;			// 現在のパラメーター
	CParamStorage::Param m_Param;	// パラメーターを扱う変数
	CParamStorage::TYPE m_type;		// 車のタイプ
	ACTION_STATE m_Action;			// 車の現在の状態

	float m_fAccumulationSpeed;		// 蓄積スピード(現在のスピード
	float m_fOldSpeed;				// 蓄積スピード(1フレーム前
	D3DXVECTOR3 m_oldmove;			// 過去の移動値
	D3DXVECTOR3 m_oldrot;			// 過去の角度
	float m_fMoveAngle;				// 移動方向
	int m_nTurboInterval;			// ターボの間隔
	bool m_bDeath;	// 死んだ判定
	int m_nDeathCount;	// 死んだ後に消すフレームをカウント
	int m_nDownCount;	// ダウン状態から起き上がるまでのカウント変数
	bool m_bDisDraw;	// 距離によって描画するか決める

	Forward m_ForwardInfo;	// ドリフトの情報

	float m_fDriftTargetRot;	// ドリフト時の回転

	CSphere* m_pSphere;	// 当たり判定の可視化
public:

	//================================================
	// Setter,Getter
	//================================================

	//-- 重さ --
	void SetWeight(float Weight) { m_Param.fWeight = Weight; }
	float GetWeight() { return m_Param.fWeight; }

	//-- ギアの数 --
	void SetGearNum(int num) { m_Param.nMaxGear = num; }
	int GetGearNum() { return m_Param.nMaxGear; }
	
	//-- 曲がりやすさ --
	void SetBending(float benging) { m_Param.fBending = benging; }
	float GetBending() { return m_Param.fBending; }

	//-- ギアごとの最高速度 --
	void SetMaxSpeed(int idx, float MaxSpeed) { m_Param.fMaxSpeed[idx] = MaxSpeed; }
	float GetfMaxSpeed(int idx) { return m_Param.fMaxSpeed[idx]; }

	//-- 最大体力 --
	void SetMaxLife(int maxlife) { m_Param.nMaxLife = maxlife; }
	int GetMaxLife() { return m_Param.nMaxLife; }

	//-- タイプ --
	void SetTypeCar(CParamStorage::TYPE type) { m_type = type; }
	CParamStorage::TYPE GetTypeCar() { return m_type; }

	//-- 蓄積スピード --
	void SetAccumulationSpeed(float speed) { m_fAccumulationSpeed = speed; }
	float GetAccumulationSpeed() { return m_CurrParam.Speed; }

	//-- 蓄積スピード --
	void SetGear(int gear) { m_CurrParam.nGear = gear; }
	int GetGear() { return m_CurrParam.nGear; }

	//-- 移動方向 --
	float GetMoveAngle() { return m_fMoveAngle; }

	//-- 死んだかどうか --
	void SetDeath() { m_bDeath = true; }
	bool GetDeath() { return m_bDeath; }
	
	//-- 車のアクション --
	void SetActionState(ACTION_STATE state) { m_Action = state; }
	ACTION_STATE GetActionState() { return m_Action; }

	//-- 前進する力 --
	void SetForwardForce(float force) { m_ForwardInfo.Force = force; }
	float GetForwardForce() { return m_ForwardInfo.Force; }

	//-- 回転度 --
	void SetForwardAngle(float angle) { m_ForwardInfo.Angle = angle; }
	float GetForwardAngle() { return m_ForwardInfo.Angle; }

	//-- ドリフトの情報 --
	void SetForwardInfo(Forward forward) { m_ForwardInfo = forward; }
	Forward GetForwardInfo() { return m_ForwardInfo; }
};

#endif // !CAR_H_