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

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CScore *CGame::m_pScore = nullptr;						// スコアインスタンス
CTime *CGame::m_pTime = nullptr;						// タイム
CEnemy *CGame::m_pEnemy = nullptr;						// エネミー
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
	pSound->PlaySound(CSound::SOUND_LABEL_BGM001);

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

	// カメラの追従設定(目標 : プレイヤー)
	CCamera *pCamera = CApplication::GetCamera();
	pCamera->SetViewType(CCamera::TYPE_PARALLEL);
	//pCamera->SetFollowTarget(m_pPlayer, 1.0);
	pCamera->SetPosVOffset(D3DXVECTOR3(0.0f, 0.0f, -200.0f));
	pCamera->SetPosROffset(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pCamera->SetUseRoll(true, false);

	// メッシュの設置
	CMesh3D *pMesh = CMesh3D::Create();
	assert(pMesh != nullptr);
	// 数値の設定
	pMesh->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pMesh->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pMesh->SetSize(D3DXVECTOR3(10000.0f, 0.0f, 10000.0f));
	pMesh->SetCol(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	//pMesh->LoadTex(nType);
	//pMesh->SetBlock(block);
	//pMesh->SetSplitTex(bSplitTex);
	//pMesh->SetScrollTex(move, bScrollTex);
	//pMesh->SetUseCollison(bCollison);

	CPlayer::Create(D3DXVECTOR3(50.0f, 0.0f, 100.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f));

	// エネミー
	m_pEnemy = CEnemy::Create(D3DXVECTOR3(100.0f,0.0f,100.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f));

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

	m_bGame = true;

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

	if (pKeyboard->GetPress(DIK_LSHIFT))
	{
		pCamera->Zoom();
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
