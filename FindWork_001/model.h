//===========================================================================================================================================================
// 
// model.cpp�̃w�b�_�[
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
#include "object3D.h"
#include "modeldata.h"

class CModel :public CObject3D
{
private:
	CModeldata::ModelData m_ModelInfo;
public:
	// �����Ă������
	typedef enum
	{
		DIRECTION_NONE = 0,
		DIRECTION_LEFT,
		DIRECTION_RIGHT,
		DIRECTION_MAX
	}DIRECTION;

	CModel(int nPriority = PRIORITY_DEFAULT);
	~CModel();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void BindModel(CModeldata::ModelData* modelinfo);	// ���f���̐ݒ�
	void UpdateTargetRot();	// ���������X�Ƀ^�[�Q�b�g�Ɋ񂹂Ă���

	void SetDirection(DIRECTION dire);	// �����̐ݒ�
	int GetDirection();					// �����̎擾

	void SetMat(D3DCOLORVALUE mat);
	void bMat(bool bmat) { m_bMat = bmat; }
	void SetDefaultMat(D3DCOLORVALUE mat, int nummat);
	void FixRot();	// �p�x���C������
	void SetModelTex(D3DXMATERIAL* pMat);

	void MeshColl();	// ���b�V���Ƃ̓����蔻��

	static CModel* Create(D3DXVECTOR3 pos);

	void SetModel(const char* address);
	void SetModelIdx(int nIdx) { m_nIdx = nIdx; }	// ���f���̔ԍ���ۑ�����
	int GetModelIdx() { return m_nIdx; }	// ���f���ԍ����擾����
	void SetModelAddress(const char* Address) { m_pModelAddress = Address; }
	const char* GetModelAddress() { return m_pModelAddress; }
	void SetTexIdx(int nNum, int idx) { m_TexIdx[nNum] = idx; }
	void BindModelTex(LPDIRECT3DTEXTURE9 tex,int idx) { m_apTexture[idx] = tex; }
	CModeldata::ModelData* GetModelInfo() { return &m_ModelInfo; }
	D3DXVECTOR3 *GetVtxPos() { return &m_vtxpos[0]; }
	void SetTargetrot(D3DXVECTOR3 rot) { m_targetrot = rot; }
	D3DXVECTOR3 GetTargetrot() { return m_targetrot; }
private:
	int m_nIdx;
	int m_Direction;
	LPDIRECT3DTEXTURE9 m_apTexture[128] = {};
	D3DCOLORVALUE m_Diffuse[64];
	int m_TexIdx[CModeldata::MAX_MAT_DATA];	// ���f���̃e�N�X�`���ԍ�
	bool m_bMat;	// �_���[�W��Ԃ̃}�e���A���ύX
	const char* m_pModelAddress;	// ���f���f�[�^�̃A�h���X
	D3DXVECTOR3	m_vtxpos[1024];	// ���_���W
	D3DXVECTOR3 m_targetrot;	// �ڕW�p�x
};

#endif // !_MODEL_H_
