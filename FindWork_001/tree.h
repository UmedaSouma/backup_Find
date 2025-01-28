#pragma once
//===========================================================================================================================================================
// 
// tree.cpp�̃w�b�_�[ [tree.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _TREE_H_
#define _TREE_H_
#include "main.h"
#include "model.h"


class CTree :public CModel
{
public:
	CTree();
	~CTree()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	static CTree* Create();   // ��������
private:

};



#endif // !TREE_H_