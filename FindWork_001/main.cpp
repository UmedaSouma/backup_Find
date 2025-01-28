//============================================
// 
// ���߂Ă�DirectX
// Autor:souma umeda
// 
//============================================
#include "main.h"
#include "object.h"
#include "object2D.h"
#include "manager.h"

// �v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// �O���[�o���ϐ�
DWORD dwCrrentTime;	//���ݎ���
DWORD dwEXecLastTime;	// �Ō�ɏ�����������
int g_nCountFPS;

CManager* g_pManager = nullptr;
RECT CMain::m_WindowRect = {};
bool CMain::m_IsFullScreem = false;

void SetCrrent(DWORD w)
{
	dwCrrentTime = w;
}

void SetLastTime(DWORD w)
{
	dwEXecLastTime = w;
}

DWORD* GetCrrent()
{
	return &dwCrrentTime;
}

DWORD* GetLastTime()
{
	return &dwEXecLastTime;
}

int GetCountFPS()
{
	return g_nCountFPS;
}

//============================================
// ���C���֐�
//============================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE /*hInstancePrev*/, _In_ LPSTR /*lpCmdline*/, _In_ int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				// WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,						// �E�B���h�E�̃X�^�C��
		WindowProc,						// �E�B���h�E�v���V�[�W��
		0,								// 
		0,								// 
		hInstance,						// 
		LoadIcon(nullptr,IDI_APPLICATION),	// 
		LoadCursor(nullptr,IDC_ARROW),		// 
		(HBRUSH)(COLOR_WINDOW + 1),		// 
		nullptr,							// 
		CLASS_NAME,						// 
		LoadIcon(nullptr,IDI_APPLICATION)	// 
	};

	HWND hWnd;
	MSG msg;

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };	// ��ʃT�C�Y�̍\����

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	// �����_���[����
	g_pManager = new CManager;

	//g_pManager->Init(hInstance, hWnd, TRUE);

	// ����������
	if (FAILED(g_pManager->Init(hInstance, hWnd, TRUE)))
	{// ���������������s�����ꍇ
		return-1;
	}

	// �E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	DWORD dwFrameCount;
	DWORD dwFPSLastTime;

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

#if _DEBUG
#else
	//CMain::ToggleFullscreen(hWnd);
#endif

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0)
		{// windows�̏���
			if (msg.message == WM_QUIT)
			{// WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{

				// ���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);
				DispatchMessage(&msg);

			}
		}
		else
		{
			dwCrrentTime = timeGetTime();	// ���ݎ������擾
			if ((dwCrrentTime - dwFPSLastTime) >= 500)
			{
				// FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCrrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCrrentTime;	// FPS���v������������ۑ�
				dwFrameCount = 0;	// �t���[���J�E���g���N���A
			}
			if ((dwCrrentTime - dwEXecLastTime) >= (1000 / 60))
			{// 60����1�b�o��
				dwFrameCount++;	// �t���[���J�E���g�����Z

				dwEXecLastTime = dwCrrentTime;	// �����̊J�n�̎���[���ݎ���]��ۑ�

				// �����_���[�X�V
				g_pManager->Update();

				// �����_���[�`��
				g_pManager->Draw();
			}
		}
	}

	g_pManager->Uninit();

	// �����_���[�J��
	delete g_pManager;
	g_pManager = nullptr;

	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

////============================================
//// ����������
////============================================
//HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
//{
//	D3DDISPLAYMODE d3ddm;	// �f�B�X�v���C���[�h
//	D3DPRESENT_PARAMETERS d3dpp;	// �v���[���e�[�V�����p�����[�^
//
//	// Direct3D�I�u�W�F�N�g�̐���
//	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
//
//
//	if (g_pD3D == nullptr)
//	{
//		return E_FAIL;
//	}
//
//	// ���݂̃f�B�X�v���C���[�h���擾
//	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
//	{
//		return E_FAIL;
//	}
//
//	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
//	ZeroMemory(&d3dpp, sizeof(d3dpp));							// �p�����[�^�̃[���N���A
//
//	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[����ʂ̃T�C�Y(��)
//	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[����ʂ̃T�C�Y(����)
//	d3dpp.BackBufferFormat = d3ddm.Format;						// 
//	d3dpp.BackBufferCount = 1;									// 
//	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// 
//	d3dpp.EnableAutoDepthStencil = TRUE;						// 
//	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// 
//	d3dpp.Windowed = bWindow;									// 
//	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// 
//	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// 
//
//	// 
//	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
//		D3DDEVTYPE_HAL,
//		hWnd,
//		D3DCREATE_HARDWARE_VERTEXPROCESSING,
//		&d3dpp,
//		&g_pD3DDevice)))
//	{
//		// 
//		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
//			D3DDEVTYPE_HAL,
//			hWnd,
//			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
//			&d3dpp,
//			&g_pD3DDevice)))
//		{
//			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
//				D3DDEVTYPE_REF,
//				hWnd,
//				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
//				&d3dpp,
//				&g_pD3DDevice)))
//			{
//				return E_FAIL;
//			}
//		}
//	}
//
//	//
//	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
//	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
//	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//
//	//
//	InitPolygon();
//
//
//	return S_OK;
//
//}

