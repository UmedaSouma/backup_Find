//===========================================================================================================================================================
// 
// model.cpp�̃w�b�_�[
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _OBJEXTX_H_
#define _OBJEXTX_H_

#include "main.h"
#include "object.h"

class CObjectX :public CObject
{
private:
	typedef struct
	{
		LPD3DXMESH Mesh;			// ���b�V��(���_���)�ւ̃|�C���^
		LPD3DXBUFFER BuffMat;	// �}�e���A���ւ̃|�C���^
		DWORD NumMat;	// �}�e���A���̐�
	}ModelInfo;

	ModelInfo m_ModelInfo;
public:
	CObjectX();
	~CObjectX();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void SetPos(D3DXVECTOR3 pos);
	D3DXVECTOR3& GetPos();
	void SetModelInfo(LPD3DXMESH mesh, LPD3DXBUFFER buffmat, DWORD nummat);

	static CObjectX* Create(D3DXVECTOR3 pos);
private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_scale;
	D3DXMATRIX m_mtxWorld;
};

#endif // !_MODEL_H_
