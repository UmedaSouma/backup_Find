#include "manager.h"


// 静的メンバの初期化
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
CManagerNumber* CManager::m_pCMnumber = nullptr;
bool CManager::m_SceneStop = false;

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CManager::CManager()
{

}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CManager::~CManager()
{

}

//===========================================================================================================
// 初期設定
//===========================================================================================================
HRESULT CManager::Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow)
{
	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化

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

	m_pCMnumber = new CManagerNumber;

	m_pRenderer->Init(hWnd, bWindow);
	m_pKeyboard->Init(hinstance, hWnd);
	m_pJoypad->Init();
	m_pFade->Init();
	m_pParamStrage->Road();

	m_pCamera->Init();
	m_pLight->Init();
	//m_pCMnumber->Init();

	m_pFade->SetFade(CScene::MODE_TITLE);
	//SetMode(CScene::MODE_TITLE);

	return S_OK;
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CManager::Uninit()
{
	//TextureUnLoadAll();

	m_pTexture->Unload();
	m_pModeldata->Unload();

	m_pFade->Uninit();

	m_pJoypad->Uninit();
	m_pKeyboard->Uninit();

	if (m_pCMnumber != nullptr)
	{
		m_pCMnumber->Uninit();
		m_pCMnumber = nullptr;
	}

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

	//if (m_pCMnumber != nullptr)
	//{
	//	delete m_pCMnumber;
	//	m_pCMnumber = nullptr;
	//}


	CObject::DeathAll();
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CManager::Update()
{
	m_pKeyboard->Update();
	m_pJoypad->Update();

	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

	m_pCamera->Update();

	if (m_pScene != nullptr)
	{
		m_pScene->Update();
	}
}

//===========================================================================================================
// 描画処理
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
// モード設定
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

