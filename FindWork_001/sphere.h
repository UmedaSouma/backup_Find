#pragma once
//===========================================================================================================================================================
// 
// sphere.cppのヘッダー [sphere.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _SPHERE_H_
#define _SPHERE_H_
#include "main.h"
#include "model.h"

class CSphere :public CModel
{
public:
	CSphere();
	~CSphere()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Draw()override;	// 描画
	void UpdatePos(D3DXVECTOR3 pos);	// 位置だけ持ってく

	static CSphere* Create();   // 生成処理
private:
};



#endif // !SPHERE_H_