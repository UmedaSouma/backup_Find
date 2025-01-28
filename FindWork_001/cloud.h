#pragma once
//===========================================================================================================================================================
// 
// tree.cpp�̃w�b�_�[ [tree.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _CLOUD_H_
#define _CLOUD_H_
#include "main.h"
#include "model.h"


class CCloud :public CModel
{
public:
	CCloud();
	~CCloud()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	static CCloud* Create();   // ��������
private:

};



#endif // !TREE_H_