//===========================================================================================================================================================
// 
// コースの道順を編集する処理 [editor_coursepoint.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "editor_coursepoint.h"
#include "fade.h"
#include "manager.h"
#include "course.h"
#include <fstream>
#include "search.h"

//========================================================================================================================
// コンストラクタ
//========================================================================================================================
CEditorCoursePoint::CEditorCoursePoint()
{
	m_pPointMother = nullptr;
	m_nNum = 0;
}

//========================================================================================================================
// デストラクタ
//========================================================================================================================
CEditorCoursePoint::~CEditorCoursePoint()
{
}

//========================================================================================================================
// 初期設定
//========================================================================================================================
HRESULT CEditorCoursePoint::Init()
{
	if (m_pPointMother == nullptr)
	{// 親ポイント初期設定
		m_pPointMother = new CCoursePoint;
		m_pPointMother->SetIdx(-1);
		m_pPointMother->Init();
	}

	CCamera* pCamera = CManager::GetCamera();	// camera を持ってくる
	pCamera->SetCameraTarget(CCamera::CAMERA_TARGET_TYPE::PLAYER);

	CCourse::Create(CCourse::COURSE_01);
	m_nNum = 0;

	return S_OK;
}

//========================================================================================================================
// 終了処理
//========================================================================================================================
void CEditorCoursePoint::Uninit()
{
	if (m_pPointMother != nullptr)
	{// 親ポイント終了処理
		m_pPointMother->Uninit();
	}

	CScene::Uninit();
}

//========================================================================================================================
// 更新処理
//========================================================================================================================
void CEditorCoursePoint::Update()
{
	if (m_pPointMother != nullptr)
	{
		Controll();

		CCamera* pCamera = CManager::GetCamera();	// camera を持ってくる
		pCamera->SetTargetPos(m_pPointMother->GetPos());	// camera に playerpos を入れる
		pCamera->SetRot(m_pPointMother->GetRot());

		// デバッグ表示
		CManager::GetRenderer()->SetDebugRoutePoint(m_pPointMother->GetPos(), m_pPointMother->GetRot(), { 0,0,0 }, 0, false);
	}
}

//========================================================================================================================
// 描画処理
//========================================================================================================================
void CEditorCoursePoint::Draw()
{
}

//===========================================================================================================
// 操作部分の更新処理
//===========================================================================================================
void CEditorCoursePoint::Controll()
{
	CInputKeyBoard* keyboard = CManager::GetKeyboard();
	CFade* pFade = CManager::GetFade();

	if (keyboard->GetTrigger(DIK_RETURN))
	{
		CCoursePoint::Create(m_nNum, m_pPointMother->GetPos(),m_pPointMother->GetRot());
		m_nNum++;
	}

	if (keyboard->GetTrigger(DIK_4))
	{
		Save();
	}

	if (keyboard->GetTrigger(DIK_5))
	{
		//Load();
	}

	// 移動操作
	ControllMove(keyboard);

	if (keyboard->GetTrigger(DIK_F2))
	{// シーン切り替え
		pFade->SetFade(CScene::MODE_EDIT_OBSTACLE);
	}

	if (keyboard->GetTrigger(DIK_F3))
	{// シーン切り替え
		pFade->SetFade(CScene::MODE_GAME);
	}
}

//===========================================================================================================
// 移動部分の操作
//===========================================================================================================
void CEditorCoursePoint::ControllMove(CInputKeyBoard* keyboard)
{
	// 移動値
	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f };
	// 向き
	D3DXVECTOR3 rot = m_pPointMother->GetRot();
	// 位置
	D3DXVECTOR3 pos = m_pPointMother->GetPos();

	if (keyboard->GetPress(DIK_D))
	{
		pos.x += 3;
	}
	else if (keyboard->GetPress(DIK_A))
	{
		pos.x -= 3;
	}

	if (keyboard->GetPress(DIK_W))
	{
		move.x = 1;
		move.z = 1;
	}
	else if (keyboard->GetPress(DIK_S))
	{
		move.x = -1;
		move.z = -1;
	}

	if (keyboard->GetPress(DIK_O))
	{
		move.y = 1;
	}
	else if (keyboard->GetPress(DIK_L))
	{
		move.y = -1;
	}

	if (keyboard->GetPress(DIK_E))
	{
		rot.y += 0.01f;
	}
	else if (keyboard->GetPress(DIK_Q))
	{
		rot.y -= 0.01f;
	}

	move *= 3.f;

	pos.x += sinf(rot.y) * move.x;
	pos.z += cosf(rot.y) * move.z;

	//m_pPointMother->SetMove(move);
	m_pPointMother->SetRot(rot);
	m_pPointMother->SetPos(pos);
}

//===========================================================================================================
// 書き込み処理
//===========================================================================================================
void CEditorCoursePoint::Save()
{
	using namespace std;

	// 書き出す用の変数
	ofstream OutputFile(FPASS_CORSE);

	if (!OutputFile)
	{ return; }

	// 外部ファイルに保存
	OutputFile
		<< major_h << "道順の保存先" << txt_break << major_h
		<< "SET_SCRIPT" << txt_break
		<< sub_h << "ポイントの情報" << txt_break << sub_h
		;

	OutputFile.close();
	
	SaveInfo();

	//ofstream Output(Fpass,ios::app);

	//

	//OutputFile.close();
}

//===========================================================================================================
// 情報の書き込み
//===========================================================================================================
void CEditorCoursePoint::SaveInfo()
{
	using namespace std;

	// 書き出す用の変数(追加書き込み
	ofstream OutputFile(FPASS_CORSE, ios::app);

	if (!OutputFile)
	{ return; }

	vector< CCoursePoint*>v_Point;
	v_Point.clear();

	v_Point = CSearch::SearchMultiObject(v_Point, CObject::TYPE::POINT);

	if(v_Point.empty())
	{ return; }

	unsigned int size = v_Point.size();

	for (unsigned int i = 0; i < size; i++)
	{
		D3DXVECTOR3 pos = v_Point[i]->GetPos();
		D3DXVECTOR3 rot = v_Point[i]->GetRot();

		int Idx = v_Point[i]->GetIdx();

		if (Idx >= 0)
		{
			OutputFile
				<< "SET_POINTINFO" << txt_break << txt_break
				<< "POS = " << txt_break
				<< pos.x << txt_break
				<< pos.y << txt_break
				<< pos.z << txt_break << txt_break
				<< "ROT = " << txt_break
				<< rot.x << txt_break
				<< rot.y << txt_break
				<< rot.z << txt_break << txt_break
				<< "IDX = " << Idx << txt_break << txt_break
				<< "END_POINTINFO" << txt_break << txt_break
				;
			;
		}
	}

	OutputFile
		<< "END_SCRIPT"
		;

	OutputFile.close();
}


