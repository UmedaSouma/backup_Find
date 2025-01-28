#pragma once
//===========================================================================================================================================================
// 
// param_storage.cppのヘッダー [param_storage.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _PARAM_STORAGE_H_
#define _PARAM_STORAGE_H_
#include "main.h"


class CParamStorage
{
public:

#define MAX_WORLD_GEAR	(10)	// ギア最大値
	//======================================
	// 車のタイプ
	//======================================
	typedef enum
	{
		CAR_NORMAL = 0,
		CAR_TRACK,
		CAR_SPORTS,
		CAR_BOMB,
		CAR_MAX
	}TYPE;

	//===================================================
	// 車のパラメーター
	//===================================================
	struct Param
	{
		int nMaxLife;		// 最大体力
		int nMaxGear;		// ギア数
		float fWeight;		// 車の重さ
		float fBending;		// 曲がりやすさ
		float fMaxSpeed[MAX_WORLD_GEAR];	// 最大スピード
	};

	CParamStorage();
	~CParamStorage();
	void Road();	// 読み込み処理
	void RoadParamSet(FILE*pfile);	// パラメーター読み込み
	void RoadCar(FILE* pfile, int Idx);
private:
	TYPE m_type;	// 車のタイプ
	Param m_Param[CAR_MAX];	// パラメーターを扱う変数
public:

	//================================================
	// Setter,Getter
	//================================================

	//-- 重さ --
	void SetWeight(float Weight,int idx) { m_Param[idx].fWeight = Weight; }
	float GetWeight(int idx) { return m_Param[idx].fWeight; }

	//-- ギアの数 --
	void SetGearMax(int num, int idx) { m_Param[idx].nMaxGear = num; }
	int GetGearMax(int idx) { return m_Param[idx].nMaxGear; }

	//-- 曲がりやすさ --
	void SetBending(float benging, int idx) { m_Param[idx].fBending = benging; }
	float GetBending(int idx) { return m_Param[idx].fBending; }

	//-- ギアごとの最高速度 --
	void SetMaxSpeed(int idx, float MaxSpeed, int caridx) { m_Param[caridx].fMaxSpeed[idx] = MaxSpeed; }
	float GetfMaxSpeed(int caridx, int idx) { return m_Param[caridx].fMaxSpeed[idx]; }

	//-- 最大体力 --
	void SetMaxLife(int maxlife, int idx) { m_Param[idx].nMaxLife = maxlife; }
	int GetMaxLife(int idx) { return m_Param[idx].nMaxLife; }

	//-- タイプ --
	void SetType(TYPE type, int idx) { m_type = type; }
	TYPE GetType(int idx) { return m_type; }
};


#endif // !PARAM_STORAGE_H_