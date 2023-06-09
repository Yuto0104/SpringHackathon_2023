//=============================================================================
//
// Q[NX(game.cpp)
// Author : úąl
// Tv : Q[NXĖĮđs¤
//
//=============================================================================

//*****************************************************************************
// CN[h
//*****************************************************************************
#include <assert.h>

#include "game.h"
#include "calculation.h"
#include "keyboard.h"
#include "mouse.h"
#include "application.h"
#include "renderer.h"
#include "object.h"
#include "bg.h"
#include "debug_proc.h"
#include "score.h"
#include "time.h"
#include "camera.h"
#include "enemy.h"
#include "mesh.h"
#include "sound.h"
#include "player.h"
#include "mine.h"
#include "pause.h"
#include "calculation.h"
#include "select_item.h"
#include "lille.h"
#include "life.h"

//*****************************************************************************
// ÃIoĪéž
//*****************************************************************************
CScore *CGame::m_pScore = nullptr;						// XRACX^X
CTime *CGame::m_pTime = nullptr;						// ^C
CEnemy *CGame::m_pEnemy = nullptr;						// Gl~[
CPlayer *CGame::m_pPlayer = nullptr;					// vC[
CLille *CGame::m_pLille = nullptr;						// [
D3DXCOLOR CGame::fogColor;								// tHOJ[
float CGame::fFogStartPos;								// tHOĖJn_
float CGame::fFogEndPos;								// tHOĖIš_
float CGame::fFogDensity;								// tHOĖ§x
bool CGame::m_bGame = false;							// Q[Ėķĩ

//=============================================================================
// RXgN^
// Author : úąl
// Tv : CX^XļŦÉs¤
//=============================================================================
CGame::CGame()
{

}

//=============================================================================
// fXgN^
// Author : úąl
// Tv : CX^XIšÉs¤
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// úģ
// Author : úąl
// Tv : ¸_obt@đļŦĩAoĪĖúlđŨč
//=============================================================================
HRESULT CGame::Init()
{// }EXĖæž
	CMouse *pMouse = CApplication::GetMouse();

	// foCXĖæž
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//SE
	CApplication::GetSound()->Play(CSound::SOUND_LABEL_BGM_BGM001);

	// dÍĖlđŨč
	CCalculation::SetGravity(0.2f);

	// XRA
	m_pScore = CScore::Create(10, false);
	m_pScore->SetScore(0);
	m_pScore->SetPos(D3DXVECTOR3(1280.0f, m_pScore->GetSize().y / 2.0f, 0.0f));

	// ^C
	m_pTime = CTime::Create(3);
	m_pTime->SetTime(120);
	m_pTime->SetTimeAdd(false);
	m_pTime->SetPos(D3DXVECTOR3(640.0f, m_pTime->GetSize().y / 2.0f, 0.0f));

	// HP
	CLife::Create(4);

	// vC[ļŦ
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f));

	// JĖĮ]Ũč(ÚW : vC[)
	CCamera *pCamera = CApplication::GetCamera();
	pCamera->SetViewType(CCamera::TYPE_PARALLEL);
	pCamera->SetFollowTarget(m_pPlayer, 1.0);
	pCamera->SetPosVOffset(D3DXVECTOR3(0.0f, 0.0f, -1600.0f));
	pCamera->SetPosROffset(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pCamera->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pCamera->SetUseRoll(false, false);

	// bVĖŨu
	CMesh3D *pMesh = CMesh3D::Create();
	assert(pMesh != nullptr);
	pMesh->SetPos(D3DXVECTOR3(0.0f, 0.0f, 1000.0f));
	pMesh->SetRot(D3DXVECTOR3(D3DX_PI * -0.5f, 0.0f, 0.0f));
	pMesh->SetSize(D3DXVECTOR3(10000.0f, 0.0f, 10000.0f));
	pMesh->LoadTex(2);
	pMesh->SetBlock(CMesh3D::DOUBLE_INT(30, 30));
	pMesh->SetSplitTex(true);
	//pMesh->SetScrollTex(move, bScrollTex);
	//pMesh->SetUseCollison(bCollison);

	// n
	CMine::Create(D3DXVECTOR3(100.0f, 50.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f),10);
	CMine::Create(D3DXVECTOR3(200.0f, 50.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f),1);
	CMine::Create(D3DXVECTOR3(300.0f, 50.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f),2);

	// Gl~[
	m_pEnemy = CEnemy::Create(D3DXVECTOR3(100.0f,0.0f,0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f),2);

	// }EXJ[\đÁˇ
	pMouse->SetShowCursor(false);

	// tHOĖlŨč
	fogColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// tHOJ[
	fFogStartPos = 1.0f;								// tHOĖJn_
	fFogEndPos = 100000.0f;								// tHOĖIš_
	fFogDensity = 0.00001f;								// tHOĖ§x

	// tHOĖLøŨč
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	// tHOJ[ĖŨč
	pDevice->SetRenderState(D3DRS_FOGCOLOR, fogColor);

	// tHOĖÍÍŨč
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&fFogStartPos));
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&fFogEndPos));

	// tHOĖ§xĖŨč
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&fFogDensity));

	//úģ
	m_bGame = true;
	m_nSpawnTime = 0;
	m_bSelectItem = true;
	m_bSelectItem2 = true;

	return S_OK;
}

