#pragma once
//===========================================================================================================================================================
// 
// actor.cppのヘッダー [actor.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _ACTOR_H_
#define _ACTOR_H_
#include "main.h"
#include "model.h"

class CActor :public CModel
{
public:
	inline static const float GRAVITY = 0.1f;

	CActor();
	~CActor()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	void Gravity();		// 重力

	static CActor* Create();   // 生成処理
private:
	bool m_bGravity;		// true だったら重力が付く
	D3DXVECTOR3 m_move;		// 移動値
	D3DXVECTOR3 m_oldpos;	// 過去の位置

public:
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	D3DXVECTOR3 &GetMove() { return m_move; }
	void SetGravity(bool Grav) { m_bGravity = Grav; }
	D3DXVECTOR3& GetOldPos() { return m_oldpos; }
};


#endif // !ACTOR_H_
