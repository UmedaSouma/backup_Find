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
#include "UI.h"

//CTimer* CTutorial::m_timer = nullptr;
CParamStorage* CTutorial::m_pParamStorage = nullptr;
CPlayerManager* CTutorial::m_pPlayerManager = nullptr;
int CTutorial::m_ExpranationNum = CTutorial::EXPRANATION_0;
//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CTutorial::CTutorial()
{
	m_tutorialtime = 0;
	m_firsttimestop = false;
	m_pExpranationUI = nullptr;
	m_ExpranationNum = CTutorial::EXPRANATION_0;
	m_nextpreparation = true;
	m_restartframe = 0;
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

	//// チュートリアル開始時点
	//if (m_tutorialtime > 0 && !CManager::GetScenestop() && !m_firsttimestop)
	//{// チュートリアル開始１フレーム以上 && シーン停止していないとき && 一回もシーン停止を通っていないとき
	//	CManager::SetScenestop(true);
	//	m_firsttimestop = true;
	//}

	// シーンが止まっていなかったら
	// 各更新をする
	if (!CManager::GetScenestop())
	{
		if (m_nextpreparation)
		{// 準備中だったら

			if (m_tutorialtime - m_restartframe >= m_ExtranationInterbalTime[m_ExpranationNum])
			{// 現在のチュートリアルフレームとゲーム再開時のフレームの差を計算して経過時間を求める
				CManager::SetScenestop(true);
				if (!m_firsttimestop)
					m_firsttimestop = true;
			}

		}

		// プレイヤー管理の更新
		m_pPlayerManager->Update();

		// チュートリアルの時間を進める
		m_tutorialtime++;
	}
	else
	{
		ExpranationUpdate();
	}
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
// 説明文の更新
//===========================================================================================================
void CTutorial::ExpranationUpdate()
{
	D3DXVECTOR3 pos = { SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f };
	D3DXVECTOR3 size = { SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0 };
	
	if (m_pExpranationUI == nullptr)
	{// 説明文のUIが設定されていなかったら

		switch (m_ExpranationNum)
		{// 現在の説明の番号に応じてテクスチャを変える
		case EXPRANATION_0:
			m_pExpranationUI = CUI::Create(pos, size, "data\\TEXTURE\\accele_expranation001.png");
			break;
		case EXPRANATION_1:
			m_pExpranationUI = CUI::Create(pos, size, "data\\TEXTURE\\bend_expranation_000.png");
			break;
		case EXPRANATION_2:
			m_pExpranationUI = CUI::Create(pos, size, "data\\TEXTURE\\boost_expranation_000.png");
			break;
		}
	}
	else
	{
		// 必要な変数の宣言取得
		CInputKeyBoard* keyboard = CManager::GetKeyboard(); // キーボードの取得
		int key[3] = {0,0,0};	// 設定するキー

		// 現在の説明の番号に応じて対応するキーを変える
		switch (m_ExpranationNum)
		{
		case EXPRANATION_0:
			key[0] = DIK_W;
			break;

		case EXPRANATION_1:
			key[0] = DIK_A;
			key[1] = DIK_D;
			break;

		case EXPRANATION_2:
			key[0] = DIK_SPACE;
			break;
		}

		// 対応したキーを押したら次の説明に進む
		if (keyboard->GetTrigger(key[0]) || keyboard->GetTrigger(key[1]) || keyboard->GetTrigger(key[2]))
		{
			SetNextExpranation();
		}
	}

	
	
	// ここに2Dポリゴンの設置処理
	// 説明書チュートリアルの動作をした後のフレームを数える
}

//===========================================================================================================
// 説明番号を増やす
//===========================================================================================================
void CTutorial::AddExpranationNum()
{
	if (m_ExpranationNum < EXPRANATION_MAX)
		m_ExpranationNum++;
}

//===========================================================================================================
// 次の説明文
//===========================================================================================================
void CTutorial::SetNextExpranation()
{
	AddExpranationNum();		// 説明番号を増やす
	m_pExpranationUI->Release();	// UIを破棄する
	CManager::SetScenestop(false);	// シーンを停止する
	m_pExpranationUI = nullptr;		// 説明のUIをnullptrにする
	m_nextpreparation = true;	// 次の説明に移行する
	m_restartframe = m_tutorialtime;	// 現在のフレームを設定する
}

