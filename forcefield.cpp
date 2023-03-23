//=============================================================================
//
// フォースフィールドクラス(forcefield.h)
// Author : 斉藤紫杏
// 概要 : フォースフィールド
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "forcefield.h"
#include "collision_rectangle3D.h"
#include "renderer.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "sound.h"
#include "application.h"

//=============================================================================
// インスタンス生成
// Author : 斉藤紫杏
// 概要 : フォースフィールドを生成する
//=============================================================================
CForceField * CForceField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// オブジェクトインスタンス
	CForceField *pForceField = nullptr;

	// メモリの解放
	pForceField = new CForceField;
	// メモリの確保ができなかった
	assert(pForceField != nullptr);

	// エネミーの初期化
	pForceField->Init();
	pForceField->SetPos(pos);
	pForceField->SetSize(size);
	pForceField->m_pCollisionRectangle3D->SetSize(D3DXVECTOR3(size.x * 2.0f, size.y * 2.0f, 10.0f));

	// インスタンスを返す
	return pForceField;
}

//=============================================================================
// コンストラクタ
// Author : 斉藤紫杏
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CForceField::CForceField()
{
	// タイプの付与
	SetObjType(OBJETYPE_FORCEFIELD);
}

//=============================================================================
// デストラクタ
// Author : 斉藤紫杏
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CForceField::~CForceField()
{

}

//=============================================================================
// 初期化
// Author : 斉藤紫杏
// 概要 : 初期化
//=============================================================================
HRESULT CForceField::Init()
{// 初期化処理
	// メンバ変数の初期化
	m_nDamage = 1;
	m_AttackTime = 0;

	CSkill::Init();

	LoadTex(4);

	return S_OK;
}

//=============================================================================
// 終了
// Author : 斉藤紫杏
// 概要 : フォースフィールドの解放
//=============================================================================
void CForceField::Uninit()
{
	// 終了処理
	CSkill::Uninit();

	// フォースフィールドの解放
	Release();
}

//=============================================================================
// 更新
// Author : 斉藤紫杏
// 概要 : フォースフィールドを更新を行う
//=============================================================================
void CForceField::Update()
{// 更新処理
	CPlayer *pPlayer = CGame::GetPlayer();
	if (pPlayer != nullptr)
	{
		//位置の取得
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

		m_AttackTime--;

		if (m_AttackTime <= 0)
		{
			// 当たり判定
			if (m_pCollisionRectangle3D->Collision(CObject::OBJETYPE_ENEMY, false))
			{
				// 当たった相手の情報を持ってくるを
				CEnemy *pEnemy = (CEnemy*)m_pCollisionRectangle3D->GetCollidedObj();
				//ライフの減少
				pEnemy->SetLife(pEnemy->GetLife() - m_nDamage);
				// サウンド情報の取得
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_HIT);

				m_AttackTime = 50;
			}
		}
		SetPos(PlayerPos);
	}
}

//=============================================================================
// 描画
// Author : 斉藤紫杏
// 概要 : フォースフィールドを描画を行う
//=============================================================================
void CForceField::Draw()
{// 描画処理
	CSkill::Draw();
}
