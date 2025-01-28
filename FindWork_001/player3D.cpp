//===========================================================================================================================================================
// 
// 3D�v���C���[�̏���
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "player3D.h"
#include "manager.h"
#include "game.h"
#include "search.h"
#include "block3D.h"


// �ÓI�����o�ϐ��̏�����
int CPlayer3D::m_nFragmentNum = 0;

//========================================================================================================================
// �R���X�g���N�^
//========================================================================================================================
CPlayer3D::CPlayer3D(int nPriority) :CModel(nPriority)
, m_Move{ 0.0f,0.0f,0.0f }
, m_fSpeed(0)
, m_oldPos{ 0.0f,0.0f,0.0f }
, m_skillstate(SKILL_NONE)
, m_bUseJump(false)
, m_bSlip(false)
, m_nSlipCnt(0)
, m_bDammage(false)
, m_nLife(0)
, m_nCntDamage(0)
{
}

//========================================================================================================================
// �f�X�g���N�^
//========================================================================================================================
CPlayer3D::~CPlayer3D()
{
}

//========================================================================================================================
// �����ݒ�
//========================================================================================================================
HRESULT CPlayer3D::Init()
{
	// ���f���̐ݒ�
	SetModelAddress("data\\model\\player_001.x");		// �A�h���X��ۑ����Ă���
	CModeldata* pModeldata = CManager::GetModeldata();	// modeldata �̃|�C���^�������Ă���
	int nIdx = pModeldata->Regist(GetModelAddress());	// ���f���f�[�^�̓o�^
	BindModel(pModeldata->GetAddress(nIdx));			// ���f�������Z�b�g����
	SetModelIdx(nIdx);

	CModel::Init();

	SetSize({ 10.0f, 20.0f, 15.0f });
	m_fSpeed = 3.0f;

	m_nLife = m_MaxLife;

	return S_OK;
}

//========================================================================================================================
// �I������
//========================================================================================================================
void CPlayer3D::Uninit()
{
	CModel::Uninit();
}

//========================================================================================================================
// �X�V����
//========================================================================================================================
void CPlayer3D::Update()
{
	D3DXVECTOR3 pos = GetPos();

	// �����蔻�����(��X�֐���
	{
		if (m_nSlipCnt == 0)
		{
			m_bSlip = false;
		}
		if (m_bSlip)
		{
			m_nSlipCnt--;
		}

		DeathPlayer();
	}

	// �v���C���[����
	InputPosPlayer();

	

	if (!m_bSlip)
	{
		m_bUseJump = true;

		// Y���̓����蔻��E�X�V
		pos.y += m_Move.y;
		SetPos(pos);
		pos = LookObjectCollision(COLLISION_HIGHLOW);

		// X���̓����蔻��E�X�V
		pos.x += m_Move.x;
		SetPos(pos);
		pos = LookObjectCollision(COLLISION_HORIZON);

		// Z���̓����蔻��E�X�V
		pos.z += m_Move.z;
		SetPos(pos);
		pos = LookObjectCollision(COLLISION_VERTICAL);
	}

	// �J�����ǔ�
	SetTargetCamera();

	// ���x���X�Ɍ���
	m_Move.x += (0.0f - m_Move.x) * 0.5f;
	m_Move.z += (0.0f - m_Move.z) * 0.5f;
	//m_Move.y += (0.0f - m_Move.y) * 0.2f;

	CModel::Update();

	if (m_bDammage)
	{
		UpdateDamage();
	}

	// �ߋ��̈ʒu��o�^
	m_oldPos = pos;
}

//========================================================================================================================
// �`�揈��
//========================================================================================================================
void CPlayer3D::Draw()
{
	CModel::Draw();
}

