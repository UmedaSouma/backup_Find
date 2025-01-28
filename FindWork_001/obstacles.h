#pragma once
//===========================================================================================================================================================
// 
// obstacle.cpp�̃w�b�_�[ [obstacle.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_
#include "main.h"
#include "model.h"
#include "car.h"

class CObstacle :public CModel
{
public:
	typedef enum
	{
		OBS_DRUMCAN = 0,
		OBS_,
		OBS_MAX,
	}OBS_TYPE;

	CObstacle();
	~CObstacle()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	void InitSet();
	void HitMovement(CCar*pcar);

	static CObstacle* Create(D3DXVECTOR3 pos, OBS_TYPE type);   // ��������

	OBS_TYPE GetObsType() { return m_obstype; }
private:
	float m_Weight;	// ��Q���̏d��(���̏d�����Ԃ��X�s�[�h���o���Ȃ��Ɛ�����΂��Ȃ�
	OBS_TYPE m_obstype;
};

#endif // !OBSTACLE_H_