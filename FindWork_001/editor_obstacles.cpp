//===========================================================================================================================================================
// 
// ��Q���ݒu�p�̃V�[�� [editor_obstacles.cpp]
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
// �R���X�g���N�^
//========================================================================================================================
CEditorObstacle::CEditorObstacle()
{
	m_pMother = nullptr;
}

//========================================================================================================================
// �f�X�g���N�^
//========================================================================================================================
CEditorObstacle::~CEditorObstacle()
{
}

//========================================================================================================================
// �����ݒ�
//========================================================================================================================
HRESULT CEditorObstacle::Init()
{
	if (m_pMother == nullptr)
	{// �e�|�C���g�����ݒ�
		m_pMother = CObstacle::Create({ 0.0f,0.0f,0.0f }, CObstacle::OBS_DRUMCAN);
	}

	CCourse::Create(CCourse::COURSE_01);


	//CScene::Init();
	return S_OK;
}

//========================================================================================================================
// �I������
//========================================================================================================================
void CEditorObstacle::Uninit()
{
	CScene::Uninit();
}

//========================================================================================================================
// �X�V����
//========================================================================================================================
void CEditorObstacle::Update()
{
	Controll();

	CCamera* pCamera = CManager::GetCamera();	// camera �������Ă���
	pCamera->SetTargetPos(m_pMother->GetPos());	// camera �� playerpos ������

	CScene::Update();
}

//========================================================================================================================
// �`�揈��
//========================================================================================================================
void CEditorObstacle::Draw()
{
	CScene::Draw();
}

//===========================================================================================================
// ���암���̍X�V����
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

	// �ړ�����
	ControllMove(keyboard);

	if (keyboard->GetTrigger(DIK_F3))
	{// �V�[���؂�ւ�
		pFade->SetFade(CScene::MODE_GAME);
	}
}

//===========================================================================================================
// �ړ������̑���
//===========================================================================================================
void CEditorObstacle::ControllMove(CInputKeyBoard* keyboard)
{
	// �ړ��l
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
// �������ݏ���
//===========================================================================================================
void CEditorObstacle::SaveObs()
{
	using namespace std;

	// �����o���p�̕ϐ�
	ofstream OutputFile(FPASS_OBS);

	if (!OutputFile)
	{
		return;
	}

	// �O���t�@�C���ɕۑ�
	OutputFile
		<< major_h << "��Q���̕ۑ���" << txt_break << major_h
		<< "SET_SCRIPT" << txt_break
		<< sub_h << "��Q���̏��" << txt_break << sub_h
		;

	OutputFile.close();

	SaveInfoObs();

	//ofstream Output(Fpass,ios::app);

	//

	//OutputFile.close();
}

//===========================================================================================================
// ���̏�������
//===========================================================================================================
void CEditorObstacle::SaveInfoObs()
{
	using namespace std;

	// �����o���p�̕ϐ�(�ǉ���������
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
// ��������
//========================================================================================================================
CEditorObstacle* CEditorObstacle::Create()
{
	CEditorObstacle* pEditObs = new CEditorObstacle;
	pEditObs->Init();

	return pEditObs;
}