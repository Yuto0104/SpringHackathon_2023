//=============================================================================
//
// player.h
// Author : 梶田大夢
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

//=============================================================================
//プレイヤークラス
//=============================================================================
class CPlayer : public CObject3D
{
public:

	enum Parts
	{
		BODY = 0,								//体
		HEAD,									//頭
		LEFT_ARM,								//左腕
		LEFT_HAND,								//左手
		RIGHT_ARM,								//右腕
		RIGHT_HAND,								//右手
		LEFT_LEG,								//左足
		LEFT_FOOT,								//左太腿
		RIGHT_LEG,								//右足
		RIGHT_FOOT,								//右太腿
		PARTS_MAX
	};

	CPlayer();															//コンストラクタ
	~CPlayer() override;												//デストラクタ

	HRESULT Init(void) override;										//初期化処理
	void Uninit(void) override;											//終了処理
	void Update(void) override;											//更新処理
	void Draw(void) override;											//描画処理

	static CPlayer* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	//生成処理

private:
	void  PlayerController(void);										//プレイヤーの操作
	static const float m_MaxWalkingSpeed;								//最大の歩くスピード

	D3DXVECTOR3 m_pos;													//位置
	D3DXVECTOR3 m_move;													//速度
	D3DXVECTOR3 m_rot;													//向き
	D3DXMATRIX  m_mtxWorld;												//ワールドマトリックス
};

#endif