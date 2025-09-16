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
CTutorial::TUTORIAL_EXPRANATION CTutorial::m_ExpranationNum = CTutorial::EXPRANATION_1;
//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CTutorial::CTutorial()
{
	m_tutorialtime = 0;
	m_firsttimestop = false;
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CTutorial::~CTutorial()
{
	CManager::SetScenestop(false);
}

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT CTutorial::Init()
{
	// 変数の初期化
	m_tutorialtime = 0;
	m_firsttimestop = false;

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

	// チュートリアル開始時点
	if (m_tutorialtime > 0 && !CManager::GetScenestop() && !m_firsttimestop)
	{// チュートリアル開始１フレーム以上 && シーン停止していないとき && 一回もシーン停止を通っていないとき
		CManager::SetScenestop(true);
		m_firsttimestop = true;
	}
	
	m_tutorialtime++;
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CTutorial::Draw()
{
	CInputKeyBoard* keyboard = CManager::GetKeyboard();

	if (keyboard->GetTrigger(DIK_0))
		CManager::SetScenestop(!CManager::GetScenestop());
}

//===========================================================================================================
// 説明番号を増やす
//===========================================================================================================
void CTutorial::AddExprationNum()
{
	if (m_ExpranationNum < EXPRANATION_MAX)
		m_ExpranationNum + 1;
}

