//=============================================================================
//
// ミサイルクラス(skill.h)
// Author : 斉藤紫杏
// 概要 : オブジェクト生成を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "missile.h"
#include "collision_rectangle3D.h"
#include "renderer.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "application.h"
#include "bullet.h"

//=============================================================================
// インスタンス生成
// Author : 斉藤紫杏
// 概要 : ミサイルを生成する
//=============================================================================
CMissile * CMissile::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// オブジェクトインスタンス
	CMissile *pMine = nullptr;

	// メモリの解放
	pMine = new CMissile;
	// メモリの確保ができなかった
	assert(pMine != nullptr);

	// エネミーの初期化
	pMine->Init();
	pMine->SetPos(pos);
	pMine->SetSize(size);
	pMine->m_pCollisionRectangle3D->SetSize(D3DXVECTOR3(size.x * 2.0f, size.y * 2.0f, 10.0f));

	// インスタンスを返す
	return pMine;
}

//=============================================================================
// コンストラクタ
// Author : 斉藤紫杏
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CMissile::CMissile()
{

}

//=============================================================================
// デストラクタ
// Author : 斉藤紫杏
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CMissile::~CMissile()
{

}

//=============================================================================
// 初期化
// Author : 斉藤紫杏
// 概要 : 初期化
//=============================================================================
HRESULT CMissile::Init()
{// 初期化処理
	m_BulletMove = D3DXVECTOR3(0.0f,0.0f,0.0f);

	CSkill::Init();

	return S_OK;
}

//=============================================================================
// 終了
// Author : 斉藤紫杏
// 概要 : ミサイルの解放
//=============================================================================
void CMissile::Uninit()
{
	// 終了処理
	CSkill::Uninit();

	// ミサイルの解放
	Release();
}

//=============================================================================
// 更新
// Author : 斉藤紫杏
// 概要 : ミサイル更新を行う
//=============================================================================
void CMissile::Update()
{// 更新処理

	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	if (CGame::GetEnemy() != nullptr)
	{
		D3DXVECTOR3 EnemyPos = CGame::GetEnemy()->GetPos();

		m_BulletMove = PlayerPos - EnemyPos;
		D3DXVec3Normalize(&m_BulletMove, &m_BulletMove);
		m_BulletMove *= 15.0f;

		m_nNormalTime--;
		m_MissileTime--;

		if (m_nNormalTime <= 0)
		{
			m_pBullet = CBullet::Create(PlayerPos, -m_BulletMove, D3DXVECTOR3(5.0f, 5.0f, 0.0f), 100, CBullet::BulletType_Normal);
		}
		if (m_nNormalTime <= 0)
		{
			m_nNormalTime = 40;
		}

		if (m_MissileTime <= 0)
		{
			m_pBullet = CBullet::Create(PlayerPos, -m_BulletMove, D3DXVECTOR3(25.0f, 25.0f, 0.0f), 100, CBullet::BulletType_Missile);
		}
		if (m_MissileTime <= 0)
		{
			m_MissileTime = 250;
		}
	}

}

//=============================================================================
// 描画
// Author : 斉藤紫杏
// 概要 : ミサイル描画を行う
//=============================================================================
void CMissile::Draw()
{// 描画処理
	CSkill::Draw();
}