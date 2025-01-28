//===========================================================================================================================================================
// 
// input.cpp�̃w�b�_�[
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

#define MAX_KEY	(256)
#define JOYPAD_DEADZONE	(3000)

//===========================================================================================================
// �C���v�b�g�N���X
//===========================================================================================================
class CInput
{
public:
	CInput();
	~CInput();
	virtual HRESULT Init(HINSTANCE hInstance,HWND hWnd);
	virtual void Uninit();
	virtual void Update() = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
private:

};

//===========================================================================================================
// �L�[�{�[�h�N���X
//===========================================================================================================
class CInputKeyBoard :public CInput
{
public:
	CInputKeyBoard();
	~CInputKeyBoard();
	HRESULT Init(HINSTANCE hinstance, HWND hWnd)override;
	void Uninit()override;
	void Update()override;

	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
private:
	BYTE m_aKeyState[MAX_KEY];
	BYTE m_aKeyStateTrigger[MAX_KEY];
	BYTE m_aKeyStateRelease[MAX_KEY];
};

//===========================================================================================================
// �W���C�p�b�h�N���X
//===========================================================================================================
class CInputJoypad
{
public:

	static const unsigned int PEDAL_DEADZONE = 5;	// �y�_���𔽉�������ŏ��l

	typedef enum
	{
		JOYKEY_UP = 0,
		JOYKEY_DOWN,
		JOYKEY_LEFT,
		JOYKEY_RIGHT,
		JOYKEY_START,
		JOYKEY_BACK,
		JOYKEY_LEFT_THUMB,
		JOYKEY_RIGHT_THUMB,
		JOYKEY_LEFT_SHOULDER,
		JOYKEY_RIGHT_SHOULDER,
		JOYKEY_LEFT_TRIGGER,
		JOYKEY_RIGHT_TRIGGER,
		JOYKEY_A,
		JOYKEY_B,
		JOYKEY_X,
		JOYKEY_Y,
		JOYKEY_MAX
	}JOYKEY;

	typedef enum
	{
		PEDAL_LEFT = 0,
		PEDAL_RIGHT,
		PEDAL_MAX
	}PEDAL;

	CInputJoypad();
	~CInputJoypad();
	HRESULT Init();
	void Uninit();
	void Update();
	bool GetPress(JOYKEY key);
	bool GetTrigger(JOYKEY key);
	bool GetRelese(JOYKEY key);
	bool GetTriggerPedal(JOYKEY key);
	bool GetPressPedal(JOYKEY key);
	WORD ThumbToDPad(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);
private:
	XINPUT_STATE m_joyKeyState;	// �W���C�p�b�h�̃v���X���
	XINPUT_STATE m_joyKeyStateTrigger;	// �W���C�p�b�h�̃g���K�[���
	XINPUT_STATE m_joyKeyStateRelese;	// �W���C�p�b�h�̃����[�X���
	BYTE m_joyTBpedal[PEDAL_MAX];	// �g���K�[�{�^���̃y�_��;
	BYTE m_joyTBpedalTrigger[PEDAL_MAX];	// �g���K�[�{�^���̃y�_��;
	XINPUT_VIBRATION m_joyPadVibration;
	bool m_TBtrigger[PEDAL_MAX];
};

//===========================================================================================================
// �}�E�X�N���X
//===========================================================================================================
//class CInputMouse :public CInput
//{
//public:
//	typedef enum
//	{
//		MOUSEBUTTON_LEFT = 0,   // ���N���b�N
//		MOUSEBUTTON_RIGHT,      // �E�N���b�N
//		MOUSEBUTTON_CENTER,     // �z�C�[��
//		MOUSEBUTTON_MAX
//	}MOUSEBUTTON;
//
//	CInputMouse();
//	~CInputMouse();
//	HRESULT Init(HINSTANCE hinstance, HWND hWnd)override;
//	void Uninit()override;
//	void Update()override;
//	bool CreateMouseDevice();
//	bool GetMousePress(MOUSEBUTTON button);
//	bool GetMouseTrigger(MOUSEBUTTON button);
//	bool GetMouseRelease(MOUSEBUTTON button);
//	D3DXVECTOR3 GetMousePos(void);
//	D3DXVECTOR3 GetMouseMove(void);
//
//private:
//	DIMOUSESTATE m_CurrentMouseState;		//!< �}�E�X�̌��݂̓��͏��
//};

#endif // !_INPUT_H_
