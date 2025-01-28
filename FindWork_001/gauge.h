#pragma once
//===========================================================================================================================================================
// 
// gauge.cpp�̃w�b�_�[ [gauge.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_
#include "main.h"
#include "object2D.h"


class CGauge :public CObject2D
{
public:
	CGauge(int nPriority = PRIORITY_DEFAULT+1, int nOrigin = LEFT_CENTER);
	~CGauge()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	static CGauge* Create();   // ��������

	void SetMaxValue(float value) { m_Max = value; }
	float GetMaxValue() { return m_Max; }
	void SetCurrValue(float value) { m_Current = value; }
	float GetCurrValue() { return m_Current; }
private:
	float m_fRatio;	// ����
	float m_Max;		// �ő�̒l
	float m_Current;	// ���݂̒l
};

#endif // !GAUGE_H_