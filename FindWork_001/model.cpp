//===========================================================================================================================================================
// 
// ���f���̊Ǘ�
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "model.h"
#include "manager.h"
#include "calculation.h"
#include "course.h"
#include "collision.h"
#include "search.h"


//===================================================================================
// �R���X�g���N�^
//===================================================================================
CModel::CModel(int nPriority) :CObject3D(nPriority)
, m_Direction(0)
, m_nIdx(-1)
, m_bMat(false)
, m_Diffuse{}
, m_pModelAddress{}
, m_apTexture{}
, m_targetrot({0.0f ,0.0f,0.0f })
{
	m_ModelInfo = {};

	for (int n = 0; n < 1024; n++)
	{
		m_vtxpos[n] = { 0.0f,0.0f,0.0f };
	}
}

//===================================================================================
// �f�X�g���N�^
//===================================================================================
CModel::~CModel()
{
}

//===================================================================================
// �����ݒ�
//===================================================================================
HRESULT CModel::Init()
{
	UpdateMatrix();

	//int nNumVtx = 0;	// ���_��
	//DWORD sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y
	//BYTE* pVtxBuff;	// ���_�o�b�t�@�̃|�C���^

	//// ���_���̎擾
	//nNumVtx = m_ModelInfo.Mesh->GetNumVertices();
	//// 
	//sizeFVF = D3DXGetFVFVertexSize(m_ModelInfo.Mesh->GetFVF());
	//// 
	//m_ModelInfo.Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	//for (int nvtx = 0; nvtx < nNumVtx; nvtx++)
	//{
	//	// ���_���W�̑��
	//	D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

	//	// ���_���W���r����[�ő�l�E�ŏ��l]���擾

	//	m_vtxpos[nvtx] = vtx;

	//	// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	//	pVtxBuff += sizeFVF;
	//}

	return S_OK;
}

//===================================================================================
// �I������
//===================================================================================
void CModel::Uninit()
{
	Release();
}

//===================================================================================
// �X�V����
//===================================================================================
void CModel::Update()
{
	// �I�u�W�F�N�g3D�̍X�V
	CObject3D::Update();	// �����Ń}�g���b�N�X�̐ݒ�����Ă���

	FixRot();
}

//===================================================================================
// �`�揈��
//===================================================================================
void CModel::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DMATERIAL9 matDef;			// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;				// �}�e���A���f�[�^�̃|�C���^

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &GetMatrix());

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	if (m_ModelInfo.BuffMat != nullptr
		&& m_ModelInfo.Mesh != nullptr
		&& m_ModelInfo.NumMat != 0)
	{
		// �}�e���A���f�[�^�̃|�C���^�̎擾
		pMat = (D3DXMATERIAL*)m_ModelInfo.BuffMat->GetBufferPointer();
		CModeldata* pModeldata = CManager::GetModeldata();	// Modeldata �̃|�C���^�������Ă���

		SetModelTex(pMat);

		if (pModeldata)
		{
			for (int nCntMat = 0; nCntMat < (int)m_ModelInfo.NumMat; nCntMat++)
			{
				if (m_bMat)
				{// �_���[�W���󂯂��Ƃ�
					pMat[nCntMat].MatD3D.Diffuse = { 1.0f,0.0f,0.0f,0.5f };	// �Ԃ�����
				}
				else
				{// ���̂ق��̏�Ԃ̎�

					//if (CScene::GetMode() != CScene::MODE_EDITOR)
					{
						pMat[nCntMat].MatD3D.Diffuse = *pModeldata->GetMatData(m_pModelAddress, nCntMat);	// �ʏ�F�ɂ���
					}

				}

				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, m_apTexture[nCntMat]);

				// ���f���p�[�c�̕`��
				m_ModelInfo.Mesh->DrawSubset(nCntMat);
			}
		}
	
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//===========================================================================================================
// �p�x���C������
//===========================================================================================================
void CModel::FixRot()
{
	if (GetRot().x >= D3DX_PI*2 ||  GetRot().x <= -D3DX_PI*2)
	{
		SetRot({ 0.0f,GetRot().y,GetRot().z });
	}
	if (GetRot().y >= D3DX_PI * 2 || GetRot().y <= -D3DX_PI * 2)
	{
		SetRot({ GetRot().x,0.0f,GetRot().z });
	}
	if (GetRot().z >= D3DX_PI * 2 ||  GetRot().z <= -D3DX_PI * 2)
	{
		SetRot({ GetRot().x,GetRot().y,0.0f });
	}
}

