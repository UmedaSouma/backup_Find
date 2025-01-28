#pragma once
//===========================================================================================================================================================
// 
// speedmeter.cppのヘッダー [speedmeter.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _SPEEDMETER_H_
#define _SPEEDMETER_H_
#include "main.h"
#include "object2D.h"

class CSpeedMeter :public CObject2D
{
public:
	CSpeedMeter();
	~CSpeedMeter()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	static CSpeedMeter* Create();   // 生成処理
private:

};

#endif // !SPEEDMETER_H_