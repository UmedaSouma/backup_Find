//==============================================================================================================================================
// 
// �J��������E�Ǘ�
// Author umeda souma
// 
//==============================================================================================================================================
#include "camera.h"
#include "manager.h"
#include "input.h"
#include "calculation.h"

//======================================================================================================
// �R���X�g���N�^
//======================================================================================================
CCamera::CCamera() :
	m_posV{ 0.0f,0.0f,0.0f }				// ���_(�J�����ʒu)
	, m_posR{ 0.0f,0.0f,0.0f }			// �����_(�J�����̌��Ă����)
	, m_rot{ 0.0f,0.0f,0.0f }			// ����
	, m_vecU{ 0.0f,0.0f,0.0f }			// vectorUP 
	, m_targetpos{ 0.0f,0.0f,0.0f }		// �^�[�Q�b�g
	, m_targetrot{ 0.0f,0.0f,0.0f }
	, m_fDis(0)							// ���_�ƒ����_�̋���
	, nCntFollow(0)						// �J�����̒ǂ����Ԋu
	, m_fStrength(0.0f)
	, m_nFrame(0)
	, m_mtxProjection{}
	, m_mtxView{}
	, m_TargetType(PLAYER)
{
}

//======================================================================================================
// �f�X�g���N�^
//======================================================================================================
CCamera::~CCamera()
{
}

//======================================================================================================
// �����ݒ�
//======================================================================================================
HRESULT CCamera::Init()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, -0.0f);
	m_posR = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	m_TargetType = PLAYER;

	m_fDis = 170.0f;
	m_follow = 1.0f;

	return S_OK;
}

//======================================================================================================
// �I������
//======================================================================================================
void CCamera::Uninit()
{

}

//======================================================================================================
// �X�V����
//======================================================================================================
void CCamera::Update()
{
	// �J�������s�b�^������p
	//m_posR = m_targetpos;

	// �J�������_����
	m_posV =
	{
		sinf(m_rot.x) * sinf(m_rot.y) * m_fDis,
		/*cosf(m_rot.x) * m_fDis,*/40.0f,
		sinf(m_rot.x) * cosf(m_rot.y) * m_fDis
	};

	// �J�����𒍎��_�ɍ��킹��
	m_posV += m_posR;

	// follow �̒l��ύX���邱�ƂŃJ������x�点�邱�Ƃ��ł���
	m_posR.x += (m_targetpos.x - m_posR.x) * m_follow;
	m_posR.y += (m_targetpos.y - m_posR.y) */* m_follow**/0.1f;
	m_posR.z += (m_targetpos.z - m_posR.z) * m_follow;

	// follow �̒l��ύX���邱�ƂŃJ������x�点�邱�Ƃ��ł���
	//m_rot.y += (m_targetrot.y - m_rot.y) * 0.001f;
	//m_rot.x = m_targetrot.x;
	//m_rot.z = m_targetrot.z;
	//m_rot.z = m_targetrot.y;


	

	// �J�������������Ɗp�x�����Z�b�g����
	if (m_rot.y >= D3DX_PI * 2 || m_rot.y <= -D3DX_PI * 2)
	{
		m_rot.y = 0.0f;
	}
	if (m_targetrot.y >= D3DX_PI * 2 || m_targetrot.y <= -D3DX_PI * 2)
	{
		m_targetrot.y = 0.0f;
	}
	
	UpdateInput();
}

//===========================================================================================================
// �J��������
//===========================================================================================================
void CCamera::UpdateInput()
{
	CInputKeyBoard* keyboard = CManager::GetKeyboard();

	if (keyboard->GetPress(DIK_1))
	{
		m_fDis--;
	}
	else if (keyboard->GetPress(DIK_2))
	{
		m_fDis++;
	}

	if (keyboard->GetPress(DIK_E))
	{
		m_rot.y += 0.01f;
	}
	else if (keyboard->GetPress(DIK_Q))
	{
		m_rot.y += -0.01f;
	}
	else
	{
		//if (CScene::GetMode() == CScene::MODE_COURSEPOINT) 
		//{ return; }

		if (m_TargetType != NONE)
		{
			// follow �̒l��ύX���邱�ƂŃJ������x�点�邱�Ƃ��ł���
			m_targetrot.y = CCalculation::FixAngle(m_rot.y, m_targetrot.y);
			m_rot.y += (m_targetrot.y - m_rot.y) * 0.05f;
		}
	}

	
}

//======================================================================================================
// �`�揈��
//======================================================================================================
void CCamera::Draw()
{

}

//======================================================================================================
// �J�����̐ݒ�
//======================================================================================================
void CCamera::SetCamera()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000000.0f);

	CInputKeyBoard* keyboard = CManager::GetKeyboard();

	if (keyboard->GetPress(DIK_F1))
	{
		// �v���W�F�N�V�����}�g���b�N�X���쐬(���t���e)
		D3DXMatrixOrthoLH(
			&m_mtxProjection,
			(float)SCREEN_WIDTH * 0.1f,
			(float)SCREEN_HEIGHT * 0.1f,
			10.0f,
			1000.0f);
	}

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	D3DXVECTOR3 adjust = { 0.0f,0.0f,0.0f };

	if (m_nFrame > 0)
	{// �h�ꂪ�����Ă����

		m_nFrame--;	// �h��̎��Ԃ����炵�Ă���

		//�h��̐��l�������_���Ő���
		adjust = {
			(float)(rand() % (int)m_fStrength - 1),
			(float)(rand() % (int)m_fStrength - 1),
			0.0f
		};
	}
	// �h�ꂽ�l��pos�ƍ��킹�Ĉꎞ�ۑ�
	D3DXVECTOR3 posv = m_posV + adjust;
	D3DXVECTOR3 posR = m_posR + adjust;

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&posv,
		&posR,
		&m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//======================================================================================================
// �J�����ʒu�̐ݒ�
//======================================================================================================
void CCamera::SetTargetPos(D3DXVECTOR3 pos)
{
	m_targetpos = pos;
}

//======================================================================================================
// �J�����h��
//======================================================================================================
void CCamera::SetShake(int frame, float strength)
{
	m_nFrame = frame;
	m_fStrength = strength;
}