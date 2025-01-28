#pragma once
//===========================================================================================================================================================
// 
// effect.cpp�̃w�b�_�[ [effect.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "main.h"
#include "billboard.h"

class CEffect :public CBillboard
{
public:
	CEffect(int nPrio = PRIORITY_DEFAULT+2);
	~CEffect()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	static CEffect* Create(D3DXVECTOR3 pos,int nLife);   // ��������

	void SetLife(int Life) { m_nLife = Life; }
	int GetLife() { return m_nLife; }

	void SetMaxLife(int life) { m_nMaxLife = life; }
	int GetMaxLife() { return m_nMaxLife; }
private:
	int m_nLife;	// ����
	int m_nMaxLife;	// �ő����
};



#endif // !EFFECT_H_