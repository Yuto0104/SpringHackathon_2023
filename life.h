//=============================================================================
//
// ライフクラス(life.h)
// Author : ��野馨將
// 概要 : オブジェクト生成を行う
//
//=============================================================================
#ifndef _LIFE_H_		// このマクロ定義がされてなかったら
#define _LIFE_H_		// 二重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object2D.h"
#include "texture.h"

//=============================================================================
// ライフクラス
// Author : ��野馨將
// 概要 : ライフ生成を行うクラス
//=============================================================================
class CLife : public CObject2D
{
public:
	//--------------------------------------------------------------------
	// 静的メンバ関数
	//--------------------------------------------------------------------
	static CLife *Create(void);				// ライフの生成
	static CLife *Create(int nPriority);	// ライフの生成(オーバーロード)

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	explicit CLife(int nPriority = PRIORITY_LEVEL0);
	~CLife() override;

	//--------------------------------------------------------------------
	// オーバーライド関数
	//--------------------------------------------------------------------
	HRESULT Init() override;														// 初期化
	void Uninit() override;															// 終了
	void Update() override;															// 更新
	void Draw() override;															// 描画

private:
	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	
};

#endif