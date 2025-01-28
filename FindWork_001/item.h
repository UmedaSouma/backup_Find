#pragma once
//===========================================================================================================================================================
// 
// item.cpp�̃w�b�_�[ [item.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"
#include "model.h"

class CItem:public CModel
{
public:
	CItem();
	~CItem()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	bool Collision();	// �����蔻��

	static CItem* Create(D3DXVECTOR3 pos);   // ��������
private:

};



#endif // !ITEM_H_