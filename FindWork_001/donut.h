#pragma once
//===========================================================================================================================================================
// 
// donut.cppのヘッダー [donut.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _DONUT_H_
#define _DONUT_H_
#include "main.h"
#include "object2D.h"


class CDonut :public CObject2D
{
public:
	CDonut();
	~CDonut()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Draw()override;	// 描画

	static CDonut* Create(D3DXVECTOR3 Parepos);   // 生成処理
private:

};

#endif // !DONUT_H_