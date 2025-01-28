//===========================================================================================================================================================
// 
// モデルの管理
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "model.h"
#include "manager.h"
#include "calculation.h"
#include "course.h"
#include "collision.h"
#include "search.h"


//===================================================================================
// コンストラクタ
//===================================================================================
CModel::CModel(int nPriority) :CObject3D(nPriority)
, m_Direction(0)
, m_nIdx(-1)
, m_bMat(false)
, m_Diffuse{}
, m_pModelAddress{}
, m_apTexture{}
, m_targetrot({0.0f ,0.0f,0.0f })
{
	m_ModelInfo = {};

	for (int n = 0; n < 1024; n++)
	{
		m_vtxpos[n] = { 0.0f,0.0f,0.0f };
	}
}

//===================================================================================
// デストラクタ
//===================================================================================
CModel::~CModel()
{
}

//===================================================================================
// 初期設定
//===================================================================================
HRESULT CModel::Init()
{
	UpdateMatrix();

	//int nNumVtx = 0;	// 頂点数
	//DWORD sizeFVF;	// 頂点フォーマットのサイズ
	//BYTE* pVtxBuff;	// 頂点バッファのポインタ

	//// 頂点数の取得
	//nNumVtx = m_ModelInfo.Mesh->GetNumVertices();
	//// 
	//sizeFVF = D3DXGetFVFVertexSize(m_ModelInfo.Mesh->GetFVF());
	//// 
	//m_ModelInfo.Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	//for (int nvtx = 0; nvtx < nNumVtx; nvtx++)
	//{
	//	// 頂点座標の代入
	//	D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

	//	// 頂点座標を比較して[最大値・最小値]を取得

	//	m_vtxpos[nvtx] = vtx;

	//	// 頂点フォーマットのサイズ分ポインタを進める
	//	pVtxBuff += sizeFVF;
	//}

	return S_OK;
}

//===================================================================================
// 終了処理
//===================================================================================
void CModel::Uninit()
{
	Release();
}

//===================================================================================
// 更新処理
//===================================================================================
void CModel::Update()
{
	// オブジェクト3Dの更新
	CObject3D::Update();	// ここでマトリックスの設定をしている

	FixRot();
}

//===================================================================================
// 描画処理
//===================================================================================
void CModel::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DMATERIAL9 matDef;			// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;				// マテリアルデータのポインタ

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &GetMatrix());

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	if (m_ModelInfo.BuffMat != nullptr
		&& m_ModelInfo.Mesh != nullptr
		&& m_ModelInfo.NumMat != 0)
	{
		// マテリアルデータのポインタの取得
		pMat = (D3DXMATERIAL*)m_ModelInfo.BuffMat->GetBufferPointer();
		CModeldata* pModeldata = CManager::GetModeldata();	// Modeldata のポインタを持ってくる

		SetModelTex(pMat);

		if (pModeldata)
		{
			for (int nCntMat = 0; nCntMat < (int)m_ModelInfo.NumMat; nCntMat++)
			{
				if (m_bMat)
				{// ダメージを受けたとき
					pMat[nCntMat].MatD3D.Diffuse = { 1.0f,0.0f,0.0f,0.5f };	// 赤くする
				}
				else
				{// そのほかの状態の時

					//if (CScene::GetMode() != CScene::MODE_EDITOR)
					{
						pMat[nCntMat].MatD3D.Diffuse = *pModeldata->GetMatData(m_pModelAddress, nCntMat);	// 通常色にする
					}

				}

				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, m_apTexture[nCntMat]);

				// モデルパーツの描画
				m_ModelInfo.Mesh->DrawSubset(nCntMat);
			}
		}
	
	}

	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//===========================================================================================================
// 角度を修正する
//===========================================================================================================
void CModel::FixRot()
{
	if (GetRot().x >= D3DX_PI*2 ||  GetRot().x <= -D3DX_PI*2)
	{
		SetRot({ 0.0f,GetRot().y,GetRot().z });
	}
	if (GetRot().y >= D3DX_PI * 2 || GetRot().y <= -D3DX_PI * 2)
	{
		SetRot({ GetRot().x,0.0f,GetRot().z });
	}
	if (GetRot().z >= D3DX_PI * 2 ||  GetRot().z <= -D3DX_PI * 2)
	{
		SetRot({ GetRot().x,GetRot().y,0.0f });
	}
}

//===================================================================================
// 生成処理
//===================================================================================
CModel* CModel::Create(D3DXVECTOR3 pos)
{
	CModel* pModel = new CModel;

	pModel->SetPos(pos);
	pModel->SetType(TYPE::MODEL);

	pModel->Init();

	return pModel;
}

