#pragma once
//===========================================================================================================================================================
// 
// car_normal.cpp�̃w�b�_�[ [car_normal.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _CAR_NORMAL_H_
#define _CAR_NORMAL_H_
#include "main.h"
#include "car.h"


class CCarNormal:public CCar
{
private:
	//================================================================

	//--------------------------------------------------------
	// < debugmemo >
	// ��U�����Œl��ݒ肵�Ƃ��B
	// ��Ńe�L�X�g�t�@�C���œ��o�͂�����
	//--------------------------------------------------------
	static const int MAX_LIFE = 150;					// �ő呬�x
	static const int MAX_GEAR = 5;						// �M�A��
	inline static const float MAX_WEIGHT = 30.0f;		// �d��
	inline static const float MAX_BENDING = 0.1f;		// �Ȃ���₷��

	inline static const float							// �M�A���Ƃ̃X�s�[�h
		MAX_SPEED[MAX_GEAR] = {
		12.0f,
		15.0f,
		18.0f,
		22.0f,
		30.0f
	};

	//================================================================

public:
	CCarNormal();
	~CCarNormal()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	static CCarNormal* Create(D3DXVECTOR3 pos);   // ��������
private:

};

#endif // !CAR_NORMAL_H_
