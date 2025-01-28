//===========================================================================================================================================================
// 
// object.cpp�̃w�b�_�[
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"

class CObject
{
public:

	typedef enum
	{
		NONE=0,
		PLAYER,		// �v���C���[
		CAR,		// ��
		CAR_PLAYER,	// �v���C���[�̎�
		CAR_ENEMY,	// �G�̎�
		ENEMY,		// �G
		COURSE,		// �R�[�X
		BLOCK,		// �u���b�N
		FIELD,		// �t�B�[���h
		FADE,		// �t�F�[�h
		MODEL,		// ���f��
		POINT,		// �����̃|�C���g
		GOAL,		// �S�[���I�u�W�F�N�g
		OBSTACLE,	// ��Q��
		MAX
	}TYPE;

	// -- �قڃ}�N�� --
	static unsigned const int PRIORITY_DEFAULT = 3;	// �D��x�̃f�t�H���g
	static unsigned const int PRIORITY_MAX = 7;		// �D��x�̍ő�l
	static unsigned const int MAX_OBJECT = 2048;	// �I�u�W�F�N�g�̍ő吔

	CObject(int nPriority = PRIORITY_DEFAULT);
	virtual ~CObject();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	void Death();

	static void ReleaseAll();	// �S�Ă��J������
	static void UpdateAll();	// �S�Ă��X�V
	static void DrawAll();		// �S�Ă�`��
	static void DeathAll();		// ���ׂč폜

	TYPE GetType();				// �^�C�v���擾
	void SetType(TYPE nType);	// �^�C�v��ݒ�
protected:
	void Release();	// �������g�̉��
private:
	int m_nID;	// �������g��ID
	int m_nPriority;	// �`��D��x
	TYPE m_type;

	static CObject* m_apObject[PRIORITY_MAX][MAX_OBJECT];	// �I�u�W�F�N�g���X�g
	static int m_nNumAll;	// �I�u�W�F�N�g�̑���

	// ���X�g�̕ϐ�
	static CObject*m_pObjectList;	// ���X�g�\���̃I�u�W�F�N�g���X�g
	static CObject* m_pTop[PRIORITY_MAX];			// ���X�g�̒��̍ŏ��̃|�C���^
	static CObject* m_pCur[PRIORITY_MAX];			// ���X�g�̒��̍Ō���̃|�C���^
	CObject* m_pPrev;				// ���g�̑O�̃|�C���^
	CObject* m_pNext;				// ���̃|�C���^
	bool m_bRelese;					// ����t���O
public:
	static CObject* GetOBJECT(int nPrio,int nIdx);	// �I�u�W�F�N�g���擾
	static CObject* GetTop(int Prio) { return m_pTop[Prio]; }

	CObject* GetNext() { return m_pNext; }
	CObject* GetPrev() { return m_pPrev; }
};

#endif // !_OBJECT_H_
