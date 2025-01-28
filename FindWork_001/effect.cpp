//===========================================================================================================================================================
// 
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "effect.h"
#include "manager.h"
#include "billboard.h"

//========================================================================================================================
// �R���X�g���N�^
//========================================================================================================================
CEffect::CEffect(int nPrio):CBillboard(nPrio)
{
}

//========================================================================================================================
// �f�X�g���N�^
//========================================================================================================================
CEffect::~CEffect()
{
}

//========================================================================================================================
// �����ݒ�
//========================================================================================================================
HRESULT CEffect::Init()
{
	int Idx = 0;
	Idx = CManager::GetTexture()->Regist("data\\TEXTURE\\shadow000.jpg");
	BindTexture(CManager::GetTexture()->GetAddress(Idx));

	// �����ݒ�
	m_nLife = m_nMaxLife;

	CBillboard::Init();
	return S_OK;
}

//========================================================================================================================
// �I������
//========================================================================================================================
void CEffect::Uninit()
{
	CBillboard::Uninit();
}

//========================================================================================================================
// �X�V����
//========================================================================================================================
void CEffect::Update()
{
	if (m_nLife == -1)
	{
	}
	else if (m_nLife <= 0)
	{
		Uninit();
	}
	else
	{
		m_nLife--;
	}

	CBillboard::Update();
}

//========================================================================================================================
// �`�揈��
//========================================================================================================================
void CEffect::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// Z�̔�r���@
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// Z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	CBillboard::Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// Z�̔�r���@
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// Z�o�b�t�@�ɏ�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//========================================================================================================================
// ��������
//========================================================================================================================
CEffect* CEffect::Create(D3DXVECTOR3 pos, int nLife)
{
	CEffect* pEffect = new CEffect;
	pEffect->SetPos(pos);
	pEffect->m_nMaxLife = nLife;

	pEffect->Init();

	return pEffect;
}