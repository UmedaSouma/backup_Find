#pragma once
//===========================================================================================================================================================
// 
// meterneedle.cppのヘッダー [meterneedle.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _METER_NEEDLE_H_
#define _METER_NEEDLE_H_
#include "main.h"
#include "object2D.h"


class CMeterNeedle :public CObject2D
{
public:
	CMeterNeedle(int Prio=PRIORITY_DEFAULT+2,int nOrigin = CENTER_DOWN);
	~CMeterNeedle()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	static CMeterNeedle* Create(D3DXVECTOR3 Parepos);   // 生成処理
private:

};



#endif // !METER_NEEDLE_H_
