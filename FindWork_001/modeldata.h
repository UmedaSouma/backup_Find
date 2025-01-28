#ifndef _MODELDATA_H_
#define _MODELDATA_H_

#include "main.h"


//====================================================================================
// ���f���ɕK�v�ȏ��̍\����
//====================================================================================

// ���f���f�[�^�̃N���X
class CModeldata
{
public:
	typedef struct
	{
		LPD3DXMESH Mesh;		// ���b�V��(���_���)�ւ̃|�C���^
		LPD3DXBUFFER BuffMat;	// �}�e���A���ւ̃|�C���^
		DWORD NumMat;			// �}�e���A���̐�
	}ModelData;

	static const unsigned int MAX_MODEL_DATA = 64;	// ���f���f�[�^�̍ő�l
	static const unsigned int MAX_MAT_DATA = 514;	// �P�L�����N�^�[���̃}�e���A���f�[�^�ő�l

	typedef struct
	{
		LPDIRECT3DTEXTURE9 pTex[MAX_MAT_DATA];
		int nIdx;
	}TexData;

	CModeldata();	// �R���X�g���N�^
	~CModeldata();	// �f�X�g���N�^
	void Unload();	// 
	int Regist(const char* pTexturename);
	ModelData *GetAddress(int Idx);
	D3DCOLORVALUE *GetMatData(const char* pAddress, int MatNum);
private:
	
	TexData m_pTexData[MAX_MODEL_DATA];
	ModelData m_pModelData[MAX_MODEL_DATA];
	D3DCOLORVALUE m_StandardCol[MAX_MODEL_DATA][MAX_MAT_DATA];	// �F��ς���O�̌��̐F

	const char* m_pStorage[MAX_MODEL_DATA];
	static int m_NumAll;
	

	//LPD3DXMESH Mesh;			// ���b�V��(���_���)�ւ̃|�C���^
	//LPD3DXBUFFER BuffMat;	// �}�e���A���ւ̃|�C���^
	//DWORD NumMat;	// �}�e���A���̐�
};

#endif // !_MODELDATA_H_
