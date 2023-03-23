//=============================================================================
//
// エネミークラス(enemy.h)
// Author : ��野馨將
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
// Author : ��野馨將
// 概要 : エネミーを生成する
//=============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nLife)
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
	pEnemy->m_nLife = nLife;

	// インスタンスを返す
	return pEnemy;
}

//=============================================================================
// コンストラクタ
// Author : ��野馨將
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CEnemy::CEnemy()
{
	// タイプの付与
	SetObjType(OBJETYPE_ENEMY);
}

//=============================================================================
// デストラクタ
// Author : ��野馨將
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// 初期化
// Author : ��野馨將
// 概要 : 初期化
//=============================================================================
HRESULT CEnemy::Init()
{// 初期化処理
	CObject3D::Init();
	m_nLife = 0;

	// 3D矩形の当たり判定の設定
	m_pCollisionRectangle3D = CCollision_Rectangle3D::Create();
	m_pCollisionRectangle3D->SetParent(this);
	m_pCollisionRectangle3D->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCollisionRectangle3D->SetSize(D3DXVECTOR3(45.0f, 45.0f, 10.0f));

	return S_OK;
}

//=============================================================================
// 終了
// Author : ��野馨將
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
// Author : ��野馨將
// 概要 : エネミー更新を行う
//=============================================================================
void CEnemy::Update()
{// 更新処理
	// 情報の取得
	CPlayer *pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 pos = GetPos();
	if (pPlayer != nullptr)
	{
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

		// 追尾
		float fRot = sqrtf((float)(pow(PlayerPos.x - pos.x, 2) + pow(PlayerPos.y - pos.y, 2)));
		m_move.x = (PlayerPos.x - pos.x) / (fRot / 1.0f);
		m_move.y = (PlayerPos.y - pos.y) / (fRot / 1.0f);
	}

	//前回位置の保存
	SetPosOld(pos);

	// 位置の更新
	pos += m_move;
	SetPos(pos);

	// 当たり判定
	m_pCollisionRectangle3D->Collision(CObject::OBJETYPE_PLAYER, true);

	// ライフが0より小さくなったら
	if (m_nLife <= 0)
	{// リザルトに行く
		CApplication::SetNextMode(CApplication::MODE_RESULT);
		// 終了処理
		Uninit();

		return;
	}
}

//=============================================================================
// 描画
// Author : ��野馨將
// 概要 : エネミー描画を行う
//=============================================================================
void CEnemy::Draw()
{// 描画処理
	CObject3D::Draw();
}