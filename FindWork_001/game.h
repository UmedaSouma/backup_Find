//===========================================================================================================================================================
// 
// game.cpp�̃w�b�_�[
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "main.h"
#include "scene.h"
#include "param_storage.h"
#include "player_manager.h"
#include "countdown.h"
#include "timer.h"

class CGame :public CScene
{
public:
	CGame();
	~CGame()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void Load();	// �ǂݍ���
	void LoadObs();	// �ǂݍ���
	void LoadInfo(FILE* pfile);	// �|�C���g���̓ǂݍ���
	void LoadObsInfo(FILE* pfile);	// �|�C���g���̓ǂݍ���
	void SetInitUI();	// ui�̃Z�b�g

	static CCountdown* GetCountDown() { return m_pCountDown; }
private:
	static int m_nDelayEnd;	// �|���Ă��烊�U���g�ɂȂ�܂�
	static bool m_Delay;
	static CTimer* m_timer;	// �^�C�}�[�̃|�C���^

public:
	static CParamStorage* m_pParamStorage;
	static CPlayerManager* m_pPlayerManager;
	static CCountdown* m_pCountDown;
};