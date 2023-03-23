//=============================================================================
//
// フォースフィールドクラス(forcefield.h)
// Author : 斉藤紫杏
// 概要 : フォースフィールド
//
//=============================================================================
#ifndef _FORCEFIELD_H_		// このマクロ定義がされてなかったら
#define _FORCEFIELD_H_		// 二重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "skill.h"

//*****************************************************************************
//	前方宣言
//*****************************************************************************

//=============================================================================
// フォースフィールドクラス
// Author : 斉藤紫杏
// 概要 : フォースフィールド
//=============================================================================
class CForceField : public CSkill
{
public:
	//--------------------------------------------------------------------
	// 静的メンバ関数
	//--------------------------------------------------------------------
	static CForceField *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// 地雷の生成

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CForceField();
	~CForceField();

	//--------------------------------------------------------------------
	// オーバーライド関数
	//--------------------------------------------------------------------
	HRESULT Init() override;								// 初期化
	void Uninit() override;									// 終了
	void Update() override;									// 更新
	void Draw() override;									// 描画

	void HitArea(D3DXVECTOR3 pos);											// フォースフィールドの範囲

private:
	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	int m_nDamage;											// ダメージ量
	int m_AttackTime;										// 攻撃時間
};

#endif