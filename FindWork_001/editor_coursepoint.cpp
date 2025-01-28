//===========================================================================================================================================================
// 
// �R�[�X�̓�����ҏW���鏈�� [editor_coursepoint.cpp]
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
// �R���X�g���N�^
//========================================================================================================================
CEditorCoursePoint::CEditorCoursePoint()
{
	m_pPointMother = nullptr;
	m_nNum = 0;
}

//========================================================================================================================
// �f�X�g���N�^
//========================================================================================================================
CEditorCoursePoint::~CEditorCoursePoint()
{
}

//========================================================================================================================
// �����ݒ�
//========================================================================================================================
HRESULT CEditorCoursePoint::Init()
{
	if (m_pPointMother == nullptr)
	{// �e�|�C���g�����ݒ�
		m_pPointMother = new CCoursePoint;
		m_pPointMother->SetIdx(-1);
		m_pPointMother->Init();
	}

	CCamera* pCamera = CManager::GetCamera();	// camera �������Ă���
	pCamera->SetCameraTarget(CCamera::CAMERA_TARGET_TYPE::PLAYER);

	CCourse::Create(CCourse::COURSE_01);
	m_nNum = 0;

	return S_OK;
}

//========================================================================================================================
// �I������
//========================================================================================================================
void CEditorCoursePoint::Uninit()
{
	if (m_pPointMother != nullptr)
	{// �e�|�C���g�I������
		m_pPointMother->Uninit();
	}

	CScene::Uninit();
}

//========================================================================================================================
// �X�V����
//========================================================================================================================
void CEditorCoursePoint::Update()
{
	if (m_pPointMother != nullptr)
	{
		Controll();

		CCamera* pCamera = CManager::GetCamera();	// camera �������Ă���
		pCamera->SetTargetPos(m_pPointMother->GetPos());	// camera �� playerpos ������
		pCamera->SetRot(m_pPointMother->GetRot());

		// �f�o�b�O�\��
		CManager::GetRenderer()->SetDebugRoutePoint(m_pPointMother->GetPos(), m_pPointMother->GetRot(), { 0,0,0 }, 0, false);
	}
}

//========================================================================================================================
// �`�揈��
//========================================================================================================================
void CEditorCoursePoint::Draw()
{
}

//===========================================================================================================
// ���암���̍X�V����
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

	// �ړ�����
	ControllMove(keyboard);

	if (keyboard->GetTrigger(DIK_F2))
	{// �V�[���؂�ւ�
		pFade->SetFade(CScene::MODE_EDIT_OBSTACLE);
	}

	if (keyboard->GetTrigger(DIK_F3))
	{// �V�[���؂�ւ�
		pFade->SetFade(CScene::MODE_GAME);
	}
}

//===========================================================================================================
// �ړ������̑���
//===========================================================================================================
void CEditorCoursePoint::ControllMove(CInputKeyBoard* keyboard)
{
	// �ړ��l
	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f };
	// ����
	D3DXVECTOR3 rot = m_pPointMother->GetRot();
	// �ʒu
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
// �������ݏ���
//===========================================================================================================
void CEditorCoursePoint::Save()
{
	using namespace std;

	// �����o���p�̕ϐ�
	ofstream OutputFile(FPASS_CORSE);

	if (!OutputFile)
	{ return; }

	// �O���t�@�C���ɕۑ�
	OutputFile
		<< major_h << "�����̕ۑ���" << txt_break << major_h
		<< "SET_SCRIPT" << txt_break
		<< sub_h << "�|�C���g�̏��" << txt_break << sub_h
		;

	OutputFile.close();
	
	SaveInfo();

	//ofstream Output(Fpass,ios::app);

	//

	//OutputFile.close();
}

//===========================================================================================================
// ���̏�������
//===========================================================================================================
void CEditorCoursePoint::SaveInfo()
{
	using namespace std;

	// �����o���p�̕ϐ�(�ǉ���������
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


