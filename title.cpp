//=============================================================================
//
// タイトルクラス(title.cpp)
// Author : 唐﨑結斗
// 概要 : タイトルクラスの管理を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "title.h"

#include "application.h"
#include "keyboard.h"
#include "object2D.h"
#include "sound.h"
#include "bg.h"

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CTitle::CTitle() : m_nextMode(MODE_GAME),	// 次に設定するモード
m_pTitleLogo(nullptr),						// タイトルロゴオブジェクト
m_pNewGame(nullptr),						// ニューゲームオブジェクト
m_pExit(nullptr),							// 終了オブジェクト
m_fAddAlpha(0.0f),							// フレーム数のカウント
m_nCntFrame(0),								// フレームカウント
m_bPressEnter(true)							// エンターキーを押せるか
{

}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CTitle::Init()
{
	//SE
	CApplication::GetSound()->Play(CSound::SOUND_LABEL_BGM_BGM000);

	CBG *pBG = CBG::Create();
	pBG->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	pBG->LoadTex(17);

	m_pTitleLogo = CObject2D::Create();
	m_pTitleLogo->SetPos(D3DXVECTOR3(640.0f, 280.0f, 0.0f));
	m_pTitleLogo->SetSize(D3DXVECTOR3(640.0f, 200.0f, 0.0f));
	m_pTitleLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pTitleLogo->LoadTex(5);

	m_pNewGame = CObject2D::Create();
	m_pNewGame->SetPos(D3DXVECTOR3(640.0f, 560.0f, 0.0f));
	m_pNewGame->SetSize(D3DXVECTOR3(300.0f, 60.0f, 0.0f));
	m_pNewGame->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pNewGame->LoadTex(9);

	m_pExit = CObject2D::Create();
	m_pExit->SetPos(D3DXVECTOR3(640.0f, 630.0f, 0.0f));
	m_pExit->SetSize(D3DXVECTOR3(170.0f, 50.0f, 0.0f));
	m_pExit->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pExit->LoadTex(10);

	return S_OK;
}

//=============================================================================
// 終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CTitle::Uninit()
{
	// サウンド情報の取得
	CSound *pSound = CApplication::GetSound();

	// サウンド終了
	pSound->Stop();

	// スコアの解放
	Release();
}

//=============================================================================
// 更新
// Author : 唐﨑結斗
// 概要 : 更新を行う
//=============================================================================
void CTitle::Update()
{
	// サウンド情報の取得
	CSound *pSound = CApplication::GetSound();

	// 入力情報の取得
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	if (m_bPressEnter)
	{
		SelectMode();
	}

	FlashObj();

	if (m_bPressEnter
		&& pKeyboard->GetTrigger(DIK_RETURN))
	{
		//SE
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_ENTER);
		m_bPressEnter = false;
	}

	if (!m_bPressEnter
		&& m_nCntFrame >= 40)
	{
		switch (m_nextMode)
		{
		case MODE_GAME:
			CApplication::SetNextMode(CApplication::MODE_GAME);
			break;

		case MODE_EXIT:
			// ウィンドウを破棄
			DestroyWindow(CApplication::GetWnd());
			break;

		default:
			assert(false);
			break;
		}
	}
}

//=============================================================================
// 描画
// Author : 唐﨑結斗
// 概要 : 描画を行う
//=============================================================================
void CTitle::Draw()
{

}

//=============================================================================
// オブジェクトの点滅
// Author : 唐﨑結斗
// 概要 : 指定のオブジェクトを点滅させる
//=============================================================================
void CTitle::FlashObj()
{
	CObject2D *pObj = nullptr;

	if (m_bPressEnter)
	{
		m_fAddAlpha += 0.07f;
	}
	else if (!m_bPressEnter)
	{
		m_fAddAlpha += 0.5f;
		m_nCntFrame++;
	}

	switch (m_nextMode)
	{
	case MODE_GAME:
		pObj = m_pNewGame;
		m_pExit->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;

	case MODE_EXIT:
		pObj = m_pExit;
		m_pNewGame->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;

	default:
		assert(false);
		break;
	}

	pObj->SetCol(D3DXCOLOR(0.7f, 0.7f, 0.7f, sinf(m_fAddAlpha) * 3.0f));
}

//=============================================================================
// モードの選択
// Author : 唐﨑結斗
// 概要 : モードの選択する
//=============================================================================
void CTitle::SelectMode()
{
	int nMode = (int)m_nextMode;

	// サウンド情報の取得
	CSound *pSound = CApplication::GetSound();

	// 入力情報の取得
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_W))
	{
		//pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		nMode--;

		if (nMode < 0)
		{
			nMode = 2;
		}
	}
	else if (pKeyboard->GetTrigger(DIK_S))
	{
		//pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		nMode++;

		if (nMode > 2)
		{
			nMode = 0;
		}
	}

	m_nextMode = (NEXT_MODE)nMode;
}
