#pragma once
//===========================================================================================================================================================
// 
// title.cppのヘッダー
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "main.h"
#include "scene.h"

// 前方宣言
class CParamStorage;	// パラメーター管理クラス
class CPlayerManager;	// プレイヤー管理クラス

class CTutorial :public CScene
{
public:
	// チュートリアルの説明
	typedef enum
	{
		EXPRANATION_0 = 0,
		EXPRANATION_1,
		EXPRANATION_2,
		EXPRANATION_MAX,
	}TUTORIAL_EXPRANATION;

	CTutorial();
	~CTutorial()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static void AddExprationNum();
private:
	static CParamStorage* m_pParamStorage;	// パラメーター管理
	static CPlayerManager* m_pPlayerManager;	// プレイヤー管理
	static TUTORIAL_EXPRANATION m_ExpranationNum;	// 何番目の説明か
	int m_tutorialtime;	// チュートリアルの時間
	bool m_firsttimestop;	// 初めてチュートリアルに入ったかどうか
};