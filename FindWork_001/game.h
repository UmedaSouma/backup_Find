//===========================================================================================================================================================
// 
// game.cppのヘッダー
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "main.h"
#include "scene.h"
#include "param_storage.h"
#include "player_manager.h"
#include "countdown.h"
#include "timer.h"

class CGame :public CScene
{
public:
	CGame();
	~CGame()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void Load();	// 読み込み
	void LoadObs();	// 読み込み
	void LoadInfo(FILE* pfile);	// ポイント情報の読み込み
	void LoadObsInfo(FILE* pfile);	// ポイント情報の読み込み
	void SetInitUI();	// uiのセット

	static CCountdown* GetCountDown() { return m_pCountDown; }
private:
	static int m_nDelayEnd;	// 倒してからリザルトになるまで
	static bool m_Delay;
	static CTimer* m_timer;	// タイマーのポインタ

public:
	static CParamStorage* m_pParamStorage;
	static CPlayerManager* m_pPlayerManager;
	static CCountdown* m_pCountDown;
};