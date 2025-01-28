#pragma once
//===========================================================================================================================================================
// 
// car.cpp�̃w�b�_�[ [car.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _CAR_H_
#define _CAR_H_
#include "main.h"
#include "param_storage.h"
#include "actor.h"
#include "sphere.h"

class CCar:public CActor
{
private:

	// ���݂̃p�����[�^�[
	struct CurrParam
	{
		int nLife;
		int nGear;
		float Speed;
	};

	// ���C�̎n�_�̈ʒu
	typedef enum
	{
		CENTER = 0,
		FRONT_RIGHT,
		FRONT_LEFT,
		BACK_RIGHT,
		BACK_LEFT,
	}START_POINT;

public:
	// �Ԃ̃A�N�V����
	typedef enum
	{
		NONE = 0,	// ���ʂ̏��
		ACCELE,		// �O�i
		BRAKE,		// ��i
		TURBO,		// �ːi
		DOWN,		// ����
		DRIFTR,		// �h���t�g
		DRIFTL,		// �h���t�g
		MAX
	}ACTION_STATE;

	// �h���t�g�ɕK�v�ȗv�f
	typedef struct
	{
		float Force;	// �h���t�g�����u�Ԃ̑O�i�����
		float Angle;	// �h���t�g�����u�Ԃ̊p�x
	}Forward;

	CCar();
	~CCar()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	void MeshCollision(START_POINT point);	// ���b�V���Ƃ̓����蔻��
	void ViewSetting();	// �\���X�s�[�h�̐ݒ�
	void InitType(CParamStorage::TYPE type);		// �^�C�v���Ƃ̏����ݒ�
	void PramSet();
	void TarboCamera();	// �^�[�{�g�p���̃J�����̋���
	void HitObstacle();	// ��Q���Ɠ�����܂�
	void DrawDistance();	// �`��͈̔͐ݒ�

	static CCar* Create();   // ��������

	//-------------------------------------------------------
	// �Ԃ̃A�N�V����
	//-------------------------------------------------------
	void ActionAccele();	// �A�N�Z��(����
	void ActionBrake();		// �u���[�L(����
	float ActionBend();		// �Ȃ���
	void ActionBend_R();	// �E�ɋȂ���
	void ActionBend_L();	// ���ɋȂ���
	void ActionTurbo();		// �u�[�X�g(�}����
	void ActionAttack();	// �U��(�ːi
	void ActionDown();		// ����
	void ActionDrift();		// �h���t�g����
	void ActionDriftR();		// �h���t�g����
	void ActionDriftL();		// �h���t�g����

	void ActionUpdate();	// �A�N�V�������̍X�V����(�ȍ~ ActionUpdate = AU �Ɨ���
	void AUdown();			// �_�E�����̍X�V����
	//===================================================================

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//======================================================================
	// �h���t�g�������p
	//======================================================================
public:
	typedef struct
	{
		float Current;	// ���݂̊p�x
		float Target;	// �ړI�̊p�x
	}Drift_Direction;
private:
	void StartDrift();	// �h���t�g���J�n
	bool m_IsDrift;	// �h���t�g�����Ă��邩�ǂ���
	float m_ChargeTime;	// �h���t�g�`���[�W����
	Drift_Direction m_DDire;	// �h���t�g�̊p�x
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
private:
	CurrParam m_CurrParam;			// ���݂̃p�����[�^�[
	CParamStorage::Param m_Param;	// �p�����[�^�[�������ϐ�
	CParamStorage::TYPE m_type;		// �Ԃ̃^�C�v
	ACTION_STATE m_Action;			// �Ԃ̌��݂̏��

	float m_fAccumulationSpeed;		// �~�σX�s�[�h(���݂̃X�s�[�h
	float m_fOldSpeed;				// �~�σX�s�[�h(1�t���[���O
	D3DXVECTOR3 m_oldmove;			// �ߋ��̈ړ��l
	D3DXVECTOR3 m_oldrot;			// �ߋ��̊p�x
	float m_fMoveAngle;				// �ړ�����
	int m_nTurboInterval;			// �^�[�{�̊Ԋu
	bool m_bDeath;	// ���񂾔���
	int m_nDeathCount;	// ���񂾌�ɏ����t���[�����J�E���g
	int m_nDownCount;	// �_�E����Ԃ���N���オ��܂ł̃J�E���g�ϐ�
	bool m_bDisDraw;	// �����ɂ���ĕ`�悷�邩���߂�

	Forward m_ForwardInfo;	// �h���t�g�̏��

	float m_fDriftTargetRot;	// �h���t�g���̉�]

	CSphere* m_pSphere;	// �����蔻��̉���
public:

	//================================================
	// Setter,Getter
	//================================================

	//-- �d�� --
	void SetWeight(float Weight) { m_Param.fWeight = Weight; }
	float GetWeight() { return m_Param.fWeight; }

	//-- �M�A�̐� --
	void SetGearNum(int num) { m_Param.nMaxGear = num; }
	int GetGearNum() { return m_Param.nMaxGear; }
	
	//-- �Ȃ���₷�� --
	void SetBending(float benging) { m_Param.fBending = benging; }
	float GetBending() { return m_Param.fBending; }

	//-- �M�A���Ƃ̍ō����x --
	void SetMaxSpeed(int idx, float MaxSpeed) { m_Param.fMaxSpeed[idx] = MaxSpeed; }
	float GetfMaxSpeed(int idx) { return m_Param.fMaxSpeed[idx]; }

	//-- �ő�̗� --
	void SetMaxLife(int maxlife) { m_Param.nMaxLife = maxlife; }
	int GetMaxLife() { return m_Param.nMaxLife; }

	//-- �^�C�v --
	void SetTypeCar(CParamStorage::TYPE type) { m_type = type; }
	CParamStorage::TYPE GetTypeCar() { return m_type; }

	//-- �~�σX�s�[�h --
	void SetAccumulationSpeed(float speed) { m_fAccumulationSpeed = speed; }
	float GetAccumulationSpeed() { return m_CurrParam.Speed; }

	//-- �~�σX�s�[�h --
	void SetGear(int gear) { m_CurrParam.nGear = gear; }
	int GetGear() { return m_CurrParam.nGear; }

	//-- �ړ����� --
	float GetMoveAngle() { return m_fMoveAngle; }

	//-- ���񂾂��ǂ��� --
	void SetDeath() { m_bDeath = true; }
	bool GetDeath() { return m_bDeath; }
	
	//-- �Ԃ̃A�N�V���� --
	void SetActionState(ACTION_STATE state) { m_Action = state; }
	ACTION_STATE GetActionState() { return m_Action; }

	//-- �O�i����� --
	void SetForwardForce(float force) { m_ForwardInfo.Force = force; }
	float GetForwardForce() { return m_ForwardInfo.Force; }

	//-- ��]�x --
	void SetForwardAngle(float angle) { m_ForwardInfo.Angle = angle; }
	float GetForwardAngle() { return m_ForwardInfo.Angle; }

	//-- �h���t�g�̏�� --
	void SetForwardInfo(Forward forward) { m_ForwardInfo = forward; }
	Forward GetForwardInfo() { return m_ForwardInfo; }
};

#endif // !CAR_H_