//===========================================================================================================================================================
// 
// 車のベース処理 [car.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "car.h"
#include "course.h"
#include "search.h"
#include "manager.h"
#include "param_storage.h"
#include "backlight.h"
#include "collision.h"
#include "calculation.h"
#include "obstacles.h"
#include "countdown.h"
#include "game.h"

#include <tuple>

//========================================================================================================================
// コンストラクタ
//========================================================================================================================
CCar::CCar()
{
	m_type = CParamStorage::CAR_NORMAL;

	m_fOldSpeed = 0.0f;
	m_Action = NONE;

	m_CurrParam.nGear = 0;
	m_CurrParam.Speed = 0.0f;
	m_CurrParam.nLife = m_Param.nMaxLife;

	m_fMoveAngle = 0.0f;
	m_nTurboInterval = 0;

	m_pSphere = nullptr;

	m_nDeathCount = 0;
	m_bDeath = false;

	m_fDriftTargetRot = 0.0f;

	m_oldrot = { 0.0f,0.0f,0.0f };

	m_bDisDraw = false;

	m_ForwardInfo.Force = 0.0f;
	m_ForwardInfo.Angle = 0.0f;

	m_IsDrift = false;
	m_ChargeTime = 0;

	m_nDownCount = 0;
}

//========================================================================================================================
// デストラクタ
//========================================================================================================================
CCar::~CCar()
{
}

//========================================================================================================================
// 初期設定
//========================================================================================================================
HRESULT CCar::Init()
{
	PramSet();
	m_pSphere = CSphere::Create();

	CActor::Init();

	return S_OK;
}

//========================================================================================================================
// 終了処理
//========================================================================================================================
void CCar::Uninit()
{
	CActor::Uninit();
}

//========================================================================================================================
// 更新処理
//========================================================================================================================
void CCar::Update()
{
	CCountdown* pCD = CGame::GetCountDown();
	if (pCD != nullptr)
	{
		if (pCD->GetUse())
		{
			return;
		}
	}

	ActionUpdate();

	if (m_CurrParam.Speed<=0.0f)
	{
		m_Action = NONE;
	}

	// ターボ時のカメラ挙動
	TarboCamera();
	// ターボ間隔のカウントをディクリメント
	m_nTurboInterval--;

	// 角度
	m_fMoveAngle = atan2f(GetMove().z, GetMove().x);

	D3DXVECTOR3 pos = GetPos();		// 位置
	D3DXVECTOR3 move = GetMove();	// 移動値
	D3DXVECTOR3 rot = GetRot();		// 向き
	m_oldrot = rot;


	// 表示上のスピード設定
	ViewSetting();
	
	// 速度が過去の速度より上がっていなかったら
	if (m_fOldSpeed >= m_CurrParam.Speed)
	{// だんだん減速する
		move.x += -1 * ( move.x * 0.01f);
		move.z += -1 * ( move.z * 0.01f);
	}

	// 位置を設定
	pos.y += move.y;

	if (m_Action != CCar::DRIFTR || m_Action != CCar::DRIFTL)
	{
		pos.x += sinf(GetRot().y) * move.x;
		pos.z += cosf(GetRot().y) * move.z;
	}
	
	SetPos(pos);

	if (m_CurrParam.Speed > m_Param.fMaxSpeed[m_CurrParam.nGear] + 10.0f)
	{
		//バックライト点灯
		CBackLight::Create(pos, rot, 100, false);	// 左ライト
		CBackLight::Create(pos, rot, 100, true);	// 右ライト
	}

	// 移動値を保存
	m_oldmove = move;

	SetRot(rot);

	// 移動値を設定
	SetMove(move);

	HitObstacle();

	DrawDistance();

	CActor::Update();

	if(m_bDeath)
	{
		m_nDeathCount++;
	}

	if (m_nDeathCount >= 600)
	{
		Uninit();
	}
	else if(GetPos().y<=-15000.0f)
	{
		Uninit();
	}
}

//========================================================================================================================
// 描画処理
//========================================================================================================================
void CCar::Draw()
{
	MeshCollision(FRONT_LEFT);
	MeshCollision(FRONT_RIGHT);
	MeshCollision(BACK_LEFT);
	MeshCollision(BACK_RIGHT);

	if (m_bDisDraw == false) 
	{ return; }

	CActor::Draw();
}

//===========================================================================================================
// タイプごとの初期設定
//===========================================================================================================
void CCar::InitType(CParamStorage::TYPE type)
{
	switch (type)
	{
	case CParamStorage::CAR_NORMAL:
		SetModel("data\\model\\car_normal_005.x");	// モデルを設定
		break;

	case CParamStorage::CAR_TRACK:
		SetModel("data\\model\\car_normal_001.x");	// モデルを設定
		break;

	case CParamStorage::CAR_SPORTS:
		SetModel("data\\model\\car_sample.x");	// モデルを設定
		break;

	case CParamStorage::CAR_BOMB:
		SetModel("data\\model\\car_bomb_000.x");	// モデルを設定
		break;

	default:
		break;
	}

	if (m_type == type)
	{
		return;
	}

	// タイプを設定する
	m_type = type;

	PramSet();
}

