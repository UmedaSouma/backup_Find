//===========================================================================================================================================================
// 
// ���f���f�[�^�̊Ǘ�
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "modeldata.h"
#include "manager.h"

int CModeldata::m_NumAll = 0;

//========================================================================================================================
// �R���X�g���N�^
//========================================================================================================================
CModeldata::CModeldata()
{


	for (int nCnt = 0; nCnt < MAX_MODEL_DATA; nCnt++)
	{
		m_pModelData[nCnt] = {};

		
		m_pStorage[nCnt] = nullptr;

		m_pModelData[nCnt].Mesh = nullptr;
		m_pModelData[nCnt].BuffMat = nullptr;
		m_pModelData[nCnt].NumMat = 0;

		for (int n = 0; n < MAX_MAT_DATA; n++)
		{
			m_StandardCol[nCnt][n] = { 0.0f,0.0f,0.0f };
			m_pTexData[nCnt].pTex[n] = nullptr;
		}

		m_pTexData[nCnt].nIdx = 0;
	}
}

//========================================================================================================================
// �f�X�g���N�^
//========================================================================================================================
CModeldata::~CModeldata()
{
}

//========================================================================================================================
// �j��
//========================================================================================================================
void CModeldata::Unload()
{
	//for (int nCnt = 0; nCnt < MAX_MODEL_DATA; nCnt++)
	//{
	//	if (m_pModelData != nullptr)
	//	{
	//		m_pModelData[nCnt] = {};
	//	}
	//}

	for (int nCnt = 0; nCnt < MAX_MODEL_DATA; nCnt++)
	{
		if (m_pStorage[nCnt] != nullptr)
		{
			m_pStorage[nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < MAX_MODEL_DATA; nCnt++)
	{
		if (m_pModelData[nCnt].BuffMat != nullptr)
		{
			m_pModelData[nCnt].BuffMat->Release();
			m_pModelData[nCnt].BuffMat = nullptr;
		}	
	}

	for (int nCnt = 0; nCnt < MAX_MODEL_DATA; nCnt++)
	{
		if (m_pModelData[nCnt].Mesh != nullptr)
		{
			m_pModelData[nCnt].Mesh->Release();
			m_pModelData[nCnt].Mesh = nullptr;
		}	
	}
}

//========================================================================================================================
// ���f���f�[�^�̓o�^
//========================================================================================================================
int CModeldata::Regist(const char*modelpass)
{
	int nIdx = 0;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCnt = 0; nCnt < MAX_MODEL_DATA; nCnt++)
	{
		if (m_pModelData[nCnt].BuffMat == nullptr
			&& m_pModelData[nCnt].Mesh == nullptr
			&& m_pModelData[nCnt].NumMat == 0)
		{
			// X�t�@�C���̓ǂݍ���
			if (SUCCEEDED(D3DXLoadMeshFromX(modelpass,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				nullptr,
				&m_pModelData[nCnt].BuffMat,
				nullptr,
				&m_pModelData[nCnt].NumMat,
				&m_pModelData[nCnt].Mesh)))
			{
				D3DXMATERIAL* pMat;				// �}�e���A���f�[�^�̃|�C���^
				pMat = (D3DXMATERIAL*)m_pModelData[nCnt].BuffMat->GetBufferPointer();	// �}�e���A���f�[�^�̃|�C���^�̎擾

				for (int nCntMat = 0; nCntMat < (int)m_pModelData[nCnt].NumMat; nCntMat++)
				{
					m_StandardCol[nCnt][nCntMat] = pMat[nCntMat].MatD3D.Diffuse;	// ���̐F��ۑ����Ă���
				}

				m_pStorage[nCnt] = modelpass;
				nIdx = nCnt;
				m_NumAll++;

				break;
			}
			else
			{
				assert(false);
			}

			//===========================================================================================================
			// < debugmemo >
			// �����Ō��̐F��ۑ����Ă���
			// SET or GET �łǂ��ɂ�����
			//===========================================================================================================
			
		}
		else if (!strcmp(modelpass, m_pStorage[nCnt]))
		{
			nIdx = nCnt;

			break;
		}
	}

	return nIdx;
}

//========================================================================================================================
// �A�h���X��Ԃ�
//========================================================================================================================
CModeldata::ModelData *CModeldata::GetAddress(int Idx)
{
	return &m_pModelData[Idx];
}

//===========================================================================================================
// �ʏ�F�̃}�e���A���f�[�^��Ԃ�
//===========================================================================================================
D3DCOLORVALUE *CModeldata::GetMatData(const char* pAddress, int MatNum)
{
	for (int nCnt = 0; nCnt < MAX_MODEL_DATA; nCnt++)
	{
		if (!strcmp(pAddress, m_pStorage[nCnt]))
		{// �A�h���X�������ԍ���������
			return &m_StandardCol[nCnt][MatNum];	// �ʏ�F��Ԃ�
		}
	}

	return nullptr;
}
