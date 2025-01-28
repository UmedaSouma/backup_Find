#pragma once
//===========================================================================================================================================================
// 
// title_poly.cppのヘッダー [title_poly.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _TITLE_POLY_H_
#define _TITLE_POLY_H_
#include "main.h"
#include "object2D.h"

class CTitlePoly :public CObject2D
{
public:
	CTitlePoly(int Prio=PRIORITY_DEFAULT+2);
	~CTitlePoly()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	static CTitlePoly* Create();   // 生成処理
private:

};



#endif // !TITLE_POLY_H_