//===========================================================================================================================================================
// 
// �v���C���[�̑��쐧�� [player_controller.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "player_controller.h"
#include "manager.h"
#include "countdown.h"
#include "game.h"

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CPlayerController::CPlayerController()
{
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CPlayerController::~CPlayerController()
{
}

//===========================================================================================================
// �����ݒ�
//===========================================================================================================
void CPlayerController::Init()
{
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CPlayerController::Uninit()
{
}

//===========================================================================================================
// �X�V����
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

	// �v���C���[���_�E����Ԃ̎�
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
			// �A�N�Z��
			//===========================================================================================================
			if (keyboard->GetPress(DIK_W) || joypad->GetPressPedal(CInputJoypad::JOYKEY_RIGHT_TRIGGER))
			{
				pCar->ActionAccele();
			}
			//===========================================================================================================
			// �u���[�L
			//===========================================================================================================
			else if (keyboard->GetPress(DIK_S) || joypad->GetPressPedal(CInputJoypad::JOYKEY_LEFT_TRIGGER))
			{
				pCar->ActionBrake();
			}



			//===========================================================================================================
			// �h���t�g
			//===========================================================================================================

			//===========================================================================================================
			// �h���t�g
			//===========================================================================================================

			//===========================================================================================================
			// �E�ɋȂ���
			//===========================================================================================================
			if (keyboard->GetPress(DIK_D) || joypad->GetPress(CInputJoypad::JOYKEY_RIGHT))
			{
				pCar->ActionBend_R();
			}
			//===========================================================================================================
			// ���ɋȂ���
			//===========================================================================================================
			else if (keyboard->GetPress(DIK_A) || joypad->GetPress(CInputJoypad::JOYKEY_LEFT))
			{
				pCar->ActionBend_L();
			}
			//===========================================================================================================
			// �A�^�b�N
			//===========================================================================================================
			if (keyboard->GetTrigger(DIK_SPACE) || joypad->GetTrigger(CInputJoypad::JOYKEY_X))
			{
				pCar->ActionAttack();
			}
		}

		

#ifdef _DEBUG

		// �M�A�ύX
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

