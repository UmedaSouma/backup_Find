//===========================================================================================================================================================
// 
// �`�F�b�N�|�C���g�̏��� [check_point.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "check_point.h"
#include "car_player.h"
#include "course_point.h"
#include "search.h"

CCheckPoint::CCheckPoint()
{
}

CCheckPoint::~CCheckPoint()
{
}

void CCheckPoint::SearchNearPoint()
{
	// ���ꂼ��̊i�[����ϐ���錾
	CCarPlayer* pPlayer = nullptr;		// �v���C���[���i�[����ϐ�
	pPlayer = CSearch::SearchObject(pPlayer, CObject::CAR_PLAYER);

	// �v���C���[�����݂��Ȃ�������
	if (pPlayer == nullptr) 
	{ return; }

	std::vector<CCoursePoint*>pCourseP;	// �R�[�X�|�C���g���i�[����ϐ�
	pCourseP.clear();

	// �R�[�X�|�C���g�̃|�C���^��T��
	pCourseP = CSearch::SearchMultiObject(pCourseP, CObject::POINT);

	// �󂾂�����ʂ��Ȃ�
	if (pCourseP.empty()) 
	{ return; }

	int sortIdx = 0;	// 
	unsigned int pointnum = 0;	// �R�[�X�|�C���g�̐����i�[����ϐ�
	pointnum = pCourseP.size();	// �R�[�X�|�C���g�̐��𒲂ׂ�

	for (unsigned int i = 0; i < pointnum; i++)
	{

	}

	pCourseP.clear();
}