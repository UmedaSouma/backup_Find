#pragma once
class CText
{
public:
	static const unsigned int MAX_TEXT = 1024;

	typedef enum
	{
		TEXT_TEST=0,
		TEXT_PRESSENTER,
		TEXT_RESULT_TIME,
		TEXT_MAX
	}TEXT_TYPE;

	typedef enum
	{
		FONT_ZENMARUGOTHIC_BLACK = 0,
		FONT_BESTTEN_DOT,
		FONT_MAX
	}FONT_NAME;

	typedef struct
	{
		const char* FilePass;
		const char* FileName;
	}FONT_INFO;

	CText();
	~CText();
	HRESULT Init();
	void Uninit();
	void Draw(D3DXVECTOR2 fontpos, int fontsize, FONT_NAME font, D3DXCOLOR rgba, const char* text, ...);
	void DrawAll();

	void SetText(int Idx) { m_bUse[Idx] = true; }		// �e�L�X�g��\��
	void UnSetText(int Idx) { m_bUse[Idx] = false; }	// �e�L�X�g���\��

private:
	FONT_INFO m_FontInfo[FONT_MAX] =
	{
		{"data\\FONT\\ZenMaruGothic-Black.ttf", "Zen_Maru_Gothic_Black"},
		{"data\\FONT\\BestTen-DOT.otf", "�x�X�g�e��DOT"}
	};

	bool m_bUse[TEXT_MAX];	// ���ݕ\�����Ă���e�L�X�g
	LPD3DXFONT m_pFont[FONT_MAX];	// �t�H���g�̃|�C���^
};