//===================================================================================
// モデルの情報をセットする
//===================================================================================
void CModel::BindModel(CModeldata::ModelData *modelinfo)
{
	m_ModelInfo.Mesh = modelinfo->Mesh;
	m_ModelInfo.BuffMat = modelinfo->BuffMat;
	m_ModelInfo.NumMat = modelinfo->NumMat;
}

//===========================================================================================================
// 向きを徐々にターゲットに向ける
//===========================================================================================================
void CModel::UpdateTargetRot()
{
	D3DXVECTOR3 rot = GetRot();
}

//===========================================================================================================
// 向きを設定
//===========================================================================================================
void CModel::SetDirection(DIRECTION dire)
{
	switch (dire)
	{
	case DIRECTION_LEFT:
		m_Direction = -1;
		SetRot({
			0.0f
			,D3DX_PI * 0.5f
			,0.0f
			});
		break;

	case DIRECTION_RIGHT:
		m_Direction = 1;
		SetRot({
			0.0f
			,D3DX_PI * -0.5f
			,0.0f
			});
		break;

	default:
		break;
	}
}

//===========================================================================================================
// 向きを取得
//===========================================================================================================
int CModel::GetDirection()
{
	return m_Direction;
}

//===========================================================================================================
// モデルの見た目設定
//===========================================================================================================
void CModel::SetModel(const char* address)
{
	CModeldata* pModeldata = nullptr;
	int nIdx = 0;

	SetModelAddress(address);		// アドレスを保存しておく
	pModeldata = CManager::GetModeldata();
	nIdx = pModeldata->Regist(address);
	BindModel(pModeldata->GetAddress(nIdx));
}

//===========================================================================================================
// モデルのテクスチャ設定
//===========================================================================================================
void CModel::SetModelTex(D3DXMATERIAL* pMat)
{
	if (pMat != nullptr)
	{
		for (int nCntMat = 0; nCntMat < (int)m_ModelInfo.NumMat; nCntMat++)
		{
			int nTexIdx = 0;
			CTexture* pTex = CManager::GetTexture();
			m_TexIdx[nCntMat] = pTex->Regist(pMat[nCntMat].pTextureFilename);
			BindModelTex(pTex->GetAddress(m_TexIdx[nCntMat]),nCntMat);
		}
	}
}

void CModel::MeshColl()
{
	CCourse* pCourse = nullptr;
	pCourse = CSearch::SearchObject(pCourse, CObject::COURSE);

	if (pCourse == nullptr)
	{
		return;
	}

	// メッシュに必要な情報
	CModeldata::ModelData* pModelInfo = nullptr;	// モデル情報を格納する変数
	pModelInfo = pCourse->GetModelInfo();			// モデル情報取得
	BOOL pHit = false;		// 当たったかどうか判定する変数
	float Dis = 0.0f;		// メッシュとの距離を格納する変数

	// プレイヤーの情報
	D3DXVECTOR3 move = GetMove();	// 移動値を格納する変数
	D3DXVECTOR3 pRay = { 0,1,0 };	// レイを出す方向

	// 位置を設定するための情報
	D3DXVECTOR3 pos = GetPos();	// 原点
	float Ssize = 0.0f, FBsize = 0.0f;	// 原点からどれだけずらすか ( S = サイド / FB = フロントバック )

	// メッシュ地面との当たり判定
	std::tie(pHit, Dis)
		= CCollision::MeshCollision(
			pModelInfo->Mesh,
			pRay,
			pos);

	// 頂点情報を利用してどの頂点の上にいるか判定
	{
		//LPDIRECT3DVERTEXBUFFER9* vtxbuff = nullptr;
		//pModelInfo->Mesh->GetVertexBuffer(vtxbuff);
		//VERTEX_3D* pVtx;

		//// 頂点数取得
		//DWORD dwNumVtx = pModelInfo->Mesh->GetNumVertices();
		//D3DXMATRIX mtx = GetMatrix();

		//// バッファロック
		//pModelInfo->Mesh->LockVertexBuffer(0, (void**)&pVtx);

		////for (unsigned int i = 0; i < 1; i++)
		////{
		////	pVtx[i].pos +=D3DXVECTOR3(mtx._41, mtx._42, mtx._43);
		////}

		//pModelInfo->Mesh->UnlockVertexBuffer();
	}

	// 当たっていなかったらここで返す
	if (pHit != TRUE)
	{
		return;
	}

	// 距離が離れていたら押し戻さない
	if (Dis >= 30.0f)
	{
		return;
	}

	SetPos({
		pos.x,
		pos.y + Dis + (0.0f),
		pos.z
		});

	move.y = 0.0f;

	SetMove(move);
}
