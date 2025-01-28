#pragma once
//===========================================================================================================================================================
// 
// editor_coursepoint.cpp�̃w�b�_�[ [editor_coursepoint.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _EDITOR_COURSE_POINT_H_
#define _EDITOR_COURSE_POINT_H_
#include "main.h"
#include "scene.h"
#include "course_point.h"
#include "input.h"

#define FPASS_CORSE	"data\\text\\coursepoint_01.txt"

class CEditorCoursePoint :public CScene
{
public:
	CEditorCoursePoint();
	~CEditorCoursePoint()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	void Controll();		// ����
	void ControllMove(CInputKeyBoard* keyboard);	// �ړ�����
	void Save();	// ��������
	void SaveInfo();	// �|�C���g���̏�������
	
private:
	//*******************************************************************************************************
	// �g�p�p�x�����������̕ϐ���
	//*******************************************************************************************************
	const char* Fpass = "data\\text\\corsepp.txt";	// �J���t�@�C���̃p�X
	const char* major_h = "==============================================================\n";	// �匩�o��
	const char* sub_h = "--------------------------------------------------------------\n";		// �����o��
	const char* txt_break = "\n";	// ���s

	CCoursePoint* m_pPointMother;	// �R�[�X�|�C���g�̐e
	int m_nNum;		// �����J�E���g
};

#endif // !EDITOR_COURSE_POINT_H_