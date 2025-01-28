#pragma once
//===========================================================================================================================================================
// 
// editor_obstacles.cpp�̃w�b�_�[ [editor_obstacles.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _EDITOR_OBSTACLES_H_
#define _EDITOR_OBSTACLES_H_
#include "main.h"
#include "scene.h"
#include "input.h"
#include "obstacles.h"

#define FPASS_OBS	"data\\text\\obs_01.txt"

class CEditorObstacle :public CScene
{
public:
	CEditorObstacle();
	~CEditorObstacle()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	void Controll();		// ����
	void ControllMove(CInputKeyBoard* keyboard);	// �ړ�����
	void SaveObs();	// ��������
	void SaveInfoObs();	// �|�C���g���̏�������

	static CEditorObstacle* Create();   // ��������

private:
	//*******************************************************************************************************
	// �g�p�p�x�����������̕ϐ���
	//*******************************************************************************************************
	const char* FpassObs = "data\\text\\corsepp.txt";	// �J���t�@�C���̃p�X
	const char* major_h = "==============================================================\n";	// �匩�o��
	const char* sub_h = "--------------------------------------------------------------\n";		// �����o��
	const char* txt_break = "\n";	// ���s

	CObstacle* m_pMother;	// �R�[�X�|�C���g�̐e
};

#endif // !EDITOR_OBSTACLES_H_