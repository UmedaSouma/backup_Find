#pragma once
//===========================================================================================================================================================
// 
// effect.cppのヘッダー [effect.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "main.h"
#include "billboard.h"

class CEffect :public CBillboard
{
public:
	CEffect(int nPrio = PRIORITY_DEFAULT+2);
	~CEffect()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	static CEffect* Create(D3DXVECTOR3 pos,int nLife);   // 生成処理

	void SetLife(int Life) { m_nLife = Life; }
	int GetLife() { return m_nLife; }

	void SetMaxLife(int life) { m_nMaxLife = life; }
	int GetMaxLife() { return m_nMaxLife; }
private:
	int m_nLife;	// 寿命
	int m_nMaxLife;	// 最大寿命
};



#endif // !EFFECT_H_