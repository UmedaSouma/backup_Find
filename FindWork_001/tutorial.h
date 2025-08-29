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
	CTutorial();
	~CTutorial()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	static CParamStorage* m_pParamStorage;	// パラメーター管理
	static CPlayerManager* m_pPlayerManager;	// プレイヤー管理
};