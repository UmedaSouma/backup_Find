//===========================================================================================================================================================
// 
// ƒ^ƒCƒgƒ‹‚Ìˆ—
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "title.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "course.h"
#include "title_poly.h"

CTitle::CTitle()
{
}

CTitle::~CTitle()
{
}

HRESULT CTitle::Init()
{
	CTitlePoly::Create();

	CCourse::Create(CCourse::COURSE_TITLE);

	CScene::Init();

	return S_OK;
}

void CTitle::Uninit()
{
	CScene::Uninit();
}

void CTitle::Update()
{
	CScene::Update();

	CInputKeyBoard* keyboard = CManager::GetKeyboard();
	CInputJoypad* joypad = CManager::GetJoypad();

	if (keyboard->GetTrigger(DIK_RETURN) || joypad->GetTrigger(CInputJoypad::JOYKEY_START))
	{
		CFade* pFade = CManager::GetFade();
		pFade->SetFade(CScene::MODE_GAME);
	}
}

void CTitle::Draw()
{
	CScene::Draw();
}