//===========================================================================================================
// パラメーターの設定
//===========================================================================================================
void CCar::PramSet()
{
	// パラメーターストレージクラスを持ってくる
	CParamStorage* pParamStorage = CManager::GetParamStrage();

	if (pParamStorage == nullptr)
	{ return; }

	// タイプを持ってくる
	int type = GetTypeCar();

	// パラメーターの設定
	m_Param.fWeight = pParamStorage->GetWeight(type);
	m_Param.nMaxGear = pParamStorage->GetGearMax(type);
	m_Param.fBending = pParamStorage->GetBending(type);
	m_Param.nMaxLife = pParamStorage->GetMaxLife(type);

	for (int i = 0; i < m_Param.nMaxGear; i++)
	{// スピードの設定
		m_Param.fMaxSpeed[i] = pParamStorage->GetfMaxSpeed(type, i);
	}
}

//===========================================================================================================
// ターボ時のカメラ挙動
//===========================================================================================================
void CCar::TarboCamera()
{
	CCamera* pCamera = CManager::GetCamera();	// camera を持ってくる
	
	if (m_nTurboInterval == 90)
	{// インターバルのカウントが始まったら
		pCamera->SetFollow(0.001f);
	}
	else if (pCamera->GetFollow() >= 1.0f)
	{// カメラが車に追いついたら
	}
	else
	{// そのほか

		// カメラ遅延を持ってくる
		float follow = pCamera->GetFollow();
		
		// 一段目で差を求めて、その差を指定のフレーム数で分割する
		float f = 1.0f - 0.1f;
		f /= 5000;

		// 
		pCamera->SetFollow(follow + f);
	}

}

//===========================================================================================================
// 障害物と当たるまでの処理
//===========================================================================================================
void CCar::HitObstacle()
{
	std::vector<CObstacle*>pObs;
	pObs.clear();

	pObs = CSearch::SearchMultiObject(pObs, OBSTACLE);
	if (pObs.empty()) 
	{ return; }

	unsigned int nSize = pObs.size();
	for (unsigned int i = 0; i < nSize; i++)
	{
		D3DXVECTOR3 obspos = pObs[i]->GetPos();
		float obsrange = pObs[i]->GetSize().x;
		D3DXVECTOR3 carpos = GetPos();
		float carrange = GetSize().z;

		if (CCollision::CircleTrigger(carpos, carrange, obspos, obsrange))
		{
			pObs[i]->HitMovement(this);
		}
	}
}

//===========================================================================================================
// カメラとの距離を測る
//===========================================================================================================
void CCar::DrawDistance()
{
	// カメラを持ってくる
	CCamera* pCamera = CManager::GetCamera();
	if (pCamera == nullptr)
	{
		return;
	}

	// カメラと車の距離を計算する
	float dis = CCalculation::TwoPointDistance(pCamera->GetPos(), GetPos());

	if (dis > 5000.0f)
	{// 距離が遠かったら
		m_bDisDraw = false;	// 映さない
	}
	else
	{// 近かったら
		m_bDisDraw = true;
	}
}

//===========================================================================================================
// 表示上のスピード設定
//===========================================================================================================
void CCar::ViewSetting()
{
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 copymove = GetMove();				// 移動値のコピー
	D3DXVECTOR3 normalize = { 1.0f,1.0f,1.0f };		// 正規化の変数


	// 表示上の数値を整数にする
	if (move.x < 0.0f)
	{
		normalize.x = -1;
	}
	if (move.z < 0.0f)
	{
		normalize.z = -1;
	}

	copymove.x = copymove.x * normalize.x;
	copymove.z = copymove.z * normalize.z;

	// 見た目のスピード
	m_CurrParam.Speed = sqrtf(copymove.x * copymove.x + copymove.z * copymove.z);

	// 表示上のスピードを保存
	m_fOldSpeed = m_CurrParam.Speed;
}

//===========================================================================================================
// アクセル処理
//===========================================================================================================
void CCar::ActionAccele()
{
	D3DXVECTOR3 move = GetMove();

	// 今の一個前のギアを設定
	int PreGear = m_CurrParam.nGear - 2;

	// 前のギアが 0 未満になってしまったら
	if (PreGear < 0) 
	{ PreGear = 0; }	// ギアを 0 に設定

	if (m_CurrParam.Speed < m_Param.fMaxSpeed[m_CurrParam.nGear])
	{// 現在のスピードが最大スピードに追いついていなかったら
		move.x += m_Param.fMaxSpeed[PreGear] * 0.025f;
		move.z += m_Param.fMaxSpeed[PreGear] * 0.025f;
	}

	//SetMove({ move.x,0.0f,move.z });
	SetMove(move);

	m_Action = ACCELE;
}

