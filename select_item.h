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
#include "object.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObject2D;
class CLille;

//=============================================================================
// ゲームクラス
// Author : 唐﨑結斗
// 概要 : ゲーム生成を行うクラス
//=============================================================================
class CSelectItem : public CObject
{
public:
	//--------------------------------------------------------------------
	// モードの列挙型
	// Author : 唐﨑結斗
	// 概要 : モードを識別する
	//--------------------------------------------------------------------
	enum NEXT_MODE
	{
		MODE_SLOT = 0,		// スロット
		MODE_ITEM,			// アイテム
		MAX_MODE,			// シーンの最大数
		MODE_NONE,			// シーン無し
	};

	//--------------------------------------------------------------------
	// 静的メンバ関数
	//--------------------------------------------------------------------
	static CSelectItem *Create();		// アイテムセレクトの生成

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CSelectItem(int nPriority = CObject::PRIORITY_LEVEL3);
	~CSelectItem() override;

	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	HRESULT Init() override;						// 初期化
	void Uninit() override;							// 終了
	void Update() override;							// 更新
	void Draw() override;							// 描画
	void SetPos(const D3DXVECTOR3 &pos) override;									// 位置のセッター
	void SetPosOld(const D3DXVECTOR3 &posOld) override { m_posOld = posOld; }		// 過去位置のセッター
	void SetRot(const D3DXVECTOR3 &rot) override;									// 向きのセッター
	void SetSize(const D3DXVECTOR3 &size) override;									// 大きさのセッター
	void SetColor(const D3DXCOLOR &col);											// 色の設定
	void SetPause(const bool bPause, const bool bSelect);							// ポーズの使用状況
	void SetPause(const bool bPause);												// ポーズの使用状況
	D3DXVECTOR3 GetPos() override { return m_pos; }									// 位置のゲッター
	D3DXVECTOR3 GetPosOld()  override { return m_posOld; }							// 過去位置のゲッター
	D3DXVECTOR3 GetRot()  override { return m_rot; }								// 向きのゲッター
	D3DXVECTOR3 GetSize()  override { return m_size; }								// 大きさのゲッター
	bool GetPause() { return m_bPause; }

private:
	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	void FlashObj();
	void SelectMode();
	void Select();

	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	NEXT_MODE		m_nextMode;			// 次のモード
	CObject2D		*m_pSelectBGObj;	// ポーズ背景オブジェクト
	CObject2D		*m_pSlotObj;		// スロットオブジェクト
	CObject2D		*m_pItemObj;		// アイテムオブジェクト
	CLille			*m_pLille;			// リール
	D3DXVECTOR3		m_pos;				// 位置
	D3DXVECTOR3		m_posOld;			// 過去の位置
	D3DXVECTOR3		m_rot;				// 向き
	D3DXVECTOR3		m_size;				// 大きさ

	float			m_fAddAlpha;		// フレーム数のカウント
	int				m_nCntFrame;		// フレームカウント
	bool			m_bPressEnter;		// エンターキーを押せるか
	bool			m_bPause;			// ポーズしているか
	bool			m_bSelect;			// 選択の使用状況
	bool			m_bSlot;			// スロットを使っているか
};
#endif