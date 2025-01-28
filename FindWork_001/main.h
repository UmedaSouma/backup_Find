//===========================================================================================================================================================
// 
// main.cpp�̃w�b�_�[
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _MAIN_H_
#define _MAIN_H_


#include <vector>
#include <unordered_map>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"xinput.lib")	// �W���C�p�b�h�����ɕK�v

//#pragma warning (disable: 4100)

#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE| D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// �}�N����`
#define CLASS_NAME		 "WindowClass"			// �E�B���h�E�N���X�̖��O
#define WINDOW_NAME		 "DirectX��{����"	// �E�B���h�E�̖��O
#define ID_BUTTON_FINISH (101)

//using namespace std;

// ���_���[3D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_2D;

// ���_���[3D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_3D;

class CMain
{
public:
	CMain();
	~CMain();
	static void ToggleFullscreen(HWND hWnd);
private:
	static bool m_IsFullScreem;
	static RECT m_WindowRect;
};

void SetCrrent(DWORD w);
DWORD* GetCrrent();
void SetLastTime(DWORD w);
DWORD* GetLastTime();
int GetCountFPS();

// ���������[�N�̌��o
#include <crtdbg.h>
#include <stdlib.h>
#define _CRTDBG_MAP_ALLOC

#ifdef _DEBUG
#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#endif // !_MAIN_H_

