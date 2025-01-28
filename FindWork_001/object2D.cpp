//===========================================================================================================================================================
// 
// �I�u�W�F�N�g�̒��_���W�̊Ǘ�
// Author : souma umeda
// 
//===========================================================================================================================================================

// �C���N���[�h
#include "object2D.h"
#include "renderer.h"
#include "manager.h"


//========================================================================================================================
// �R���X�g���N�^
//========================================================================================================================
CObject2D::CObject2D(int nPriority, int nOrigin) :CObject(nPriority)
, m_nTexSplit{ 1,1 }
, m_color{ 1.0f,1.0f ,1.0f ,1.0f }
, m_fAngle(0)
, m_fLength(0)
, m_size{ 1.0f,1.0f ,1.0f }
, m_rot{ 0.0f,0.0f ,0.0f }
, m_pos{ 0.0f,0.0f ,0.0f }
, m_nCnt(0)
, m_pVtxBuff(nullptr)
, m_pVtxTexture(nullptr)
, m_nAnimeCounter{ 0,0 }
, m_nAnimeInterval(0)
, m_bHP(false)
, m_fHPratio(1.0f)
{
	m_nPriority = nPriority;
	m_nOrigin = nOrigin;
}

//========================================================================================================================
// �f�X�g���N�^
//========================================================================================================================
CObject2D::~CObject2D()
{

}

//========================================================================================================================
// �����ݒ�
//========================================================================================================================
HRESULT CObject2D::Init()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	// ���_�o�b�t�@�̐ݒ�
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr)))
	{
		return E_FAIL;
	}

	// �e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, &TexFile[m_texfile][0], &m_pVtxTexture);

	//m_pVtxTexture = nullptr;

	// ���_�o�b�t�@�̃|�C���^����
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	//// �Ίp��
	//m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) / 2.0f;

	//// �p�x
	//m_fAngle = atan2f(m_size.x, m_size.y);
	
	D3DXVECTOR3 size = m_size;

	// ���W�̐ݒ�
	if (m_bHP)
	{
		pVtx[0].pos.x = m_pos.x;
		pVtx[0].pos.y = m_pos.y - m_size.y;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = m_pos.x + (m_size.x * m_fHPratio);
		pVtx[1].pos.y = m_pos.y - m_size.y;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = m_pos.x;
		pVtx[2].pos.y = m_pos.y + m_size.y;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = m_pos.x + m_size.x * m_fHPratio;
		pVtx[3].pos.y = m_pos.y + m_size.y;
		pVtx[3].pos.z = 0.0f;
	}

	switch(m_nOrigin)
	{
	case CENTER:
		// �Ίp��
		m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y);
		// �p�x
		m_fAngle = atan2f(m_size.x, m_size.y);

		pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
		pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
		pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
		pVtx[3].pos.z = 0.0f;
		break;

	case CENTER_DOWN:

		size.x *= 0.5f;
		size.y *= 2;

		// �Ίp��
		m_fLength = sqrtf(size.x * size.x + size.y * size.y);
		// �p�x
		m_fAngle = atan2f(size.x, size.y);

		pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI * 0.5f)/*m_fAngle*/) * /*m_fLength*/size.x;
		pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI * 0.5f)/*m_fAngle*/) * /*m_fLength*/size.x;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI * 0.5f)/*m_fAngle*/) * /*m_fLength*/size.x;
		pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI * 0.5f)/*m_fAngle*/) * /*m_fLength*/size.x;
		pVtx[3].pos.z = 0.0f;
		break;

		
	case LEFT_CENTER:

		// �܂��������Ă��Ȃ�(�����]�ɑΉ�������

		pVtx[0].pos.x = m_pos.x;
		pVtx[0].pos.y = m_pos.y - m_size.y;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = m_pos.x + (m_size.x * m_fHPratio);
		pVtx[1].pos.y = m_pos.y - m_size.y;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = m_pos.x;
		pVtx[2].pos.y = m_pos.y + m_size.y;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = m_pos.x + m_size.x * m_fHPratio;
		pVtx[3].pos.y = m_pos.y + m_size.y;
		pVtx[3].pos.z = 0.0f;

		break;
	}

	//pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	//pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	//pVtx[0].pos.z = 0.0f;

	//pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	//pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	//pVtx[1].pos.z = 0.0f;

	//pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - 0.5f/*m_fAngle*/) * /*m_fLength*/size.x;
	//pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - 0.5f/*m_fAngle*/) * /*m_fLength*/size.x;
	//pVtx[2].pos.z = 0.0f;

	//pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + 0.5f/*m_fAngle*/) * /*m_fLength*/size.x;
	//pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + 0.5f/*m_fAngle*/) * /*m_fLength*/size.x;
	//pVtx[3].pos.z = 0.0f;
	
	// �@���̐ݒ�
	{
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
	}
	
	// �J���[�̐ݒ�
	{
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	
	// �e�N�X�`�����W�̐ݒ�
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f / m_nTexSplit.x, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / m_nTexSplit.y);
		pVtx[3].tex = D3DXVECTOR2(1.0f / m_nTexSplit.x, 1.0f / m_nTexSplit.y);
	}
	
	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//========================================================================================================================
