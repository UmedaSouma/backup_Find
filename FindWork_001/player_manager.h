#pragma once
//===========================================================================================================================================================
// 
// player_manager.cppÇÃÉwÉbÉ_Å[ [player_manager.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _PLAYER_MANAGER_H_
#define _PLAYER_MANAGER_H_
#include "main.h"
#include "car_player.h"
#include "player_controller.h"

class CPlayerManager
{
public:
	CPlayerManager();
	~CPlayerManager();
	void Init();
	void Uninit();
	void Update();
	static CPlayerManager* Create();

	static CCarPlayer* GetPlayerCar() { return m_pCar; }
private:
	static CCarPlayer* m_pCar;
	CPlayerController* m_pController;
};

#endif // !PLAYER_MANAGER_H_