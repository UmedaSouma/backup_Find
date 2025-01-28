//===========================================================================================================================================================
// 
// �e�L�X�g�̏����A�t�H���g�̐ݒ� [text.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "text.h"
#include "manager.h"
#include "search.h"
#include "goal.h"

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CText::CText()
{
	for (int nCntFont = 0; nCntFont < FONT_MAX; nCntFont++)
	{
		m_pFont[nCntFont] = nullptr;
	}

	for (int nCntText = 0; nCntText < TEXT_MAX; nCntText++)
	{
		m_bUse[nCntText] = false;
	}
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CText::~CText()
{
}

//===========================================================================================================
// �����ݒ�
//===========================================================================================================
HRESULT CText::Init()
{
	//�@�t�H���g�̓ǂݍ���
	for (int nCntFont = 0; nCntFont < FONT_MAX; nCntFont++)
	{
		LPCSTR font_path = m_FontInfo[nCntFont].FilePass; // �����Ŋe�t�H���g���g�p�\��

		if (AddFontResourceEx(font_path, FR_PRIVATE, nullptr) > 0)
		{
		}
		else
		{
			// �t�H���g�Ǎ��G���[����
			//MessageBox(nullptr, "�t�H���g�Ǎ����s", "", MB_OK);
		}
	}

	return S_OK;
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CText::Uninit()
{
	// �t�H���g�̔j��
	for (int nCntFont = 0; nCntFont < FONT_MAX; nCntFont++)
	{
		if (m_pFont[nCntFont] != nullptr)
		{
			m_pFont[nCntFont]->Release();
			m_pFont[nCntFont] = nullptr;
		}
	}
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void CText::Draw(D3DXVECTOR2 fontpos, int fontsize, FONT_NAME font, D3DXCOLOR rgba, const char* text, ...)
{
	// ����������
	if (m_pFont[font] != nullptr)
	{
		m_pFont[font]->Release();
		m_pFont[font] = nullptr;
	}

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	RECT rect = { (LONG)fontpos.x, (LONG)fontpos.y, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
	char aStr[MAX_TEXT] = {};

	D3DXCreateFont(
		pDevice, fontsize, 0, FW_HEAVY, 1,
		FALSE,
		DEFAULT_CHARSET,
		OUT_TT_ONLY_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE,
		TEXT(m_FontInfo[font].FileName),
		&m_pFont[font]);
	
	// �ϒ������̏���
	va_list args;					// �ϒ������̈������X�g���w�肷��
	va_start(args, text);			// va_list �������� -> �ϒ������̈�O�̈������w��
	vsprintf_s(aStr, text, args);	// �����w�蕶������g�p���ĉϒ��������當����𐶐����邽�߂̈��S�Ȋ֐�
	va_end(args);					// va_start �}�N���ɂ���ĊJ�n���ꂽ�ϒ��������X�g���I�����邽�߂Ɏg�p

	// �e�L�X�g�̕`��
	m_pFont[font]->DrawText(NULL, aStr, -1, &rect, DT_CENTER | DT_WORDBREAK, rgba);
}

//===========================================================================================================
// �S�Ă̕`��
//===========================================================================================================
void CText::DrawAll()
{
	int n = 0;

	if (m_bUse[TEXT_TEST])
	{
		Draw(
			{ 100.0f, 110.0f },
			25,
			CText::FONT_ZENMARUGOTHIC_BLACK,
			{ .0f, .0f, .0f, 1.0f },
			"����ɂ��� hello world!! %d"
			,n
		);
	}
	
	if (m_bUse[TEXT_PRESSENTER])
	{
		Draw(
			{ 0.0f, SCREEN_HEIGHT*0.8f },
			100,
			CText::FONT_BESTTEN_DOT,
			{ .0f, .0f, .0f, 1.0f },
			"Enter or StartButton"
		);
	}

	if (m_bUse[TEXT_RESULT_TIME])
	{
		Draw(
			{ 0.0f, SCREEN_HEIGHT * 0.8f },
			100,
			CText::FONT_BESTTEN_DOT,
			{ .0f, .0f, .0f, 1.0f },
			"Enter or StartButton"
		);
	}

	//CGoal* pGoal = nullptr;
	//pGoal = CSearch::SearchObject(pGoal, CObject::GOAL);

	//if (pGoal != nullptr)
	//{
	//	Draw(
	//		{ 0.0f, SCREEN_HEIGHT * 0.8f },
	//		100,
	//		CText::FONT_BESTTEN_DOT,
	//		{ .0f, .0f, .0f, 1.0f },
	//		"goal : %d", pGoal->GetDierTrvel());
	//}
}