// �I������
//========================================================================================================================
void CObject2D::Uninit()
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// �e�N�X�`���̔j��
	{
		// �e�e�N�X�`���ȊO��j��
		CFade* pFade = dynamic_cast<CFade*>(this);	// cast�����Ƃ��^����v���Ă��Ȃ���null������

		if (pFade != nullptr)
		{
			// �e�N�X�`���̔j��
			if (m_pVtxTexture != nullptr)
			{
				m_pVtxTexture->Release();
				m_pVtxTexture = nullptr;
			}
		}
	}

	Release();
}

//========================================================================================================================
// �X�V����
//========================================================================================================================
void CObject2D::Update()
{
	//CRenderer* Renderer = CManager::GetRenderer();
	//LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	// ���_�|�C���^����
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 size = m_size;

	// ���W�̐ݒ�
	if (m_bHP)
	{
		pVtx[0].pos.x = m_pos.x;
		pVtx[0].pos.y = m_pos.y - m_size.y;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = m_pos.x + (m_size.x * m_fHPratio);
		pVtx[1].pos.y = m_pos.y - m_size.y;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = m_pos.x;
		pVtx[2].pos.y = m_pos.y + m_size.y;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = m_pos.x + (m_size.x * m_fHPratio);
		pVtx[3].pos.y = m_pos.y + m_size.y;
		pVtx[3].pos.z = 0.0f;
	}

	switch (m_nOrigin)
	{
	case CENTER_DOWN:
		//D3DXVECTOR3 size = m_size;
		size.x *= 0.5f;
		size.y *= 2;

		pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI * 0.5f)/*m_fAngle*/) * /*m_fLength*/size.x;
		pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI * 0.5f)/*m_fAngle*/) * /*m_fLength*/size.x;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI * 0.5f)/*m_fAngle*/) * /*m_fLength*/size.x;
		pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI * 0.5f)/*m_fAngle*/) * /*m_fLength*/size.x;
		pVtx[3].pos.z = 0.0f;
		break;

	case CENTER:

		pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
		pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
		pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
		pVtx[3].pos.z = 0.0f;
		break;

	case LEFT_CENTER:
		pVtx[0].pos.x = m_pos.x;
		pVtx[0].pos.y = m_pos.y - m_size.y;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = m_pos.x + (m_size.x * m_fHPratio);
		pVtx[1].pos.y = m_pos.y - m_size.y;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = m_pos.x;
		pVtx[2].pos.y = m_pos.y + m_size.y;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = m_pos.x + (m_size.x * m_fHPratio);
		pVtx[3].pos.y = m_pos.y + m_size.y;
		pVtx[3].pos.z = 0.0f;
		break;

	default:
		return;
	}


	//if (m_nOrigin == CENTER_DOWN)
	//{
	//	
	//	size.x *= 0.5f;
	//	size.y *= 2;

	//	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	//	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	//	pVtx[0].pos.z = 0.0f;

	//	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	//	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	//	pVtx[1].pos.z = 0.0f;

	//	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI * 0.5f)/*m_fAngle*/) * /*m_fLength*/size.x;
	//	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI * 0.5f)/*m_fAngle*/) * /*m_fLength*/size.x;
	//	pVtx[2].pos.z = 0.0f;

	//	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI * 0.5f)/*m_fAngle*/) * /*m_fLength*/size.x;
	//	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI * 0.5f)/*m_fAngle*/) * /*m_fLength*/size.x;
	//	pVtx[3].pos.z = 0.0f;
	//}

	//else
	//{
	//	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	//	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	//	pVtx[0].pos.z = 0.0f;

	//	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	//	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	//	pVtx[1].pos.z = 0.0f;

	//	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	//	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	//	pVtx[2].pos.z = 0.0f;

	//	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	//	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	//	pVtx[3].pos.z = 0.0f;
	//}
	

	{//// ���W�̐ݒ�
	//pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	//pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	//pVtx[0].pos.z = 0.0f;

	//pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	//pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	//pVtx[1].pos.z = 0.0f;

	//pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	//pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	//pVtx[2].pos.z = 0.0f;

	//pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	//pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	//pVtx[3].pos.z = 0.0f;

	}

	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(1.0f / m_nTexSplit.x * m_nAnimeCounter.x, 1.0f / m_nTexSplit.y * m_nAnimeCounter.y);
	pVtx[1].tex = D3DXVECTOR2(1.0f / m_nTexSplit.x * (m_nAnimeCounter.x + 1), 1.0f / m_nTexSplit.y * m_nAnimeCounter.y);
	pVtx[2].tex = D3DXVECTOR2(1.0f / m_nTexSplit.x * m_nAnimeCounter.x, 1.0f / m_nTexSplit.y * (m_nAnimeCounter.y + 1));
	pVtx[3].tex = D3DXVECTOR2(1.0f / m_nTexSplit.x * (m_nAnimeCounter.x + 1), 1.0f / m_nTexSplit.y * (m_nAnimeCounter.y + 1));

		//// �J�E���g���C���^�[�o���t���[���܂ŃJ�E���g������
		//if (m_nCnt == m_nAnimeInterval)
		//{
		//	// ���̕������ɓ��B����܂�
		//	if (m_nAnimeCounter.x < m_nTexSplit.x)
		//	{
		//		m_nAnimeCounter.x++;	// ���A�j���[�V�����i�߂�
		//	}

		//	// ���̃A�j���[�V�����J�E���^�[�����̕�������������
		//	if (m_nAnimeCounter.x >= m_nTexSplit.x)
		//	{
		//		m_nAnimeCounter.y++;	// �c�A�j���[�V������i�߂�
		//		m_nAnimeCounter.x = 0;	// ���̃A�j���[�V���������Z�b�g����
		//	}

		//	// �c�̃A�j���[�V�����J�E���^�[���c�̕�������������
		//	if (m_nAnimeCounter.y >= m_nTexSplit.y)
		//	{
		//		m_nAnimeCounter.y = 0;	// �c�̃A�j���[�V���������Z�b�g����
		//	}		

		//	// �A�j���[�V�����J�E���^�[���Z�b�g
		//	m_nCnt = 0;
		//}

		// �A�j���[�V�����J�E���^�[��i�߂�
		m_nCnt++;

		// ���_�o�b�t�@�̃A�����b�N
		m_pVtxBuff->Unlock();
	
}

