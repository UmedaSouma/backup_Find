//===========================================================================================================================================================
// 
// renderer.cppのヘッダー
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include"d3dx9.h"
#include "text.h"
#include "main.h"

class CRenderer
{
private:

	typedef enum
	{
		_FADE_ALPHA=0,
		_ENEMY_POS,
		_ENEMY_MOVE,
		_PLAYER_POS,
		_PLAYER_MOVE,
		_ENEMY_BUTTLE,
		_MAX_PRINT
	}_DEBUG_PRINT;

public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd,BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	LPDIRECT3DDEVICE9 GetDevice();	// 3Dデバイスの取得
	static CText* GetText() { return m_pText; }
	void SetDebugInfo(VERTEX_3D* pVtx, WORD dwHitVertexNo1, WORD dwHitVertexNo2, WORD dwHitVertexNo3);
	void SetDebugRoutePoint(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXVECTOR3 nextroute,int ID, bool clear);
	

	void DebugPrint(char&pStr);
private:
	LPDIRECT3D9 m_pD3D;	// Direct3D
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// Direct3Dデバイス
	LPD3DXFONT m_pFont;	// フォントのポインタ
	static CText* m_pText;	// テキストのポインタ
	char m_aStr[256];
	
};

#endif // !_RENDERER_H_