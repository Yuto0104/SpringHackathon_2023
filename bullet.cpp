//============================================
//
//	bullet.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "bullet.h"
#include "application.h"
#include "renderer.h"
#include "player.h"
#include "object2D.h"
#include "score.h"
#include "game.h"
#include "enemy.h"
#include "fade.h"
#include "result.h"
#include "sound.h"
#include "camera.h"

//============================================
// 静的メンバ変数宣言
//============================================
CBullet::BulletType CBullet::m_type = BulletType_Normal;

//============================================
// 弾のコンストラクタ
//============================================
CBullet::CBullet()
{
	//============================================
	//メンバ変数のクリア
	//============================================
	m_BulletPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//弾の位置のクリア
	m_BulletPosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//弾の前回の位置のクリア
	m_BulletMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//弾の移動のクリア
	m_BulletSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//弾のサイズのクリア
	m_EnemyDeathFlag = false;								//敵が死んだのかフラグのクリア
	m_GimmickUninitFlag = false;							//ギミックが消えたのかフラグのクリア
	m_RandFlag = false;										//ランダムフラグのクリア
	m_BossDeathFlag = false;								//ボスが死んだのかのフラグのクリア							
}

//============================================
// 弾のデストラクタ
//============================================
CBullet::~CBullet()
{
	//何も書かない
}

//============================================
// 弾の初期化処理
//============================================
HRESULT CBullet::Init(void)
{
	//============================================
	//メンバ変数の初期化
	//============================================
	m_BulletPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_BulletPosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_BulletMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ExplosionTime = 200;
	m_BulletSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_EnemyDeathFlag = false;
	m_GimmickUninitFlag = false;
	m_RandFlag = false;
	m_BossDeathFlag = false;
	m_ExplosionFlag = false;

	//オブジェクト基礎の初期化処理
	CObject3D::Init();
	LoadTex(15);

	return S_OK;
}

//============================================
// 弾の終了処理
//============================================
void CBullet::Uninit(void)
{
	//オブジェクト基礎の終了処理
	CObject3D::Uninit();
}

//============================================
// 弾の更新処理
//============================================
void CBullet::Update(void)
{
	//弾の情報取得
	D3DXVECTOR3 BulletPos = GetPos();
	D3DXVECTOR3 BulletSize = GetSize();
	int BulletLife = GetBulletLife();

	//カメラの情報を取得
	CCamera *pCamera = CApplication::GetCamera();

	//弾の位置更新
	BulletPos += m_BulletMove;

	//前回の位置を保存
	m_BulletPosOld = m_BulletPos;

	//寿命を減らす処理
	m_nLife--;

	//プレイヤーの弾の時
	if (m_nLife <= 0 )
	{
		Uninit();
		return;
	}

	// 弾と敵の当たり判定処理
	//============================================
	if (m_EnemyDeathFlag == false && m_type == BulletType_Normal)
	{
		HitEnemy(BulletPos, 1);
	}

	if (m_EnemyDeathFlag == false && m_type == BulletType_Missile)
	{
		HitEnemy(BulletPos, 20);
	}

	//位置の設定
	SetPos(BulletPos);
	//向きの設定
	SetRot(m_BulletRot);
	//サイズの設定処理
	SetSize(BulletSize);

	//============================================
	// オブジェクト基礎の更新処理
	//============================================
	CObject3D::Update();
}

//============================================
// 弾の描画処理
//============================================
void CBullet::Draw(void)
{
	//オブジェクト基礎の描画処理
	CObject3D::Draw();
}

//============================================
// 弾の生成
//============================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife, BulletType type)
{
	CBullet *pBullet = nullptr;

	//弾のインスタンスの生成
	pBullet = new CBullet;				//2Dオブジェクトのインスタンス生成

										//nullチェック
	if (pBullet != nullptr)
	{
		pBullet->SetType(type);
		//初期化処理
		pBullet->Init();
		//設定処理
		pBullet->SetPos(pos);
		pBullet->m_BulletMove = move;
		pBullet->SetLife(nLife);
		pBullet->SetSize(size);
	}
	else
	{
		assert(false);
	}

	return pBullet;
}

//============================================
// 弾のライフの設定処理
//============================================
void CBullet::SetLife(int life)
{
	m_nLife = life;
}
//============================================
// 弾と敵の当たり判定
//============================================
void CBullet::HitEnemy(D3DXVECTOR3 pos, int life)
{
	if (CGame::GetEnemy() != nullptr)
	{
		//敵の位置
		D3DXVECTOR3 EnemyPos = CGame::GetEnemy()->GetPos();
		//敵のサイズ
		D3DXVECTOR3 EnemySize = CGame::GetEnemy()->GetSize();
		//敵の体力
		int EnemyLife = CGame::GetEnemy()->GetLife();
		//弾と敵の当たり判定
		if (pos.x + 0.5f >= EnemyPos.x - EnemySize.x
			&&pos.x - 0.5f <= EnemyPos.x + EnemySize.x
			&&pos.y + 0.5f >= EnemyPos.y - EnemySize.y
			&&pos.z + 0.5f >= EnemyPos.z - EnemySize.z
			&&pos.z - 0.5f <= EnemyPos.z + EnemySize.z)
		{
			//SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_HIT);
			//弾の削除
			m_nLife = 0;
			SetLife(m_nLife);

			EnemyLife -= life;

			if (EnemyLife <= 0)
			{
				CGame::GetScore()->AddScore(200);
				CGame::GetEnemy()->Uninit();
				CGame::SetEnemy(nullptr);
			}
			else
			{
				CGame::GetEnemy()->SetLife(EnemyLife);
			}
		}
	}
}

//============================================
// 弾の体力
//============================================
void CBullet::BulletLife()
{
	//弾の削除
	m_nLife = 0;
	SetLife(m_nLife);
}