//========================================================================================================================
// �v���C���[�̓��͏���
//========================================================================================================================
D3DXVECTOR3 CPlayer3D::InputPosPlayer()
{
	CInputKeyBoard* keyboard = CManager::GetKeyboard();
	CInputJoypad* joypad = CManager::GetJoypad();
	CCamera* pCamera = CManager::GetCamera();

	D3DXVECTOR3 rot = GetRot();


	//if (keyboard->GetPress(DIK_A) || joypad->GetPress(CInputJoypad::JOYKEY_LEFT))
	//{
	//	m_Move.x += sinf(-D3DX_PI * 0.5f) * m_fSpeed;
	//	m_Move.y += cosf(-D3DX_PI * 0.5f) * m_fSpeed;

	//	SetDirection(CModel::DIRECTION_LEFT);
	//}
	//if (keyboard->GetPress(DIK_D)||joypad->GetPress(CInputJoypad::JOYKEY_RIGHT))
	//{
	//	m_Move.x += sinf(-D3DX_PI * 0.5f) * -m_fSpeed;
	//	m_Move.y += cosf(-D3DX_PI * 0.5f) * -m_fSpeed;

	//	SetDirection(CModel::DIRECTION_RIGHT);
	//}
	if (keyboard->GetPress(DIK_A))
	{
		if (keyboard->GetPress(DIK_W) || joypad->GetPress(CInputJoypad::JOYKEY_UP))
		{
			m_Move.x = sinf(pCamera->GetRot().y - 0.75f) * m_fSpeed;
			m_Move.z = cosf(pCamera->GetRot().y - 0.75f) * m_fSpeed;

			//g_player.rotmove.y = 1.0f;

			//g_player.GetRot().y = (pCamera->GetRot().y - (D3DX_PI * 2.32f));
		}
		else if (keyboard->GetPress(DIK_S) || joypad->GetPress(CInputJoypad::JOYKEY_DOWN))
		{

			m_Move.x = sinf(pCamera->GetRot().y - 2.32f) * m_fSpeed;
			m_Move.z = cosf(pCamera->GetRot().y - 2.32f) * m_fSpeed;

			//g_player.GetRot().y = (pCamera->GetRot().y - (D3DX_PI * 0.75f));
		}
		else if (keyboard->GetPress(DIK_A) || joypad->GetPress(CInputJoypad::JOYKEY_LEFT))
		{
			m_Move.x = sinf(pCamera->GetRot().y - (D3DX_PI * 0.5f)) * m_fSpeed;
			m_Move.z = cosf(pCamera->GetRot().y - (D3DX_PI * 0.5f)) * m_fSpeed;

			//g_player.GetRot().y = (pCamera->GetRot().y - (D3DX_PI * 0.5f));
		}
	}
	else if (keyboard->GetPress(DIK_D))
	{
		if (keyboard->GetPress(DIK_W) || joypad->GetPress(CInputJoypad::JOYKEY_UP))
		{
			m_Move.x = sinf(pCamera->GetRot().y - -0.75f) * m_fSpeed;
			m_Move.z = cosf(pCamera->GetRot().y - -0.75f) * m_fSpeed;

			//g_player.GetRot().y = (pCamera->GetRot().y - (D3DX_PI * -2.32f));
		}
		else if (keyboard->GetPress(DIK_S) || joypad->GetPress(CInputJoypad::JOYKEY_DOWN))
		{

			m_Move.x = sinf(pCamera->GetRot().y - -2.32f) * m_fSpeed;
			m_Move.z = cosf(pCamera->GetRot().y - -2.32f) * m_fSpeed;

			//g_player.GetRot().y = (pCamera->GetRot().y - (D3DX_PI * -0.75f));
		}
		else if (keyboard->GetPress(DIK_D) || joypad->GetPress(CInputJoypad::JOYKEY_RIGHT))
		{
			m_Move.x = sinf(pCamera->GetRot().y - (D3DX_PI * -0.5f)) * m_fSpeed;
			m_Move.z = cosf(pCamera->GetRot().y - (D3DX_PI * -0.5f)) * m_fSpeed;

			//g_player.GetRot().y = (pCamera->GetRot().y - (D3DX_PI * -0.5f));
		}
	}
	else if (keyboard->GetPress(DIK_W))
	{
		m_Move.x = sinf(/*pCamera->GetRot().y+*/ rot.y)/*+ sinf()*/ * m_fSpeed;
		m_Move.z = cosf(/*pCamera->GetRot().y+*/ rot.y)/*+ cosf()*/ * m_fSpeed;

		//g_player.GetRot().y = (pCamera->GetRot().y);
	}
	else if (keyboard->GetPress(DIK_S))
	{
		m_Move.x = sinf(pCamera->GetRot().y) + sinf(rot.y) * -m_fSpeed;
		m_Move.z = cosf(pCamera->GetRot().y) + cosf(rot.y) * -m_fSpeed;

		//g_player.GetRot().y = (pCamera->GetRot().y + D3DX_PI);
	}

	if (keyboard->GetPress(DIK_RIGHTARROW))
	{
		SetRot({ rot.x,rot.y + 0.01f,rot.z });
	}
	if (keyboard->GetPress(DIK_LEFTARROW))
	{
		SetRot({ rot.x,rot.y - 0.01f,rot.z });
	}

	// �W�����v�d�͏���
	Jump();

	return m_Move;
}

