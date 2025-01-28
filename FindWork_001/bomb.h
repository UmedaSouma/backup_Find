#pragma once
//===========================================================================================================================================================
// 
// bomb.cppのヘッダー [bomb.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _BOMB_H_
#define _BOMB_H_
#include "main.h"
#include "model.h"

class CBomb :public CModel
{
public:
	CBomb();
	~CBomb()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	static CBomb* Create(D3DXVECTOR3 pos, int time);   // 生成処理
private:
	int m_nExplCnt;	// 爆発するまでのカウント (カウントしてくれる変数
	int m_nExplTargetTime;	// 爆発するまでの時間 (時間設定の変数
};

#endif // !BOMB_H_