#pragma once
//===========================================================================================================================================================
// 
// editor_parama.cppのヘッダー [editor_parama.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _EDITOR_PARAM_H_
#define _EDITOR_PARAM_H_
#include "main.h"
#include "scene.h"
#include "player_manager.h"


class CEditor_Param :public CScene
{
public:
	CEditor_Param();
	~CEditor_Param()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画
private:

public:
	static CPlayerManager* pPlayerManager;
};


#endif // !EDITOR_PARAM_H_