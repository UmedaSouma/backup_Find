#pragma once
//===========================================================================================================================================================
// 
// editor_coursepoint.cppのヘッダー [editor_coursepoint.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _EDITOR_COURSE_POINT_H_
#define _EDITOR_COURSE_POINT_H_
#include "main.h"
#include "scene.h"
#include "course_point.h"
#include "input.h"

#define FPASS_CORSE	"data\\text\\coursepoint_01.txt"

class CEditorCoursePoint :public CScene
{
public:
	CEditorCoursePoint();
	~CEditorCoursePoint()override;
	HRESULT Init()override;	// 初期設定
	void Uninit()override;	// 終了
	void Update()override;	// 更新
	void Draw()override;	// 描画

	void Controll();		// 操作
	void ControllMove(CInputKeyBoard* keyboard);	// 移動操作
	void Save();	// 書き込み
	void SaveInfo();	// ポイント情報の書き込み
	
private:
	//*******************************************************************************************************
	// 使用頻度が多い文字の変数化
	//*******************************************************************************************************
	const char* Fpass = "data\\text\\corsepp.txt";	// 開くファイルのパス
	const char* major_h = "==============================================================\n";	// 大見出し
	const char* sub_h = "--------------------------------------------------------------\n";		// 小見出し
	const char* txt_break = "\n";	// 改行

	CCoursePoint* m_pPointMother;	// コースポイントの親
	int m_nNum;		// 総数カウント
};

#endif // !EDITOR_COURSE_POINT_H_