//============================================
//
//	bullet.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
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
// �ÓI�����o�ϐ��錾
//============================================
CBullet::BulletType CBullet::m_type = BulletType_Normal;

//============================================
// �e�̃R���X�g���N�^
//============================================
CBullet::CBullet()
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
	m_BulletPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�e�̈ʒu�̃N���A
	m_BulletPosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�e�̑O��̈ʒu�̃N���A
	m_BulletMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�e�̈ړ��̃N���A
	m_BulletSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�e�̃T�C�Y�̃N���A
	m_EnemyDeathFlag = false;								//�G�����񂾂̂��t���O�̃N���A
	m_GimmickUninitFlag = false;							//�M�~�b�N���������̂��t���O�̃N���A
	m_RandFlag = false;										//�����_���t���O�̃N���A
	m_BossDeathFlag = false;								//�{�X�����񂾂̂��̃t���O�̃N���A							
}

//============================================
// �e�̃f�X�g���N�^
//============================================
CBullet::~CBullet()
{
	//���������Ȃ�
}

//============================================
// �e�̏���������
//============================================
HRESULT CBullet::Init(void)
{
	//============================================
	//�����o�ϐ��̏�����
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

	//�I�u�W�F�N�g��b�̏���������
	CObject3D::Init();
	LoadTex(15);

	return S_OK;
}

//============================================
// �e�̏I������
//============================================
void CBullet::Uninit(void)
{
	//�I�u�W�F�N�g��b�̏I������
	CObject3D::Uninit();
}

//============================================
// �e�̍X�V����
//============================================
void CBullet::Update(void)
{
	//�e�̏��擾
	D3DXVECTOR3 BulletPos = GetPos();
	D3DXVECTOR3 BulletSize = GetSize();
	int BulletLife = GetBulletLife();

	//�J�����̏����擾
	CCamera *pCamera = CApplication::GetCamera();

	//�e�̈ʒu�X�V
	BulletPos += m_BulletMove;

	//�O��̈ʒu��ۑ�
	m_BulletPosOld = m_BulletPos;

	//���������炷����
	m_nLife--;

	//�v���C���[�̒e�̎�
	if (m_nLife <= 0 )
	{
		Uninit();
		return;
	}

	// �e�ƓG�̓����蔻�菈��
	//============================================
	if (m_EnemyDeathFlag == false && m_type == BulletType_Normal)
	{
		HitEnemy(BulletPos, 1);
	}

	if (m_EnemyDeathFlag == false && m_type == BulletType_Missile)
	{
		HitEnemy(BulletPos, 20);
	}

	//�ʒu�̐ݒ�
	SetPos(BulletPos);
	//�����̐ݒ�
	SetRot(m_BulletRot);
	//�T�C�Y�̐ݒ菈��
	SetSize(BulletSize);

	//============================================
	// �I�u�W�F�N�g��b�̍X�V����
	//============================================
	CObject3D::Update();
}

//============================================
// �e�̕`�揈��
//============================================
void CBullet::Draw(void)
{
	//�I�u�W�F�N�g��b�̕`�揈��
	CObject3D::Draw();
}

//============================================
// �e�̐���
//============================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife, BulletType type)
{
	CBullet *pBullet = nullptr;

	//�e�̃C���X�^���X�̐���
	pBullet = new CBullet;				//2D�I�u�W�F�N�g�̃C���X�^���X����

										//null�`�F�b�N
	if (pBullet != nullptr)
	{
		pBullet->SetType(type);
		//����������
		pBullet->Init();
		//�ݒ菈��
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
// �e�̃��C�t�̐ݒ菈��
//============================================
void CBullet::SetLife(int life)
{
	m_nLife = life;
}
//============================================
// �e�ƓG�̓����蔻��
//============================================
void CBullet::HitEnemy(D3DXVECTOR3 pos, int life)
{
	if (CGame::GetEnemy() != nullptr)
	{
		//�G�̈ʒu
		D3DXVECTOR3 EnemyPos = CGame::GetEnemy()->GetPos();
		//�G�̃T�C�Y
		D3DXVECTOR3 EnemySize = CGame::GetEnemy()->GetSize();
		//�G�̗̑�
		int EnemyLife = CGame::GetEnemy()->GetLife();
		//�e�ƓG�̓����蔻��
		if (pos.x + 0.5f >= EnemyPos.x - EnemySize.x
			&&pos.x - 0.5f <= EnemyPos.x + EnemySize.x
			&&pos.y + 0.5f >= EnemyPos.y - EnemySize.y
			&&pos.z + 0.5f >= EnemyPos.z - EnemySize.z
			&&pos.z - 0.5f <= EnemyPos.z + EnemySize.z)
		{
			//SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_HIT);
			//�e�̍폜
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
// �e�̗̑�
//============================================
void CBullet::BulletLife()
{
	//�e�̍폜
	m_nLife = 0;
	SetLife(m_nLife);
}
