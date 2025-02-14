//===========================================================================================================================================================
// 
// チェックポイントの処理 [check_point.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "check_point.h"
#include "search.h"
#include "calculation.h"

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CCheckPoint::CCheckPoint()
{
	for (int i = 0; i < 2; i++)
	{
		m_Info[i].Idx = 0;
		m_Info[i].pos = 0.0f;
	}
	
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CCheckPoint::~CCheckPoint()
{
}

//===========================================================================================================
// 近くのポイントを探す
//===========================================================================================================
void CCheckPoint::SearchNearPoint()
{
	// それぞれの格納する変数を宣言
	CCarPlayer* pPlayer = nullptr;		// プレイヤーを格納する変数
	pPlayer = CSearch::SearchObject(pPlayer, CObject::CAR_PLAYER);

	// プレイヤーが存在しなかったら
	if (pPlayer == nullptr) 
	{ return; }

	std::vector<CCoursePoint*>pCourseP;	// コースポイントを格納する変数
	pCourseP.clear();	// 初期化

	// コースポイントのポインタを探す
	pCourseP = CSearch::SearchMultiObject(pCourseP, CObject::POINT);

	// 空だったら通さない
	if (pCourseP.empty()) 
	{ return; }

	unsigned int pointnum = 0;	// コースポイントの数を格納する変数
	pointnum = pCourseP.size();	// コースポイントの数を調べる

	// 一番近いチェックポイントを探す
	int Idx = 0;	// コースポイントの番号格納変数
	Idx = LookDis(pPlayer, pCourseP, pointnum);	// すべてのコースポイントをソートする

	// プレイヤーをチェックポイントに配置する
	pPlayer->SetPos(pCourseP[Idx]->GetPos());
	pPlayer->SetRot(pCourseP[Idx]->GetRot());

	// vector の初期化
	pCourseP.clear();

}

//===========================================================================================================
// コースポイントのソート
//===========================================================================================================
int CCheckPoint::LookDis(CCarPlayer* player, std::vector<CCoursePoint*> point, unsigned int size)
{
	D3DXVECTOR3 ppos = player->GetPos();	// プレイヤーの位置

	// プレイヤーとコースポイントの距離を格納する変数
	float Pos1,Pos2 = 0.0f;	// 現在と次の番号の変数を用意
	int nearIdx = 0;	// 近かったインデックスを格納する変数

	for (unsigned int i = 0; i < size; i++)
	{// 初回で通った時
	 // 比較するものがないため 0 と 1 で比べる
		if (i == 0)
		{// for文が0番目の時
			// プレイヤーとポイントの距離を求める
			Pos1 = CCalculation::TwoPointDistance(ppos, point[i]->GetPos());
			Pos2 = CCalculation::TwoPointDistance(ppos, point[i + 1]->GetPos());

			// 構造体の情報を格納
			m_Info[0].Idx = i;	// カウントをインデックスに設定
		}
		else
		{
			if (i < size - 1)
			{// 配列オーバーさせない
				// プレイヤーとポイントの距離を求める
				Pos1 = CCalculation::TwoPointDistance(ppos, point[nearIdx]->GetPos());
				Pos2 = CCalculation::TwoPointDistance(ppos, point[i + 1]->GetPos());

				// 構造体の情報を格納
				m_Info[0].Idx = nearIdx;	// 比較して近かった方のインデックスを設定
			}
		}

		if (i < size - 1)
		{// 配列オーバーさせない
			// 構造体の情報を格納
			m_Info[0].pos = Pos1;	// 比較用のposを設定
			m_Info[1].Idx = i + 1;		// 一つ先のカウントを設定
			m_Info[1].pos = Pos2;	// 比較用のposを設定
		}

		// 2点の距離をソートする
		nearIdx = SortDis(m_Info[0], m_Info[1]);	// 近くだった方のインデックスを保存する
	}

	// 一番近いポイントを通っていたら
	if(point[nearIdx]->GetPassPoint())
	{	return nearIdx;	}

	// この下は通っていなかった時の処理
	else

	// 番号が -1 にならないように
	if (nearIdx == 0)
	{	nearIdx = 1;	}

	// 一番近いポイントの前の番号を返す
	return nearIdx - 1;
}

//===========================================================================================================
// 2点の距離を比べる
//===========================================================================================================
int CCheckPoint::SortDis(SortInfo sort1, SortInfo sort2)
{
	int Idx = 0;	// 近かった方の Idx を格納する変数

	// 2点の距離を比較
	if (sort1.pos < sort2.pos)
	{
		Idx = sort1.Idx;
	}
	else
	{
		Idx = sort2.Idx;
	}

	return Idx;
}

//===========================================================================================================
// 通ったことをリセットする
//===========================================================================================================
void CCheckPoint::Reset()
{
	std::vector<CCoursePoint*>pCourseP;	// コースポイントを格納する変数
	pCourseP.clear();	// 初期化

	// コースポイントのポインタを探す
	pCourseP = CSearch::SearchMultiObject(pCourseP, CObject::POINT);

	// 空だったら通さない
	if (pCourseP.empty())
	{	return;	}

	unsigned int pointnum = pCourseP.size();	// コースポイントの数を格納する変数

	for (unsigned int i = 0; i < pointnum; i++)
	{// すべて通ってないことにする
		pCourseP[i]->SetPassPoint(false);
	}
}

//int CCheckPoint::SortDis(float dis1, float dis2)
//{
//	int nearIdx = 0;
//
//	if (dis1 > dis2)
//	{
//		nearIdx=
//	}
//	else
//	{
//
//	}
//
//	return 0;
//}
