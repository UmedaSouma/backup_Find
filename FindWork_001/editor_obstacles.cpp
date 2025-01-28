//===========================================================================================================================================================
// 
// 障害物設置用のシーン [editor_obstacles.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "editor_obstacles.h"
#include "fade.h"
#include "manager.h"
#include "course.h"
#include <fstream>
#include "search.h"


//========================================================================================================================
// コンストラクタ
//========================================================================================================================
CEditorObstacle::CEditorObstacle()
{
	m_pMother = nullptr;
}

//========================================================================================================================
// デストラクタ
//========================================================================================================================
CEditorObstacle::~CEditorObstacle()
{
}

//========================================================================================================================
// 初期設定
//========================================================================================================================
HRESULT CEditorObstacle::Init()
{
	if (m_pMother == nullptr)
	{// 親ポイント初期設定
		m_pMother = CObstacle::Create({ 0.0f,0.0f,0.0f }, CObstacle::OBS_DRUMCAN);
	}

	CCourse::Create(CCourse::COURSE_01);


	//CScene::Init();
	return S_OK;
}

//========================================================================================================================
// 終了処理
//========================================================================================================================
void CEditorObstacle::Uninit()
{
	CScene::Uninit();
}

//========================================================================================================================
// 更新処理
//========================================================================================================================
void CEditorObstacle::Update()
{
	Controll();

	CCamera* pCamera = CManager::GetCamera();	// camera を持ってくる
	pCamera->SetTargetPos(m_pMother->GetPos());	// camera に playerpos を入れる

	CScene::Update();
}

//========================================================================================================================
// 描画処理
//========================================================================================================================
void CEditorObstacle::Draw()
{
	CScene::Draw();
}

//===========================================================================================================
// 操作部分の更新処理
//===========================================================================================================
void CEditorObstacle::Controll()
{
	CInputKeyBoard* keyboard = CManager::GetKeyboard();
	CFade* pFade = CManager::GetFade();

	if (keyboard->GetTrigger(DIK_RETURN))
	{
		CObstacle::Create(m_pMother->GetPos(),m_pMother->GetObsType());
		//m_nNum++;
	}

	if (keyboard->GetTrigger(DIK_4))
	{
		SaveObs();
	}

	if (keyboard->GetTrigger(DIK_5))
	{
		//Load();
	}

	// 移動操作
	ControllMove(keyboard);

	if (keyboard->GetTrigger(DIK_F3))
	{// シーン切り替え
		pFade->SetFade(CScene::MODE_GAME);
	}
}

//===========================================================================================================
// 移動部分の操作
//===========================================================================================================
void CEditorObstacle::ControllMove(CInputKeyBoard* keyboard)
{
	// 移動値
	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f };

	if (keyboard->GetPress(DIK_D))
	{
		move.x = 1;
	}
	else if (keyboard->GetPress(DIK_A))
	{
		move.x = -1;
	}

	if (keyboard->GetPress(DIK_W))
	{
		move.z = 1;
	}
	else if (keyboard->GetPress(DIK_S))
	{
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

	if (keyboard->GetPress(DIK_LSHIFT))
	{
		move *= 6.f;
	}
	else
	{
		move *= 3.f;
	}


	m_pMother->SetMove(move);
}

//===========================================================================================================
// 書き込み処理
//===========================================================================================================
void CEditorObstacle::SaveObs()
{
	using namespace std;

	// 書き出す用の変数
	ofstream OutputFile(FPASS_OBS);

	if (!OutputFile)
	{
		return;
	}

	// 外部ファイルに保存
	OutputFile
		<< major_h << "障害物の保存先" << txt_break << major_h
		<< "SET_SCRIPT" << txt_break
		<< sub_h << "障害物の情報" << txt_break << sub_h
		;

	OutputFile.close();

	SaveInfoObs();

	//ofstream Output(Fpass,ios::app);

	//

	//OutputFile.close();
}

//===========================================================================================================
// 情報の書き込み
//===========================================================================================================
void CEditorObstacle::SaveInfoObs()
{
	using namespace std;

	// 書き出す用の変数(追加書き込み
	ofstream OutputFile(FPASS_OBS, ios::app);

	if (!OutputFile)
	{
		return;
	}

	vector< CObstacle*>v_Point;
	v_Point.clear();

	v_Point = CSearch::SearchMultiObject(v_Point, CObject::TYPE::OBSTACLE);

	if (v_Point.empty())
	{
		return;
	}

	unsigned int size = v_Point.size();

	for (unsigned int i = 0; i < size; i++)
	{
		if (i == 0) 
		{ continue; }

		D3DXVECTOR3 pos = v_Point[i]->GetPos();
		CObstacle::OBS_TYPE type = v_Point[i]->GetObsType();

		OutputFile
			<< "SET_OBSTACLE_INFO" << txt_break << txt_break
			<< "POS = " << txt_break
			<< pos.x << txt_break
			<< pos.y << txt_break
			<< pos.z << txt_break << txt_break
			<< "TYPE = " << type << txt_break
			<< "END_OBSTACLE_INFO" << txt_break << txt_break
			;
	}

	OutputFile
		<< "END_SCRIPT"
		;

	OutputFile.close();
}

//========================================================================================================================
// 生成処理
//========================================================================================================================
CEditorObstacle* CEditorObstacle::Create()
{
	CEditorObstacle* pEditObs = new CEditorObstacle;
	pEditObs->Init();

	return pEditObs;
}