//=============================================================================
// Iš
// Author : úąl
// Tv : eNX`Ė|C^Æ¸_obt@Ėđú
//=============================================================================
void CGame::Uninit()
{// }EXĖæž
	CMouse *pMouse = CApplication::GetMouse();

	// foCXĖæž
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// TEhîņĖæž
	CSound *pSound = CApplication::GetSound();

	// TEhIš
	pSound->Stop();

	CCamera *pCamera = CApplication::GetCamera();
	pCamera->SetFollowTarget(false);

	// tHOĖLøŨč
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	// }EXJ[\đoˇ
	pMouse->SetShowCursor(true);

	// XRAĖđú
	Release();
}

//=============================================================================
// XV
// Author : úąl
// Tv : XVđs¤
//=============================================================================
void CGame::Update()
{
	// L[{[hĖæž
	CKeyboard *pKeyboard = CApplication::GetKeyboard();
	CCamera *pCamera = CApplication::GetCamera();
	CPause *pPause = CApplication::GetPause();
	CSelectItem *pSelect = CApplication::GetSelectItem();

	if (pKeyboard->GetPress(DIK_LSHIFT))
	{
		pCamera->Zoom();
	}

	if (!pPause->GetPause()
		&& pKeyboard->GetTrigger(DIK_P))
	{
		pPause->SetPause(true, true);
	}
	else if (pPause->GetPause()
		&& pKeyboard->GetTrigger(DIK_P))
	{
		pPause->SetPause(false, false);
	}

	if (m_pTime->GetTime() == 100)
	{
		if (m_bSelectItem)
		{
			pSelect->SetPause(true, true);
			m_bSelectItem = false;
		}
	}

	if (m_pTime->GetTime() == 80)
	{
		if (m_bSelectItem2)
		{
			pSelect->SetPause(true, true);
			m_bSelectItem2 = false;
		}
	}

	if (m_pTime->GetTime() == 50)
	{
		if (m_bSelectItem3)
		{
			pSelect->SetPause(true, true);
			m_bSelectItem3 = false;
		}
	}

	if (m_nSpawnTime < 60
		&& !pSelect->GetPause())
	{//X|[ÔĒęčČēČįÁZˇé
		m_nSpawnTime++;
	}
	else if (m_nSpawnTime >= 60)
	{//ęčČãČįX|[ŗšÄ0Éˇé
		EnemySpawn();
		m_nSpawnTime = 0;
	}

	// Ct0ČēžÆ
	if (m_pPlayer != nullptr)
	{
		if (m_pPlayer->GetLife() <= 0)
		{// UgÖ
			CApplication::SetNextMode(CApplication::MODE_RESULT);
			// Iš
			m_pPlayer->Uninit();
			//vC[Ė|C^đúģ
			m_pPlayer = nullptr;
			CCamera *pCamera = CApplication::GetCamera();
			pCamera->SetFollowTarget(false);

			return;
		}
	}

	if (m_pTime->GetTimeEnd()
		&& m_bGame)
	{
		m_bGame = false;

		// JĖĮ]Ũč
		pCamera = CApplication::GetCamera();
		pCamera->SetFollowTarget(false);
		pCamera->SetFollowTarget(false);

		// XRAĖŨč
		CApplication::SetScore(m_pScore->GetScore());
	}

	if (!m_bGame)
	{
		CApplication::SetNextMode(CApplication::MODE_RESULT);
	}
}

//=============================================================================
// `æ
// Author : úąl
// Tv : `æđs¤
//=============================================================================
void CGame::Draw()
{

}

//=============================================================================
// Gl~[ĖX|[
// Author : ûüė]
// Tv : Gđoģŗšé
//=============================================================================
void CGame::EnemySpawn()
{
	// X|[ˇéûü
	int Spawn = 0;
	if (m_pPlayer != nullptr)
	{
		// vC[ĖĘuđæž
		D3DXVECTOR3 pos = m_pPlayer->GetPos();
		D3DXVECTOR3 EnemyPos;
		// _ÅGĖX|[ˇéûüđßé
		Spawn = CCalculation::Rand(4);
		// _ÅGĖxŠyđĪĻé
		int rand = CCalculation::Rand(5,-2);

		switch (Spawn)
		{// Gl~[ĖX|[
		case 0:
			// ļ
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(pos.x - (CRenderer::SCREEN_WIDTH / 2), pos.y + (125.0f * rand), 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), 3);
			break;

		case 1:
			// E
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(pos.x + (CRenderer::SCREEN_WIDTH / 2), pos.y + (125.0f * rand), 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), 3);
			break;

		case 2:
			// ē
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(pos.x + (245.0f * rand), pos.y + (CRenderer::SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), 3);
			break;

		case 3:
			// ã
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(pos.x + (245.0f * rand), pos.y - (CRenderer::SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), 3);
			break;

		default:
			break;
		}
	}
}