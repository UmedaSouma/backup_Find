//===========================================================================================================================================================
// 
// camera.cpp�̃w�b�_�[
// Author : souma umeda
// 
//===========================================================================================================================================================
//===========================================================================================================================================================
// 
// camera.cpp�̃w�b�_�[
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

class CCamera
{
private:
	const float ROT_SPEED = 0.1f;

public:
	// �J�����̃^�[�Q�b�g�̎��
	typedef enum
	{
		NONE = 0,	// �����Ȃ�
		PLAYER,		// �v���C���[�ɒǔ�(�ړ�����]���ǔ�)
		MAX
	}CAMERA_TARGET_TYPE;

	CCamera();
	~CCamera();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void UpdateInput();
	void SetCamera();	// �J�����̐ݒ�
	void SetTargetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot) { m_targetrot = rot; }
	void SetFollow(float follow) { m_follow = follow; }
	float GetFollow() { return m_follow; }
	void SetShake(int frame, float strength);	// �J�����h��̏���
	
private:
	D3DXVECTOR3 m_posV;
	D3DXVECTOR3 m_posR;
	D3DXVECTOR3 m_targetpos;
	D3DXVECTOR3 m_vecU;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_targetrot;
	D3DXMATRIX m_mtxProjection;
	D3DXMATRIX m_mtxView;
	float m_fDis;
	float m_follow=0.001f;
	int nCntFollow;
	int m_nFrame;	// �J�����h��̃t���[����
	float m_fStrength;	// �J�����h��̋��x
	CAMERA_TARGET_TYPE m_TargetType;	// �J�����^�[�Q�b�g�̎��
public:
	void SetCameraTarget(CAMERA_TARGET_TYPE type) { m_TargetType = type; }	// �J�����^�[�Q�b�g�̐ݒ�
	CAMERA_TARGET_TYPE GetCameraTarget() { return m_TargetType; }			// �J�����^�[�Q�b�g�̎擾
	D3DXVECTOR3 GetPos() { return m_posV; }
	D3DXVECTOR3 GetRot() { return m_rot; }
};



//// �J�����̍\����
//typedef struct
//{
//	D3DXVECTOR3 posV;			// ���_
//	D3DXVECTOR3 posR;			// �����_
//	D3DXVECTOR3 vecU;			// ������x�N�g��
//	D3DXVECTOR3 rot;
//	D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
//	D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
//	D3DXVECTOR3 targetPosV;
//	D3DXVECTOR3 targetPosR;
//	D3DXVECTOR3 fDis;
//}Camera;
//
//// �v���g�^�C�v�錾
//void InitCamera(void);
//void UninitCamera(void);
//void UpdateCamera(void);
//void SetCamera(void);
//Camera* GetCamera(void);
//void SetPosCamera(D3DXVECTOR3 pos);

#endif