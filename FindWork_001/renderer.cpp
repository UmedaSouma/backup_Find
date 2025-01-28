#include "renderer.h"
#include "object.h"
#include "scene.h"
#include "manager.h"
#include "search.h"
#include "car_player.h"
#include "car_enemy.h"

// 静的メンバ変数の初期化
CText* CRenderer::m_pText = nullptr;
//===========================================================================================================
// コンストラクタ
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
// デストラクタ
//===========================================================================================================
CRenderer::~CRenderer()
{

}

//===========================================================================================================
// 初期設定
//===========================================================================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;	// ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	// プレゼンテーションパラメータ

	timeBeginPeriod(1);
	SetCrrent(0);
	SetLastTime(timeGetTime());


	// Direct3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	m_pText = new CText;
	m_pText->Init();

	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// ゲーム画面のサイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// ゲーム画面のサイズ(高さ)
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

	// デバック表示用フォントの生成
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH, "Terminal", &m_pFont);

	return S_OK;
}

//===========================================================================================================
// 終了処理
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
// 更新処理
//===========================================================================================================
void CRenderer::Update()
{
	// 全て更新
	CObject::UpdateAll();
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CRenderer::Draw()
{
	// 背景などの設定
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

		// 全て描画
		CObject::DrawAll();

		m_pText->DrawAll();

		// デバッグテキスト
		DebugPrint(aStr[0]);

		// 
		m_pD3DDevice->EndScene();

#ifdef _DEBUG

		// テキストの描画
		m_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

		m_pFont->DrawText(NULL, &m_aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 255, 255, 255));

#endif // _DEBUG
	}

	m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

//===========================================================================================================
// デバッグテキストの描画
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
		"\n車の位置 : %f , %f , %f"
		"\n車の移動量 : %f , %f , %f"
		"\n車の向き : %f"
		"\n車の移動方向 : %f"
		"\n車のスピード : %f"
		"\nカメラの向き : x = %f , y = %f ,  z = %f"
		"\n現在のギア : %d"
		"\nカメラをどのくらい遅らせているか : %f"
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
// デバイスの取得
//===========================================================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice()
{
	return m_pD3DDevice;
}

//===========================================================================================================
// デバッグテキスト
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
// デバッグテキスト
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
