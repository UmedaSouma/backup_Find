#pragma once
//===========================================================================================================================================================
// 
// UI.cppのヘッダー [UI.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _UI_H_
#define _UI_H_
#include "main.h"
#include "object2D.h"

//===========================================================================================================
// クラス
//===========================================================================================================
class CUI :public CObject2D
{
public:
	CUI(int nPriority = PRIORITY_DEFAULT + 2);
	~CUI()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	static CUI* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* texpass);   // 生成処理
private:

};

#endif // !UI_H_