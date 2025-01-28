#pragma once
//===========================================================================================================================================================
// 
// bomb.cpp�̃w�b�_�[ [bomb.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _BOMB_H_
#define _BOMB_H_
#include "main.h"
#include "model.h"

class CBomb :public CModel
{
public:
	CBomb();
	~CBomb()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	static CBomb* Create(D3DXVECTOR3 pos, int time);   // ��������
private:
	int m_nExplCnt;	// ��������܂ł̃J�E���g (�J�E���g���Ă����ϐ�
	int m_nExplTargetTime;	// ��������܂ł̎��� (���Ԑݒ�̕ϐ�
};

#endif // !BOMB_H_