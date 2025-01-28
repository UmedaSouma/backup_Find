#pragma once
//===========================================================================================================================================================
// 
// actor.cpp�̃w�b�_�[ [actor.h]
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
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	void Gravity();		// �d��

	static CActor* Create();   // ��������
private:
	bool m_bGravity;		// true ��������d�͂��t��
	D3DXVECTOR3 m_move;		// �ړ��l
	D3DXVECTOR3 m_oldpos;	// �ߋ��̈ʒu

public:
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	D3DXVECTOR3 &GetMove() { return m_move; }
	void SetGravity(bool Grav) { m_bGravity = Grav; }
	D3DXVECTOR3& GetOldPos() { return m_oldpos; }
};


#endif // !ACTOR_H_
