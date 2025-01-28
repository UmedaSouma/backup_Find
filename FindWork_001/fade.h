//===========================================================================================================================================================
// 
// fade.cpp�̃w�b�_�[
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"
#include "object2D.h"
#include "scene.h"

class CFade :public CObject2D
{
public:
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_STOP,
		FADE_MAX
	}STATE;

	//CFade();
	CFade(int nPriority = PRIORITY_MAX-1);
	~CFade()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��
	void SetFade(CScene::MODE nextmode);
	void FadeIn();
	void FadeOut();
	STATE GetState();
private:
	STATE m_State;
	CScene::MODE m_NextMode;
	int m_fFadeframe;	// �t�F�[�h�J�ڂ̎���
	//CFade* m_pState;
};



#endif // !_FADE_H_