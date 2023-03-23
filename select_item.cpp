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
#include "object2D.h"
#include "renderer.h"
#include "application.h"
#include "keyboard.h"
#include "sound.h"
#include "fade.h"

//=============================================================================
// インスタンス生成
// Author : 唐�ｱ結斗
// 概要 : スコアを生成する
//=============================================================================
CSelectItem *CSelectItem::Create()
{
	// オブジェクトインスタンス
	CSelectItem *pPause = nullptr;

	pPause = new CSelectItem;

	// メモリの確保ができなかった
	assert(pPause != nullptr);

	// 数値の初期化
	pPause->Init();

	// インスタンスを返す
	return pPause;
}

//=============================================================================
// コンストラクタ
// Author : 唐�ｱ結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CSelectItem::CSelectItem(int nPriority /*= CObject::PRIORITY_LEVEL3*/) : CObject(nPriority)
{
	m_nextMode = MODE_SLOT;								// 次のモード
	m_pSelectBGObj = nullptr;							// セレクト背景オブジェクト
	m_pSlotObj = nullptr;								// スロットオブジェクト
	m_pItemObj = nullptr;								// アイテムオブジェクト
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 位置
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 過去の位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 向き
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 大き
	
	m_fAddAlpha = 0.0f;									// フレーム数のカウント
	m_nCntFrame = 0;									// フレームカウント
	m_bPressEnter = true;								// エンターキーを押せるか
	m_bPause = false;									// ポーズしているか
	m_bSelect = false;									// 選択の使用状況
}

//=============================================================================
// デストラクタ
// Author : 唐�ｱ結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CSelectItem::~CSelectItem()
{

}

//=============================================================================
// 初期化
// Author : 唐�ｱ結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CSelectItem::Init()
{
	m_pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(400.0f, 400.0f, 0.0f);
	SetObjType(CObject::OBJTYPE_SELECT_ITEM);

	// 生存フラグ
	SetPermanent(true);

	return S_OK;
}

//=============================================================================
// 終了
// Author : 唐�ｱ結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CSelectItem::Uninit()
{
	// スコアの解放
	Release();
}

//=============================================================================
// 更新
// Author : 唐�ｱ結斗
// 概要 : 更新を行う
//=============================================================================
void CSelectItem::Update()
{
	if (CApplication::GetMode() == CApplication::MODE_GAME
		&& !CApplication::GetFade()->GetFadeSituation())
	{
		if (m_bSelect)
		{// 選択画面
			Select();
		}
	}
}

//=============================================================================
// 描画
// Author : 唐�ｱ結斗
// 概要 : 描画を行う
//=============================================================================
void CSelectItem::Draw()
{

}

//=============================================================================
// 位置のセッター
// Author : 唐�ｱ結斗
// 概要 : 位置のメンバ変数に引数を代入
//=============================================================================
void CSelectItem::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}

//=============================================================================
// 向きのセッター
// Author : 唐�ｱ結斗
// 概要 : 向きのメンバ変数に引数を代入
//=============================================================================
void CSelectItem::SetRot(const D3DXVECTOR3 &rot)
{
	m_rot = rot;
}

//=============================================================================
// 大きさのセッター
// Author : 唐�ｱ結斗
// 概要 : 大きさのメンバ変数に引数を代入
//=============================================================================
void CSelectItem::SetSize(const D3DXVECTOR3 & size)
{
	m_size = size;
}

//=============================================================================
// 色のセッター
// Author : 唐�ｱ結斗
// 概要 : 色の設定を行う
//=============================================================================
void CSelectItem::SetColor(const D3DXCOLOR & col)
{

}

