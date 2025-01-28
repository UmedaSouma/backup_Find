//===========================================================================================================================================================
// 
// �Q�[���̏���
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "game.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"
#include "model.h"
#include "search.h"
#include "player3D.h"
#include "block3D.h"
#include "item.h"
#include "billboard.h"
#include "car_player.h"
#include "car_enemy.h"
#include "param_storage.h"
#include "player_manager.h"
#include "course.h"
#include "course_point.h"
#include "goal.h"
#include "editor_coursepoint.h"
#include "editor_obstacles.h"
#include "speedmeter.h"
#include "gauge.h"
#include "obstacles.h"
#include "tree.h"
#include "cloud.h"
#include "calculation.h"

#include <fstream>

CTimer* CGame::m_timer = nullptr;
CParamStorage* CGame::m_pParamStorage = nullptr;
CPlayerManager* CGame::m_pPlayerManager = nullptr;
CCountdown* CGame::m_pCountDown = nullptr;
int CGame::m_nDelayEnd = 0; // �|���Ă��烊�U���g�ɂȂ�܂�
bool CGame::m_Delay = false;
//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CGame::CGame()
{
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CGame::~CGame()
{
}

//===========================================================================================================
// �����ݒ�
//===========================================================================================================
HRESULT CGame::Init()
{
	// ���ǂݍ���
	Load();
	LoadObs();

	if (m_timer == nullptr)
	{
		m_timer = new CTimer;
		m_timer->Init();
	}
	
	for (int i = 0; i < 100; i++)
	{
		uint64_t type = CCalculation::RandomInt((uint64_t)0, (uint64_t)CParamStorage::CAR_MAX-1);

		CCarEnemy::Create((CParamStorage::TYPE)type/*CParamStorage::CAR_SPORTS*/, { 0.0f,0.0f,100.0f });
	}

	CTree::Create();
	CCloud::Create();
	m_pCountDown = CCountdown::Create();

	//CCarEnemy::Create(CParamStorage::CAR_NORMAL, { 0.0f,0.0f,100.0f });
	//CCarEnemy::Create(CParamStorage::CAR_NORMAL, { 0.0f,0.0f,200.0f });
	//CCarEnemy::Create(CParamStorage::CAR_NORMAL, { 70.0f,0.0f,200.0f });

	CCourse::Create(CCourse::COURSE_01);

	CObstacle::Create({ 120.0f,0.0f,300.0f }, CObstacle::OBS_DRUMCAN);
	CObstacle::Create({ 140.0f,0.0f,300.0f }, CObstacle::OBS_DRUMCAN);

	CSpeedMeter::Create();

	CGoal::Create();

	// �p�����[�^�[�Ǘ��N���X�쐬
	m_pParamStorage = new CParamStorage[CParamStorage::CAR_MAX];

	// �v���C���[�Ǘ��N���X�쐬
	m_pPlayerManager = new CPlayerManager;
	m_pPlayerManager->Init();

	return S_OK;
}

//===========================================================================================================
// ����UI�̃Z�b�g
//===========================================================================================================
void CGame::SetInitUI()
{
	//CUI::Create(
	//	{ SCREEN_WIDTH * 0.4f,SCREEN_HEIGHT * 0.78f,0.0f }
	//	, { 50.0f,50.0f,0 }
	//	, -1
	//	, "data\\TEXTURE\\ui_key_square_1_000.png"
	//);
	//CUI::Create(
	//	{ SCREEN_WIDTH * 0.6f,SCREEN_HEIGHT * 0.78f,0.0f }
	//	, { 50.0f,50.0f,0 }
	//	, -1
	//	, "data\\TEXTURE\\ui_key_square_2_000.png"
	//);
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CGame::Uninit()
{
	if (m_pParamStorage != nullptr)
	{
		// �p�����[�^�[�̕ۊǌɂ��폜
		delete[] m_pParamStorage;
		m_pParamStorage = nullptr;
	}

	if (m_pPlayerManager != nullptr)
	{
		// �v���C���[�Ǘ����폜
		m_pPlayerManager->Uninit();

		delete m_pPlayerManager;
		m_pPlayerManager = nullptr;
	}

	if (m_timer != nullptr)
	{
		m_timer->Uninit();
		m_timer = nullptr;
	}

	CScene::Uninit();
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CGame::Update()
{
	CInputKeyBoard* keyboard = CManager::GetKeyboard();
	CFade* pFade = CManager::GetFade();

#ifdef _DEBUG

	// �f�o�b�O�p�E���ŃV�[���؂�ւ�
	if (keyboard->GetTrigger(DIK_RETURN))
	{
		pFade->SetFade(CScene::MODE_TITLE);

		//CManager::SetMode(CScene::MODE_GAME);
	}

	if (keyboard->GetTrigger(DIK_F2))
	{
		pFade->SetFade(CScene::MODE_EDITOR_PRAM);
	}

#endif // _DEBUG

	if (m_timer != nullptr)
	{
		m_timer->Update();
	}

	m_pPlayerManager->Update();

	//CScene::Update();
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CGame::Draw()
{
	//CScene::Draw();
}

//===========================================================================================================
// �R�[�X�|�C���g�̓ǂݍ���
//===========================================================================================================
void CGame::Load()
{
	// �t�@�C���I�[�v��
	FILE* pfile = fopen(FPASS_CORSE, "r");
	char aString[256];

	if (pfile == nullptr)
	{
		fclose(pfile);
		return;
	}

	while (1)
	{
		fscanf(pfile, "%s", &aString[0]);
		if (strcmp(&aString[0], "END_SCRIPT") == 0)
		{
			fclose(pfile);
			break;
		}
		else if (strcmp(&aString[0], "SET_POINTINFO") == 0)
		{
			LoadInfo(pfile);
		}
	}

	if (pfile != nullptr)
	{// ��̃R�[�h��null�ɂł��Ă��Ȃ�������
		return;
	}

}

//===========================================================================================================
// ��Q���̓ǂݍ���
//===========================================================================================================
void CGame::LoadObs()
{
	// �t�@�C���̓ǂݍ���
	FILE* pfile = fopen(FPASS_OBS, "r");
	char aString[256];

	// �t�@�C���ǂݍ��ݎ��s
	if (pfile == nullptr)
	{
		fclose(pfile);
		return;
	}

	while (1)
	{
		fscanf(pfile, "%s", &aString);
		if (strcmp(&aString[0], "END_SCRIPT") == 0)
		{
			fclose(pfile);
			pfile = nullptr;
			break;
		}
		else if (strcmp(&aString[0], "SET_OBSTACLE_INFO") == 0)
		{
			LoadObsInfo(pfile);
		}
	}

}

//===========================================================================================================
// �R�[�X�|�C���g�̏��ǂݍ���
//===========================================================================================================
void CGame::LoadInfo(FILE* pfile)
{
	char aString[256];

	D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f };
	int Idx = 0;

	while (1)
	{
		fscanf(pfile, "%s", &aString[0]);
		if (strcmp(&aString[0], "END_POINTINFO") == 0)
		{
			CCoursePoint::Create(Idx, pos, rot);
			break;
		}
		else if (strcmp(&aString[0], "POS") == 0)
		{
			fscanf(pfile, "%s", &aString[0]);
			fscanf(pfile, "%f", &pos.x);
			fscanf(pfile, "%f", &pos.y);
			fscanf(pfile, "%f", &pos.z);
		}
		else if (strcmp(&aString[0], "ROT") == 0)
		{
			fscanf(pfile, "%s", &aString[0]);
			fscanf(pfile, "%f", &rot.x);
			fscanf(pfile, "%f", &rot.y);
			fscanf(pfile, "%f", &rot.z);
		}
		else if (strcmp(&aString[0], "IDX") == 0)
		{
			fscanf(pfile, "%s", &aString[0]);
			fscanf(pfile, "%d", &Idx);
		}
	}
}

//===========================================================================================================
// ��Q���̏��ǂݍ���
//===========================================================================================================
void CGame::LoadObsInfo(FILE* pfile)
{
	char aString[256];

	D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };
	CObstacle::OBS_TYPE type = CObstacle::OBS_DRUMCAN;

	while (1)
	{
		fscanf(pfile, "%s", &aString[0]);
		if (strcmp(&aString[0], "END_OBSTACLE_INFO") == 0)
		{
			CObstacle::Create(pos, type);
			break;
		}
		else if (strcmp(&aString[0], "POS") == 0)
		{
			fscanf(pfile, "%s", &aString[0]);
			fscanf(pfile, "%f", &pos.x);
			fscanf(pfile, "%f", &pos.y);
			fscanf(pfile, "%f", &pos.z);
		}
		else if (strcmp(&aString[0], "TYPE") == 0)
		{
			fscanf(pfile, "%s", &aString[0]);
			fscanf(pfile, "%d", &type);
		}
	}
}
