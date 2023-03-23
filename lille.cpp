//=============================================================================
//
// 2Dリール(lille.cpp)
// Author : 唐﨑結斗
// 概要 : 2Dリール生成を行う
//
//=============================================================================

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define UDATE_FRAME (7)
#define DIGITS (10)

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "lille.h"
#include "renderer.h"
#include "application.h"
#include "calculation.h"
#include "number.h"

//=============================================================================
// インスタンス生成
// Author : 唐﨑結斗
// 概要 : 2Dバレットを生成する
//=============================================================================
CLille * CLille::Create()
{
	// オブジェクトインスタンス
	CLille *pLille = nullptr;

	pLille = new CLille;

	// メモリの確保ができなかった
	assert(pLille != nullptr);

	// 数値の初期化
	pLille->Init();

	// インスタンスを返す
	return pLille;
}

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CLille::CLille(int nPriority) : CObject2D(nPriority)
{
	m_pNumDest = nullptr;		// 目標の番号
	m_pNumber = nullptr;		// 番号
	m_nNumDest = 0;				// 目標の番号
	m_nNumber = 0;				// 目標の番号
	m_nCntFrame = 0;			// フレームカウント
	bool m_bScroll = true;		// スクロール
}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CLille::~CLille()
{

}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : テクスチャの設定し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CLille::Init()
{
	// オブジェクト2Dの終了
	CObject2D::Init();

	// スクロールを行う
	m_bScroll = true;		

	// 生成
	m_pNumDest = CNumber::Create();
	m_pNumber = CNumber::Create();

	// 目標の番号
	m_nNumDest = CCalculation::Rand(10);
	m_pNumDest->SetNumber(m_nNumDest);
	m_pNumDest->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.2f, 1.0f));

	// 現在の番号
	m_nNumber = CCalculation::Rand(10);
	m_pNumber->SetNumber(m_nNumber);

	return S_OK;
}

//=============================================================================
// 終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CLille::Uninit()
{
	m_pNumDest->Uninit();
	m_pNumber->Uninit();

	// オブジェクト2Dの終了
	CObject2D::Uninit();
}

//=============================================================================
// 更新
// Author : 唐﨑結斗
// 概要 : 2D更新を行う
//=============================================================================
void CLille::Update()
{
	// オブジェクト2Dの更新
	CObject2D::Update();

	if (m_bScroll)
	{
		Scroll();
	}
	else if (!m_bScroll)
	{
		if (m_nNumber == m_nNumDest)
		{// 当たり
		
		}

		m_nCntFrame++;

		if (m_nCntFrame % 150 == 0)
		{
			Uninit();
		}
	}
}

//=============================================================================
// 描画
// Author : 唐﨑結斗
// 概要 : 2D描画を行う
//=============================================================================
void CLille::Draw()
{// プレイヤー2Dの描画
	CObject2D::Draw();
}

//=============================================================================
// リールの設定
// Author : 唐﨑結斗
// 概要 : リールの回転を行う
//=============================================================================
void CLille::SetLille(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	SetPos(pos);
	SetSize(D3DXVECTOR3(0.0f,0.0f,0.0f));

	m_pNumDest->SetSize(D3DXVECTOR3(size.x / 2.0f, size.y / 2.0f, 0.0f));
	m_pNumber->SetSize(D3DXVECTOR3(size.x / 1.5f, size.y / 1.5f, 0.0f));

	m_pNumDest->SetPos(D3DXVECTOR3(pos.x, pos.y - size.y + size.y / 3.0f, 0.0f));
	m_pNumber->SetPos(D3DXVECTOR3(pos.x, pos.y + size.y - size.y / 1.5f, 0.0f));
}

//=============================================================================
// スクロール
// Author : 唐﨑結斗
// 概要 : リールの回転を行う
//=============================================================================
void CLille::Scroll()
{
	m_nCntFrame++;

	if (m_nCntFrame % UDATE_FRAME == 0)
	{
		m_pNumber->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_nNumber++;

		if (m_nNumber >= DIGITS)
		{
			m_nNumber = 0;
		}

		if (m_nNumber == m_nNumDest)
		{
			m_pNumber->SetCol(D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f));
		}

		m_pNumber->SetNumber(m_nNumber);
	}
}


