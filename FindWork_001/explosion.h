#pragma once
//===========================================================================================================================================================
// 
// explosion.cpp�̃w�b�_�[ [explosion.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "main.h"
#include "model.h"

class CExplosion :public CModel
{
public:
	CExplosion();
	~CExplosion()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	static CExplosion* Create(D3DXVECTOR3 pos, int Expantion);	// ��������
private:
	int m_nTargetCnt;	// �ڕW�̃J�E���g
	int m_nExpansionCnt;	// �g�傷��J�E���g
};

#endif // !EXPLOSION_H_