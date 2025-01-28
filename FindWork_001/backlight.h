#pragma once
//===========================================================================================================================================================
// 
// backlight.cppのヘッダー [backlight.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _BACKLIGHT_H_
#define _BACKLIGHT_H_
#include "main.h"
#include "effect.h"

class CBackLight :public CEffect
{
public:
	CBackLight();
	~CBackLight()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	static CBackLight* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int life, bool bRight);   // 生成処理
private:

};

#endif // !BACKLIGHT_H_