//========================================================================================================================
// �v���C���[�̓��͏���
//========================================================================================================================
void CPlayer3D::Jump()
{
	CInputKeyBoard* keyboard = CManager::GetKeyboard();
	CInputJoypad* joypad = CManager::GetJoypad();

	if (!m_bUseJump)
	{
		if (keyboard->GetTrigger(DIK_SPACE) || joypad->GetTrigger(CInputJoypad::JOYKEY_A))
		{
			m_Move.y += m_fJumpPower;	// �W�����v
			m_bUseJump = true;
		}
	}

	m_Move.y -= m_fGravity;	// �d�͉��Z
}

//===========================================================================================================
// �_���[�W���₷����
//===========================================================================================================
void CPlayer3D::AddDamage(int nDamage)
{
	if (!m_bDammage)
	{// �_���[�W��Ԃł͂Ȃ��Ƃ�

		m_nCntDamage = m_MaxInterval;	// �_���[�W��Ԃ̃J�E���g��ݒ�
		m_nLife -= nDamage;	// �_���[�W�����C�t�����炷
		m_bDammage = true;	// �_���[�W��Ԃɂ���
	}
}

//===========================================================================================================
// �_���[�W��Ԃ̍X�V
//===========================================================================================================
void CPlayer3D::UpdateDamage()
{
	m_nCntDamage--;	// �_���[�W��Ԃ̃J�E���g�����炷
	bMat(true);

	if (m_nCntDamage <= 0)
	{
		bMat(false);
		m_bDammage = false;
	}
}

//===========================================================================================================
// ���񂾂Ƃ��̏���
//===========================================================================================================
void CPlayer3D::DeathPlayer()
{
	if (GetPos().y <= -50.0f || m_nLife <= 0)
	{// ���ɗ������Ƃ� || �̗͂��Ȃ��Ȃ����Ƃ�
		m_nLife = m_MaxLife;			// �̗͂��ő�l�ɖ߂�
		SetPos({ 40.0f, 25.0f, 0.0f });	// ���X�|�[��������
		m_bSlip = true;					// ���蔲��������
		m_nSlipCnt = 5;					// ���蔲�������鎞�Ԃ�ݒ�
	}
}

//========================================================================================================================
// ��������
//========================================================================================================================
CPlayer3D* CPlayer3D::Create(D3DXVECTOR3 pos)
{
	CPlayer3D* pPlayer3D = new CPlayer3D;	// �v���C���[�̌^�œ��I�m��

	pPlayer3D->SetPos(pos);	// �ʒu��ݒ�
	pPlayer3D->SetType(TYPE::PLAYER);

	pPlayer3D->Init();	// �RD�̏����ݒ�

	return pPlayer3D;
}

//========================================================================================================================
// player��pos��camera��target�ɃZ�b�g����
//========================================================================================================================
void CPlayer3D::SetTargetCamera()
{
	CCamera* pCamera = CManager::GetCamera();	// camera �������Ă���
	pCamera->SetTargetPos(GetPos());			// camera �� playerpos ������
}

//========================================================================================================================
// �e�I�u�W�F�N�g���m�F����
//========================================================================================================================
D3DXVECTOR3 CPlayer3D::LookObjectCollision(COLLISION_TYPE type)
{
	D3DXVECTOR3 pos = {};

	for (int nPrio = 0; nPrio < CObject::PRIORITY_MAX; nPrio++)
	{
		CObject* pObj = CObject::GetTop(nPrio);

		while (pObj != nullptr)
		{
			CObject* pNext = pObj->GetNext();

			switch (type)
			{
				// �c�̓����蔻��(z��)
			case COLLISION_VERTICAL:
				pos = VerticalCollision(pObj);
				break;

				// ���̓����蔻��(x��)
			case COLLISION_HORIZON:
				pos = HorizonCollision(pObj);
				break;

				// �㉺�̓����蔻��(y��)
			case COLLISION_HIGHLOW:
				pos = HighLowCollision(pObj);
				break;

			default:
				assert(1);
				break;
			}

			pObj = pNext;
		}
	}

	return pos;
}

