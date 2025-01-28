#pragma once
//===========================================================================================================================================================
// 
// title_poly.cpp�̃w�b�_�[ [title_poly.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _TITLE_POLY_H_
#define _TITLE_POLY_H_
#include "main.h"
#include "object2D.h"

class CTitlePoly :public CObject2D
{
public:
	CTitlePoly(int Prio=PRIORITY_DEFAULT+2);
	~CTitlePoly()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	static CTitlePoly* Create();   // ��������
private:

};



#endif // !TITLE_POLY_H_