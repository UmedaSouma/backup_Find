//===========================================================================================================================================================
// 
// コースモデルの処理 [course.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "course.h"
#include "car_player.h"
#include "search.h"

//========================================================================================================================
// コンストラクタ
//========================================================================================================================
CCourse::CCourse() :
	m_Distance(0.0f)
{
}

//========================================================================================================================
// デストラクタ
//========================================================================================================================
CCourse::~CCourse()
{
}

//========================================================================================================================
// 初期設定
//========================================================================================================================
HRESULT CCourse::Init()
{
	//SetModel("data\\MODEL\\stage_00.x");
	SetType(CObject::COURSE);

	CModel::Init();

	return S_OK;
}

//========================================================================================================================
// 終了処理
//========================================================================================================================
void CCourse::Uninit()
{
	CModel::Uninit();
}

//========================================================================================================================
// 更新処理
//========================================================================================================================
void CCourse::Update()
{
	CModel::Update();
}

//========================================================================================================================
// 描画処理
//========================================================================================================================
void CCourse::Draw()
{
	CModel::Draw();

	//D3DXMATRIX mat = GetMatrix();
	//D3DXVECTOR3 pos_ = GetPos();

	//// メッシュに必要な情報
	//CModeldata::ModelData* pModelInfo = nullptr;
	//pModelInfo = GetModelInfo();
	//BOOL pHit = false;
	//FLOAT pDistance = 0.0f;
	//DWORD dwHitIndex = -1;
	//float fHitU;
	//float fHitV;

	//// プレイヤーの情報
	//CCarPlayer* pPlayer = nullptr;
	//pPlayer = CSearch::SearchObject(pPlayer, CObject::CAR_PLAYER);
	//D3DXVECTOR3 move = pPlayer->GetMove();
	//D3DXVECTOR3 pos = pPlayer->GetPos();
	//D3DXVECTOR3 pRay = { 0,1,0 };

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

	//// レイとメッシュが当たったか判定する
	//D3DXIntersect(
	//	pModelInfo->Mesh,		// メッシュの情報
	//	&pos,					// レイの始点
	//	&pRay,					// レイの方向
	//	&pHit,					// 当たったかどうか
	//	&dwHitIndex,			// 当たったメッシュのインデックス
	//	&fHitU,					// 
	//	&fHitV,					// 
	//	&m_Distance,			// レイの始点とメッシュの距離
	//	NULL,					// 
	//	NULL);					// 

	//// 当たっていなかったらここで返す
	//if (pHit != TRUE)
	//{
	//	return;
	//}

	//// 距離が離れていたら押し戻さない
	//if (m_Distance >= 15.0f)
	//{
	//	return;
	//}

	//pPlayer->SetPos({
	//	pPlayer->GetPos().x,
	//	pPlayer->GetPos().y + m_Distance + (0.0f),
	//	pPlayer->GetPos().z
	//	});



	//move.y = 0.0f;

	//pPlayer->SetMove(move);
}

void CCourse::SetCourseNum(int num)
{
	switch (num)
	{
	case COURSE_TITLE:
		SetModel("data\\MODEL\\field_title_000.x");
		break;

	case COURSE_01:
		SetModel("data\\MODEL\\course_021.x");
		break;

	default:
		assert(1);
		break;
	}
}

//========================================================================================================================
// 生成処理
//========================================================================================================================
CCourse* CCourse::Create(int type)
{
	CCourse* pCourse = new CCourse;
	pCourse->SetCourseNum(type);
	pCourse->Init();

	return pCourse;
}