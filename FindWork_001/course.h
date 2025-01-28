#pragma once
//===========================================================================================================================================================
// 
// course.cppのヘッダー [course.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _COURSE_H_
#define _COURSE_H_
#include "main.h"
#include "actor.h"

class CCourse:public CModel
{
public:
	typedef enum
	{
		COURSE_TITLE=0,
		COURSE_01,
		COURSE_MAX
	}COURSE_;

	CCourse();
	~CCourse()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	void SetCourseNum(int num);	// コース選択

	static CCourse* Create(int type);   // 生成処理
private:
	float m_Distance;
};



#endif // !COURSE_H_