//===========================================================================================================================================================
// 
// �e�N�X�`���Ǘ�����
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "texture.h"
#include "manager.h"

int CTexture::m_NumAll = 0;
//==================================================================================================
// �R���X�g���N�^
//==================================================================================================
CTexture::CTexture()
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		m_pTexture[nCnt] = {};
		m_pTexStorage[nCnt] = {};
	}
}

//==================================================================================================
// �f�X�g���N�^
//==================================================================================================
CTexture::~CTexture()
{
}

//==================================================================================================
// �j��
//==================================================================================================
void CTexture::Unload()
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		if (m_pTexture[nCnt] != nullptr)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		if (m_pTexStorage[nCnt] != nullptr)
		{
			m_pTexStorage[nCnt] = nullptr;
		}
	}
}

//==================================================================================================
// �e�N�X�`���o�^
//==================================================================================================
int CTexture::Regist(const char* pTexturename)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	int nIdx = 0;

	// �e�N�X�`�����ݒ肳��Ă��Ȃ�������
	if (pTexturename == nullptr) 
	{ return -1; }		// �����ݒ肳��Ă��Ȃ��Ƃ��� -1 ��ݒ肷��

	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		if (m_pTexture[nCntTex] == nullptr && m_pTexStorage[nCntTex] == nullptr)
		{// �e�N�X�`�����ݒ肳��Ă��Ȃ�������
			if (SUCCEEDED(D3DXCreateTextureFromFile(pDevice, pTexturename, &m_pTexture[nCntTex])))	// �e�N�X�`���쐬
			{
				m_pTexStorage[nCntTex] = pTexturename;	// �e�N�X�`���l�[����ۊ�
				nIdx = nCntTex;	// ID��ݒ�
				m_NumAll++;		// ��������

				break;

			}
			else
			{// �e�N�X�`�����f�[�^�ɑ��݂��Ă��Ȃ�
				assert(false && "�e�N�X�`�������݂��ĂȂ���I�I");
			}
		}
		else if(!strcmp(pTexturename, m_pTexStorage[nCntTex]))
		{// 
			nIdx = nCntTex;	// ID��ݒ�

			break;
		}
	}

	return nIdx;
}

//==================================================================================================
// �e�N�X�`���̃A�h���X�擾
//==================================================================================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int Idx)
{
	if (Idx == -1)
	{// -1�� nullptr �ŕԂ�
		return nullptr;
	}

	return m_pTexture[Idx];
}