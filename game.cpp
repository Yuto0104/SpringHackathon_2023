//=============================================================================
//
// ゲームクラス(game.cpp)
// Author : 唐﨑結斗
// 概要 : ゲームクラスの管理を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
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

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CScore *CGame::m_pScore = nullptr;						// スコアインスタンス
CTime *CGame::m_pTime = nullptr;						// タイム
CEnemy *CGame::m_pEnemy = nullptr;						// エネミー
CPlayer *CGame::m_pPlayer = nullptr;					// プレイヤー
CLille *CGame::m_pLille = nullptr;						// リール
D3DXCOLOR CGame::fogColor;								// フォグカラー
float CGame::fFogStartPos;								// フォグの開始点
float CGame::fFogEndPos;								// フォグの終了点
float CGame::fFogDensity;								// フォグの密度
bool CGame::m_bGame = false;							// ゲームの状況

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CGame::CGame()
{

}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CGame::Init()
{// マウスの取得
	CMouse *pMouse = CApplication::GetMouse();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// サウンド情報の取得
	CSound *pSound = CApplication::GetSound();
	//pSound->PlaySound(CSound::SOUND_LABEL_BGM000);

	// 重力の値を設定
	CCalculation::SetGravity(0.2f);

	// スコア
	m_pScore = CScore::Create(10, false);
	m_pScore->SetScore(0);
	m_pScore->SetPos(D3DXVECTOR3(1280.0f, m_pScore->GetSize().y / 2.0f, 0.0f));

	// タイム
	m_pTime = CTime::Create(3);
	m_pTime->SetTime(120);
	m_pTime->SetTimeAdd(false);
	m_pTime->SetPos(D3DXVECTOR3(640.0f, m_pTime->GetSize().y / 2.0f, 0.0f));

	// プレイヤー生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f));

	// カメラの追従設定(目標 : プレイヤー)
	CCamera *pCamera = CApplication::GetCamera();
	pCamera->SetViewType(CCamera::TYPE_PARALLEL);
	pCamera->SetFollowTarget(m_pPlayer, 1.0);
	pCamera->SetPosVOffset(D3DXVECTOR3(0.0f, 0.0f, -1600.0f));
	pCamera->SetPosROffset(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pCamera->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pCamera->SetUseRoll(false, false);

	// メッシュの設置
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

	// 地雷
	CMine::Create(D3DXVECTOR3(100.0f, 50.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f),1);
	CMine::Create(D3DXVECTOR3(200.0f, 50.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f),1);
	CMine::Create(D3DXVECTOR3(300.0f, 50.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f),2);

	// エネミー
	m_pEnemy = CEnemy::Create(D3DXVECTOR3(100.0f,0.0f,0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f),2);

	// マウスカーソルを消す
	pMouse->SetShowCursor(false);

	// フォグの数値設定
	fogColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// フォグカラー
	fFogStartPos = 1.0f;								// フォグの開始点
	fFogEndPos = 100000.0f;								// フォグの終了点
	fFogDensity = 0.00001f;								// フォグの密度

	// フォグの有効設定
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	// フォグカラーの設定
	pDevice->SetRenderState(D3DRS_FOGCOLOR, fogColor);

	// フォグの範囲設定
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&fFogStartPos));
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&fFogEndPos));

	// フォグの密度の設定
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&fFogDensity));

	//初期化
	m_bGame = true;
	m_nSpawnTime = 0;

	return S_OK;
}

//=============================================================================
// 終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CGame::Uninit()
{// マウスの取得
	CMouse *pMouse = CApplication::GetMouse();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// サウンド情報の取得
	CSound *pSound = CApplication::GetSound();

	// サウンド終了
	pSound->StopSound();

	CCamera *pCamera = CApplication::GetCamera();
	pCamera->SetFollowTarget(false);

	// フォグの有効設定
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	// マウスカーソルを出す
	pMouse->SetShowCursor(true);

	// スコアの解放
	Release();
}

//=============================================================================
// 更新
// Author : 唐﨑結斗
// 概要 : 更新を行う
//=============================================================================
void CGame::Update()
{
	// キーボードの取得
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

	if (!pSelect->GetPause()
		&& pKeyboard->GetTrigger(DIK_H))
	{
		pSelect->SetPause(true, true);

	}
	else if (pSelect->GetPause()
		&& pKeyboard->GetTrigger(DIK_H))
	{
		pSelect->SetPause(false, false);
	}

	if (m_nSpawnTime < 60
		&& !pSelect->GetPause())
	{//スポーン時間が一定以下なら加算する
		m_nSpawnTime++;
	}
	else if (m_nSpawnTime >= 60)
	{//一定以上ならスポーンさせて0にする
		EnemySpawn();
		m_nSpawnTime = 0;
	}

	if (m_pTime->GetTimeEnd()
		&& m_bGame)
	{
		m_bGame = false;

		// カメラの追従設定
		pCamera = CApplication::GetCamera();
		pCamera->SetFollowTarget(false);
		pCamera->SetFollowTarget(false);

		// スコアの設定
		CApplication::SetScore(m_pScore->GetScore());
	}

	if (!m_bGame)
	{
		CApplication::SetNextMode(CApplication::MODE_RESULT);
	}
}

//=============================================================================
// 描画
// Author : 唐﨑結斗
// 概要 : 描画を行う
//=============================================================================
void CGame::Draw()
{

}

//=============================================================================
// エネミーのスポーン
// Author : 髙野馨將
// 概要 : 敵を出現させる
//=============================================================================
void CGame::EnemySpawn()
{
	// スポーンする方向
	int Spawn = 0;
	if (m_pPlayer != nullptr)
	{
		// プレイヤーの位置を取得
		D3DXVECTOR3 pos = m_pPlayer->GetPos();
		D3DXVECTOR3 EnemyPos;
		// ランダムで敵のスポーンする方向を決める
		Spawn = CCalculation::Rand(4);
		// ランダムで敵のxかyを変える
		int rand = CCalculation::Rand(5,-2);

		switch (Spawn)
		{// エネミーのスポーン
		case 0:
			// 左
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(pos.x - (CRenderer::SCREEN_WIDTH / 2), pos.y + (125.0f * rand), 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), 3);
			break;

		case 1:
			// 右
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(pos.x + (CRenderer::SCREEN_WIDTH / 2), pos.y + (125.0f * rand), 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), 3);
			break;

		case 2:
			// 下
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(pos.x + (245.0f * rand), pos.y + (CRenderer::SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), 3);
			break;

		case 3:
			// 上
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(pos.x + (245.0f * rand), pos.y - (CRenderer::SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), 3);
			break;

		default:
			break;
		}
	}
}