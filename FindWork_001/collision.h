#pragma once
//===========================================================================================================================================================
// 
// collision.cppのヘッダー [collision.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_
#include "main.h"
#include <tuple>

class CCollision
{
public:
	CCollision();
	~CCollision();
	HRESULT Init();	// 初期設定
	void Uninit();	// 終了
	void Update();	// 更新
	void Draw();	// 描画

	// 矩形の当たり判定
	static bool BoxTrigger(D3DXVECTOR3 posA,D3DXVECTOR3 sizeA,D3DXVECTOR3 posB,D3DXVECTOR3 sizeB);
	// 円の当たり判定
	static bool CircleTrigger(D3DXVECTOR3 posA, float radiusA, D3DXVECTOR3 posB, float radiusB);
	// 球の当たり判定
	static bool SphereTrigger(D3DXVECTOR3 posA, float radiusA, D3DXVECTOR3 pos, float radiusB);
	// 矩形の押し出し当たり判定
	static bool BoxCollision(D3DXVECTOR3 posA, D3DXVECTOR3 sizeA, D3DXVECTOR3 posB, D3DXVECTOR3 sizeB);
	// メッシュとの当たり判定
	static std::tuple<BOOL,float> MeshCollision(LPD3DXBASEMESH pMesh,D3DXVECTOR3 RayWay,D3DXVECTOR3 StartPos);
private:

};


#endif // !COLLISION_H_