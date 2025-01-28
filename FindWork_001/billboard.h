#pragma once
//===========================================================================================================================================================
// 
// billboard.cppのヘッダー [billboard.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
#include "main.h"
#include "object3D.h"

class CBillboard :public CObject3D
{
public:
	CBillboard(int nPrio = PRIORITY_DEFAULT);
	~CBillboard()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	static CBillboard* Create(D3DXVECTOR3 pos);   // 生成処理
private:

};

#endif // !BILLBOARD_H_
