#pragma once
//===========================================================================================================================================================
// 
// backlight.cpp�̃w�b�_�[ [backlight.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _BACKLIGHT_H_
#define _BACKLIGHT_H_
#include "main.h"
#include "effect.h"

class CBackLight :public CEffect
{
public:
	CBackLight();
	~CBackLight()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	static CBackLight* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int life, bool bRight);   // ��������
private:

};

#endif // !BACKLIGHT_H_