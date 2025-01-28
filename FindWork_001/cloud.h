#pragma once
//===========================================================================================================================================================
// 
// tree.cppのヘッダー [tree.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _CLOUD_H_
#define _CLOUD_H_
#include "main.h"
#include "model.h"


class CCloud :public CModel
{
public:
	CCloud();
	~CCloud()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	static CCloud* Create();   // 生成処理
private:

};



#endif // !TREE_H_