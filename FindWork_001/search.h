//===========================================================================================================================================================
// 
// search.cpp�̃w�b�_�[
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _SEARCH_H_
#define _SEARCH_H_
#include "main.h"
#include "player3D.h"

class CSearch
{
public:
	CSearch();
	~CSearch();
	
private:
	static int m_nCnt;

public:
	static CPlayer3D* SearchPlayer();

	template<typename typeclass>static typeclass* SearchObject(typeclass* Class, CObject::TYPE type);
	template<typename typeclass> static typeclass* SearchType(typeclass* Class, CObject* pObj);
	template<typename typeclass>static std::vector<typeclass*> SearchMultiObject(std::vector<typeclass*>Class, CObject::TYPE type);
	template<typename typeclass> static std::vector<typeclass*> SearchTypeMulti(std::vector<typeclass*> Class, CObject* pObj);
};

//===========================================================================================================
// �I�u�W�F�N�g��T��
//===========================================================================================================
template<typename typeclass> inline typeclass* CSearch::SearchObject(typeclass* Class, CObject::TYPE type)
{
	//===========================================================================================================
	// < debugmemo >
	// ���̏����ɂ���
	// ����[�[�[�[�[�[�[�[�[�[�[�[
	// �܂��I�u�W�F�N�g��������T���ȁ[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[��
	//===========================================================================================================

	//typeclass ArryClass[100] = {};
	//int nCnt = 0;

	

	for (int nPrio = 0; nPrio < CObject::PRIORITY_MAX; nPrio++)
	{
		CObject* pObj = CObject::GetTop(nPrio);

		while (pObj != nullptr)
		{
			CObject* pNext = pObj->GetNext();

			if (pObj->GetType() == type)
			{
				Class = SearchType(Class, pObj);	// �^�C�v���Z�b�g����
				return Class;
			}

			pObj = pNext;
		}
	}

	
	

	//for (int nCntPrio = 0; nCntPrio < CObject::PRIORITY_MAX; nCntPrio++)
	//{
	//	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJECT; nCntObj++)
	//	{
	//		CObject* pObj = CObject::GetOBJECT(nCntPrio, nCntObj);

	//		if (pObj != nullptr
	//			&& pObj->GetType() == type)	// �I�u�W�F�N�g�����݂��āA�^�C�v����v�����Ƃ�
	//		{
	//			Class = SearchType(Class, pObj);	// �^�C�v���Z�b�g����
	//			//ArryClass[nCnt] = *Class;
	//			//nCnt++;

	//			return Class;
	//		}
	//	}
	//}
	//return &ArryClass[0];
	return Class;
}

//===========================================================================================================
// �T�����I�u�W�F�N�g�������N���X�ɃL���X�g����
//===========================================================================================================
template<typename typeclass> inline typeclass* CSearch::SearchType(typeclass* Class, CObject* pObj)
{ // ( ���߂Ă���N���X�A�T�����I�u�W�F�N�g )
	Class = (typeclass*)pObj;	// �N���X���L���X�g����
	return Class;
}

//===========================================================================================================
// �I�u�W�F�N�g��T��(����?!)
//===========================================================================================================
template<typename typeclass> inline std::vector<typeclass*> CSearch::SearchMultiObject(std::vector<typeclass*>Class, CObject::TYPE type)
{
	std::vector<typeclass*>ClassTemp{};	//
	ClassTemp.clear();

	for (int nPrio = 0; nPrio < CObject::PRIORITY_MAX; nPrio++)
	{
		CObject* pObj = CObject::GetTop(nPrio);
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->GetNext();

			if (pObj->GetType() == type)
			{
				ClassTemp = SearchTypeMulti(ClassTemp, pObj);	// �^�C�v���Z�b�g����
				//return ClassTemp;
			}

			pObj = pNext;
		}
	}

	return ClassTemp;
}

//===========================================================================================================
// �T�����I�u�W�F�N�g�������N���X�ɃL���X�g����
//===========================================================================================================
template<typename typeclass> inline std::vector<typeclass*> CSearch::SearchTypeMulti(std::vector<typeclass*> Class, CObject* pObj) // ( ���߂Ă���N���X�A�T�����I�u�W�F�N�g )
{
	//Class = (typeclass*)pObj;	// �N���X���L���X�g����

	//Class.emplace_back((std::vector<typeclass*>)pObj);
	Class.emplace_back((typeclass*)pObj);
	return Class;
}

#endif // !SEARCH_H_