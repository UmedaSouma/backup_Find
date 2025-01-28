//===========================================================================================================================================================
// 
// テクスチャ管理処理
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "texture.h"
#include "manager.h"

int CTexture::m_NumAll = 0;
//==================================================================================================
// コンストラクタ
//==================================================================================================
CTexture::CTexture()
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		m_pTexture[nCnt] = {};
		m_pTexStorage[nCnt] = {};
	}
}

//==================================================================================================
// デストラクタ
//==================================================================================================
CTexture::~CTexture()
{
}

//==================================================================================================
// 破棄
//==================================================================================================
void CTexture::Unload()
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		if (m_pTexture[nCnt] != nullptr)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		if (m_pTexStorage[nCnt] != nullptr)
		{
			m_pTexStorage[nCnt] = nullptr;
		}
	}
}

//==================================================================================================
// テクスチャ登録
//==================================================================================================
int CTexture::Regist(const char* pTexturename)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	int nIdx = 0;

	// テクスチャが設定されていなかったら
	if (pTexturename == nullptr) 
	{ return -1; }		// 何も設定されていないという -1 を設定する

	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		if (m_pTexture[nCntTex] == nullptr && m_pTexStorage[nCntTex] == nullptr)
		{// テクスチャが設定されていなかったら
			if (SUCCEEDED(D3DXCreateTextureFromFile(pDevice, pTexturename, &m_pTexture[nCntTex])))	// テクスチャ作成
			{
				m_pTexStorage[nCntTex] = pTexturename;	// テクスチャネームを保管
				nIdx = nCntTex;	// IDを設定
				m_NumAll++;		// 総数増加

				break;

			}
			else
			{// テクスチャがデータに存在していない
				assert(false && "テクスチャが存在してないよ！！");
			}
		}
		else if(!strcmp(pTexturename, m_pTexStorage[nCntTex]))
		{// 
			nIdx = nCntTex;	// IDを設定

			break;
		}
	}

	return nIdx;
}

//==================================================================================================
// テクスチャのアドレス取得
//==================================================================================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int Idx)
{
	if (Idx == -1)
	{// -1は nullptr で返す
		return nullptr;
	}

	return m_pTexture[Idx];
}