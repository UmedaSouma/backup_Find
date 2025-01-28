//===========================================================================================================================================================
// 
// チェックポイントの処理 [check_point.cpp]
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
	// それぞれの格納する変数を宣言
	CCarPlayer* pPlayer = nullptr;		// プレイヤーを格納する変数
	pPlayer = CSearch::SearchObject(pPlayer, CObject::CAR_PLAYER);

	// プレイヤーが存在しなかったら
	if (pPlayer == nullptr) 
	{ return; }

	std::vector<CCoursePoint*>pCourseP;	// コースポイントを格納する変数
	pCourseP.clear();

	// コースポイントのポインタを探す
	pCourseP = CSearch::SearchMultiObject(pCourseP, CObject::POINT);

	// 空だったら通さない
	if (pCourseP.empty()) 
	{ return; }

	int sortIdx = 0;	// 
	unsigned int pointnum = 0;	// コースポイントの数を格納する変数
	pointnum = pCourseP.size();	// コースポイントの数を調べる

	for (unsigned int i = 0; i < pointnum; i++)
	{

	}

	pCourseP.clear();
}