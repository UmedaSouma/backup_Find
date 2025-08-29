#pragma once
//===========================================================================================================================================================
// 
// carplayer.cppのヘッダー [carplayer.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _CAR_PLAYER_H_
#define _CAR_PLAYER_H_
#include "main.h"
#include "car.h"
#include "param_storage.h"

// 前方宣言
class CDisplayNumber;
class CGauge;

class CCarPlayer:public CCar
{
public:
	CCarPlayer();
	~CCarPlayer()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画
	void ChangeCar(CParamStorage::TYPE hittype);		// 車変更(当たった車の種類)

	static CCarPlayer* Create(CParamStorage::TYPE cartype);   // 生成処理

	void SetRecoveryGauge(int n);
private:
	static const int GEARNUM_POS_X = 1200;
	static const int GEARNUM_POS_Y = 600;

	void UpdateGauge();
	void UpdateGearNum();

	CGauge* m_pGauge;	// ゲージのポインタ
	CDisplayNumber* m_pGearNum;	// ギアの数値
};

#endif // !CAR_PLAYER_H_