//===========================================================================================================
// ブレーキ処理
//===========================================================================================================
void CCar::ActionBrake()
{
	D3DXVECTOR3 move = GetMove();

	if (m_CurrParam.Speed < m_Param.fMaxSpeed[m_CurrParam.nGear] * 0.5f)
	{
		move.x += m_Param.fMaxSpeed[0] *-0.0125f;
		move.z += m_Param.fMaxSpeed[0] *-0.0125f;
	}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
	m_CurrParam.Speed += -0.1f;

	//SetMove({ move.x,0.0f,move.z });
	SetMove(move);

	m_Action = BRAKE;
}

//===========================================================================================================
// メッシュの地面との当たり判定
//===========================================================================================================
void CCar::MeshCollision(START_POINT point)
{
	CCourse* pCourse = nullptr;
	pCourse = CSearch::SearchObject(pCourse, CObject::COURSE);

	if (pCourse == nullptr)
	{	return;	}

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

	switch (point)
	{
	case CENTER:
		break;

	case FRONT_LEFT:
		Ssize = 10.0f;
		FBsize = 30.0f;
		break;

	case FRONT_RIGHT:
		Ssize = -10.0f;
		FBsize = 30.0f;
		break;

	case BACK_RIGHT:
		Ssize = -10.0f;
		FBsize = -30.0f;
		break;

	case BACK_LEFT:
		Ssize = 10.0f;
		FBsize = -30.0f;
		break;
	}

	// 位置をずらす
	pos = CCalculation::ShiftPosition(
		pos, 
		GetRot(), 
		{ Ssize,FBsize }, 
		CCalculation::ROT_Y);

	if (m_pSphere != nullptr)
	{
		m_pSphere->SetPos(pos);
	}

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
	{	return;	}

	// 距離が離れていたら押し戻さない
	if (Dis >= 30.0f)
	{	return;	}

	SetPos({
		GetPos().x,
		GetPos().y + Dis + (0.0f),
		GetPos().z
		});

	move.y = 0.0f;

	SetMove(move);
}

//===========================================================================================================
// カーブ処理
//===========================================================================================================
float CCar::ActionBend()
{
	float fAddRot = 0.0f;	// 加える回転量

	bool bFront = false;

	if (m_fMoveAngle > 0.0f)
	{// 進んでる方向が前の時
		bFront = true;
	}

	switch (bFront)
	{// 車のスピードと乗算することによって速度が落ちたときに曲がれないようにする
	case true:
		fAddRot += 0.005f * m_CurrParam.Speed;
		break;

	case false:
		fAddRot += -0.005f * m_CurrParam.Speed;
		break;
	}

	// 回転しすぎないように制御
	if (fAddRot > m_Param.fBending)
	{
		fAddRot = m_Param.fBending;
	}
	else if (fAddRot < -m_Param.fBending)
	{
		fAddRot = -m_Param.fBending;
	}

	if (fAddRot > m_Param.fBending)
	{// 加算角度がパラメーターの数値を超えてしまった時
		return m_Param.fBending;	// 最大の値を返す
	}

	return fAddRot;
}

//===========================================================================================================
// カーブ処理　右
//===========================================================================================================
void CCar::ActionBend_R()
{	
	D3DXVECTOR3 rot = GetRot();
	float fAddRot = 0.0f;	// 加える回転量

	// 加算する回転量を取得
	fAddRot = ActionBend();

	// ここで車に加える
	rot.y += fAddRot;

	SetRot(rot);
}

//===========================================================================================================
// カーブ処理　左
//===========================================================================================================
void CCar::ActionBend_L()
{
	D3DXVECTOR3 rot = GetRot();
	float fAddRot = 0.0f;	// 加える回転量

	// 加算する回転量を取得
	fAddRot = ActionBend();
	// 反対方向にする
	fAddRot *= -1;

	// ここで車に加える
	rot.y += fAddRot;

	SetRot(rot);
}

//===========================================================================================================
// ターボ処理
//===========================================================================================================
void CCar::ActionTurbo()
{
	if (m_nTurboInterval > 0)
	{
		return;
	}

	D3DXVECTOR3 move = GetMove();
	m_CurrParam.nGear++;

	if (m_Param.nMaxGear <= m_CurrParam.nGear)
	{// ギアが最大以上だったとき
		m_CurrParam.nGear = m_Param.nMaxGear - 1;
	}

	move.x = m_Param.fMaxSpeed[m_CurrParam.nGear] + 5.0f;
	move.z = m_Param.fMaxSpeed[m_CurrParam.nGear] + 5.0f;

	SetMove(move);

	m_nTurboInterval = 90;
}

