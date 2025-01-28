//===========================================================================================================================================================
// 
// �v�Z [calculation.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "calculation.h"

CCalculation::CCalculation()
{
}

CCalculation::~CCalculation()
{
}

//===========================================================================================================
// �p�x�␳�v�Z
//===========================================================================================================
float CCalculation::FixAngle(float Angle, float TargetAngle)
{
	// �ړI�̊p�x�ƌ��݂̊p�x�̍���
	float Diff = TargetAngle - Angle;

	// ���� �}�� ��������␳������
	if (Diff > D3DX_PI)
	{
		TargetAngle -= D3DX_PI * 2;
	}
	if (Diff < -D3DX_PI)
	{
		TargetAngle += D3DX_PI * 2;
	}

	return TargetAngle;
}

float CCalculation::DemandAngle(D3DXVECTOR3 posA, D3DXVECTOR3 posB)
{
	// 2�_�̍��W�Ŋp�x���Z�o����
	float ResultRot = 0.0f;		// �v�Z���ʂ�����ϐ�
	float Z = posA.z - posB.z;	// Z�̑傫���𑪂�
	float X = posA.x - posB.x;	// X�̑傫���𑪂�
	ResultRot = atan2f(X, Z);	// �v�Z

	return ResultRot;
}

//===========================================================================================================
// �����v�Z
//===========================================================================================================
float CCalculation::Ratio(float Max, float Curr)
{
	float Ratio = Curr / Max;

	return Ratio;
}


//===========================================================================================================
// �����v�Z
//===========================================================================================================
D3DXVECTOR3 CCalculation::ShiftPosition(D3DXVECTOR3 pos,D3DXVECTOR3 rot, D3DXVECTOR2 shiftsize, ROT_AXIS axis)
{
	D3DXVECTOR3 resultpos = pos;
	float fRot = 0.0f;
	float fPos_1 = 0.0f;
	float fPos_2 = 0.0f;

	// �Ίp��
	float fLength = sqrtf(shiftsize.x * shiftsize.x + shiftsize.y * shiftsize.y);
	// �p�x
	float fAngle = atan2f(shiftsize.x, shiftsize.y);

	switch (axis)
	{
	case ROT_X:

		break;

	case ROT_Y:
		// �ʒu��ݒ�
		resultpos.x += sinf(rot.y - fAngle) * fLength;
		resultpos.z += cosf(rot.y - fAngle) * fLength;

		break;

	case ROT_Z:

		break;
	}

	//// �ʒu��ݒ�
	//resultpos.x += sinf(rot.y - fAngle) * fLength;
	//resultpos.z += cosf(rot.y - fAngle) * fLength;

	return resultpos;
}

//===========================================================================================================
// 2�_�Ԃ̋������v�Z����
//===========================================================================================================
float CCalculation::TwoPointDistance(D3DXVECTOR3 posA, D3DXVECTOR3 posB)
{
	float LengthX = posA.x - posB.x;
	float LengthY = posA.z - posB.z;

	float ResultDis = sqrtf(LengthX * LengthX + LengthY * LengthY);

	return ResultDis;
}

float CCalculation::TwoPointDistanceHeight(D3DXVECTOR3 posA, D3DXVECTOR3 posB)
{
	float LengthX = posA.x - posB.x;
	float LengthY = posA.y - posB.y;

	float ResultDis = sqrtf(LengthX * LengthX + LengthY * LengthY);

	return ResultDis;
}

//===========================================================================================================
// �����_���Ȑ����𐶐�
//===========================================================================================================
uint64_t CCalculation::RandomInt(uint64_t min, uint64_t max)
{
	static std::mt19937_64 mt64(0);
	std::uniform_int_distribution<uint64_t>randint(min, max);

	return randint(mt64);
}
