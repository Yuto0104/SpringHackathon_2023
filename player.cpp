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
#include "debug_proc.h"

//=============================================================================
//							静的変数の初期化
//=============================================================================
const float CPlayer::m_MaxWalkingSpeed = 7.0f;			//最大歩くスピード

//コンストラクタ
CPlayer::CPlayer()
{
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

	CObject3D::Init();

	return S_OK;
}

//終了処理
void CPlayer::Uninit(void)
{
	CObject3D::Uninit();
}

//更新処理
void CPlayer::Update(void)
{
	PlayerController();
	CObject3D::Update();

	m_pos = CObject3D::GetPos();
	m_rot = CObject3D::GetRot();

	m_pos += m_move;

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

	//プレイヤーの初期化処理
	if (FAILED(pPlayer->Init()))
	{
		return nullptr;
	}

	if (!pPlayer)
	{
		pPlayer->SetPos(pos);
		pPlayer->SetSize(size);
	}

	//生成したインスタンスを返す
	return pPlayer;
}

//プレイヤーのキー処理
void CPlayer::PlayerController(void)
{
	CKeyboard *pKeyboard = CApplication::GetKeyboard();
	D3DXVECTOR3 cameraRot = CApplication::GetCamera()->GetRot();	//カメラの向きの取得処理

	//移動量と目的の角度の計算
	if (pKeyboard->GetPress(DIK_W))
	{//Wキーが押された場合
		if (pKeyboard->GetPress(DIK_A))
		{//Aキーも押された場合
			m_move.x -= sinf(D3DX_PI * 0.75f + cameraRot.y) * m_MaxWalkingSpeed;
			m_move.z -= cosf(D3DX_PI * 0.75f + cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y - D3DX_PI * 0.25f;
		}
		else if (pKeyboard->GetPress(DIK_D))
		{//Dキーも押された場合
			m_move.x += sinf(D3DX_PI * 0.25f + cameraRot.y) * m_MaxWalkingSpeed;
			m_move.z += cosf(D3DX_PI * 0.25f + cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y + D3DX_PI * 0.25f;
		}
		else
		{//Wキーだけが押された場合
			m_move.x += sinf(cameraRot.y) * m_MaxWalkingSpeed;
			m_move.z += cosf(cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y;
		}
	}
	else if (pKeyboard->GetPress(DIK_S))
	{//Sキーが押された場合
		if (pKeyboard->GetPress(DIK_A))
		{//Aキーも押された場合
			m_move.x -= sinf(D3DX_PI * 0.25f + cameraRot.y) * m_MaxWalkingSpeed;
			m_move.z -= cosf(D3DX_PI * 0.25f + cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y - D3DX_PI * 0.75f;
		}
		else if (pKeyboard->GetPress(DIK_D))
		{//Dキーも押された場合
			m_move.x += sinf(D3DX_PI * 0.75f + cameraRot.y) * m_MaxWalkingSpeed;
			m_move.z += cosf(D3DX_PI * 0.75f + cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y + D3DX_PI * 0.75f;
		}
		else
		{//Sキーだけが押された場合
			m_move.x -= sinf(cameraRot.y) * m_MaxWalkingSpeed;
			m_move.z -= cosf(cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y - D3DX_PI;
		}
	}
	else if (pKeyboard->GetPress(DIK_D))
	{//Dキーだけ押された場合
		m_move.x += sinf(D3DX_PI * 0.5f + cameraRot.y) * m_MaxWalkingSpeed;
		m_move.z += cosf(D3DX_PI * 0.5f + cameraRot.y) * m_MaxWalkingSpeed;

		m_rot.y = cameraRot.y + D3DX_PI* 0.5f;
	}
	else if (pKeyboard->GetPress(DIK_A))
	{//Aキーだけ押された場合
		m_move.x -= sinf(D3DX_PI * 0.5f + cameraRot.y) * m_MaxWalkingSpeed;
		m_move.z -= cosf(D3DX_PI * 0.5f + cameraRot.y) * m_MaxWalkingSpeed;

		m_rot.y = cameraRot.y - D3DX_PI * 0.5f;
	}
}