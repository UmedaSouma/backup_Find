#pragma once
//===========================================================================================================================================================
// 
// billboard.cpp�̃w�b�_�[ [billboard.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
#include "main.h"
#include "object3D.h"

class CBillboard :public CObject3D
{
public:
	CBillboard(int nPrio = PRIORITY_DEFAULT);
	~CBillboard()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	static CBillboard* Create(D3DXVECTOR3 pos);   // ��������
private:

};

#endif // !BILLBOARD_H_
