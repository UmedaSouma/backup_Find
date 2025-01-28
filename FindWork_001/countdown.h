#pragma once
//===========================================================================================================================================================
// 
// countdoen.cpp�̃w�b�_�[ [countdoen.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _COUNTDOWN_H_
#define _COUNTDOWN_H_
#include "main.h"
#include "object2D.h"


class CCountdown :public CObject2D
{
public:
	CCountdown(int prio=PRIORITY_DEFAULT+1);
	~CCountdown()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	bool GetUse() { return m_bUseCount; }
	static CCountdown* Create();   // ��������
private:
	bool m_bUseCount;	// �J�E���g�����Ă��邩�ǂ���
	int m_nCountnum;	// �J�E���g�J�E���g
};


#endif // !COUNTDOWN_H_