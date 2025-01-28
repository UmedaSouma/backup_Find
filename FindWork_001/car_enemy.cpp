//===========================================================================================================================================================
// 
// �G�̎� [car_enemy.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "car_enemy.h"
#include "car_player.h"
#include "search.h"
#include "manager.h"
#include "collision.h"
#include "course_point.h"
#include "search.h"
#include "text.h"
#include "manager.h"
#include "calculation.h"
#include "backlight.h"
#include "countdown.h"
#include "game.h"
#include "bomb.h"
#include <random>

//========================================================================================================================
// �R���X�g���N�^
//========================================================================================================================
CCarEnemy::CCarEnemy() :
	m_nCnt(0),
	m_bRouteClear(true),
	m_NextRoute({ 0.0f,0.0f,0.0f }),
	m_NextIdx(-1)
{
}

//========================================================================================================================
// �f�X�g���N�^
//========================================================================================================================
CCarEnemy::~CCarEnemy()
{
}

//========================================================================================================================
// �����ݒ�
//========================================================================================================================
HRESULT CCarEnemy::Init()
{
	InitRandTargetPoint();

	SetType(TYPE::CAR_ENEMY);
	SetSize({ 10.0f,10.0f,30.0f });
	SetGravity(true);
	CCar::Init();

	return S_OK;
}

//========================================================================================================================
// �I������
//========================================================================================================================
void CCarEnemy::Uninit()
{
	CCar::Uninit();
}

//========================================================================================================================
// �X�V����
//========================================================================================================================
void CCarEnemy::Update()
{
	CCountdown* pCD = CGame::GetCountDown();
	if (pCD != nullptr)
	{
		if (pCD->GetUse())
		{
			return;
		}
	}

	CCar::Update();

	// �Ԃ��_�E����Ԃ�������ȍ~�̏��������Ȃ�
	if (GetActionState() == CCar::ACTION_STATE::DOWN) 
	{ return; }

	BlowAwayPtoE();
	//BlowAwayEtoE();

	if (GetDeath())
	{ return; }

	Route();

	TargetRouteUpdate();

}

//========================================================================================================================
// �`�揈��
//========================================================================================================================
void CCarEnemy::Draw()
{
	CCar::Draw();
}

//===========================================================================================================
// �Ԃ���΂���鏈��(�v���C���[�ƓG)
//===========================================================================================================
void CCarEnemy::BlowAwayPtoE()
{
	CCarPlayer* pCarP = nullptr;
	pCarP = CSearch::SearchObject(pCarP, CObject::TYPE::CAR_PLAYER);

	// �v���C���[�����݂��Ȃ������珈���͒ʂ��Ȃ�
	if (pCarP == nullptr)
	{	return;	};
	
	// ����������
	//if (CCollision::BoxTrigger(pCarP->GetPos(), pCarP->GetSize(), GetPos(), GetSize()))
	if (CCollision::SphereTrigger(pCarP->GetPos(),30, GetPos(), 30))
	{
		D3DXVECTOR3 move = { 0,0,0 };

		// ���݂̃v���C���[�̑��x
		float Speed = pCarP->GetAccumulationSpeed();
		float eSpeed = GetAccumulationSpeed();

		// �v���C���[�Ɠ��������Ԃ̈ʒu�Ŋp�x���Z�o����
		float ResultRot = 0.0f;		// �v�Z���ʂ�����ϐ�
		float Z = pCarP->GetPos().z - GetPos().z;	// Z�̑傫���𑪂�
		float X = pCarP->GetPos().x - GetPos().x;	// X�̑傫���𑪂�
		ResultRot = atan2f(X, Z);	// �v�Z

		float R = Speed - eSpeed;

	
		if(R <= 0)
		{
			if (!GetDeath()) 
			{ return; }
			move = pCarP->GetMove();

			eSpeed *= 1.f;

			//// �X�s�[�h�̕���΂�
			//pCarP->SetMove({
			//	(sinf(D3DX_PI - ResultRot) * -eSpeed) + -move.x,
			//	(eSpeed * 0.01f) + move.y ,
			//	(cosf(D3DX_PI - ResultRot) * eSpeed) + -move.z
			//	});
		}
		else
		{
			move = GetMove();

			Speed *= 0.5f;

			if (GetTypeCar() == CParamStorage::TYPE::CAR_BOMB)
			{
				pCarP->ActionDown();

				D3DXVECTOR3 pos = GetPos();
				pos.y += 100;

				CBomb::Create(pos, 1);
				Uninit();
			}

			// �X�s�[�h�̕���΂�
			SetMove({
				(sinf(D3DX_PI - ResultRot) * -Speed) + move.x,
				(Speed * 1.f) + move.y ,
				(cosf(D3DX_PI - ResultRot) * Speed) + move.z
				});

			if (GetTypeCar() != CParamStorage::CAR_BOMB)
			{
				// �ԕύX
				pCarP->ChangeCar(GetTypeCar());
			}

			pCarP->ActionTurbo();

			pCarP->SetRecoveryGauge(1000);

			if (!GetDeath())
			{
				SetDeath();	// �����g��Ȃ��I�I
			}
		}
		

		
	}
}

