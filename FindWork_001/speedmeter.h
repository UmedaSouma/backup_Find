#pragma once
//===========================================================================================================================================================
// 
// speedmeter.cpp�̃w�b�_�[ [speedmeter.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _SPEEDMETER_H_
#define _SPEEDMETER_H_
#include "main.h"
#include "object2D.h"

class CSpeedMeter :public CObject2D
{
public:
	CSpeedMeter();
	~CSpeedMeter()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	static CSpeedMeter* Create();   // ��������
private:

};

#endif // !SPEEDMETER_H_