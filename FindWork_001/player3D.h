//===========================================================================================================================================================
// 
// player3D.cpp�̃w�b�_�[
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _PLAYER_3D_H_
#define _PLAYER_3D_H_
#include "main.h"
#include "model.h"

//===================================================================================
// �N���X
//===================================================================================

// Player3D�̃N���X
class CPlayer3D :public CModel
{
private:
	typedef enum
	{
		COLLISION_HORIZON = 0,
		COLLISION_VERTICAL, 
		COLLISION_HIGHLOW,
		COLLISION_MAX
	}COLLISION_TYPE;

	static inline const float m_fJumpPower = 8.0f;	// �W�����v��
	static inline const float m_fGravity = 0.5f;	// �d��
	static const unsigned int m_MaxLife = 560;		// �̗�
	static const unsigned int m_MaxInterval = 15;	// �_���[�W���󂯂�Ԋu
public:

	// �v���C���[�̃X�L�����
	typedef enum
	{
		SKILL_NONE = 0,
		SKILL_TRIGGER,		// �X�L���{�^���������ꂽ�u��
		SKILL_PRESS,		// ������Ă����
		SKILL_RELEASE,		// �����ꂽ�Ƃ�
		SKILL_CANCELL,		// �X�L������
		SKILL_SWORD,		// ���X�L������
		SKILL_SWORD_CANCEL,	// ���X�L������
		SKILL_MAX
	}SKILL_STATE;

	CPlayer3D(int nPriority = PRIORITY_DEFAULT-1);			// �R���X�g���N�^
	~CPlayer3D()override;			// �f�X�g���N�^
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I������
	void Update()override;	// �X�V����
	void Draw()override;	// �`�揈��

	D3DXVECTOR3 InputPosPlayer();
	void SetTargetCamera();	// player �� pos �� camera �� target �ɃZ�b�g����
	void Jump();
	void UpdateDamage();		// �_���[�W���󂯂Ă���Ƃ��̏���
	void DeathPlayer();			// �v���C���[�����񂾂Ƃ�

	D3DXVECTOR3 LookObjectCollision(COLLISION_TYPE type);
	D3DXVECTOR3 VerticalCollision(CObject* pObj);	// �c�̓����蔻��
	D3DXVECTOR3 HorizonCollision(CObject* pObj);	// ���̓����蔻��
	D3DXVECTOR3 HighLowCollision(CObject* pObj);	// �㉺�̓����蔻��

	CPlayer3D* GetPlayer() { return this; }
	static CPlayer3D* Create(D3DXVECTOR3 pos);	// ��������
private:
	float m_fSpeed;				// �v���C���[�̑��x
	bool m_bUseJump;			// �W�����v���g���Ă��邩�ǂ����̔���(�����W�����v���Ȃ�����)
	D3DXVECTOR3 m_Move;			// �ړ�����
	D3DXVECTOR3 m_oldPos;		// 1�t���[���O��pos
	SKILL_STATE m_skillstate;	// �X�L���{�^���������Ƃ��̏��
	static int m_nFragmentNum;	// ���ݎ����Ă��錇�Ђ̐�
	
	bool m_bSlip;
	int m_nSlipCnt;
	bool m_bDammage;	// �_���[�W��Ԃ����� bool
	int m_nMaxLife = m_MaxLife;
	int m_nLife;		// �̗�
	int m_nCntDamage;	// �_���[�W��Ԃ̃J�E���g
	
public:
	SKILL_STATE GetSkillstate(){ return m_skillstate; }	// �X�L���{�^���̏��

	void SetMove(D3DXVECTOR3 move) { m_Move = move; }	// move �̐��l��ݒ肷��
	D3DXVECTOR3 GetMove() { return m_Move; }			// move �̐��l��Ԃ�

	D3DXVECTOR3 GetOldPos() { return m_oldPos; }		// 1�t���[���O�� pos ���擾����
	void SetbUseJump(bool use) { m_bUseJump = use; }	// �W�����v�̏�Ԃ�ݒ肷��

	void AddDamage(int nDamage);	// �_���[�W���₷����

	void SetLife(int life) { m_nLife = life; }
	int GetLife() { return m_nLife; }

	int GetMaxLife() { return m_MaxLife; }
};


#endif // !_PLAYER_3D_H_