//========================================================================================================================
// �c�̓����蔻��
//========================================================================================================================
D3DXVECTOR3 CPlayer3D::VerticalCollision(CObject* pObj)
{
	CObject::TYPE type = pObj->GetType();

	D3DXVECTOR3 PlayerPos = GetPos();
	D3DXVECTOR3 PlayerSize = GetSize();

	PlayerSize.x *= 0.5f;
	PlayerSize.y *= 0.5f;
	PlayerSize.z *= 0.5f;

	if (type == TYPE::BLOCK)
	{
		CBlock3D* pBlock = (CBlock3D*)pObj;

		D3DXVECTOR3 BlockPos = pBlock->GetPos();
		D3DXVECTOR3 BlockSize = pBlock->GetSize();

		BlockSize.x *= 0.5f;
		BlockSize.y *= 0.5f;
		BlockSize.z *= 0.5f;

		if (BlockPos.z - BlockSize.z < PlayerPos.z + PlayerSize.z		// �v���C���[���u���b�N�ɂ߂荞�񂾎�
			&& BlockPos.x - BlockSize.x < PlayerPos.x + PlayerSize.x	// -------------------------------------------
			&& BlockPos.x + BlockSize.x > PlayerPos.x - PlayerSize.x	// �v���C���[���u���b�N��
			&& BlockPos.y - BlockSize.y < PlayerPos.y + PlayerSize.y	// xy�͈͓��ɂ����Ƃ�
			&& BlockPos.y + BlockSize.y > PlayerPos.y - PlayerSize.y	// -------------------------------------------
			&& m_oldPos.z + PlayerSize.z <= BlockPos.z - BlockSize.z	// �v���C���[�̉ߋ��̈ʒu���u���b�N����O�ɂ������Ƃ�
			)
		{// ��ɏ��
			m_Move.z = 0;

			SetPos({ PlayerPos.x,PlayerPos.y,PlayerPos.z = (BlockPos.z - BlockSize.z - PlayerSize.z) });
		}

		if (BlockPos.z + BlockSize.z > PlayerPos.z - PlayerSize.z		// �v���C���[���u���b�N�ɂ߂荞�񂾎�
			&& BlockPos.x - BlockSize.x < PlayerPos.x + PlayerSize.x	// -------------------------------------------
			&& BlockPos.x + BlockSize.x > PlayerPos.x - PlayerSize.x	// �v���C���[���u���b�N��
			&& BlockPos.y - BlockSize.y < PlayerPos.y + PlayerSize.y	// xy�͈͓��ɂ����Ƃ�
			&& BlockPos.y + BlockSize.y > PlayerPos.y - PlayerSize.y	// -------------------------------------------
			&& m_oldPos.z - PlayerSize.z >= BlockPos.z + BlockSize.z	// �v���C���[�̉ߋ��̈ʒu���u���b�N��艜�ɂ������Ƃ�
			)
		{
			m_Move.z = 0;

			SetPos({ PlayerPos.x,PlayerPos.y ,PlayerPos.z = (BlockPos.z + BlockSize.z + PlayerSize.z) });
		}
	}

	return PlayerPos;
}

//========================================================================================================================
// ���̓����蔻��
//========================================================================================================================
D3DXVECTOR3 CPlayer3D::HorizonCollision(CObject* pObj)
{
	CObject::TYPE type = pObj->GetType();

	D3DXVECTOR3 PlayerPos = GetPos();
	D3DXVECTOR3 PlayerSize = GetSize();

	PlayerSize.x *= 0.5f;
	PlayerSize.y *= 0.5f;
	PlayerSize.z *= 0.5f;

	if (type == TYPE::BLOCK)
	{
		CBlock3D* pBlock = (CBlock3D*)pObj;

		D3DXVECTOR3 BlockPos = pBlock->GetPos();
		D3DXVECTOR3 BlockSize = pBlock->GetSize();

		BlockSize.x *= 0.5f;
		BlockSize.y *= 0.5f;
		BlockSize.z *= 0.5f;

		if (BlockPos.x + BlockSize.x > PlayerPos.x - PlayerSize.x		// �v���C���[���u���b�N�ɂ߂荞�񂾎�
			&& BlockPos.y - BlockSize.y < PlayerPos.y + PlayerSize.y	// -------------------------------------------
			&& BlockPos.y + BlockSize.y > PlayerPos.y - PlayerSize.y	// �v���C���[���u���b�N��
			&& BlockPos.z - BlockSize.z < PlayerPos.z + PlayerSize.z	// yz�͈͓��ɂ����Ƃ�
			&& BlockPos.z + BlockSize.z > PlayerPos.z - PlayerSize.z	// -------------------------------------------
			&& m_oldPos.x - PlayerSize.x >= BlockPos.x + BlockSize.x	// �v���C���[�̉ߋ��̈ʒu���u���b�N���E�ɂ������Ƃ�
			)
		{
			m_Move.x = 0;

			SetPos({ PlayerPos.x = (BlockPos.x + BlockSize.x + PlayerSize.x),PlayerPos.y,PlayerPos.z });
		}

		else if (BlockPos.x - BlockSize.x < PlayerPos.x + PlayerSize.x	// �v���C���[���u���b�N�ɂ߂荞�񂾎�
			&& BlockPos.y - BlockSize.y < PlayerPos.y + PlayerSize.y	// -------------------------------------------
			&& BlockPos.y + BlockSize.y > PlayerPos.y - PlayerSize.y	// �v���C���[���u���b�N��
			&& BlockPos.z - BlockSize.z < PlayerPos.z + PlayerSize.z	// yz�͈͓��ɂ����Ƃ�
			&& BlockPos.z + BlockSize.z > PlayerPos.z - PlayerSize.z	// -------------------------------------------
			&& m_oldPos.x + PlayerSize.x <= BlockPos.x - BlockSize.x	// �v���C���[�̉ߋ��̈ʒu���u���b�N��荶�ɂ������Ƃ�
			)
		{
			m_Move.x = 0;

			SetPos({ PlayerPos.x = (BlockPos.x - BlockSize.x - PlayerSize.x),PlayerPos.y,PlayerPos.z });
		}
	}

	return PlayerPos;
}

