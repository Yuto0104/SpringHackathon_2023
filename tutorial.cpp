//=============================================================================
//
// チュートリアルクラス(tutorial.cpp)
// Author : 唐﨑結斗
// 概要 : チュートリアルクラスの管理を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "tutorial.h"
#include "calculation.h"
#include "keyboard.h"
#include "mouse.h"
#include "application.h"
#include "renderer.h"
#include "object.h"
#include "bg.h"
#include "score.h"
#include "time.h"
#include "sound.h"
#include "object2D.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CScore *CTutorial::m_pScore = nullptr;						// スコアインスタンス
D3DXCOLOR CTutorial::fogColor;								// フォグカラー
float CTutorial::fFogStartPos;								// フォグの開始点
float CTutorial::fFogEndPos;								// フォグの終了点
float CTutorial::fFogDensity;								// フォグの密度

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CTutorial::CTutorial() : m_pTutorial(nullptr),
m_nCntFrame(0)
{

}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CTutorial::Init()
{// マウスの取得
	CMouse *pMouse = CApplication::GetMouse();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// サウンド情報の取得
	CSound *pSound = CApplication::GetSound();
	//pSound->PlaySound(CSound::SOUND_LABEL_BGM003);

	// 重力の値を設定
	CCalculation::SetGravity(0.2f);

	// スコア
	m_pScore = CScore::Create(10, false);
	m_pScore->SetScore(0);
	m_pScore->SetPos(D3DXVECTOR3(1280.0f, m_pScore->GetSize().y / 2.0f, 0.0f));

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

	m_pTutorial = CObject2D::Create();
	m_pTutorial->SetPos(D3DXVECTOR3(1050.0f, 320.0f, 0.0f));
	m_pTutorial->SetSize(D3DXVECTOR3(500.0f, 500.0f, 0.0f));
	m_pTutorial->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pTutorial->LoadTex(-1);

	m_pTutorialEnd = CObject2D::Create();
	m_pTutorialEnd->SetPos(D3DXVECTOR3(1050.0f, 600.0f, 0.0f));
	m_pTutorialEnd->SetSize(D3DXVECTOR3(500.0f, 50.0f, 0.0f));
	m_pTutorialEnd->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pTutorialEnd->LoadTex(-1);

	m_bTutoItem = false;

	return S_OK;
}

//=============================================================================
// 終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CTutorial::Uninit()
{// マウスの取得
	CMouse *pMouse = CApplication::GetMouse();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// サウンド情報の取得
	CSound *pSound = CApplication::GetSound();

	// サウンド終了
	pSound->Stop();

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
void CTutorial::Update()
{
	// キーボードの取得
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	if (m_bTutoItem)
	{
		m_nCntFrame--;
		m_pTutorial->SetSize(D3DXVECTOR3(500.0f, 300.0f, 0.0f));
		m_pTutorial->LoadTex(-1);

		if (m_nCntFrame <= 0)
		{
			m_nCntFrame = 0;
			m_bTutoItem = false;
		}
	}
	else
	{
		m_pTutorial->SetSize(D3DXVECTOR3(500.0f, 500.0f, 0.0f));
		m_pTutorial->LoadTex(-1);
	}

	if (pKeyboard->GetTrigger(DIK_F3))
	{
		CApplication::SetNextMode(CApplication::MODE_TITLE);
	}
}

//=============================================================================
// 描画
// Author : 唐﨑結斗
// 概要 : 描画を行う
//=============================================================================
void CTutorial::Draw()
{

}

//=============================================================================
// アイテムのチュートリアル
// Author : 唐﨑結斗
// 概要 : アイテムのチュートリアルを使用する
//=============================================================================
void CTutorial::SetTutoItem(bool bTutoItem)
{
	m_bTutoItem = bTutoItem;
	m_nCntFrame = 300;
}
