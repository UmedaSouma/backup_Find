//===========================================================================================================================================================
// 
// パラメーターの保管 [param_storage.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "param_storage.h"

CParamStorage::CParamStorage()
{
	for (int n = 0; n < CAR_MAX; n ++ )
	{
		m_Param[n].fWeight = 0.0f;
		m_Param[n].fBending = 0.0f;
		m_Param[n].nMaxGear = 0;
		m_Param[n].nMaxLife = 0;

		for (int i = 0; i < MAX_WORLD_GEAR; i++)
		{
			m_Param[n].fMaxSpeed[i] = 0.0f;
		}
	}
	

	m_type = TYPE::CAR_NORMAL;

}

CParamStorage::~CParamStorage()
{
}

//===========================================================================================================
// パラメーター読み込み処理
//===========================================================================================================
void CParamStorage::Road()
{
	// ファイルオープン
	FILE* pfile = fopen("data\\TEXT\\carparam.txt", "r");
	char aString[256];

	if (pfile == nullptr)
	{
		fclose(pfile);
		return;
	}

	while (1)
	{
		fscanf(pfile, "%s", &aString[0]);
		if (strcmp(&aString[0], "END_SCRIPT") == 0)
		{
			fclose(pfile);
			break;
		}
		else if (strcmp(&aString[0], "SET_PARAM") == 0)
		{
			RoadParamSet(pfile);
		}
	}



	// ファイルクローズ
	fclose(pfile);
}

void CParamStorage::RoadParamSet(FILE*pfile)
{
	char aString[256];
	int nIdx = 0;

	while (1)
	{
		fscanf(pfile, "%s", &aString[0]);
		if (strcmp(&aString[0], "END_PARAM") == 0)
		{
			break;
		}
		else if (strcmp(&aString[0], "SET_CAR") == 0)
		{
			// 車のパラメーターを設定
			RoadCar(pfile, nIdx);
			nIdx++;		// インデックスを進める
		}
	}
}

void CParamStorage::RoadCar(FILE* pfile, int Idx)
{
	char aString[256];

	while (1)
	{
		fscanf(pfile, "%s", &aString[0]);
		if (strcmp(&aString[0], "END_CAR") == 0)
		{
			break;
		}
		else if (strcmp(&aString[0], "WEIGHT") == 0)
		{
			fscanf(pfile, "%s", &aString[0]);
			fscanf(pfile, "%f", &m_Param[Idx].fWeight);
		}
		else if (strcmp(&aString[0], "BENDING") == 0)
		{
			fscanf(pfile, "%s", &aString[0]);
			fscanf(pfile, "%f", &m_Param[Idx].fBending);
		}
		else if (strcmp(&aString[0], "MAXGEAR") == 0)
		{
			fscanf(pfile, "%s", &aString[0]);
			fscanf(pfile, "%d", &m_Param[Idx].nMaxGear);
		}
		else if (strcmp(&aString[0], "MAXLIFE") == 0)
		{
			fscanf(pfile, "%s", &aString[0]);
			fscanf(pfile, "%d", &m_Param[Idx].nMaxLife);
		}
		else if (strcmp(&aString[0], "GEARSPEED") == 0)
		{
			for (int i = 0; i < m_Param[Idx].nMaxGear; i++)
			{
				fscanf(pfile, "%s", &aString[0]);
				fscanf(pfile, "%f", &m_Param[Idx].fMaxSpeed[i]);
			}
		}
	}
}