//===========================================================================================================
// �Ԃ���΂���鏈��(�G�ƓG)
//===========================================================================================================
void CCarEnemy::BlowAwayEtoE()
{
	std::vector<CCarEnemy*>pEnemy;
	pEnemy.clear();

	pEnemy = CSearch::SearchMultiObject(pEnemy, CObject::CAR_ENEMY);
	if (pEnemy.empty()) { return; }

	unsigned int eSize = pEnemy.size();
	for (unsigned int i = 0; i < eSize; i++)
	{
		if(pEnemy[i]==this)
		{// �����I�u�W�F�N�g�������画�肵�Ȃ�
			return;
		}

		if (CCollision::BoxTrigger(pEnemy[i]->GetPos(), pEnemy[i]->GetSize(), GetPos(), GetSize()))
		{
			D3DXVECTOR3 move = GetMove();

			// ���݂̃v���C���[�̑��x
			float Speed = pEnemy[i]->GetAccumulationSpeed();

			// �v���C���[�Ɠ��������Ԃ̈ʒu�Ŋp�x���Z�o����
			float ResultRot = 0.0f;		// �v�Z���ʂ�����ϐ�
			float Z = pEnemy[i]->GetPos().z - GetPos().z;	// Z�̑傫���𑪂�
			float X = pEnemy[i]->GetPos().x - GetPos().x;	// X�̑傫���𑪂�
			ResultRot = atan2f(X, Z);	// �v�Z

			Speed *= 0.1f;

			// �X�s�[�h�̕���΂�
			SetMove({
				(sinf(D3DX_PI - ResultRot) * -Speed) + move.x,
				(Speed * 0.1f) + move.y ,
				(cosf(D3DX_PI - ResultRot) * Speed) + move.z
				});

			pEnemy[i]->SetMove({
				(sinf(D3DX_PI - ResultRot) * -Speed) + -move.x,
				(Speed * 0.1f) + move.y ,
				(cosf(D3DX_PI - ResultRot) * Speed) + -move.z
				});
		}
	}

}

//========================================================================================================================
// ��������
//========================================================================================================================
CCarEnemy* CCarEnemy::Create(CParamStorage::TYPE cartype, D3DXVECTOR3 pos)
{
	CCarEnemy* pCarEnemy = new CCarEnemy;

	//pCarEnemy->SetPos(pos);
	pCarEnemy->InitType(cartype);

	pCarEnemy->Init();

	return pCarEnemy;
}

//===========================================================================================================
// ���̃��[�g��ݒ肷��
//===========================================================================================================
void CCarEnemy::Route()
{
	// �܂����̃^�[�Q�b�g�܂œ��B���Ă��Ȃ�������
	if (!m_bRouteClear) 
	{ return; }

	using namespace std;
	vector<CCoursePoint*>pCoursePoint;
	int nCnt = m_nCnt;

	// �����̃|�C���g��T��
	pCoursePoint.clear();
	pCoursePoint = CSearch::SearchMultiObject(pCoursePoint, CObject::POINT);

	// vector�̒��g���󂾂����珈�����s��Ȃ�
	if (pCoursePoint.empty()) { return; }

	// �T�C�Y�����炩���ߕʂ̕ϐ��ɓ���Ă���
	unsigned int coursesize = pCoursePoint.size();

	for (unsigned int i = 0; i < coursesize; i++)
	{
		if (pCoursePoint[i]->GetIdx() == m_nCnt)
		{// �C���f�b�N�X���ɂȂ�悤�ɂ���
			// ���̃^�[�Q�b�g��ݒ肷��
			SetTargetRoute(pCoursePoint[i]->GetPos());
			SetNextIdx(pCoursePoint[i]->GetIdx());
			break;
		}
	}

	// �J�E���g��i�߂�
	m_nCnt++;
	m_nCnt %= coursesize;	// �T�C�Y�ŏ�]�Z���Ă���

	// ���̃^�[�Q�b�g�ɓ��B���Ă��Ȃ��ɐݒ肷��
	m_bRouteClear = false;
}

