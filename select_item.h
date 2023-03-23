//=============================================================================
//
// select_item
// Author : 梶田大夢
//
//=============================================================================
#ifndef _SELECT_ITEM_H_		// このマクロ定義がされてなかったら
#define _SELECT_ITEM_H_		// 二重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "scene_mode.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObject2D;
class CFade;

//=============================================================================
// ゲームクラス
// Author : 唐�ｱ結斗
// 概要 : ゲーム生成を行うクラス
//=============================================================================
class CSelectItem : public CSceneMode
{
public:
	//--------------------------------------------------------------------
	// 静的メンバ関数
	//--------------------------------------------------------------------

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CSelectItem();
	~CSelectItem() override;

	//--------------------------------------------------------------------
	// 静的メンバ変数
	//--------------------------------------------------------------------
	static D3DXCOLOR fogColor;						// フォグカラー
	static float fFogStartPos;						// フォグの開始点
	static float fFogEndPos;						// フォグの終了点
	static float fFogDensity;						// フォグの密度

	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	HRESULT Init() override;						// 初期化
	void Uninit() override;							// 終了
	void Update() override;							// 更新
	void Draw() override;							// 描画

private:
	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------

	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	CObject2D *m_pSelectItem;			// アイテムオブジェクト
	CObject2D *m_pSelectItem2;			// アイテムオブジェクト
	CFade *m_pFade;
	int m_Menu;
};
#endif