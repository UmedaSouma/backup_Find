#pragma once
//===========================================================================================================================================================
// 
// fixed_value.cppのヘッダー [fixed_value.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _FIXED_VALUE_H_
#define _FIXED_VALUE_H_
#include "main.h"

class CFixedValue
{
public:
	CFixedValue();		// コンストラクタ
	~CFixedValue();		// デストラクタ
	
	//===========================================================================================================
	// < memo >
	// クラスごとに構造体を持たせる
	// 構造体を持たせた先で変数に固定値を入れていく
	//===========================================================================================================

	// カメラ
	typedef struct
	{
		float DISTANCE;	// 視点と注視点の距離
		D3DXVECTOR3 ADDROT;	// カメラの回転加速度
	}Camera;

	// 爆弾
	typedef struct
	{
		int EXPLOSION_TIME;	// 爆発の持続時間
		const char *MODEL_PASS;	// モデルデータのパス
	}Bomb;

	Bomb* GetBomb() { return &m_Bomb; }
	Camera* GetCamerata() { return &m_Camera; }
private:
	Camera m_Camera;
	Bomb m_Bomb;
};


#endif // !FIXED_VALUE_H_