//============================================
// �E�B���h�E�v���V�[�W��
//============================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	static HWND hWndEditInput;
	static HWND hWndEditOutput;

	switch (uMsg)
	{
	case WM_DESTROY:

		PostQuitMessage(0);
		break;



	case WM_COMMAND:
		if (LOWORD(wParam) == ID_BUTTON_FINISH)
		{
			nID = MessageBox(hWnd, "�I�����܂���", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
		}

	case WM_CLOSE:

		nID = MessageBox(hWnd, "�I�����܂���", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_ICONERROR);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
				break;
			}
			break;

		case VK_F11:
			CMain::ToggleFullscreen(hWnd);
			break;
		}

	

		break;
	}

	

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//====================================================================================
// �t���X�N���[��
//====================================================================================
void CMain::ToggleFullscreen(HWND hWnd)
{
	// ���݂̃E�B���h�E�X�^�C�����擾
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (m_IsFullScreem)
	{
		// �E�B���h�E���[�h�ɐ؂�ւ�
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, m_WindowRect.left, m_WindowRect.top,
			m_WindowRect.right - m_WindowRect.left, m_WindowRect.bottom - m_WindowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// �t���X�N���[�����[�h�ɐ؂�ւ�
		GetWindowRect(hWnd, &m_WindowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	m_IsFullScreem = !m_IsFullScreem;
}

CMain::CMain()
{
}

CMain::~CMain()
{
}

////============================================
//// �X�V����
////============================================
//void Update(void)
//{
//	UpdatePolygon();
//}
//
////============================================
//// �I������
////============================================
//void Uninit(void)
//{
//	//
//	UninitPolygon();
//
//	// 
//	if (g_pD3DDevice != nullptr)
//	{
//		g_pD3DDevice->Release();
//		g_pD3DDevice = nullptr;
//	}
//
//	// 
//	if (g_pD3D != nullptr)
//	{
//		g_pD3D->Release();
//		g_pD3D = nullptr;
//	}
//}
//
////============================================
//// �`�揈��
////============================================
//void Draw(void)
//{
//	// 
//	g_pD3DDevice->Clear(0, nullptr,
//		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
//		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
//
//	// 
//	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
//	{
//		//
//		DrawPolygon();
//
//		// 
//		g_pD3DDevice->EndScene();
//	}
//
//	g_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
//}

////============================================
//// �|���S������������
////============================================
//void InitPolygon(void)
//{
//	g_aVertex[0].pos = { SCREEN_WIDTH * 0.4f,SCREEN_HEIGHT * 0.4f,0 };
//	g_aVertex[1].pos = { SCREEN_WIDTH * 0.8f,SCREEN_HEIGHT * 0.4f,0 };
//	g_aVertex[2].pos = { SCREEN_WIDTH * 0.4f,SCREEN_HEIGHT * 0.8f,0 };
//	g_aVertex[3].pos = { SCREEN_WIDTH * 0.8f,SCREEN_HEIGHT * 0.8f,0 };
//
//	for (int nCnt = 0; nCnt < 4; nCnt++)
//	{
//		g_aVertex[nCnt].rhw = 1.0f;
//		g_aVertex[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
//	}
//}
//
////============================================
//// �|���S���I������
////============================================
//void UninitPolygon(void)
//{
//
//}
//
////============================================
//// �|���S���X�V����
////============================================
//void UpdatePolygon(void)
//{
//
//}
//
////============================================
//// �|���S���`�揈��
////============================================
//void DrawPolygon(void)
//{
//	//
//	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
//
//	//
//	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
//		2,
//		&g_aVertex[0],
//		sizeof(VERTEX_2D));
//
//}
//
//void CPolygon::Init()
//{
//
//}
//
//void CPolygon::Uninit()
//{
//
//}
//
//void CPolygon::Update()
//{
//
//}
//
//void CPolygon::Draw()
//{
//
//}