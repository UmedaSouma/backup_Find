#include "renderer.h"
#include "object.h"
#include "scene.h"
#include "manager.h"
#include "search.h"
#include "car_player.h"
#include "car_enemy.h"

// �ÓI�����o�ϐ��̏�����
CText* CRenderer::m_pText = nullptr;
//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CRenderer::CRenderer()
{
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;
	m_pFont = nullptr;

	for (int i = 0; i < 256; i++)
	{
		m_aStr[i] = NULL;
	}
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CRenderer::~CRenderer()
{

}

//===========================================================================================================
// �����ݒ�
//===========================================================================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;	// �f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	// �v���[���e�[�V�����p�����[�^

	timeBeginPeriod(1);
	SetCrrent(0);
	SetLastTime(timeGetTime());


	// Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	m_pText = new CText;
	m_pText->Init();

	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// �p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[����ʂ̃T�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[����ʂ̃T�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						// 
	d3dpp.BackBufferCount = 1;									// 
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// 
	d3dpp.EnableAutoDepthStencil = TRUE;						// 
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// 
	d3dpp.Windowed = bWindow;									// 
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// 
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// 

	// 
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		// 
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �f�o�b�N�\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH, "Terminal", &m_pFont);

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CRenderer::Uninit()
{

	// 
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	// 
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}

	if (m_pText != nullptr)
	{
		m_pText->Uninit();
		delete m_pText;
		m_pText = nullptr;
	}
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CRenderer::Update()
{
	// �S�čX�V
	CObject::UpdateAll();
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CRenderer::Draw()
{
	// �w�i�Ȃǂ̐ݒ�
	if (CScene::GetMode() == CScene::MODE_GAME)
	{
		m_pD3DDevice->Clear(0, nullptr,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(100, 178, 255, 0), 1.0f, 0);
	}
	else
	{
		m_pD3DDevice->Clear(0, nullptr,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	}

	// 
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

		char aStr[512] = {};
		char astrr[512] = {};

		CManager::GetCamera()->SetCamera();

		// �S�ĕ`��
		CObject::DrawAll();

		m_pText->DrawAll();

		// �f�o�b�O�e�L�X�g
		DebugPrint(aStr[0]);

		// 
		m_pD3DDevice->EndScene();

#ifdef _DEBUG

		// �e�L�X�g�̕`��
		m_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

		m_pFont->DrawText(NULL, &m_aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 255, 255, 255));

#endif // _DEBUG
	}

	m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

//===========================================================================================================
// �f�o�b�O�e�L�X�g�̕`��
//===========================================================================================================
void CRenderer::DebugPrint(char& pStr)
{
	CCarPlayer* pCarPlayer = nullptr;
	CCarEnemy* pCarEnemy = nullptr;
	CCamera* pCamera = CManager::GetCamera();

	pCarPlayer = CSearch::SearchObject(pCarPlayer, CObject::TYPE::CAR_PLAYER);
	//pCarEnemy = CSearch::SearchObject(pCarEnemy, CObject::TYPE::CAR_ENEMY);

	if (pCarPlayer == nullptr || pCamera == nullptr/* || pCarEnemy == nullptr*/)
	{
		return;
	}

	sprintf(&pStr,
		"\nFPS : %d"
		"\n�Ԃ̈ʒu : %f , %f , %f"
		"\n�Ԃ̈ړ��� : %f , %f , %f"
		"\n�Ԃ̌��� : %f"
		"\n�Ԃ̈ړ����� : %f"
		"\n�Ԃ̃X�s�[�h : %f"
		"\n�J�����̌��� : x = %f , y = %f ,  z = %f"
		"\n���݂̃M�A : %d"
		"\n�J�������ǂ̂��炢�x�点�Ă��邩 : %f"
		, GetCountFPS()
		, pCarPlayer->GetPos().x, pCarPlayer->GetPos().y, pCarPlayer->GetPos().z
		, pCarPlayer->GetMove().x, pCarPlayer->GetMove().y, pCarPlayer->GetMove().z
		, pCarPlayer->GetRot().y
		, pCarPlayer->GetMoveAngle()
		, pCarPlayer->GetAccumulationSpeed()
		, pCamera->GetRot().x, pCamera->GetRot().y, pCamera->GetRot().z
		, pCarPlayer->GetGear()
		, pCamera->GetFollow()
	);
}

//===========================================================================================================
// �f�o�C�X�̎擾
//===========================================================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice()
{
	return m_pD3DDevice;
}

//===========================================================================================================
// �f�o�b�O�e�L�X�g
//===========================================================================================================
void CRenderer::SetDebugInfo(VERTEX_3D* pVtx, WORD dwHitVertexNo1, WORD dwHitVertexNo2, WORD dwHitVertexNo3)
{
	sprintf(m_aStr,
		"\nVtxIdx 0 = %d"
		"\nVtxIdx 1 = %d"
		"\nVtxIdx 2 = %d"
		,dwHitVertexNo1
		,dwHitVertexNo2
		,dwHitVertexNo3
	);
}

//===========================================================================================================
// �f�o�b�O�e�L�X�g
//===========================================================================================================
void CRenderer::SetDebugRoutePoint(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 nextroute, int ID, bool clear)
{
	const char* btext[64];
	for (int i = 0; i < 64; i++)
	{
		btext[i] = nullptr;
	}

	if (clear)
	{
		btext[0] = "true";
	}
	else
	{
		btext[0] = "false";
	}

	sprintf(m_aStr,
		"\npos = %f,%f,%f"
		"\nmove = %f,%f,%f"
		"\nnextroute = %f,%f,%f"
		"\nnextrouteID = %d"
		"\nclear = %s"
		, pos.x, pos.y, pos.z
		, move.x, move.y, move.z
		, nextroute.x, nextroute.y, nextroute.z
		, ID
		, btext[0]
	);
}
