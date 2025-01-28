#pragma once
//===========================================================================================================================================================
// 
// meterneedle.cpp�̃w�b�_�[ [meterneedle.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _METER_NEEDLE_H_
#define _METER_NEEDLE_H_
#include "main.h"
#include "object2D.h"


class CMeterNeedle :public CObject2D
{
public:
	CMeterNeedle(int Prio=PRIORITY_DEFAULT+2,int nOrigin = CENTER_DOWN);
	~CMeterNeedle()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	static CMeterNeedle* Create(D3DXVECTOR3 Parepos);   // ��������
private:

};



#endif // !METER_NEEDLE_H_