//===========================================================================================================
// 突進
//===========================================================================================================
void CCar::ActionAttack()
{
	// 移動値取得
	D3DXVECTOR3 move = GetMove();

	// 最大スピードにさらに速度を足す
	move.x = m_Param.fMaxSpeed[m_CurrParam.nGear] + 15.0f;
	move.z = m_Param.fMaxSpeed[m_CurrParam.nGear] + 15.0f;

	// 移動値を反映
	SetMove(move);
	
	//m_nTurboInterval = 90;
}

//===========================================================================================================
// 衰退
//===========================================================================================================
void CCar::ActionDown()
{
	if (m_Action == DOWN) 
	{ return; }

	//D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 move = { 0.0001f,0.0f,0.0001f };
	move *= 0.001f;
	SetMove(move);

	CCamera* pCamera = CManager::GetCamera();	// camera を持ってくる
	pCamera->SetCameraTarget(CCamera::CAMERA_TARGET_TYPE::NONE);

	m_Action = DOWN;
}

//===========================================================================================================
// ドリフト
//===========================================================================================================
void CCar::ActionDrift()
{
	if (m_Action == DRIFTR || m_Action == DRIFTL)
	{ return; }

	D3DXVECTOR3 rot = GetRot();

	if (rot.y < m_oldrot.y)
	{
		m_Action = DRIFTL;
	}
	else if(rot.y > m_oldrot.y)
	{
		m_Action = DRIFTR;
	}
}

//===========================================================================================================
// 右ドリフト
//===========================================================================================================
void CCar::ActionDriftR()
{
#include <cmath>

	

	{
		//float addrot = 0.1f;

		//m_fDriftTargetRot += addrot;
		//D3DXVECTOR3 rot = GetRot();
		//rot.y += addrot;

		//if (m_fDriftTargetRot <= 1.0f)
		//{
		//	SetRot(rot);
		//}
		//else
		//{
		//	m_fDriftTargetRot = 0.0f;
		//}

		//m_Action = CCar::NONE;
	}
	
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();

	// 今の一個前のギアを設定
	int PreGear = m_CurrParam.nGear - 2;

	// 前のギアが 0 未満になってしまったら
	if (PreGear < 0)
	{
		PreGear = 0;
	}	// ギアを 0 に設定

	if (m_CurrParam.Speed < m_Param.fMaxSpeed[m_CurrParam.nGear])
	{// 現在のスピードが最大スピードに追いついていなかったら
		move.x = m_ForwardInfo.Force;
		move.z = m_ForwardInfo.Force;
	}

	// 位置を設定
	pos.y += move.y;

	pos.x += sinf((m_ForwardInfo.Angle + GetRot().y) / 2) * move.x;
	pos.z += cosf((m_ForwardInfo.Angle + GetRot().y) / 2) * move.z;

	SetPos(pos);
	
}

//===========================================================================================================
// 左ドリフト
//===========================================================================================================
void CCar::ActionDriftL()
{
}

//===========================================================================================================
// アクション毎の更新処理
//===========================================================================================================
void CCar::ActionUpdate()
{
	switch (m_Action)
	{
	case DOWN:
		AUdown();
		break;

	case DRIFTR:
		ActionDriftR();
		break;

	case DRIFTL:
		ActionDriftL();
		break;
	}
}

//===========================================================================================================
// ダウン時の更新
//===========================================================================================================
void CCar::AUdown()
{
	CCamera* pCamera = CManager::GetCamera();	// camera を持ってくる
	m_nDownCount++;
	int nDTime = 84;	// ダウン時間

	// =============================================================================-
	// memo : なぜか move値 をそのまま0にするとカメラが追尾しなくなる
	// =============================================================================-
	D3DXVECTOR3 move = { 0.0001f,0.0f,0.0001f };
	move *= 0.001f;
	SetMove(move);

	// rot を取得
	D3DXVECTOR3 rot = GetRot();

	rot.y += 0.3f;
	SetRot(rot);

	if (m_nDownCount >= nDTime)
	{// 設定した時間より大きくなったら
		m_nDownCount = 0;	// カウントをリセット
		m_Action = NONE;	// アクションをリセット
		pCamera->SetCameraTarget(CCamera::CAMERA_TARGET_TYPE::PLAYER);	// カメラのターゲットをプレイヤーにする
	}
}

void CCar::StartDrift()
{
	
}

//========================================================================================================================
// 生成処理
//========================================================================================================================
CCar* CCar::Create()
{
	CCar* pCar = new CCar;

	pCar->Init();

	return pCar;
}