//=============================================================================
// ポーズのセッター
// Author : 唐�ｱ結斗
// 概要 : ポーズの設定を行う
//=============================================================================
void CSelectItem::SetPause(const bool bPause, const bool bSelect)
{
	m_bPause = bPause;
	CSuper::SetPause(m_bPause);

	if (m_bPause)
	{
		m_bSelect = true;

		// セレクト背景オブジェクト
		m_pSelectBGObj = CObject2D::Create();
		m_pSelectBGObj->SetSize(m_size);
		m_pSelectBGObj->SetPos(m_pos);
		m_pSelectBGObj->LoadTex(-1);
		m_pSelectBGObj->SetCol(D3DXCOLOR(0.7f, 0.7f, 0.2f, 0.5f));
		m_pSelectBGObj->SetObjType(CObject::OBJTYPE_SELECT_ITEM);

		// スロットオブジェクト
		m_pSlotObj = CObject2D::Create();
		m_pSlotObj->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 100.0f, m_pos.z));
		m_pSlotObj->SetSize(D3DXVECTOR3(300.0f, 150.0f, 0.0f));
		m_pSlotObj->LoadTex(-1);
		m_pSlotObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pSlotObj->SetObjType(CObject::OBJTYPE_SELECT_ITEM);

		// アイテムオブジェクト
		m_pItemObj = CObject2D::Create();
		m_pItemObj->SetPos(D3DXVECTOR3(m_pos.x,m_pos.y - 100.0f,m_pos.z));
		m_pItemObj->SetSize(D3DXVECTOR3(300.0f, 150.0f, 0.0f));
		m_pItemObj->LoadTex(-1);
		m_pItemObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pItemObj->SetObjType(CObject::OBJTYPE_SELECT_ITEM);
	}
	else
	{
		if (m_bSelect)
		{
			m_bSelect = false;

			// ポーズ背景オブジェクト
			m_pSelectBGObj->Uninit();

			// スロットオブジェクト
			m_pSlotObj->Uninit();

			// アイテムオブジェクト
			m_pItemObj->Uninit();
		}
	}
}

//=============================================================================
// ポーズのセッター
// Author : 唐�ｱ結斗
// 概要 : ポーズの設定を行う
//=============================================================================
void CSelectItem::SetPause(const bool bPause)
{
	m_bPause = bPause;
	CSuper::SetPause(m_bPause);
	m_bSelect = false;
}

//=============================================================================
// オブジェクトの点滅
// Author : 唐�ｱ結斗
// 概要 : 指定のオブジェクトを点滅させる
//=============================================================================
void CSelectItem::FlashObj()
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
	case MODE_SLOT:
		pObj = m_pSlotObj;
		m_pItemObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;

	case MODE_ITEM:
		pObj = m_pItemObj;
		m_pSlotObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;

	default:
		assert(false);
		break;
	}

	pObj->SetCol(D3DXCOLOR(0.7f, 0.7f, 0.7f, sinf(m_fAddAlpha) * 3.0f));
}

//=============================================================================
// モードの選択
// Author : 唐�ｱ結斗
// 概要 : モードの選択する
//=============================================================================
void CSelectItem::SelectMode()
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
			nMode = 1;
		}
	}
	else if (pKeyboard->GetTrigger(DIK_S))
	{
		//pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		nMode++;

		if (nMode > 1)
		{
			nMode = 0;
		}
	}

	m_nextMode = (NEXT_MODE)nMode;
}

//=============================================================================
// 選択画面
// Author : 唐�ｱ結斗
// 概要 : 選択画面
//=============================================================================
void CSelectItem::Select()
{
	// サウンド情報の取得
	CSound *pSound = CApplication::GetSound();

	// 入力情報の取得
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	if (m_bPause)
	{
		if (m_bPressEnter)
		{
			SelectMode();
		}

		FlashObj();

		if (m_bPressEnter
			&& pKeyboard->GetTrigger(DIK_RETURN))
		{
			//pSound->PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
			m_bPressEnter = false;
		}

		if (!m_bPressEnter
			&& m_nCntFrame >= 40)
		{
			m_bPressEnter = true;
			m_nCntFrame = 0;

			switch (m_nextMode)
			{
			case MODE_SLOT:
				SetPause(false, false);
				//CApplication::SetNextMode(CApplication::MODE_TITLE);
				break;

			case MODE_ITEM:
				SetPause(false, false);
				//CApplication::SetNextMode(CApplication::MODE_GAME);
				break;

			default:
				assert(false);
				break;
			}
		}
	}
}