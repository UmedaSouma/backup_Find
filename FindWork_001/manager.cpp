#include "manager.h"


// �ÓI�����o�̏�����
CScene* CManager::m_pScene = nullptr;
CRenderer* CManager::m_pRenderer = nullptr;
CInputKeyBoard* CManager::m_pKeyboard = nullptr;
CInputJoypad* CManager::m_pJoypad = nullptr;
CTexture* CManager::m_pTexture = nullptr;
CModeldata* CManager::m_pModeldata = nullptr;
CFade* CManager::m_pFade = nullptr;
CLight* CManager::m_pLight = nullptr;
CCamera* CManager::m_pCamera = nullptr;
CParamStorage* CManager::m_pParamStrage = nullptr;
CFixedValue* CManager::m_pFixedValue = nullptr;


//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CManager::CManager()
{

}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CManager::~CManager()
{

}

//===========================================================================================================
// �����ݒ�
//===========================================================================================================
HRESULT CManager::Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow)
{

	srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����

	m_pKeyboard = new CInputKeyBoard;
	m_pJoypad = new CInputJoypad;
	m_pRenderer = new CRenderer;
	m_pTexture = new CTexture;
	m_pModeldata = new CModeldata;
	m_pFade = new CFade;
	m_pParamStrage = new CParamStorage;
	if (m_pFixedValue == nullptr)
	{
		m_pFixedValue = new CFixedValue;
	}


	m_pCamera = new CCamera;
	m_pLight = new CLight;

	m_pRenderer->Init(hWnd, bWindow);
	m_pKeyboard->Init(hinstance, hWnd);
	m_pJoypad->Init();
	m_pFade->Init();
	m_pParamStrage->Road();

	m_pCamera->Init();
	m_pLight->Init();

	m_pFade->SetFade(CScene::MODE_TITLE);
	//SetMode(CScene::MODE_TITLE);

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CManager::Uninit()
{
	//TextureUnLoadAll();

	m_pTexture->Unload();
	m_pModeldata->Unload();

	m_pFade->Uninit();

	m_pJoypad->Uninit();
	m_pKeyboard->Uninit();

	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
	}

	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pLight != nullptr)
	{
		delete m_pLight;
		m_pLight = nullptr;
	}

	if (m_pCamera != nullptr)
	{
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pParamStrage != nullptr)
	{
		delete m_pParamStrage;
		m_pParamStrage = nullptr;
	}

	if (m_pFixedValue != nullptr)
	{
		delete m_pFixedValue;
		m_pFixedValue = nullptr;
	}


	CObject::DeathAll();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CManager::Update()
{

	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

	//if (m_pFade->GetState() != CFade::FADE_OUT)
	{
		if (m_pScene != nullptr)
		{
			m_pScene->Update();
		}
	}

	m_pCamera->Update();
	m_pKeyboard->Update();
	m_pJoypad->Update();

	//m_pFade->Update();

}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CManager::Draw()
{
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}

	if (m_pFade->GetState() == CFade::FADE_NONE)
	{
		if (m_pScene != nullptr)
		{
			m_pScene->Draw();
		}
	}

	//m_pFade->Draw();
}

//===========================================================================================================
// ���[�h�ݒ�
//===========================================================================================================
void CManager::SetMode(CScene::MODE mode)
{
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	m_pScene = CScene::Create(mode);
	m_pScene->Init();
}

