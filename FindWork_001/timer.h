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
#include "display_number.h"

class CTimer
{
public:
	CTimer();		// コンストラクタ
	~CTimer();		// デストラクタ
	void Init();	// 初期化処理
	void Uninit();	// 終了処理
	void Update();	// 更新処理
	void Draw();	// 描画処理

	bool GetPlay() { return m_bPlay; }	// タイマーシステムの取得

	//---------------------------------------
	// タイマーシステム
	//---------------------------------------
	void Play();	// 再生
	void Pause();	// 一時停止
	void Reset();	// リセット
	void Stop();	// リセット + 停止
private:

	// displayの配列用列挙
	typedef enum
	{
		TIME_SEC = 0,	// 秒
		TIME_MIN,		// 分
		TIME_MAX
	}TIME_;

	// 時間情報の構造体
	typedef struct
	{
		int sec;	// 秒数
		int min;	// 分数
		int hor;	// 時数
	}TimeInfo;

	int m_Timer;	// フレームカウント
	bool m_bPlay;	// 再生中か否か
	TimeInfo m_TimeInfo;	// 時間情報
	CDisplayNumber* m_pDisNum[TIME_MAX];	// 表示する数字のポインタ
	
	void TimeCalculation();	// 時間計算
};

#endif // !TIMER_H_