//===================================================================================
// ��������
//===================================================================================
CModel* CModel::Create(D3DXVECTOR3 pos)
{
	CModel* pModel = new CModel;

	pModel->SetPos(pos);
	pModel->SetType(TYPE::MODEL);

	pModel->Init();

	return pModel;
}

//===================================================================================
// ���f���̏����Z�b�g����
//===================================================================================
void CModel::BindModel(CModeldata::ModelData *modelinfo)
{
	m_ModelInfo.Mesh = modelinfo->Mesh;
	m_ModelInfo.BuffMat = modelinfo->BuffMat;
	m_ModelInfo.NumMat = modelinfo->NumMat;
}

//===========================================================================================================
// ���������X�Ƀ^�[�Q�b�g�Ɍ�����
//===========================================================================================================
void CModel::UpdateTargetRot()
{
	D3DXVECTOR3 rot = GetRot();
}

//===========================================================================================================
// ������ݒ�
//===========================================================================================================
void CModel::SetDirection(DIRECTION dire)
{
	switch (dire)
	{
	case DIRECTION_LEFT:
		m_Direction = -1;
		SetRot({
			0.0f
			,D3DX_PI * 0.5f
			,0.0f
			});
		break;

	case DIRECTION_RIGHT:
		m_Direction = 1;
		SetRot({
			0.0f
			,D3DX_PI * -0.5f
			,0.0f
			});
		break;

	default:
		break;
	}
}

//===========================================================================================================
// �������擾
//===========================================================================================================
int CModel::GetDirection()
{
	return m_Direction;
}

//===========================================================================================================
// ���f���̌����ڐݒ�
//===========================================================================================================
void CModel::SetModel(const char* address)
{
	CModeldata* pModeldata = nullptr;
	int nIdx = 0;

	SetModelAddress(address);		// �A�h���X��ۑ����Ă���
	pModeldata = CManager::GetModeldata();
	nIdx = pModeldata->Regist(address);
	BindModel(pModeldata->GetAddress(nIdx));
}

//===========================================================================================================
// ���f���̃e�N�X�`���ݒ�
//===========================================================================================================
void CModel::SetModelTex(D3DXMATERIAL* pMat)
{
	if (pMat != nullptr)
	{
		for (int nCntMat = 0; nCntMat < (int)m_ModelInfo.NumMat; nCntMat++)
		{
			int nTexIdx = 0;
			CTexture* pTex = CManager::GetTexture();
			m_TexIdx[nCntMat] = pTex->Regist(pMat[nCntMat].pTextureFilename);
			BindModelTex(pTex->GetAddress(m_TexIdx[nCntMat]),nCntMat);
		}
	}
}

void CModel::MeshColl()
{
	CCourse* pCourse = nullptr;
	pCourse = CSearch::SearchObject(pCourse, CObject::COURSE);

	if (pCourse == nullptr)
	{
		return;
	}

	// ���b�V���ɕK�v�ȏ��
	CModeldata::ModelData* pModelInfo = nullptr;	// ���f�������i�[����ϐ�
	pModelInfo = pCourse->GetModelInfo();			// ���f�����擾
	BOOL pHit = false;		// �����������ǂ������肷��ϐ�
	float Dis = 0.0f;		// ���b�V���Ƃ̋������i�[����ϐ�

	// �v���C���[�̏��
	D3DXVECTOR3 move = GetMove();	// �ړ��l���i�[����ϐ�
	D3DXVECTOR3 pRay = { 0,1,0 };	// ���C���o������

	// �ʒu��ݒ肷�邽�߂̏��
	D3DXVECTOR3 pos = GetPos();	// ���_
	float Ssize = 0.0f, FBsize = 0.0f;	// ���_����ǂꂾ�����炷�� ( S = �T�C�h / FB = �t�����g�o�b�N )

	// ���b�V���n�ʂƂ̓����蔻��
	std::tie(pHit, Dis)
		= CCollision::MeshCollision(
			pModelInfo->Mesh,
			pRay,
			pos);

	// ���_���𗘗p���Ăǂ̒��_�̏�ɂ��邩����
	{
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
	}

	// �������Ă��Ȃ������炱���ŕԂ�
	if (pHit != TRUE)
	{
		return;
	}

	// ����������Ă����牟���߂��Ȃ�
	if (Dis >= 30.0f)
	{
		return;
	}

	SetPos({
		pos.x,
		pos.y + Dis + (0.0f),
		pos.z
		});

	move.y = 0.0f;

	SetMove(move);
}
