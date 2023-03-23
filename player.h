//=============================================================================
//
// player.h
// Author : 梶田大夢 髙野馨將
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object3D.h"

//=============================================================================
//前方宣言
//=============================================================================
class CCollision_Rectangle3D;

//=============================================================================
//プレイヤークラス
//=============================================================================
class CPlayer : public CObject3D
{
public:
	CPlayer();															//コンストラクタ
	~CPlayer() override;												//デストラクタ

	HRESULT Init(void) override;										//初期化処理
	void Uninit(void) override;											//終了処理
	void Update(void) override;											//更新処理
	void Draw(void) override;											//描画処理

	int GetLife(void) { return m_nLife; }								//ライフの取得

	static CPlayer* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const int nLife);	//生成処理

private:
	void  PlayerController(void);										//プレイヤーの操作
	static const float m_MaxWalkingSpeed;								//最大の歩くスピード

	CCollision_Rectangle3D *m_pCollisionRectangle3D;					//3D矩形の当たり判定
	D3DXVECTOR3 m_pos;													//位置
	D3DXVECTOR3 m_move;													//速度
	D3DXVECTOR3 m_rot;													//向き
	D3DXMATRIX  m_mtxWorld;												//ワールドマトリックス
	int m_nMineCT;														//地雷のクールタイム
	int m_nLife;														//体力
	int m_nInvincibleCnt;												//無敵時間
};

#endif