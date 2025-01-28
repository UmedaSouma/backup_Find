//===========================================================================================================================================================
// 
// �X�^�[�g���̃J�E���g�_�E�� [countdown.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "countdown.h"
#include "manager.h"

//========================================================================================================================
// �R���X�g���N�^
//========================================================================================================================
CCountdown::CCountdown(int prio) :CObject2D(prio, CENTER)
{
	m_bUseCount = true;
	m_nCountnum = 0;
}

//========================================================================================================================
// �f�X�g���N�^
//========================================================================================================================
CCountdown::~CCountdown()
{
}

//========================================================================================================================
// �����ݒ�
//========================================================================================================================
HRESULT CCountdown::Init()
{
	int Idx = 0;
	Idx = CManager::GetTexture()->Regist("data\\TEXTURE\\CD_GO.png");
	BindTexture(CManager::GetTexture()->GetAddress(Idx));

	Idx = CManager::GetTexture()->Regist("data\\TEXTURE\\CD_1.png");
	BindTexture(CManager::GetTexture()->GetAddress(Idx));

	Idx = CManager::GetTexture()->Regist("data\\TEXTURE\\CD_2.png");
	BindTexture(CManager::GetTexture()->GetAddress(Idx));

	Idx = CManager::GetTexture()->Regist("data\\TEXTURE\\CD_3.png");
	BindTexture(CManager::GetTexture()->GetAddress(Idx));

	SetPos({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f });
	SetSize({ 300,300,0 });

	CObject2D::Init();
	return S_OK;
}

//========================================================================================================================
// �I������
//========================================================================================================================
void CCountdown::Uninit()
{
	CObject2D::Uninit();
}

//========================================================================================================================
// �X�V����
//========================================================================================================================
void CCountdown::Update()
{
	int Idx = 0;

	//if (m_bUseCount)
	{
		m_nCountnum++;
	}

	if (m_nCountnum == 60)
	{
		Idx = CManager::GetTexture()->Regist("data\\TEXTURE\\CD_2.png");
		BindTexture(CManager::GetTexture()->GetAddress(Idx));

	}
	else if (m_nCountnum == 120)
	{
		Idx = CManager::GetTexture()->Regist("data\\TEXTURE\\CD_1.png");
		BindTexture(CManager::GetTexture()->GetAddress(Idx));

	}
	else if (m_nCountnum == 180)
	{
		Idx = CManager::GetTexture()->Regist("data\\TEXTURE\\CD_GO.png");
		BindTexture(CManager::GetTexture()->GetAddress(Idx));
		m_bUseCount = false;
	}

	CObject2D::Update();
}

//========================================================================================================================
// �`�揈��
//========================================================================================================================
void CCountdown::Draw()
{
	if (m_nCountnum > 210)
	{ return; }
	CObject2D::Draw();
}

//========================================================================================================================
// ��������
//========================================================================================================================
CCountdown* CCountdown::Create()
{
	CCountdown* pCD = new CCountdown;
	pCD->Init();

	return pCD;
}
