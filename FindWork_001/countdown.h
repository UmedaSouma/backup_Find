#pragma once
//===========================================================================================================================================================
// 
// countdoen.cppのヘッダー [countdoen.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _COUNTDOWN_H_
#define _COUNTDOWN_H_
#include "main.h"
#include "object2D.h"


class CCountdown :public CObject2D
{
public:
	CCountdown(int prio=PRIORITY_DEFAULT+1);
	~CCountdown()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	bool GetUse() { return m_bUseCount; }
	static CCountdown* Create();   // 生成処理
private:
	bool m_bUseCount;	// カウントをしているかどうか
	int m_nCountnum;	// カウントカウント
};


#endif // !COUNTDOWN_H_