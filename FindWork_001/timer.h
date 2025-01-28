#pragma once
//===========================================================================================================================================================
// 
// timer.cppのヘッダー [timer.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _TIMER_H_
#define _TIMER_H_
#include "main.h"

class CTimer
{
public:
	CTimer();
	~CTimer();
	void Init();
	void Uninit();
	void Update();
	void Draw();



	//---------------------------------------
	// タイマーシステム
	//---------------------------------------
	void Play();	// 再生
	void Pause();	// 一時停止
	void Reset();	// リセット
	void Stop();	// リセット + 停止
private:
	void TimeCalculation();	// 時間計算

	int m_Timer;	// フレームカウント
	bool m_bPlay;	// 再生中か否か
	int m_nSeconds;	// 秒数カウント
	int m_nMinutes;	// 分数カウント
	int m_nHours;	// 時数カウント
};

#endif // !TIMER_H_