#include "input.h"

// �ÓI�����o�ϐ��̏�����
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CInput::CInput()
{

}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CInput::~CInput()
{
}

//===========================================================================================================
// �����ݒ�
//===========================================================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND /*hWnd*/)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_pInput, nullptr)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CInput::Uninit()
{
	// ���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	// DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CInput::Update()
{
}

//===========================================================================================================
// �L�[�{�[�h�̃R���X�g���N�^
//===========================================================================================================
CInputKeyBoard::CInputKeyBoard() : m_aKeyState(), m_aKeyStateTrigger(), m_aKeyStateRelease()
{
}

//===========================================================================================================
// �L�[�{�[�h�̃f�X�g���N�^
//===========================================================================================================
CInputKeyBoard::~CInputKeyBoard()
{
}

//===========================================================================================================
// �L�[�{�[�h�����ݒ�
//===========================================================================================================
HRESULT CInputKeyBoard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, nullptr)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}

//===========================================================================================================
// �L�[�{�[�h�̏I������
//===========================================================================================================
void CInputKeyBoard::Uninit()
{
	CInput::Uninit();
}

//===========================================================================================================
// �L�[�{�[�h�̃A�b�v�f�[�g
//===========================================================================================================
void CInputKeyBoard::Update()
{
	BYTE aKeyState[MAX_KEY];	// �L�[�{�[�h�̓��͏��
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{
			//g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];

			m_aKeyStateTrigger[nCntKey] = ~m_aKeyState[nCntKey] & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = ~aKeyState[nCntKey] & m_aKeyState[nCntKey];

			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//===========================================================
// �L�[�{�[�h�̃v���X�����擾
//===========================================================
bool CInputKeyBoard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) != 0;
}

//===========================================================
// �L�[�{�[�h�̃g���K�[�����擾
//===========================================================
bool CInputKeyBoard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) != 0;
}

//===========================================================================================================
// �L�[�{�[�h�̃����[�X����
//===========================================================================================================
bool CInputKeyBoard::GetRelease(int Key)
{
	return (m_aKeyStateRelease[Key] & 0x80) != 0;
}

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CInputJoypad::CInputJoypad()
{
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CInputJoypad::~CInputJoypad()
{
}

HRESULT CInputJoypad::Init()
{
	for (int i = 0; i < PEDAL_MAX; i++)
	{
		m_TBtrigger[i] = false;
		m_joyTBpedal[i] = 0;
	}

	// �������N���A
	memset(&m_joyKeyState, 0, sizeof(XINPUT_STATE));
	memset(&m_joyKeyStateTrigger, 0, sizeof(XINPUT_STATE));
	memset(&m_joyKeyStateRelese, 0, sizeof(XINPUT_STATE));

	memset(&m_joyPadVibration, 0, sizeof(XINPUT_VIBRATION));

	// Xinput�̃X�e�[�g��ݒ�(�L���ɂ���)
	XInputEnable(true);

	return S_OK;
}

void CInputJoypad::Uninit()
{
	// XInput�̃X�e�[�g��ݒ�(�����ɂ���)
	XInputEnable(false);
}

void CInputJoypad::Update()
{
	XINPUT_STATE joykeyState;	// �W���C�p�b�h�̓��͏��

	// �W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		m_joyTBpedal[PEDAL_LEFT] = joykeyState.Gamepad.bLeftTrigger;
		m_joyTBpedal[PEDAL_RIGHT] = joykeyState.Gamepad.bRightTrigger;
		joykeyState.Gamepad.wButtons |= ThumbToDPad(m_joyKeyState.Gamepad.sThumbLX, m_joyKeyState.Gamepad.sThumbLY, JOYPAD_DEADZONE);

		m_joyKeyStateRelese.Gamepad.wButtons = ~joykeyState.Gamepad.wButtons & m_joyKeyState.Gamepad.wButtons;	// �����[�X����
		m_joyKeyStateTrigger.Gamepad.wButtons = (m_joyKeyState.Gamepad.wButtons ^ joykeyState.Gamepad.wButtons) & joykeyState.Gamepad.wButtons;	// �g���K�[����
		m_joyTBpedalTrigger[PEDAL_LEFT] = (m_joyKeyState.Gamepad.bLeftTrigger ^ joykeyState.Gamepad.bLeftTrigger) & joykeyState.Gamepad.bLeftTrigger;
		m_joyTBpedalTrigger[PEDAL_RIGHT] = (m_joyKeyState.Gamepad.bRightTrigger ^ joykeyState.Gamepad.bRightTrigger) & joykeyState.Gamepad.bRightTrigger;

		m_joyKeyState = joykeyState;	// �W���C�p�b�h�̃v���X����ۑ�
	}
}

bool CInputJoypad::GetPress(JOYKEY key)
{
	return(m_joyKeyState.Gamepad.wButtons & (0x01 << key)) /*? true : false*/;
}

bool CInputJoypad::GetTrigger(JOYKEY key)
{
	return(m_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << key)) /*? true : false*/;
}

