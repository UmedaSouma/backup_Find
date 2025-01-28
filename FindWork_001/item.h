#pragma once
//===========================================================================================================================================================
// 
// item.cppのヘッダー [item.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"
#include "model.h"

class CItem:public CModel
{
public:
	CItem();
	~CItem()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	bool Collision();	// 当たり判定

	static CItem* Create(D3DXVECTOR3 pos);   // 生成処理
private:

};



#endif // !ITEM_H_