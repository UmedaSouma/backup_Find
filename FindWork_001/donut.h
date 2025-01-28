#pragma once
//===========================================================================================================================================================
// 
// donut.cpp�̃w�b�_�[ [donut.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _DONUT_H_
#define _DONUT_H_
#include "main.h"
#include "object2D.h"


class CDonut :public CObject2D
{
public:
	CDonut();
	~CDonut()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Draw()override;	// �`��

	static CDonut* Create(D3DXVECTOR3 Parepos);   // ��������
private:

};

#endif // !DONUT_H_