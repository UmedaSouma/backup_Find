#pragma once
//===========================================================================================================================================================
// 
// fixed_value.cpp�̃w�b�_�[ [fixed_value.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _FIXED_VALUE_H_
#define _FIXED_VALUE_H_
#include "main.h"

class CFixedValue
{
public:
	CFixedValue();		// �R���X�g���N�^
	~CFixedValue();		// �f�X�g���N�^
	
	//===========================================================================================================
	// < memo >
	// �N���X���Ƃɍ\���̂���������
	// �\���̂�����������ŕϐ��ɌŒ�l�����Ă���
	//===========================================================================================================

	// �J����
	typedef struct
	{
		float DISTANCE;	// ���_�ƒ����_�̋���
		D3DXVECTOR3 ADDROT;	// �J�����̉�]�����x
	}Camera;

	// ���e
	typedef struct
	{
		int EXPLOSION_TIME;	// �����̎�������
		const char *MODEL_PASS;	// ���f���f�[�^�̃p�X
	}Bomb;

	Bomb* GetBomb() { return &m_Bomb; }
	Camera* GetCamerata() { return &m_Camera; }
private:
	Camera m_Camera;
	Bomb m_Bomb;
};


#endif // !FIXED_VALUE_H_