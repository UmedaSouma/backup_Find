#pragma once
//===========================================================================================================================================================
// 
// explosion.cppのヘッダー [explosion.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "main.h"
#include "model.h"

class CExplosion :public CModel
{
public:
	CExplosion();
	~CExplosion()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	static CExplosion* Create(D3DXVECTOR3 pos, int Expantion);	// 生成処理
private:
	int m_nTargetCnt;	// 目標のカウント
	int m_nExpansionCnt;	// 拡大するカウント
};

#endif // !EXPLOSION_H_