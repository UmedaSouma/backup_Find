#pragma once
//===========================================================================================================================================================
// 
// check_point.cppのヘッダー [check_point.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _CHECK_POINT_H_
#define _CHECK_POINT_H_
#include "main.h"
#include "course_point.h"
#include "car_player.h"

class CCheckPoint
{
private:
	// ソートに必要な情報の構造体
	typedef struct
	{
		int Idx;	// ポイントの番号
		float pos;	// 位置
	}SortInfo;
public:
	CCheckPoint();
	~CCheckPoint();
	void SearchNearPoint();	// 近くにあるチェックポイントを探す
	int LookDis(CCarPlayer* player, std::vector<CCoursePoint*>point, unsigned int size);	// 2点の距離を見る
	int SortDis(SortInfo sort1, SortInfo sort2);	// 一番近いチェックポイントをソートする
	void Reset();	// チェックポイントを通ったことをリセットする

private:
	SortInfo m_Info[2];	// ソートに必要な情報
};




#endif // !CHECK_POINT_H_