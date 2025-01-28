#pragma once
//===========================================================================================================================================================
// 
// timer.cpp�̃w�b�_�[ [timer.h]
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
	// �^�C�}�[�V�X�e��
	//---------------------------------------
	void Play();	// �Đ�
	void Pause();	// �ꎞ��~
	void Reset();	// ���Z�b�g
	void Stop();	// ���Z�b�g + ��~
private:
	void TimeCalculation();	// ���Ԍv�Z

	int m_Timer;	// �t���[���J�E���g
	bool m_bPlay;	// �Đ������ۂ�
	int m_nSeconds;	// �b���J�E���g
	int m_nMinutes;	// �����J�E���g
	int m_nHours;	// �����J�E���g
};

#endif // !TIMER_H_