//===========================================================================================================================================================
// 
// object3D.cpp‚Ìƒwƒbƒ_[
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "main.h"
#include "object.h"

class CObject3D:public CObject 
{
public:
	CObject3D(int nPriority = PRIORITY_DEFAULT);
	~CObject3D()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void UpdateMatrix();
	void InitMatrix();
	void ScaleMatrix();
	void RotMatrix();
	void PosMatrix();
	void YawPitchRoll();
	void SetMatrix();
	void ViewMatrix();

	void SetPos(D3DXVECTOR3 pos);
	D3DXVECTOR3& GetPos();
	void SetSize(D3DXVECTOR3 size);
	D3DXVECTOR3& GetSize();
	void SetMove(D3DXVECTOR3 move);
	D3DXVECTOR3& GetMove();
	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }
	D3DXVECTOR3& GetScale() { return m_scale; }
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 &GetRot() { return m_rot; }
	void SetLength(D3DXVECTOR3 sizeA, D3DXVECTOR3 sizeB);
	float GetLength() { return m_length; }
	void SetAngle(float sizeA, float sizeB);
	float GetAngle() { return m_Angle; }
	LPDIRECT3DVERTEXBUFFER9* GetVtxBuff() { return &m_pVtxBuff; }

	void SetNormalize(D3DXVECTOR3 nor) { m_normalize = nor; }
	D3DXVECTOR3 GetNormalize() { return m_normalize; }

	const D3DXMATRIX& GetMatrix() const { return m_mtxWorld; }

	static CObject3D* Create(D3DXVECTOR3 pos);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pVtxTexture;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_scale;
	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 m_normalize;

	float m_length;	// ”ÍˆÍ	
					//	|[>‰~‚Ì”»’è‚ÉŽg‚¤•¨
	float m_Angle;	// Šp“x
};

#endif // !_OBJECT3D_H_
