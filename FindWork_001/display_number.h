#pragma once
//===========================================================================================================================================================
// 
// display_number.cppのヘッダー [display_number.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _DISPLAY_NUMBER_H_
#define _DISPLAY_NUMBER_H_
#include "main.h"
#include "number.h"

class CDisplayNumber
{
public:
	typedef enum
	{
		DIGID_ONE = 0,	// 一の位
		DIGID_TEN,		// 十の位
		DIGID_HANDRED,	// 百の位
		DIGID_MAX
	}DIGID;

	CDisplayNumber();
	~CDisplayNumber();
	void Update(int num);
	void SetDisplayNumber(int num);	// 表示する数字の設定

	static CDisplayNumber* Create(D3DXVECTOR3 pos , int num ,DIGID dig , CNumber::FONT_TYPE font);	// 生成
private:
	CNumber *m_pDisplayNum[DIGID_MAX];	// 数字を格納する変数
	int m_Number;	// 数字
	DIGID m_MaxDig;	// 最大桁数
	CNumber::FONT_TYPE m_Font;	// フォントタイプ

public:
	void SetNumber(int num) { m_Number = num; }
	int GetNumber() { return m_Number; }
	void SetDisplaypos(D3DXVECTOR3 pos);	// 表示する位置を設定
};



#endif // !DISPLAY_NUMBER_H_