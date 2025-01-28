#pragma once
//===========================================================================================================================================================
// 
// course_point.cppのヘッダー [course_point.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _COURSE_POINT_H_
#define _COURSE_POINT_H_
#include "main.h"
#include "model.h"

class CCoursePoint:public CModel
{
public:
	CCoursePoint();
	~CCoursePoint()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	void SetIdx(int Idx) { m_nIdxPoint = Idx; }
	int GetIdx() { return m_nIdxPoint; }

	static CCoursePoint* Create(int Idx, D3DXVECTOR3 pos, D3DXVECTOR3 rot);   // 生成処理
private:
	int m_nIdxPoint;	// 車が通る順番
};


#endif // !COURSE_POINT_H_