#pragma once
//===========================================================================================================================================================
// 
// car_normal.cppのヘッダー [car_normal.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _CAR_NORMAL_H_
#define _CAR_NORMAL_H_
#include "main.h"
#include "car.h"


class CCarNormal:public CCar
{
private:
	//================================================================

	//--------------------------------------------------------
	// < debugmemo >
	// 一旦ここで値を設定しとく。
	// 後でテキストファイルで入出力をする
	//--------------------------------------------------------
	static const int MAX_LIFE = 150;					// 最大速度
	static const int MAX_GEAR = 5;						// ギア数
	inline static const float MAX_WEIGHT = 30.0f;		// 重さ
	inline static const float MAX_BENDING = 0.1f;		// 曲がりやすさ

	inline static const float							// ギアごとのスピード
		MAX_SPEED[MAX_GEAR] = {
		12.0f,
		15.0f,
		18.0f,
		22.0f,
		30.0f
	};

	//================================================================

public:
	CCarNormal();
	~CCarNormal()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	static CCarNormal* Create(D3DXVECTOR3 pos);   // 生成処理
private:

};

#endif // !CAR_NORMAL_H_
