//===========================================================================================================================================================
// 
// �R�[�X���f���̏��� [course.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "course.h"
#include "car_player.h"
#include "search.h"

//========================================================================================================================
// �R���X�g���N�^
//========================================================================================================================
CCourse::CCourse() :
	m_Distance(0.0f)
{
}

//========================================================================================================================
// �f�X�g���N�^
//========================================================================================================================
CCourse::~CCourse()
{
}

//========================================================================================================================
// �����ݒ�
//========================================================================================================================
HRESULT CCourse::Init()
{
	//SetModel("data\\MODEL\\stage_00.x");
	SetType(CObject::COURSE);

	CModel::Init();

	return S_OK;
}

//========================================================================================================================
// �I������
//========================================================================================================================
void CCourse::Uninit()
{
	CModel::Uninit();
}

//========================================================================================================================
// �X�V����
//========================================================================================================================
void CCourse::Update()
{
	CModel::Update();
}

//========================================================================================================================
// �`�揈��
//========================================================================================================================
void CCourse::Draw()
{
	CModel::Draw();

	//D3DXMATRIX mat = GetMatrix();
	//D3DXVECTOR3 pos_ = GetPos();

	//// ���b�V���ɕK�v�ȏ��
	//CModeldata::ModelData* pModelInfo = nullptr;
	//pModelInfo = GetModelInfo();
	//BOOL pHit = false;
	//FLOAT pDistance = 0.0f;
	//DWORD dwHitIndex = -1;
	//float fHitU;
	//float fHitV;

	//// �v���C���[�̏��
	//CCarPlayer* pPlayer = nullptr;
	//pPlayer = CSearch::SearchObject(pPlayer, CObject::CAR_PLAYER);
	//D3DXVECTOR3 move = pPlayer->GetMove();
	//D3DXVECTOR3 pos = pPlayer->GetPos();
	//D3DXVECTOR3 pRay = { 0,1,0 };

	//LPDIRECT3DVERTEXBUFFER9* vtxbuff = nullptr;
	//pModelInfo->Mesh->GetVertexBuffer(vtxbuff);
	//VERTEX_3D* pVtx;

	//// ���_���擾
	//DWORD dwNumVtx = pModelInfo->Mesh->GetNumVertices();
	//D3DXMATRIX mtx = GetMatrix();


	//// �o�b�t�@���b�N
	//pModelInfo->Mesh->LockVertexBuffer(0, (void**)&pVtx);

	////for (unsigned int i = 0; i < 1; i++)
	////{
	////	pVtx[i].pos +=D3DXVECTOR3(mtx._41, mtx._42, mtx._43);
	////}

	//pModelInfo->Mesh->UnlockVertexBuffer();

	//// ���C�ƃ��b�V�����������������肷��
	//D3DXIntersect(
	//	pModelInfo->Mesh,		// ���b�V���̏��
	//	&pos,					// ���C�̎n�_
	//	&pRay,					// ���C�̕���
	//	&pHit,					// �����������ǂ���
	//	&dwHitIndex,			// �����������b�V���̃C���f�b�N�X
	//	&fHitU,					// 
	//	&fHitV,					// 
	//	&m_Distance,			// ���C�̎n�_�ƃ��b�V���̋���
	//	NULL,					// 
	//	NULL);					// 

	//// �������Ă��Ȃ������炱���ŕԂ�
	//if (pHit != TRUE)
	//{
	//	return;
	//}

	//// ����������Ă����牟���߂��Ȃ�
	//if (m_Distance >= 15.0f)
	//{
	//	return;
	//}

	//pPlayer->SetPos({
	//	pPlayer->GetPos().x,
	//	pPlayer->GetPos().y + m_Distance + (0.0f),
	//	pPlayer->GetPos().z
	//	});



	//move.y = 0.0f;

	//pPlayer->SetMove(move);
}

void CCourse::SetCourseNum(int num)
{
	switch (num)
	{
	case COURSE_TITLE:
		SetModel("data\\MODEL\\field_title_000.x");
		break;

	case COURSE_01:
		SetModel("data\\MODEL\\course_021.x");
		break;

	default:
		assert(1);
		break;
	}
}

//========================================================================================================================
// ��������
//========================================================================================================================
CCourse* CCourse::Create(int type)
{
	CCourse* pCourse = new CCourse;
	pCourse->SetCourseNum(type);
	pCourse->Init();

	return pCourse;
}