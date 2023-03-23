//=============================================================================
//
// エネミークラス(enemy.h)
// Author : 髙野馨將
// 概要 : オブジェクト生成を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "enemy.h"
#include "collision_rectangle3D.h"
#include "renderer.h"
#include "game.h"
#include "player.h"
#include "application.h"

//=============================================================================
// インスタンス生成
// Author : 髙野馨將
// 概要 : エネミーを生成する
//=============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// オブジェクトインスタンス
	CEnemy *pEnemy = nullptr;

	// メモリの解放
	pEnemy = new CEnemy;

	// メモリの確保ができなかった
	assert(pEnemy != nullptr);

	// エネミーの初期化
	pEnemy->Init();
	pEnemy->SetPos(pos);
	pEnemy->SetSize(size);

	// インスタンスを返す
	return pEnemy;
}

//=============================================================================
// コンストラクタ
// Author : 髙野馨將
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CEnemy::CEnemy()
{

}

//=============================================================================
// デストラクタ
// Author : 髙野馨將
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// 初期化
// Author : 髙野馨將
// 概要 : 初期化
//=============================================================================
HRESULT CEnemy::Init()
{// 初期化処理
	CObject3D::Init();

	// 3D矩形の当たり判定の設定
	m_pCollisionRectangle3D = CCollision_Rectangle3D::Create();
	m_pCollisionRectangle3D->SetParent(this);
	m_pCollisionRectangle3D->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCollisionRectangle3D->SetSize(D3DXVECTOR3(45.0f, 45.0f, 20.0f));

	return S_OK;
}

//=============================================================================
// 終了
// Author : 髙野馨將
// 概要 : エネミーの解放
//=============================================================================
void CEnemy::Uninit()
{
	// 終了処理
	CObject3D::Uninit();

	if (m_pCollisionRectangle3D != nullptr)
	{// 3D矩形の当たり判定の終了処理
		m_pCollisionRectangle3D->Uninit();
		m_pCollisionRectangle3D = nullptr;
	}

	// エネミーの解放
	Release();
}

//=============================================================================
// 更新
// Author : 髙野馨將
// 概要 : エネミー更新を行う
//=============================================================================
void CEnemy::Update()
{// 更新処理
	// 情報の取得
	CPlayer *pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

	// 追尾
	float fRot = sqrtf((float)(pow(PlayerPos.x - pos.x, 2) + pow(PlayerPos.y - pos.y, 2)));
	m_move.x = (PlayerPos.x - pos.x) / (fRot / 1.0f);
	m_move.y = (PlayerPos.y - pos.y) / (fRot / 1.0f);

	// 位置の更新
	pos += m_move;
	SetPos(pos);

	// 当たり判定
	m_pCollisionRectangle3D->Collision(CObject::OBJETYPE_ENEMY, true);
}

//=============================================================================
// 描画
// Author : 唐﨑結斗
// 概要 : エネミー描画を行う
//=============================================================================
void CEnemy::Draw()
{// 描画処理
	CObject3D::Draw();
}