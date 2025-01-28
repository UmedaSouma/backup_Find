//===========================================================================================================================================================
// 
// light.cpp�̃w�b�_�[
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

class CLight
{
private:
	static const unsigned int MAX_LIGHT = 3;	// ���C�g�̍ő吔
public:
	CLight();
	~CLight();
	HRESULT Init();
	void Uninit();
	void Update();
private:
	D3DLIGHT9 m_aLight[MAX_LIGHT];	// ���C�g�̏��
	static int m_NumAll;	// ���C�g�̐�
};
#endif // !_LIGHT_H_
