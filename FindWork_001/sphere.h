#pragma once
//===========================================================================================================================================================
// 
// sphere.cpp�̃w�b�_�[ [sphere.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _SPHERE_H_
#define _SPHERE_H_
#include "main.h"
#include "model.h"

class CSphere :public CModel
{
public:
	CSphere();
	~CSphere()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Draw()override;	// �`��
	void UpdatePos(D3DXVECTOR3 pos);	// �ʒu���������Ă�

	static CSphere* Create();   // ��������
private:
};



#endif // !SPHERE_H_