#pragma once
//===========================================================================================================================================================
// 
// obstacle.cppのヘッダー [obstacle.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_
#include "main.h"
#include "model.h"
#include "car.h"

class CObstacle :public CModel
{
public:
	typedef enum
	{
		OBS_DRUMCAN = 0,
		OBS_,
		OBS_MAX,
	}OBS_TYPE;

	CObstacle();
	~CObstacle()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	void InitSet();
	void HitMovement(CCar*pcar);

	static CObstacle* Create(D3DXVECTOR3 pos, OBS_TYPE type);   // 生成処理

	OBS_TYPE GetObsType() { return m_obstype; }
private:
	float m_Weight;	// 障害物の重さ(この重さより車がスピードを出さないと吹っ飛ばせない
	OBS_TYPE m_obstype;
};

#endif // !OBSTACLE_H_