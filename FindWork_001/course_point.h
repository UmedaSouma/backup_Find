#pragma once
//===========================================================================================================================================================
// 
// course_point.cpp�̃w�b�_�[ [course_point.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _COURSE_POINT_H_
#define _COURSE_POINT_H_
#include "main.h"
#include "model.h"

class CCoursePoint:public CModel
{
public:
	CCoursePoint();
	~CCoursePoint()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	void SetIdx(int Idx) { m_nIdxPoint = Idx; }
	int GetIdx() { return m_nIdxPoint; }

	static CCoursePoint* Create(int Idx, D3DXVECTOR3 pos, D3DXVECTOR3 rot);   // ��������
private:
	int m_nIdxPoint;	// �Ԃ��ʂ鏇��
};


#endif // !COURSE_POINT_H_