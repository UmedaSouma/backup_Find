#pragma once
//===========================================================================================================================================================
// 
// goal.cpp�̃w�b�_�[ [goal.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _GOAL_H_
#define _GOAL_H_
#include "main.h"
#include "model.h"
#include "car_player.h"

class CGoal :public CModel
{
	// �S�[���ƏՓˎ��̐i�s����
	typedef enum
	{
		RUN_BACK = -1,
		RUN_NONE,
		RUN_FRONT,
		RUN_MAX
	}RUNTYPE;

	// �S�[���|�C���g���������l
	// ���𓥂񂾂����肷��Ƃ��Ɏg��
	typedef enum
	{
		POINT_IN_FRONT=0,	// �ŏ��̊p�x���猩�Ď�O�̃|�C���g
		POINT_IN_BACK,		// ���̃|�C���g
		POINT_IN_MAX
	}GOAL_POINT;

	typedef enum
	{
		ORDER_FIRST=0,
		ORDER_LAST,
		ORDER_MAX
	}ORDER;

public:
	CGoal(int nPrio = PRIORITY_DEFAULT - 1);
	~CGoal()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��
	RUNTYPE CollisionGoalPlayer(CCarPlayer*pPlayer);	// 
	void GoalPointOrder(GOAL_POINT point);	// �|�C���g�ɒ��������Ԃ̌��ʂ��o���֐�

	int GetDierTrvel() { return m_DireTravel; }

	static CGoal* Create();   // ��������
private:
	const int GOAL_LAPS = 2;

	RUNTYPE m_runtype;	// �S�[���Փˎ��̐i�s����
	int m_nOrder[ORDER_MAX];	// �|�C���g�𓥂񂾏���
	int m_DireTravel;	// �i�s����
	int m_nLaps;	 // ����
};

#endif // !GOAL_H_