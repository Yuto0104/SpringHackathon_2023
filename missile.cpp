//=============================================================================
//
// �~�T�C���N���X(skill.h)
// Author : �ē�����
// �T�v : �I�u�W�F�N�g�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "missile.h"
#include "collision_rectangle3D.h"
#include "renderer.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "application.h"
#include "bullet.h"

//=============================================================================
// �C���X�^���X����
// Author : �ē�����
// �T�v : �~�T�C���𐶐�����
//=============================================================================
CMissile * CMissile::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �I�u�W�F�N�g�C���X�^���X
	CMissile *pMine = nullptr;

	// �������̉��
	pMine = new CMissile;
	// �������̊m�ۂ��ł��Ȃ�����
	assert(pMine != nullptr);

	// �G�l�~�[�̏�����
	pMine->Init();
	pMine->SetPos(pos);
	pMine->SetSize(size);
	pMine->m_pCollisionRectangle3D->SetSize(D3DXVECTOR3(size.x * 2.0f, size.y * 2.0f, 10.0f));

	// �C���X�^���X��Ԃ�
	return pMine;
}

//=============================================================================
// �R���X�g���N�^
// Author : �ē�����
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CMissile::CMissile()
{

}

//=============================================================================
// �f�X�g���N�^
// Author : �ē�����
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CMissile::~CMissile()
{

}

//=============================================================================
// ������
// Author : �ē�����
// �T�v : ������
//=============================================================================
HRESULT CMissile::Init()
{// ����������
	m_BulletMove = D3DXVECTOR3(0.0f,0.0f,0.0f);

	CSkill::Init();

	return S_OK;
}

//=============================================================================
// �I��
// Author : �ē�����
// �T�v : �~�T�C���̉��
//=============================================================================
void CMissile::Uninit()
{
	// �I������
	CSkill::Uninit();

	// �~�T�C���̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �ē�����
// �T�v : �~�T�C���X�V���s��
//=============================================================================
void CMissile::Update()
{// �X�V����

	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	if (CGame::GetEnemy() != nullptr)
	{
		D3DXVECTOR3 EnemyPos = CGame::GetEnemy()->GetPos();

		m_BulletMove = PlayerPos - EnemyPos;
		D3DXVec3Normalize(&m_BulletMove, &m_BulletMove);
		m_BulletMove *= 15.0f;

		m_nNormalTime--;
		m_MissileTime--;

		if (m_nNormalTime <= 0)
		{
			m_pBullet = CBullet::Create(PlayerPos, -m_BulletMove, D3DXVECTOR3(5.0f, 5.0f, 0.0f), 100, CBullet::BulletType_Normal);
		}
		if (m_nNormalTime <= 0)
		{
			m_nNormalTime = 40;
		}

		if (m_MissileTime <= 0)
		{
			m_pBullet = CBullet::Create(PlayerPos, -m_BulletMove, D3DXVECTOR3(25.0f, 25.0f, 0.0f), 100, CBullet::BulletType_Missile);
		}
		if (m_MissileTime <= 0)
		{
			m_MissileTime = 250;
		}
	}

}

//=============================================================================
// �`��
// Author : �ē�����
// �T�v : �~�T�C���`����s��
//=============================================================================
void CMissile::Draw()
{// �`�揈��
	CSkill::Draw();
}