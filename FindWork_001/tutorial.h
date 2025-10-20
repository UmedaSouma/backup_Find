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
class CUI;				// UIクラス

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

	void ExpranationUpdate();	// 説明の更新
	void SetNextExpranation();	// 説明のリセットと番号加算

	void AddExpranationNum();	// 説明の番号を加算する
private:

	// 説明と説明の間の時間
	const int m_ExtranationInterbalTime[EXPRANATION_MAX] = {
		60,
		200,
		600,
	};

	static CParamStorage* m_pParamStorage;	// パラメーター管理
	static CPlayerManager* m_pPlayerManager;	// プレイヤー管理
	static int m_ExpranationNum;	// 何番目の説明か
	int m_tutorialtime;	// チュートリアルの時間
	bool m_firsttimestop;	// 初めてチュートリアルに入ったかどうか
	bool m_nextpreparation;	// 次の説明に準備中どうか
	int m_restartframe;	// チュートリアルの説明から抜け出してゲームを再開した時点のフレーム

	CUI* m_pExpranationUI;	//説明UI

};