//=============================================================================
//
// 3Dバレットクラス(bullet3D.cpp)
// Author : 唐﨑結斗
// 概要 : オブジェクト生成を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "bullet3D.h"
#include "renderer.h"
#include "application.h"
#include "score.h"

//=============================================================================
// インスタンス生成
// Author : 唐﨑結斗
// 概要 : 3Dバレットを生成する
//=============================================================================
CBullet3D * CBullet3D::Create(void)
{
	// オブジェクトインスタンス
	CBullet3D *pBullet3D = nullptr;

	// メモリの解放
	pBullet3D = new CBullet3D;

	// メモリの確保ができなかった
	assert(pBullet3D != nullptr);

	// 数値の初期化
	pBullet3D->Init();

	// インスタンスを返す
	return pBullet3D;
}

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CBullet3D::CBullet3D()
{
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);					// 移動量
	m_moveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 移動方向
	m_fSpeed = 0.0f;										// 速度
	m_nAttack = 0;											// 攻撃力

	// オブジェクトの種別設定
	SetObjType(CObject::OBJTYPE_3DBULLET);
}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CBullet3D::~CBullet3D()
{

}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CBullet3D::Init()
{
	// 初期化
	CObject3D::Init();

	// ビルボードオン
	SetBillboard(true);

	// 攻撃
	m_nAttack = 20;

	LoadTex(15);

	return S_OK;
}

//=============================================================================
// 終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CBullet3D::Uninit()
{
	// 終了
	CObject3D::Uninit();
}

//=============================================================================
// 更新
// Author : 唐﨑結斗
// 概要 : 2D更新を行う
//=============================================================================
void CBullet3D::Update()
{
	// 位置の取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();

	// 移動量の算出
	m_move.z = sinf(m_moveVec.x) * cosf(m_moveVec.y) * m_fSpeed;
	m_move.x = sinf(m_moveVec.x) * sinf(m_moveVec.y) * m_fSpeed;
	m_move.y = cosf(m_moveVec.x) * m_fSpeed;

	// 位置の更新
	pos += m_move;

	// 位置の更新
	SetPos(pos);

	if (CollisionScreen())
	{
		Uninit();
	}
	else
	{// 更新
		CObject3D::Update();
	}
}

//=============================================================================
// 描画
// Author : 唐﨑結斗
// 概要 : 2D描画を行う
//=============================================================================
void CBullet3D::Draw()
{
	// 描画
	CObject3D::Draw();
}

//=============================================================================
// スクリーン衝突判定
// Author : 唐﨑結斗
// 概要 : スクリーン外にでたらture
//=============================================================================
bool CBullet3D::CollisionScreen()
{
	bool bCollision = false;

	// 位置の取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();
	D3DXVECTOR3 worldPos;

	// スクリーン座標にキャスト
	D3DXVECTOR3 screenPos = CApplication::ScreenCastWorld(pos);

	if (screenPos.x + size.x < 0.0f)
	{// 終了
		bCollision = true;
	}
	else if (screenPos.x - size.x >(float)CRenderer::SCREEN_WIDTH)
	{// 終了
		bCollision = true;
	}

	if (screenPos.y + size.y < 0.0f)
	{// 終了
		bCollision = true;
	}
	else if (screenPos.y - size.y >(float)CRenderer::SCREEN_HEIGHT)
	{// 終了
		bCollision = true;
	}

	return bCollision;
}
