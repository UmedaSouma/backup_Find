#pragma once
//===========================================================================================================================================================
// 
// editor_obstacles.cppのヘッダー [editor_obstacles.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _EDITOR_OBSTACLES_H_
#define _EDITOR_OBSTACLES_H_
#include "main.h"
#include "scene.h"
#include "input.h"
#include "obstacles.h"

#define FPASS_OBS	"data\\text\\obs_01.txt"

class CEditorObstacle :public CScene
{
public:
	CEditorObstacle();
	~CEditorObstacle()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	void Controll();		// 操作
	void ControllMove(CInputKeyBoard* keyboard);	// 移動操作
	void SaveObs();	// 書き込み
	void SaveInfoObs();	// ポイント情報の書き込み

	static CEditorObstacle* Create();   // 生成処理

private:
	//*******************************************************************************************************
	// 使用頻度が多い文字の変数化
	//*******************************************************************************************************
	const char* FpassObs = "data\\text\\corsepp.txt";	// 開くファイルのパス
	const char* major_h = "==============================================================\n";	// 大見出し
	const char* sub_h = "--------------------------------------------------------------\n";		// 小見出し
	const char* txt_break = "\n";	// 改行

	CObstacle* m_pMother;	// コースポイントの親
};

#endif // !EDITOR_OBSTACLES_H_