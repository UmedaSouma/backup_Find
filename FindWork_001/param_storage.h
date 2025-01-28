#pragma once
//===========================================================================================================================================================
// 
// param_storage.cpp�̃w�b�_�[ [param_storage.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _PARAM_STORAGE_H_
#define _PARAM_STORAGE_H_
#include "main.h"


class CParamStorage
{
public:

#define MAX_WORLD_GEAR	(10)	// �M�A�ő�l
	//======================================
	// �Ԃ̃^�C�v
	//======================================
	typedef enum
	{
		CAR_NORMAL = 0,
		CAR_TRACK,
		CAR_SPORTS,
		CAR_BOMB,
		CAR_MAX
	}TYPE;

	//===================================================
	// �Ԃ̃p�����[�^�[
	//===================================================
	struct Param
	{
		int nMaxLife;		// �ő�̗�
		int nMaxGear;		// �M�A��
		float fWeight;		// �Ԃ̏d��
		float fBending;		// �Ȃ���₷��
		float fMaxSpeed[MAX_WORLD_GEAR];	// �ő�X�s�[�h
	};

	CParamStorage();
	~CParamStorage();
	void Road();	// �ǂݍ��ݏ���
	void RoadParamSet(FILE*pfile);	// �p�����[�^�[�ǂݍ���
	void RoadCar(FILE* pfile, int Idx);
private:
	TYPE m_type;	// �Ԃ̃^�C�v
	Param m_Param[CAR_MAX];	// �p�����[�^�[�������ϐ�
public:

	//================================================
	// Setter,Getter
	//================================================

	//-- �d�� --
	void SetWeight(float Weight,int idx) { m_Param[idx].fWeight = Weight; }
	float GetWeight(int idx) { return m_Param[idx].fWeight; }

	//-- �M�A�̐� --
	void SetGearMax(int num, int idx) { m_Param[idx].nMaxGear = num; }
	int GetGearMax(int idx) { return m_Param[idx].nMaxGear; }

	//-- �Ȃ���₷�� --
	void SetBending(float benging, int idx) { m_Param[idx].fBending = benging; }
	float GetBending(int idx) { return m_Param[idx].fBending; }

	//-- �M�A���Ƃ̍ō����x --
	void SetMaxSpeed(int idx, float MaxSpeed, int caridx) { m_Param[caridx].fMaxSpeed[idx] = MaxSpeed; }
	float GetfMaxSpeed(int caridx, int idx) { return m_Param[caridx].fMaxSpeed[idx]; }

	//-- �ő�̗� --
	void SetMaxLife(int maxlife, int idx) { m_Param[idx].nMaxLife = maxlife; }
	int GetMaxLife(int idx) { return m_Param[idx].nMaxLife; }

	//-- �^�C�v --
	void SetType(TYPE type, int idx) { m_type = type; }
	TYPE GetType(int idx) { return m_type; }
};


#endif // !PARAM_STORAGE_H_