#pragma once
//===========================================================================================================================================================
// 
// particle_manager.cppのヘッダー [particle_manager.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _PARTICLE_MANAGER_H_
#define _PARTICLE_MANAGER_H_
#include "main.h"

class CParticleManager
{
public:
	CParticleManager();	// コンストラクタ
	~CParticleManager();	// デストラクタ
	void Update();			// 更新処理
	void SetParticle(bool loop, int num);		// パーティクルの設定

	// -- ループするかどうか --
	void Setloop(bool loop) { m_Isloop = loop; }
	bool Getloop() { return m_Isloop; }

	// -- パーティクルの数 --
	void SetNum(int num) { m_Num = num; }
	int GetNum() { return m_Num; }
private:
	bool m_Isloop;	// ループするかどうか
	int m_Num;		// パーティクルの数
};

#endif // !PARTICLE_MANAGER_H_