//========================================================================================================================
// ���̓����蔻��
//========================================================================================================================
D3DXVECTOR3 CPlayer3D::HighLowCollision(CObject* pObj)
{
	CObject::TYPE type = pObj->GetType();

	D3DXVECTOR3 PlayerPos = GetPos();
	D3DXVECTOR3 PlayerSize = GetSize();

	PlayerSize.x *= 0.5f;
	PlayerSize.z *= 0.5f;
	PlayerSize.y *= 0.5f;

	if (type == TYPE::BLOCK)
	{// �^�C�v���u���b�N�������ꍇ

		CBlock3D* pBlock = (CBlock3D*)pObj;

		D3DXVECTOR3 BlockPos = pBlock->GetPos();
		D3DXVECTOR3 BlockSize = pBlock->GetSize();

		BlockSize.x *= 0.5f;
		BlockSize.y *= 0.5f;
		BlockSize.z *= 0.5f;

		// �v���C���[���u���b�N�ɓ����Ԃ���
		if (BlockPos.y - BlockSize.y < PlayerPos.y + PlayerSize.y		// �v���C���[���u���b�N�ɂ߂荞�񂾎�
			&& BlockPos.x - BlockSize.x < PlayerPos.x + PlayerSize.x	// -------------------------------------------
			&& BlockPos.x + BlockSize.x > PlayerPos.x - PlayerSize.x	// �v���C���[���u���b�N��
			&& BlockPos.z - BlockSize.z < PlayerPos.z + PlayerSize.z	// xz�͈͓��ɂ����Ƃ�
			&& BlockPos.z + BlockSize.z > PlayerPos.z - PlayerSize.z	// -------------------------------------------
			&& BlockPos.y - BlockSize.y >= m_oldPos.y + PlayerSize.y	// �v���C���[�̉ߋ��̈ʒu���u���b�N��艺�ɂ������Ƃ�
			)
		{
			m_Move.y = 0;

			SetPos({ PlayerPos.x,PlayerPos.y = (BlockPos.y - BlockSize.y - PlayerSize.y),PlayerPos.z });	// �v���C���[���u���b�N�̉��ɍs��
		}

		// �v���C���[���u���b�N�ɏ��
		else if (BlockPos.y + BlockSize.y > PlayerPos.y - PlayerSize.y	// �v���C���[���u���b�N�ɂ߂荞�񂾎�
			&& BlockPos.x - BlockSize.x < PlayerPos.x + PlayerSize.x	// -------------------------------------------
			&& BlockPos.x + BlockSize.x > PlayerPos.x - PlayerSize.x	// �v���C���[���u���b�N��
			&& BlockPos.z - BlockSize.z < PlayerPos.z + PlayerSize.z	// xz�͈͓��ɂ����Ƃ�
			&& BlockPos.z + BlockSize.z > PlayerPos.z - PlayerSize.z	// -------------------------------------------
			&& BlockPos.y + BlockSize.y <= m_oldPos.y - PlayerSize.y	// �v���C���[�̉ߋ��̈ʒu���u���b�N����ɂ������Ƃ�
			)
		{
			m_bUseJump = false;
			m_Move.y = 0;
			SetPos({ PlayerPos.x,PlayerPos.y = (BlockPos.y + BlockSize.y + PlayerSize.y),PlayerPos.z });	// �v���C���[���u���b�N�̏�ɏ��
		}
	}

	return PlayerPos;
}