//========================================================================================================================
// �`�揈��
//========================================================================================================================
void CObject2D::Draw()
{
	// �����_���[���擾
	CRenderer* Renderer = CManager::GetRenderer();

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();


	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�`��
	pDevice->SetFVF(FVF_VERTEX_2D);


	if (m_pVtxTexture == nullptr)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, nullptr);
	}
	else if (m_pVtxTexture != nullptr)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pVtxTexture);
	}
	

	// �|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//========================================================================================================================
// �C�ӂ̃e�N�X�`����ݒ肷��
//========================================================================================================================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pVtxTexture = pTex;
}

//========================================================================================================================
// �I�u�W�F�N�g2D�̐���
//========================================================================================================================
CObject2D* CObject2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR2 TexSplit, int Interval)
{
	CObject2D* Object2D = new CObject2D;

	Object2D->m_pos = pos;					// �ʒu�̐ݒ�
	Object2D->m_size = size;				// �T�C�Y�̐ݒ�
	Object2D->m_nTexSplit = TexSplit;		// �e�N�X�`���������̐ݒ�
	Object2D->m_nAnimeInterval = Interval;	// �e�N�X�`���A�j���[�V�����̊Ԋu��ݒ�
	Object2D->m_nAnimeCounter.x = {};		// �����ڂ̃A�j���\�\�����������Ă��邩�m�F����J�E���^�[

	Object2D->Init();	// �����ݒ�

	return Object2D;
}

//========================================================================================================================
// �A�j���[�V�����J�E���^�[�̎擾
//========================================================================================================================
D3DXVECTOR2& CObject2D::GetAnimeCounter()
{
	return m_nAnimeCounter;
}

//========================================================================================================================
// �A�j���[�V�����̊Ԋu�̐ݒ�
//========================================================================================================================
void CObject2D::SetAnimeInterval(int Interval)
{
	m_nAnimeInterval = Interval;
}

//========================================================================================================================
// �`��D�揇�ʂ̎擾
//========================================================================================================================
int CObject2D::GetPriority()
{
	return m_nPriority;
}