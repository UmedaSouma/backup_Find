#pragma once
//===========================================================================================================================================================
// 
// editor_parama.cpp�̃w�b�_�[ [editor_parama.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _EDITOR_PARAM_H_
#define _EDITOR_PARAM_H_
#include "main.h"
#include "scene.h"
#include "player_manager.h"


class CEditor_Param :public CScene
{
public:
	CEditor_Param();
	~CEditor_Param()override;
	HRESULT Init()override;	// �����ݒ�
	void Uninit()override;	// �I��
	void Update()override;	// �X�V
	void Draw()override;	// �`��
private:

public:
	static CPlayerManager* pPlayerManager;
};


#endif // !EDITOR_PARAM_H_