//===========================================================================================================================================================
// 
// タイマーの処理 [timer.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "timer.h"

CTimer::CTimer()
{
	m_Timer = 0;
	m_bPlay = false;
	m_nSeconds = 0;
	m_nMinutes = 0;
	m_nHours = 0;
}

CTimer::~CTimer()
{
}

void CTimer::Init()
{
	Play();
}

void CTimer::Uninit()
{
	delete this;
}

void CTimer::Update()
{
	if (m_bPlay)
	{// 再生中の時
		m_Timer++;	// フレームカウントを進める
	}

	TimeCalculation();
}

void CTimer::Draw()
{
}

void CTimer::Play()
{
	m_bPlay = true;
}

void CTimer::Pause()
{
	m_bPlay = false;
}

void CTimer::Reset()
{
	m_Timer = 0;
}

void CTimer::Stop()
{
	Pause();
	Reset();
}

void CTimer::TimeCalculation()
{
	int TIME_DIV = 60;

	if (m_Timer / TIME_DIV < TIME_DIV)
	{
		m_nSeconds = m_Timer / TIME_DIV;
	}
	else
	{
		m_nSeconds = m_Timer % (TIME_DIV * 10);
		m_nSeconds /= TIME_DIV;
	}

	TIME_DIV *= TIME_DIV;
	
	if (m_Timer / TIME_DIV < TIME_DIV)
	{
		m_nMinutes = m_Timer / TIME_DIV;
	}
	else
	{
		m_nMinutes = m_Timer % (TIME_DIV * 10);
		m_nMinutes /= 60;
	}

	TIME_DIV *= TIME_DIV;

	if (m_Timer / TIME_DIV < TIME_DIV)
	{
		m_nHours = m_Timer / TIME_DIV;
	}
	else
	{
		m_nHours = m_Timer % (TIME_DIV * 10);
		m_nHours /= 60;
	}
	
	
}
