//===========================================================================================================================================================
// 
// 表示する数字の処理 [display_number.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "display_number.h"

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CDisplayNumber::CDisplayNumber()
{
	for (int i = 0; i < DIGID_MAX; i++)
	{
		m_pDisplayNum[i] = nullptr;
	}

	m_MaxDig = DIGID_ONE;
	m_Font = CNumber::FONT_TYPE::FONT_DOT_WBW;
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CDisplayNumber::~CDisplayNumber()
{
	

	//// すべて削除する
	//for (int i = 0; i < DIGID_MAX; i++)
	//{
	//	if (m_pDisplayNum[i] != nullptr)
	//	{
	//		m_pDisplayNum[i]->Uninit();
	//	}
	//}
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CDisplayNumber::Uninit()
{
	for (int i = 0; i < DIGID_MAX; i++)
	{
		if (m_pDisplayNum[i] != nullptr)
		{
			m_pDisplayNum[i]->Uninit();
			m_pDisplayNum[i] = nullptr;
		}
	}
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CDisplayNumber::Update(int num)
{
	int n = num;
	for (int i = 0; i < m_MaxDig; i++)
	{
		if (m_pDisplayNum[i] != nullptr)
		{
			m_pDisplayNum[i]->SetNumber(n % 10);
			n /= 10;
		}
	}
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void CDisplayNumber::Draw()
{
	//for (int i = 0; i < m_MaxDig; i++)
	//{
	//	if (m_pDisplayNum[i] != nullptr)
	//	{
	//		m_pDisplayNum[i]->Draw();
	//	}
	//}
}

//===========================================================================================================
// 表示する数字の設定
//===========================================================================================================
void CDisplayNumber::SetDisplayNumber(int num)
{
	m_Number = num;
	//m_pDisplayNum[DIGID_ONE] = CNumber::Create(CNumber::FONT_DOT_WBW);
	//m_pDisplayNum[DIGID_TEN] = CNumber::Create(CNumber::FONT_DOT_WBW);

	for (int i = 0; i < m_MaxDig; i++)
	{
		if (m_pDisplayNum[i] == nullptr)
		{
			m_pDisplayNum[i] = CNumber::Create(m_Font);
		}
	}
}

//===========================================================================================================
// 生成処理
//===========================================================================================================
CDisplayNumber* CDisplayNumber::Create(D3DXVECTOR3 pos, int num, DIGID dig, CNumber::FONT_TYPE font)
{
	CDisplayNumber* pDisNum = new CDisplayNumber;

	// 数字の情報
	pDisNum->m_MaxDig = (DIGID)(dig + 1);	// 桁数設定( 列挙型と配列のサイズを一致させるため +1 )
	pDisNum->m_Font = font;

	pDisNum->SetDisplayNumber(num);	// 数字の生成
	pDisNum->SetDisplaypos(pos);	// 数字の位置決め

	return pDisNum;
}

//===========================================================================================================
// 表示する位置の設定
//===========================================================================================================
void CDisplayNumber::SetDisplaypos(D3DXVECTOR3 pos)
{
	//m_pDisplayNum[DIGID_ONE]->SetPos(pos);

	//pos.x -= 60;

	//m_pDisplayNum[DIGID_TEN]->SetPos(pos);

	float size = m_pDisplayNum[0]->GetSize().x * 1.5f;

	for (int i = 0; i < m_MaxDig; i++)
	{
		if (m_pDisplayNum[i] != nullptr)
		{
			m_pDisplayNum[i]->SetPos(pos);
			pos.x -= size;	// 桁ごとに位置をずらす
		}
	}
}
