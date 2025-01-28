//===========================================================================================================================================================
// 
// プレイヤーの操作制御 [player_controller.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "player_controller.h"
#include "manager.h"
#include "countdown.h"
#include "game.h"

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CPlayerController::CPlayerController()
{
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CPlayerController::~CPlayerController()
{
}

//===========================================================================================================
// 初期設定
//===========================================================================================================
void CPlayerController::Init()
{
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CPlayerController::Uninit()
{
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CPlayerController::Update(CCarPlayer* pCar)
{
	CCountdown* pCD = CGame::GetCountDown();
	if (pCD != nullptr)
	{
		if (pCD->GetUse())
		{
			return;
		}
	}

	// プレイヤーがダウン状態の時
	if (pCar->GetActionState() == CCar::ACTION_STATE::DOWN)
	{ return; }

	CInputKeyBoard* keyboard = CManager::GetKeyboard();
	CInputJoypad* joypad = CManager::GetJoypad();

	if (pCar != nullptr)
	{
		if (keyboard->GetPress(DIK_LSHIFT) || joypad->GetPress(CInputJoypad::JOYKEY_RIGHT_SHOULDER))
		{
			if (keyboard->GetPress(DIK_D) || joypad->GetPress(CInputJoypad::JOYKEY_RIGHT))
			{
				pCar->ActionDriftR();
				return;
			}
			else if (keyboard->GetPress(DIK_A) || joypad->GetPress(CInputJoypad::JOYKEY_LEFT))
			{
				pCar->ActionDriftL();
				return;
			}
			pCar->SetForwardForce(pCar->GetAccumulationSpeed());
			pCar->SetForwardAngle(pCar->GetRot().y);
		}
		else
		{
			//===========================================================================================================
			// アクセル
			//===========================================================================================================
			if (keyboard->GetPress(DIK_W) || joypad->GetPressPedal(CInputJoypad::JOYKEY_RIGHT_TRIGGER))
			{
				pCar->ActionAccele();
			}
			//===========================================================================================================
			// ブレーキ
			//===========================================================================================================
			else if (keyboard->GetPress(DIK_S) || joypad->GetPressPedal(CInputJoypad::JOYKEY_LEFT_TRIGGER))
			{
				pCar->ActionBrake();
			}



			//===========================================================================================================
			// ドリフト
			//===========================================================================================================

			//===========================================================================================================
			// ドリフト
			//===========================================================================================================

			//===========================================================================================================
			// 右に曲がる
			//===========================================================================================================
			if (keyboard->GetPress(DIK_D) || joypad->GetPress(CInputJoypad::JOYKEY_RIGHT))
			{
				pCar->ActionBend_R();
			}
			//===========================================================================================================
			// 左に曲がる
			//===========================================================================================================
			else if (keyboard->GetPress(DIK_A) || joypad->GetPress(CInputJoypad::JOYKEY_LEFT))
			{
				pCar->ActionBend_L();
			}
			//===========================================================================================================
			// アタック
			//===========================================================================================================
			if (keyboard->GetTrigger(DIK_SPACE) || joypad->GetTrigger(CInputJoypad::JOYKEY_X))
			{
				pCar->ActionAttack();
			}
		}

		

#ifdef _DEBUG

		// ギア変更
		if (keyboard->GetTrigger(DIK_UPARROW) || joypad->GetTrigger(CInputJoypad::JOYKEY_UP))
		{
			if (pCar->GetGear() < pCar->GetGearNum() - 1)
			{
				pCar->SetGear(pCar->GetGear() + 1);
			}
		}
		else if (keyboard->GetTrigger(DIK_DOWNARROW) || joypad->GetTrigger(CInputJoypad::JOYKEY_DOWN))
		{
			if (pCar->GetGear() > 0)
			{
				pCar->SetGear(pCar->GetGear() - 1);
			}
		}

		if (keyboard->GetTrigger(DIK_T) || joypad->GetTrigger(CInputJoypad::JOYKEY_UP))
		{
			pCar->ActionTurbo();
		}

		if (CScene::GetMode() == CScene::MODE_EDITOR_PRAM)
		{
			if (keyboard->GetTrigger(DIK_R) || joypad->GetTrigger(CInputJoypad::JOYKEY_RIGHT_SHOULDER))
			{
				pCar->SetPos({ 0.0f,0.0f,0.0f });
				pCar->SetMove({ 0.0f,0.0f,0.0f });
				pCar->SetRot({ 0.0f,0.0f,0.0f });
			}
		}
	
		if (keyboard->GetTrigger(DIK_8))
		{
			pCar->SetMove({ 0.0f,1.0f,0.0f });
		}
		if (keyboard->GetTrigger(DIK_5))
		{
			pCar->SetMove({ 0.0f,-1.0f,0.0f });
		}
#endif // DEBUG

		
	}

}

void CPlayerController::Move()
{
}

