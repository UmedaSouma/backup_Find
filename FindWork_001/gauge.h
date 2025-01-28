#pragma once
//===========================================================================================================================================================
// 
// gauge.cppのヘッダー [gauge.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_
#include "main.h"
#include "object2D.h"


class CGauge :public CObject2D
{
public:
	CGauge(int nPriority = PRIORITY_DEFAULT+1, int nOrigin = LEFT_CENTER);
	~CGauge()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	static CGauge* Create();   // 生成処理

	void SetMaxValue(float value) { m_Max = value; }
	float GetMaxValue() { return m_Max; }
	void SetCurrValue(float value) { m_Current = value; }
	float GetCurrValue() { return m_Current; }
private:
	float m_fRatio;	// 割合
	float m_Max;		// 最大の値
	float m_Current;	// 現在の値
};

#endif // !GAUGE_H_