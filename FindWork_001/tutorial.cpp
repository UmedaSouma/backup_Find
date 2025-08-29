//===========================================================================================================================================================
// 
// チュートリアルの処理
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "tutorial.h"
#include "param_storage.h"
#include "player_manager.h"
#include "course.h"
#include "manager.h"
#include "display_number.h"

//CTimer* CTutorial::m_timer = nullptr;
CParamStorage* CTutorial::m_pParamStorage = nullptr;
CPlayerManager* CTutorial::m_pPlayerManager = nullptr;
//CCountdown* CTutorial::m_pCountDown = nullptr;
//int CTutorial::m_nDelayEnd = 0; // 倒してからリザルトになるまで
//bool CTutorial::m_Delay = false;
//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CTutorial::CTutorial()
{
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CTutorial::~CTutorial()
{
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CTutorial::Init()
{
	CCourse::Create(CCourse::COURSE_01);

	// パラメーター管理クラス作成
	m_pParamStorage = new CParamStorage[CParamStorage::CAR_MAX];

	// プレイヤー管理クラス作成
	m_pPlayerManager = new CPlayerManager;
	m_pPlayerManager->Init();

	return E_NOTIMPL;
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CTutorial::Uninit()
{
	if (m_pParamStorage != nullptr)
	{
		// パラメーターの保管庫を削除
		delete[] m_pParamStorage;
		m_pParamStorage = nullptr;
	}

	if (m_pPlayerManager != nullptr)
	{
		// プレイヤー管理を削除
		m_pPlayerManager->Uninit();

		delete m_pPlayerManager;
		m_pPlayerManager = nullptr;
	}

	CScene::Uninit();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CTutorial::Update()
{
	CInputKeyBoard* keyboard = CManager::GetKeyboard();
	CFade* pFade = CManager::GetFade();

	// デバッグ用 Enterでシーン切り替え
	if (keyboard->GetTrigger(DIK_RETURN))
	{
		pFade->SetFade(CScene::MODE_GAME);
	}

	// プレイヤー管理の更新
	m_pPlayerManager->Update();
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CTutorial::Draw()
{
}

