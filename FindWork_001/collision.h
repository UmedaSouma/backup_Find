#pragma once
//===========================================================================================================================================================
// 
// collision.cpp�̃w�b�_�[ [collision.h]
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
	HRESULT Init();	// �����ݒ�
	void Uninit();	// �I��
	void Update();	// �X�V
	void Draw();	// �`��

	// ��`�̓����蔻��
	static bool BoxTrigger(D3DXVECTOR3 posA,D3DXVECTOR3 sizeA,D3DXVECTOR3 posB,D3DXVECTOR3 sizeB);
	// �~�̓����蔻��
	static bool CircleTrigger(D3DXVECTOR3 posA, float radiusA, D3DXVECTOR3 posB, float radiusB);
	// ���̓����蔻��
	static bool SphereTrigger(D3DXVECTOR3 posA, float radiusA, D3DXVECTOR3 pos, float radiusB);
	// ��`�̉����o�������蔻��
	static bool BoxCollision(D3DXVECTOR3 posA, D3DXVECTOR3 sizeA, D3DXVECTOR3 posB, D3DXVECTOR3 sizeB);
	// ���b�V���Ƃ̓����蔻��
	static std::tuple<BOOL,float> MeshCollision(LPD3DXBASEMESH pMesh,D3DXVECTOR3 RayWay,D3DXVECTOR3 StartPos);
private:

};


#endif // !COLLISION_H_