#pragma once
//===========================================================================================================================================================
// 
// course.cpp�̃w�b�_�[ [course.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _COURSE_H_
#define _COURSE_H_
#include "main.h"
#include "actor.h"

class CCourse:public CModel
{
public:
	typedef enum
	{
		COURSE_TITLE=0,
		COURSE_01,
		COURSE_MAX
	}COURSE_;

	CCourse();
	~CCourse()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	void SetCourseNum(int num);	// �R�[�X�I��

	static CCourse* Create(int type);   // ��������
private:
	float m_Distance;
};



#endif // !COURSE_H_