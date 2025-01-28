//===========================================================================================================================================================
// 
// object2D.cpp�̃w�b�_�[
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _OBJECT_2D_H_
#define _OBJECT_2D_H_

#include "main.h"
#include "object.h"

class CObject2D :public CObject
{
public:

	typedef enum
	{
		CENTER = 0,
		CENTER_DOWN,
		CENTER_UP,
		RIGHT_CENTER,
		RIGHT_DOWN,
		RIGHT_UP,
		LEFT_CENTER,
		LEFT_DOWN,
		LEFT_UP,
		POLYGON_MAX
	}POLYGON_ORIGIN;

	CObject2D(int nPriority = PRIORITY_DEFAULT, int nOrigin = CENTER);
	~CObject2D()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);

	static CObject2D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR2 TexSplit, int Interval);

	D3DXVECTOR2& GetAnimeCounter();

	void SetAnimeInterval(int Interval);

	int GetPriority();

	const LPDIRECT3DTEXTURE9& GetTexture() const { return m_pVtxTexture; }

protected:
	D3DXVECTOR2 m_nTexSplit;	// �e�N�X�`���̕�����
	int m_nAnimeInterval;	// �A�j���[�V�����̊Ԋu
	int m_nCnt;
private:
	D3DXVECTOR2 m_nAnimeCounter;	// �A�j���[�V����������ڂ��ۑ�����ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pVtxTexture;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_rot;
	D3DXCOLOR m_color;
	float m_fLength;
	float m_fAngle;
	int m_nPriority;
	bool m_bHP;	// HP�o�[���ۂ�
	float m_fHPratio;	//HP�o�[�̊���
	int m_nOrigin;

public:
	//--------------------------------------------------
	// Set,Get
	//--------------------------------------------------
	// pos
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3& GetPos() { return m_pos; }
	// size
	void SetSize(D3DXVECTOR3 size) { m_size = size; }
	D3DXVECTOR3& GetSize() { return m_size; }
	// rot
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3& GetRot() { return m_rot; }
	// texsplit
	void SetTexSplit(D3DXVECTOR2 TexSplit) { m_nTexSplit = TexSplit; }
	D3DXVECTOR2& GetTexSplit() { return m_nTexSplit; }
	// color
	void SetColor(D3DXCOLOR color) { m_color = color; }
	D3DXCOLOR& GetColor() { return m_color; }
	// bHP
	void SetbHP(bool hp) { m_bHP = hp; }
	bool GetbHP() { return m_bHP; }
	// HPratio
	void SetHPratio(float ratio) { m_fHPratio = ratio; }
};

#endif // !_OBJECT_2D_H_
