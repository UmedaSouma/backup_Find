#pragma once
//===========================================================================================================================================================
// 
// carplayer.cpp�̃w�b�_�[ [carplayer.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _CAR_PLAYER_H_
#define _CAR_PLAYER_H_
#include "main.h"
#include "car.h"
#include "param_storage.h"
#include "gauge.h"

class CCarPlayer:public CCar
{
public:
	CCarPlayer();
	~CCarPlayer()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��
	void ChangeCar(CParamStorage::TYPE hittype);		// �ԕύX(���������Ԃ̎��)

	static CCarPlayer* Create(CParamStorage::TYPE cartype);   // ��������

	void UpdateGauge();
	void SetRecoveryGauge(int n);
private:
	CGauge* m_pGauge;
};



#endif // !CAR_PLAYER_H_
