//=============================================================================
//
// player.cpp
// Author : ���c�喲 ����]��
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "player.h"
#include "camera.h"
#include "application.h"
#include "score.h"
#include "keyboard.h"
#include "collision_rectangle3D.h"
#include "debug_proc.h"
#include "game.h"
#include "enemy.h"
#include "forcefield.h"
#include "missile.h"
#include "bullet3D.h"
#include "sound.h"

//=============================================================================
//							�ÓI�ϐ��̏�����
//=============================================================================
const float CPlayer::m_MaxWalkingSpeed = 1.0f;			//�ő�����X�s�[�h

//�R���X�g���N�^
CPlayer::CPlayer()
{
	//�^�C�v�̕t�^
	SetObjType(OBJETYPE_PLAYER);

	//�����o�[�ϐ����N���A����
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);			//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���x�̏���������
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
}

//�f�X�g���N�^
CPlayer::~CPlayer()
{

}

//����������
HRESULT CPlayer::Init(void)
{
	//�����o�[�ϐ��̏���������
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���x�̏���������
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
	m_nLife = 10;
	m_nBulletCreateTime = 0;
	m_nMineCT = 0;									//�N�[���^�C��
	m_nInvincibleCnt = 0;							//���G����
	m_bTex = false;

	// 3D��`�̓����蔻��̐ݒ�
	m_pCollisionRectangle3D = CCollision_Rectangle3D::Create();
	m_pCollisionRectangle3D->SetParent(this);
	m_pCollisionRectangle3D->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCollisionRectangle3D->SetSize(D3DXVECTOR3(45.0f, 45.0f, 20.0f));

	CObject3D::Init();

	// �e�N�X�`�����W�̐ݒ�
	SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f / 2, 1.0f));
	LoadTex(1);

	return S_OK;
}

//�I������
void CPlayer::Uninit(void)
{
	CObject3D::Uninit();

	if (m_pCollisionRectangle3D != nullptr)
	{//3D��`�̓����蔻��̏I������
		m_pCollisionRectangle3D->Uninit();
		m_pCollisionRectangle3D = nullptr;
	}

	//���
	Release();
}

//�X�V����
void CPlayer::Update(void)
{
	PlayerController();

	m_pos = CObject3D::GetPos();
	m_rot = CObject3D::GetRot();

	//�O��ʒu�̕ۑ�
	SetPosOld(m_pos);

	m_pos += m_move;

	m_nBulletCreateTime--;
	if (m_nBulletCreateTime <= 0)
	{
		CMissile::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_nBulletCreateTime = 350;
	}

	SetPos(m_pos);
	SetRot(m_rot);

	//�ړ��ʂ��X�V(����������)
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.y += (0.0f - m_move.y) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	//���G����
	if (m_nInvincibleCnt > 0)
	{
		m_nInvincibleCnt--;			//���G���Ԃ̌��Z
	}

	//�����蔻��(���G���Ԃ�0�ȉ��Ȃ�)
	if (m_pCollisionRectangle3D->Collision(CObject::OBJETYPE_ENEMY, true) && m_nInvincibleCnt <= 0)
	if (m_bTex)
	{
		// �e�N�X�`�����W�̐ݒ�
		SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f / 2, 1.0f));
	}
	else
	{
		// �e�N�X�`�����W�̐ݒ�
		SetTex(D3DXVECTOR2(0.5f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	}

	//�����蔻��
	if (m_pCollisionRectangle3D->Collision(CObject::OBJETYPE_ENEMY, true))
	{
		// �̗͂̌���
		m_nLife--;
		// �T�E���h���̎擾
		//SE
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_HIT);
		// ���G���Ԃ̐ݒ�
		m_nInvincibleCnt = 60;

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
	CDebugProc::Print("�v���C���[�̈ʒu | X : %.3f | Y : %.3f | Z : %.3f |\n", m_pos.x, m_pos.y, m_pos.z);
#endif // _DEBUG
}

void CPlayer::Draw(void)
{
	//�_�ł�����
	if (m_nInvincibleCnt % 10 <= 5)
	{
		CObject3D::Draw();
	}
}

//��������
CPlayer* CPlayer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	CPlayer* pPlayer = new CPlayer;		//�C���X�^���X�𐶐�����

	pPlayer->Init();
	pPlayer->SetPos(pos);
	pPlayer->SetSize(size);

	//���������C���X�^���X��Ԃ�
	return pPlayer;
}