bool CInputJoypad::GetRelese(JOYKEY key)
{
	return(m_joyKeyStateRelese.Gamepad.wButtons & (0x01 << key)) /*? true : false*/;
}

bool CInputJoypad::GetTriggerPedal(JOYKEY key)
{
	int KeyPedal = 0;	// �g���K�[�{�^���̐��l���i�[����
	int PedalNum = -1;	// �g���K�[�{�^���̎�ނ��i�[
	bool Trigger[PEDAL_MAX] = { false,false };	// �g���K�[�{�^���������ꂽ���m�F����

	switch (key)
	{
	case JOYKEY_LEFT_TRIGGER:
		PedalNum = PEDAL_LEFT;
		break;

	case JOYKEY_RIGHT_TRIGGER:
		PedalNum = PEDAL_RIGHT;
		break;

	default:
		break;
	}

	if (m_joyTBpedal[PedalNum] >= PEDAL_DEADZONE)
	{// �y�_�������̐��l�ȏ㉺��������

		KeyPedal = m_joyTBpedal[PedalNum];	// �y�_���̐��l����(�̂��� return �ŕԂ�
		Trigger[PedalNum] = true;	// �g���K�[��������
	}

	if ((m_TBtrigger[PedalNum] ^ Trigger[PedalNum]) != 0)
	{// �O��g���K�[�������Ă��Ȃ�������
		m_TBtrigger[PedalNum] = Trigger[PedalNum];
		return KeyPedal > 0;
	}

	m_TBtrigger[PedalNum] = Trigger[PedalNum];
	return 0;
}

bool CInputJoypad::GetPressPedal(JOYKEY key)
{
	int KeyPedal = 0;	// �g���K�[�{�^���̐��l���i�[����
	int PedalNum = -1;	// �g���K�[�{�^���̎�ނ��i�[

	switch (key)
	{
	case JOYKEY_LEFT_TRIGGER:
		PedalNum = PEDAL_LEFT;
		break;

	case JOYKEY_RIGHT_TRIGGER:
		PedalNum = PEDAL_RIGHT;
		break;

	default:
		break;
	}

	KeyPedal = m_joyTBpedal[PedalNum];	// �y�_���̐��l����(�̂��� return �ŕԂ�
	return KeyPedal > 0;
}

//===========================================================================================================
// �X�e�B�b�N�̏���
//===========================================================================================================
WORD CInputJoypad::ThumbToDPad(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone)
{
	WORD wButtons = 0;

	if (sThumbY >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	else if (sThumbY <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	if (sThumbX <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	else if (sThumbX >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	return wButtons;
}

////==========================================================================================
//// �}�E�X�̏���������
////==========================================================================================
//HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
//{
//	if (!CreateMouseDevice())
//	{
//		Uninit();
//		return E_FAIL;
//	}
//
//	ZeroMemory(&m_CurrentMouseState, sizeof(DIMOUSESTATE));
//	ZeroMemory(&m_PrevMouseState, sizeof(DIMOUSESTATE));
//
//	return S_OK;
//}
//
////==========================================================================================
//// �}�E�X�f�o�C�X�̍쐬
////==========================================================================================
//bool CInputMouse::CreateMouseDevice(void)
//{
//	// �}�E�X�p�Ƀf�o�C�X�I�u�W�F�N�g���쐬
//	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &g_MouseDevice, NULL)))
//	{
//		// �f�o�C�X�̍쐬�Ɏ��s
//		return false;
//	}
//
//	// �f�[�^�t�H�[�}�b�g��ݒ�
//	if (FAILED(g_MouseDevice->SetDataFormat(&c_dfDIMouse)))
//	{
//		// �f�[�^�t�H�[�}�b�g�Ɏ��s
//		return false;
//	}
//
//	// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
//	if (FAILED(g_MouseDevice->SetCooperativeLevel(
//		FindWindowA(CLASS_NAME, NULL),
//		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
//	{
//		// ���[�h�̐ݒ�Ɏ��s
//		return false;
//	}
//
//	// �f�o�C�X�̐ݒ�
//	DIPROPDWORD diprop;
//	diprop.diph.dwSize = sizeof(diprop);
//	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
//	diprop.diph.dwObj = 0;
//	diprop.diph.dwHow = DIPH_DEVICE;
//	diprop.dwData = DIPROPAXISMODE_REL;	// ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j
//
//	if (FAILED(g_MouseDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
//	{
//		// �f�o�C�X�̐ݒ�Ɏ��s
//		return false;
//	}
//
//	// ���͐���J�n
//	g_MouseDevice->Acquire();
//
//	return true;
//}

////===========================================================
//// �W���C�p�b�h�̃v���X�����擾
////===========================================================
//bool GetJoypadPress(JOYKEY key)
//{
//	return(g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
//}
//
////===========================================================
//// �W���C�p�b�h�̃g���K�[�����擾
////===========================================================
//bool GetJoypadTrigger(JOYKEY key)
//{
//	return(g_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
//}

