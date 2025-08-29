#pragma once
//===========================================================================================================================================================
// 
// manager_number.cppÇÃÉwÉbÉ_Å[ [manager_number.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _MANAGER_NUMBER_H_
#define _MANAGER_NUMBER_H_
#include "main.h"
#include "timer.h"

class CManagerNumber
{
public:
	CManagerNumber();
	~CManagerNumber();
	void Init();
	void Uninit();
	void Update();
	void Draw();

	CTimer* GetTimer() { return m_pTimer; }
	
private:
	CTimer* m_pTimer;
};

#endif // !MANAGER_NUMBER_H_