#pragma once
//===========================================================================================================================================================
// 
// car_enemy.cpp�̃w�b�_�[ [car_enemy.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _CAR_ENEMY_H_
#define _CAR_ENEMY_H_
#include "main.h"
#include "car.h"

class CCarEnemy:public CCar
{
public:
	CCarEnemy();
	~CCarEnemy()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��
	void BlowAwayPtoE();	// �Ԃ���΂����(�v���C���[�ƓG�̓����蔻��
	void BlowAwayEtoE();	// �Ԃ���΂����(�G�ƓG�̓����蔻��

	static CCarEnemy* Create(CParamStorage::TYPE cartype,D3DXVECTOR3 pos);   // ��������
	void Route();	// �Ԃ̓���
	void TargetRouteUpdate();
	void InitTargetPoint();	// ��ԋ߂��̃^�[�Q�b�g�|�C���g��ݒ肷��
	void InitRandTargetPoint();	// �����_���ȃ^�[�Q�b�g�|�C���g�ɎԂ�z�u

	void SetTargetRoute(D3DXVECTOR3 targetpos) { m_NextRoute = targetpos; }	// ���ɒʂ铹
	void SetNextIdx(int Idx) { m_NextIdx = Idx; }
	FLOAT* GetDistance() { return &m_Distance; }

private:
	FLOAT m_Distance = 0.0f;
	int m_nCnt;
	bool m_bRouteClear;	// ���̓���ʂ������ǂ�������
	D3DXVECTOR3 m_NextRoute;
	int m_NextIdx;
};



#endif // !CAR_ENEMY_H_