//===========================================================================================================
// ���̃^�[�Q�b�g�ɓ��B����܂ł̍X�V����
//===========================================================================================================
void CCarEnemy::TargetRouteUpdate()
{
	// ���̃^�[�Q�b�g�ɓ��B���Ă�����
	if (m_bRouteClear)
	{ return; }

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size= GetSize();
	
	D3DXVECTOR3 targetsize = { 100.0f,10.0f,100.0f };

	// ���݂̃v���C���[�̑��x
	float Speed = 3.0f;

	// ���̃|�C���g�܂ł̊p�x���Z�o����
	float ResultRot = 0.0f;		// �v�Z���ʂ�����ϐ�
	float Z = m_NextRoute.z - pos.z;	// Z�̑傫���𑪂�
	float X = m_NextRoute.x - pos.x;	// X�̑傫���𑪂�
	ResultRot = atan2f(X, Z);	// �v�Z

	float rotY = GetRot().y;	// ���݂̊p�x

	// �p�x�␳�̌v�Z
	ResultRot = CCalculation::FixAngle(rotY, ResultRot);

	if (rotY - ResultRot >= -0.15f && rotY - ResultRot <= 0.15f)
	{// �p�x��������x�����Ă�����
		// �������Ȃ��ł܂���������
	}
	else if (rotY < ResultRot)
	{// �ړI�̊p�x��菬����������
		ActionBend_R();		// �E�ɋȂ���
	}
	else if(rotY > ResultRot)
	{// �ړI�̊p�x���傫��������
		ActionBend_L();		// ���ɋȂ���
	}

	// �O�i������
	ActionAccele();

	// ���̃|�C���g�ֈړ�����
	//D3DXVECTOR3 move = { sinf(D3DX_PI - ResultRot) * -Speed,0.0f,cosf(D3DX_PI - ResultRot) * Speed };
	//pos += move;
	//SetPos(pos);

	D3DXVECTOR3 move = { 0.0f,0.0f ,0.0f };

	//if (CCollision::BoxTrigger(pos, size, m_NextRoute, targetsize))
	if (CCollision::CircleTrigger(pos, size.z, m_NextRoute, targetsize.x))
	{// �|�C���g�ɓ��B������
		m_bRouteClear = true;
	}

	// �f�o�b�O�\��
	CManager::GetRenderer()->SetDebugRoutePoint(pos, move, m_NextRoute,m_NextIdx, m_bRouteClear);
}

void CCarEnemy::InitTargetPoint()
{
	using namespace std;
	vector<CCoursePoint*>pCoursePoint;
	int nCnt = m_nCnt;

	// �����̃|�C���g��T��
	pCoursePoint.clear();
	pCoursePoint = CSearch::SearchMultiObject(pCoursePoint, CObject::POINT);

	// vector�̒��g���󂾂����珈�����s��Ȃ�
	if (pCoursePoint.empty()) { return; }

	// �T�C�Y�����炩���ߕʂ̕ϐ��ɓ���Ă���
	unsigned int coursesize = pCoursePoint.size();
	float Curr, Prev, Near=0.0f;	// ��r�p(���݁A�ЂƂO�A�߂�������

	for (unsigned int i = 0; i < coursesize; i++)
	{
		if (i == 0) 
		{ continue; }

		if (Near == 0.0f)
		{
			D3DXVECTOR3 currpos, prevpos;	// ��r�p
			currpos = pCoursePoint[i]->GetPos();
			prevpos = pCoursePoint[i - 1]->GetPos();

			Curr = CCalculation::TwoPointDistance(currpos, GetPos());
			Prev = CCalculation::TwoPointDistance(prevpos, GetPos());
		}
		else
		{

		}

		
	}
}

//===========================================================================================================
// �����_���ȃ^�[�Q�b�g�|�C���g�ɔz�u����
//===========================================================================================================
void CCarEnemy::InitRandTargetPoint()
{
	using namespace std;
	vector<CCoursePoint*>pCoursePoint;
	int nCnt = m_nCnt;
	mt19937_64 mt_64(0);

	// �����̃|�C���g��T��
	pCoursePoint.clear();
	pCoursePoint = CSearch::SearchMultiObject(pCoursePoint, CObject::POINT);

	// vector�̒��g���󂾂����珈�����s��Ȃ�
	if (pCoursePoint.empty())
	{ return; }

	// �T�C�Y�����炩���ߕʂ̕ϐ��ɓ���Ă���
	unsigned int coursesize = pCoursePoint.size();

	uint64_t Idx = CCalculation::RandomInt((uint64_t)0, (uint64_t)coursesize);

	for (unsigned int i = 0; i < coursesize; i++)
	{
		if (pCoursePoint[i]->GetIdx() == Idx)
		{// �C���f�b�N�X���ɂȂ�悤�ɂ���

			int plus = 1;

			if (i >= coursesize-1)
			{// �z��I�[�o�[�ɂȂ�Ȃ��悤��
				plus = -1 * i;
			}

			SetPos(pCoursePoint[i]->GetPos());
			SetRot(pCoursePoint[i]->GetRot());
			SetNextIdx((int)Idx + plus);
			SetTargetRoute(pCoursePoint[i + plus]->GetPos());

			m_nCnt = (int)Idx;
			m_nCnt %= coursesize;	// �T�C�Y�ŏ�]�Z���Ă���
		}
	}

	
}