//===========================================================================================================================================================
// 
// �S�[���̃��f���ƃS�[������ [goal.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "goal.h"
#include "search.h"
#include "collision.h"
#include "manager.h"

std::vector<int> g_aa;

//========================================================================================================================
// �R���X�g���N�^
//========================================================================================================================
CGoal::CGoal(int nPrio) :CModel(nPrio),
m_runtype(RUN_NONE)
, m_nOrder{ -1,-1 }
, m_DireTravel(0)
, m_nLaps(0)
{
	g_aa.clear();
}

//========================================================================================================================
// �f�X�g���N�^
//========================================================================================================================
CGoal::~CGoal()
{
}

//========================================================================================================================
// �����ݒ�
//========================================================================================================================
HRESULT CGoal::Init()
{
	SetModel("data\\MODEL\\goal.x");
	SetPos({ 200,0,0 });


	SetScale(GetScale() * 1.2f);

	CModel::Init();

	SetType(GOAL);

	return S_OK;
}

//========================================================================================================================
// �I������
//========================================================================================================================
void CGoal::Uninit()
{
	CModel::Uninit();
}

//========================================================================================================================
// �X�V����
//========================================================================================================================
void CGoal::Update()
{
	CCarPlayer* pPlayer = nullptr;
	pPlayer = CSearch::SearchObject(pPlayer, CObject::CAR_PLAYER);

	if (pPlayer == nullptr)
	{ return; }

	D3DXVECTOR3 Fpos = GetPos();
	D3DXVECTOR3 Lpos = GetPos();
	D3DXVECTOR3 RePos = GetPos();
	D3DXVECTOR3 size = { 500.0f,500.0f,50.0f };
	Fpos.z -= 300.0f;	// �S�[�����猩�Ĉ�Ԏ�O�̃|�C���g
	Lpos.z -= 100.0f;	// �S�[���ɋ߂���O
	RePos.z += 100.0f;	// �|�C���g�ɒ��������������Z�b�g����

	// ���ꂼ��̃|�C���g�ɓ��B�����Ƃ�
	if (CCollision::BoxTrigger(Fpos, size, pPlayer->GetPos(), pPlayer->GetSize()))
	{
		GoalPointOrder(POINT_IN_FRONT);
	}
	if (CCollision::BoxTrigger(Lpos, size, pPlayer->GetPos(), pPlayer->GetSize()))
	{
		GoalPointOrder(POINT_IN_BACK);
	}
	if (CCollision::BoxTrigger(RePos, size, pPlayer->GetPos(), pPlayer->GetSize()))
	{
		for (int i = 0; i < ORDER_MAX; i++)
		{
			m_nOrder[i] = -1;	// ���ԃ��Z�b�g
		}
	}

	if (m_DireTravel == RUN_FRONT)
	{// ���������s������
		m_DireTravel = RUN_NONE;	// ���Z�b�g����
		m_nLaps += 1;	// ���񐔂𑝂₷
	}

	// �񐔕��S�[���܂œ��B������
	if (m_nLaps == GOAL_LAPS)
	{
		CFade* pFade = CManager::GetFade();
		pFade->SetFade(CScene::MODE_RESULT);
	}
	
	
	//if (CCollision::BoxTrigger(Fpos, size, pPlayer->GetPos(), pPlayer->GetSize()))
	//{
	//	g_aa.push_back(1);

	//	/*RUNTYPE runtype = RUN_NONE;
	//	runtype = CollisionGoalPlayer(pPlayer);

	//	switch (runtype)
	//	{
	//	case RUN_BACK:

	//		break;

	//	case RUN_FRONT:
	//	case RUN_NONE:

	//		CFade* pFade = CManager::GetFade();
	//		pFade->SetFade(CScene::MODE_RESULT);

	//		break;
	//	}	*/
	//}

	//if (CCollision::BoxTrigger(Lpos, size, pPlayer->GetPos(), pPlayer->GetSize()))
	//{
	//	g_aa.push_back(2);
	//}

	//int bb = 0;
	//int b = 0;
	//int i = 0;
	//for (auto itr = g_aa.rbegin(); itr != g_aa.rend(); ++itr)
	//{
	//	if (i == 0)
	//	{
	//		bb = *itr;
	//	}
	//	if (i == 1)
	//	{
	//		b = *itr;
	//	}
	//	i++;
	//}

	//if (bb == 2 && b == 1)
	//{
	//	CFade* pFade = CManager::GetFade();
	//	pFade->SetFade(CScene::MODE_RESULT);
	//}


	CModel::Update();
}

//========================================================================================================================
// �`�揈��
//========================================================================================================================
void CGoal::Draw()
{
	CModel::Draw();
}

//========================================================================================================================
// �S�[���ƃv���C���[�̓����蔻��
//========================================================================================================================
CGoal::RUNTYPE CGoal::CollisionGoalPlayer(CCarPlayer* pPlayer)
{
	D3DXVECTOR3 oldpos = pPlayer->GetOldPos();
	RUNTYPE runtype = RUN_NONE;

	if (oldpos.z > pPlayer->GetPos().z)
	{
		runtype = RUN_BACK;
	}
	else if (oldpos.z < pPlayer->GetPos().z)
	{
		runtype = RUN_FRONT;
	}

	return runtype;
}

//===========================================================================================================
// �S�[���|�C���g�̏��Ԃ��o���֐�
//===========================================================================================================
void CGoal::GoalPointOrder(GOAL_POINT point)
{
	// ���X�g�������ł���΂����͒ʂ��Ȃ�
	// �����Ɠ������������̂�������邽��
	if (m_nOrder[ORDER_LAST] == point)
	{ return; }

	// ���Ԃ��X�V����
	m_nOrder[ORDER_FIRST] = m_nOrder[ORDER_LAST];
	m_nOrder[ORDER_LAST] = point;
	
	{// ���Ԃɂ��v�Z���ʂ𔽉f
		if (m_nOrder[ORDER_FIRST] == POINT_IN_FRONT
			&& m_nOrder[ORDER_LAST] == POINT_IN_BACK)
		{
			m_DireTravel += 1;
		}

		if (m_nOrder[ORDER_FIRST] == POINT_IN_BACK
			&& m_nOrder[ORDER_LAST] == POINT_IN_FRONT)
		{
			m_DireTravel -= 1;
		}
	}
}

//========================================================================================================================
// ��������
//========================================================================================================================
CGoal* CGoal::Create()
{
	CGoal* pGoal = new CGoal;
	pGoal->Init();

	return pGoal;
}