//�v���C���[�̃L�[����
void CPlayer::PlayerController(void)
{
	CKeyboard *pKeyboard = CApplication::GetKeyboard();
	D3DXVECTOR3 cameraRot = CApplication::GetCamera()->GetRot();	//�J�����̌����̎擾����

	//�ړ��ʂƖړI�̊p�x�̌v�Z
	if (pKeyboard->GetPress(DIK_UP))
	{//W�L�[�������ꂽ�ꍇ
		if (pKeyboard->GetPress(DIK_LEFT))
		{//A�L�[�������ꂽ�ꍇ
			m_move.x -= sinf(D3DX_PI * 0.75f + cameraRot.y) * m_MaxWalkingSpeed;
			m_move.y -= cosf(D3DX_PI * 0.75f + cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y - D3DX_PI * 0.25f;

			m_bTex = true;
		}
		else if (pKeyboard->GetPress(DIK_RIGHT))
		{//D�L�[�������ꂽ�ꍇ
			m_move.x += sinf(D3DX_PI * 0.25f + cameraRot.y) * m_MaxWalkingSpeed;
			m_move.y += cosf(D3DX_PI * 0.25f + cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y + D3DX_PI * 0.25f;

			m_bTex = false;
		}
		else
		{//W�L�[�����������ꂽ�ꍇ
			m_move.x += sinf(cameraRot.y) * m_MaxWalkingSpeed;
			m_move.y += cosf(cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y;
		}
	}
	else if (pKeyboard->GetPress(DIK_DOWN))
	{//S�L�[�������ꂽ�ꍇ
		if (pKeyboard->GetPress(DIK_LEFT))
		{//A�L�[�������ꂽ�ꍇ
			m_move.x -= sinf(D3DX_PI * 0.25f + cameraRot.y) * m_MaxWalkingSpeed;
			m_move.y -= cosf(D3DX_PI * 0.25f + cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y - D3DX_PI * 0.75f;

			m_bTex = true;
		}
		else if (pKeyboard->GetPress(DIK_RIGHT))
		{//D�L�[�������ꂽ�ꍇ
			m_move.x += sinf(D3DX_PI * 0.75f + cameraRot.y) * m_MaxWalkingSpeed;
			m_move.y += cosf(D3DX_PI * 0.75f + cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y + D3DX_PI * 0.75f;

			m_bTex = false;
		}
		else
		{//S�L�[�����������ꂽ�ꍇ
			m_move.x -= sinf(cameraRot.y) * m_MaxWalkingSpeed;
			m_move.y -= cosf(cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y - D3DX_PI;
		}
	}
	else if (pKeyboard->GetPress(DIK_RIGHT))
	{//D�L�[���������ꂽ�ꍇ
		m_move.x += sinf(D3DX_PI * 0.5f + cameraRot.y) * m_MaxWalkingSpeed;
		m_move.y += cosf(D3DX_PI * 0.5f + cameraRot.y) * m_MaxWalkingSpeed;

		m_rot.y = cameraRot.y + D3DX_PI* 0.5f;

		m_bTex = false;
	}
	else if (pKeyboard->GetPress(DIK_LEFT))
	{//A�L�[���������ꂽ�ꍇ
		m_move.x -= sinf(D3DX_PI * 0.5f + cameraRot.y) * m_MaxWalkingSpeed;
		m_move.y -= cosf(D3DX_PI * 0.5f + cameraRot.y) * m_MaxWalkingSpeed;

		m_rot.y = cameraRot.y - D3DX_PI * 0.5f;

		m_bTex = true;
	}
}