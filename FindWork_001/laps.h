#pragma once
//===========================================================================================================================================================
// 
// laps.cppのヘッダー [laps.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _LAPS_H_
#define _LAPS_H_
#include "main.h"
#include "display_number.h"

class CLaps
{
public:
	CLaps();
	~CLaps();
	void Init();
	void Uninit();
	void Set();

private:
	CDisplayNumber* m_pDisplayNum;	// 表示する数
};

CLaps::CLaps()
{
}

CLaps::~CLaps()
{
}

#endif // !LAPS_H_