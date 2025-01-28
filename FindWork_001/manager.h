//===========================================================================================================================================================
// 
// manager.cpp�̃w�b�_�[
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "modeldata.h"
#include "scene.h"
#include "fade.h"
#include "param_storage.h"
#include "fixed_value.h"
#include"d3dx9.h"

class CManager
{
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();

	static void SetMode(CScene::MODE mode);
private:
	static CScene* m_pScene;
	static CFade* m_pFade;

	static CRenderer* m_pRenderer;
	static CInputKeyBoard* m_pKeyboard;
	static CInputJoypad* m_pJoypad;
	static CTexture* m_pTexture;
	static CModeldata* m_pModeldata;
	static CLight* m_pLight;
	static CCamera* m_pCamera;
	static CParamStorage* m_pParamStrage;
	static CFixedValue* m_pFixedValue;	// �Œ�l�̃N���X�|�C���^
public:
	static CRenderer* GetRenderer() { return m_pRenderer; }			// �����_���[�̎擾
	static CInputKeyBoard* GetKeyboard() { return m_pKeyboard; }	// �L�[�{�[�h�̎擾
	static CInputJoypad* GetJoypad() { return m_pJoypad; }			// �W���C�p�b�h�̎擾
	static CTexture* GetTexture() { return m_pTexture; }			// �e�N�X�`���̎擾
	static CModeldata* GetModeldata() { return m_pModeldata; }		// ���f���f�[�^�̎擾
	static CFade* GetFade() { return m_pFade; }
	static CParamStorage* GetParamStrage() { return m_pParamStrage; }
	static CFixedValue* GetFixValue() { return m_pFixedValue; }	// �Œ�l�N���X�̎擾

	static CLight* GetLight() { return m_pLight; }					// ���C�g�̎擾
	static CCamera* GetCamera() { return m_pCamera; }				// �J�����̎擾

};

#endif // !_MANAGER_H_
