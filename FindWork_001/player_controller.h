#pragma once
//===========================================================================================================================================================
// 
// player_controller.cppÇÃÉwÉbÉ_Å[ [player_controller.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _PLAYER_CONTROLLER_H_
#define _PLAYER_CONTROLLER_H_
#include "main.h"
#include "car_player.h"

class CPlayerController
{
public:
	CPlayerController();
	~CPlayerController();
	void Init();
	void Uninit();
	void Update(CCarPlayer*pCar);
	void Move();
private:

};




#endif // !PLAYER_CONTROLLER_H_
