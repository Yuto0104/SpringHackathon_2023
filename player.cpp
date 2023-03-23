//=============================================================================
//
// player.cpp
// Author : 梶田大夢
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "player.h"
#include "camera.h"
#include "application.h"
#include "score.h"
#include "keyboard.h"
#include "collision_rectangle3D.h"
#include "debug_proc.h"
#include "enemy.h"

//=============================================================================
//							静的変数の初期化
//=============================================================================
const float CPlayer::m_MaxWalkingSpeed = 1.0f;			//最大歩くスピード

//コンストラクタ
CPlayer::CPlayer()
{
	//タイプの付与
	SetObjType(OBJETYPE_PLAYER);

	//メンバー変数をクリアする
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);			//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//速度の初期化処理
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き
}

//デストラクタ
CPlayer::~CPlayer()
{

}

//初期化処理
HRESULT CPlayer::Init(void)
{
	//メンバー変数の初期化処理
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//速度の初期化処理
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き

	// 3D矩形の当たり判定の設定
	m_pCollisionRectangle3D = CCollision_Rectangle3D::Create();
	m_pCollisionRectangle3D->SetParent(this);
	m_pCollisionRectangle3D->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCollisionRectangle3D->SetSize(D3DXVECTOR3(45.0f, 45.0f, 20.0f));

	CObject3D::Init();

	return S_OK;
}

//終了処理
void CPlayer::Uninit(void)
{
	CObject3D::Uninit();

	if (m_pCollisionRectangle3D != nullptr)
	{//3D矩形の当たり判定の終了処理
		m_pCollisionRectangle3D->Uninit();
		m_pCollisionRectangle3D = nullptr;
	}

	//解放
	Release();
}

//更新処理
void CPlayer::Update(void)
{
	PlayerController();

	m_pos = CObject3D::GetPos();
	m_rot = CObject3D::GetRot();

	//前回位置の保存
	SetPosOld(m_pos);

	m_pos += m_move;

	SetPos(m_pos);
	SetRot(m_rot);

	//移動量を更新(減衰させる)
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.y += (0.0f - m_move.y) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	//当たり判定
	if (m_pCollisionRectangle3D->Collision(CObject::OBJETYPE_ENEMY, true))
	{
		CEnemy *pEnemy = (CEnemy*)m_pCollisionRectangle3D->GetCollidedObj();

		D3DXVECTOR3 move = pEnemy->GetPos() - pEnemy->GetPosOld();

		m_pos = GetPos();

		if (m_pCollisionRectangle3D->GetState() == CCollision_Rectangle3D::STATE_X)
		{
			m_pos.x += move.x;
		}
		else if (m_pCollisionRectangle3D->GetState() == CCollision_Rectangle3D::STATE_Y)
		{
			m_pos.y += move.y;
		}

		SetPos(m_pos);
	}

#ifdef _DEBUG
	CDebugProc::Print("プレイヤーの位置 | X : %.3f | Y : %.3f | Z : %.3f |\n", m_pos.x, m_pos.y, m_pos.z);
#endif // _DEBUG
}

void CPlayer::Draw(void)
{
	CObject3D::Draw();
}

//生成処理
CPlayer* CPlayer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	CPlayer* pPlayer = new CPlayer;		//インスタンスを生成する

	pPlayer->Init();
	pPlayer->SetPos(pos);
	pPlayer->SetSize(size);
	
	//生成したインスタンスを返す
	return pPlayer;
}

//プレイヤーのキー処理
void CPlayer::PlayerController(void)
{
	CKeyboard *pKeyboard = CApplication::GetKeyboard();
	D3DXVECTOR3 cameraRot = CApplication::GetCamera()->GetRot();	//カメラの向きの取得処理

	//移動量と目的の角度の計算
	if (pKeyboard->GetPress(DIK_UP))
	{//Wキーが押された場合
		if (pKeyboard->GetPress(DIK_LEFT))
		{//Aキーも押された場合
			m_move.x -= sinf(D3DX_PI * 0.75f + cameraRot.y) * m_MaxWalkingSpeed;
			m_move.y -= cosf(D3DX_PI * 0.75f + cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y - D3DX_PI * 0.25f;
		}
		else if (pKeyboard->GetPress(DIK_RIGHT))
		{//Dキーも押された場合
			m_move.x += sinf(D3DX_PI * 0.25f + cameraRot.y) * m_MaxWalkingSpeed;
			m_move.y += cosf(D3DX_PI * 0.25f + cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y + D3DX_PI * 0.25f;
		}
		else
		{//Wキーだけが押された場合
			m_move.x += sinf(cameraRot.y) * m_MaxWalkingSpeed;
			m_move.y += cosf(cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y;
		}
	}
	else if (pKeyboard->GetPress(DIK_DOWN))
	{//Sキーが押された場合
		if (pKeyboard->GetPress(DIK_LEFT))
		{//Aキーも押された場合
			m_move.x -= sinf(D3DX_PI * 0.25f + cameraRot.y) * m_MaxWalkingSpeed;
			m_move.y -= cosf(D3DX_PI * 0.25f + cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y - D3DX_PI * 0.75f;
		}
		else if (pKeyboard->GetPress(DIK_RIGHT))
		{//Dキーも押された場合
			m_move.x += sinf(D3DX_PI * 0.75f + cameraRot.y) * m_MaxWalkingSpeed;
			m_move.y += cosf(D3DX_PI * 0.75f + cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y + D3DX_PI * 0.75f;
		}
		else
		{//Sキーだけが押された場合
			m_move.x -= sinf(cameraRot.y) * m_MaxWalkingSpeed;
			m_move.y -= cosf(cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y - D3DX_PI;
		}
	}
	else if (pKeyboard->GetPress(DIK_RIGHT))
	{//Dキーだけ押された場合
		m_move.x += sinf(D3DX_PI * 0.5f + cameraRot.y) * m_MaxWalkingSpeed;
		m_move.y += cosf(D3DX_PI * 0.5f + cameraRot.y) * m_MaxWalkingSpeed;

		m_rot.y = cameraRot.y + D3DX_PI* 0.5f;
	}
	else if (pKeyboard->GetPress(DIK_LEFT))
	{//Aキーだけ押された場合
		m_move.x -= sinf(D3DX_PI * 0.5f + cameraRot.y) * m_MaxWalkingSpeed;
		m_move.y -= cosf(D3DX_PI * 0.5f + cameraRot.y) * m_MaxWalkingSpeed;

		m_rot.y = cameraRot.y - D3DX_PI * 0.5f;
	}
}