//=============================================================================
//
// select_item.cpp
// Author : 梶田大夢
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "select_item.h"
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
#include "fade.h"
#include "debug_proc.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
D3DXCOLOR CSelectItem::fogColor;							// フォグカラー
float CSelectItem::fFogStartPos;							// フォグの開始点
float CSelectItem::fFogEndPos;								// フォグの終了点
float CSelectItem::fFogDensity;								// フォグの密度

//=============================================================================
// コンストラクタ
// Author : 梶田大夢
//=============================================================================
CSelectItem::CSelectItem() : m_pSelectItem(nullptr)
{

}

//=============================================================================
// デストラクタ
// Author : 梶田大夢
//=============================================================================
CSelectItem::~CSelectItem()
{

}

//=============================================================================
// 初期化
// Author : 梶田大夢
//=============================================================================
HRESULT CSelectItem::Init()
{// マウスの取得
	CMouse *pMouse = CApplication::GetMouse();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// サウンド情報の取得
	CSound *pSound = CApplication::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM003);

	// 重力の値を設定
	CCalculation::SetGravity(0.2f);

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

	m_pSelectItem = CObject2D::Create();
	m_pSelectItem->SetPos(D3DXVECTOR3(500.0f, 350.0f, 0.0f));
	m_pSelectItem->SetSize(D3DXVECTOR3(300.0f, 350.0f, 0.0f));
	m_pSelectItem->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pSelectItem->LoadTex(-1);

	m_pSelectItem2 = CObject2D::Create();
	m_pSelectItem2->SetPos(D3DXVECTOR3(800.0f, 350.0f, 0.0f));
	m_pSelectItem2->SetSize(D3DXVECTOR3(300.0f, 350.0f, 0.0f));
	m_pSelectItem2->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pSelectItem2->LoadTex(-1);

	return S_OK;
}

//=============================================================================
// 終了
// Author : 梶田大夢
//=============================================================================
void CSelectItem::Uninit()
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
// Author : 梶田大夢
//=============================================================================
void CSelectItem::Update()
{
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	//頂点カラーの更新
	if (m_Menu == 0)
	{
		m_pSelectItem->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pSelectItem2->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}
	else if (m_Menu == 1)
	{
		m_pSelectItem->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_pSelectItem2->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (pKeyboard->GetTrigger(DIK_A))
	{//←が入力されたとき
	 //サウンドの再生
		//PlaySound(SOUND_LABEL_SE_SEL);

		m_Menu--;
		if (m_Menu < 0)
		{
			m_Menu = 0;
		}
	}
	else if (pKeyboard->GetTrigger(DIK_D))
	{//→が入力されたとき
	 //サウンドの再生
		//PlaySound(SOUND_LABEL_SE_SEL);

		m_Menu++;
		if (m_Menu >= 2)
		{
			m_Menu = 1;
		}
	}

	//メニュー選択でフェード移行
	switch (m_Menu)
	{
	case 0:
		if (pKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			//サウンドの再生
			//PlaySound(SOUND_LABEL_SE_DEC);

			//モードのセット処理
			CApplication::SetNextMode(CApplication::MODE_GAME);
			break;
		}
	case 1:
		if (pKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			//サウンドの再生
			//PlaySound(SOUND_LABEL_SE_DEC);

			//モードのセット処理
			CApplication::SetNextMode(CApplication::MODE_TUTORIAL);
			break;
		}
	}

#ifdef _DEBUG
	//CDebugProc::Print("メニュー | 1 | 2 |\n", m_Menu);
#endif // _DEBUG
}

//=============================================================================
// 描画
// Author : 梶田大夢
//=============================================================================
void CSelectItem::Draw()
{

}