#pragma once
//===========================================================================================================================================================
// 
// number.cppのヘッダー [number.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_
#include "main.h"
#include "object2D.h"

//===========================================================================================================
// Numberで数字の表示！！
// 他の cpp で数字の取得・分割
//===========================================================================================================


class CNumber :public CObject2D
{
public:
	typedef enum
	{
		FONT_DOT_WBW = 0,
		FONT_MAX
	}FONT_TYPE;

	CNumber();
	~CNumber()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	static CNumber* Create(FONT_TYPE type);   // 生成処理

	// 数字
	void SetNumber(int num) { m_Number = num; }
	int GetNumber() { return m_Number; }
private:
	const char* m_NumberPass[FONT_MAX] =
	{
		"data\\TEXTURE\\akt_number002.png",
	};
	FONT_TYPE m_TypeNum;	// フォントの種類
	int m_Number;	// 数字
};
#endif // !NUMBER_H_