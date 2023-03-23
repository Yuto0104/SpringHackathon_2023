//=============================================================================
//
// �G�l�~�[�N���X(enemy.h)
// Author : ����]��
// �T�v : �I�u�W�F�N�g�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "enemy.h"
#include "collision_rectangle3D.h"
#include "renderer.h"
#include "game.h"
#include "player.h"
#include "score.h"
#include "application.h"

//=============================================================================
// �C���X�^���X����
// Author : ����]��
// �T�v : �G�l�~�[�𐶐�����
//=============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nLife)
{
	// �I�u�W�F�N�g�C���X�^���X
	CEnemy *pEnemy = nullptr;

	// �������̉��
	pEnemy = new CEnemy;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pEnemy != nullptr);

	// �G�l�~�[�̏�����
	pEnemy->Init();
	pEnemy->SetPos(pos);
	pEnemy->SetSize(size);
	pEnemy->m_nLife = nLife;

	// �C���X�^���X��Ԃ�
	return pEnemy;
}

//=============================================================================
// �R���X�g���N�^
// Author : ����]��
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CEnemy::CEnemy()
{
	// �^�C�v�̕t�^
	SetObjType(OBJETYPE_ENEMY);
}

//=============================================================================
// �f�X�g���N�^
// Author : ����]��
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// ������
// Author : ����]��
// �T�v : ������
//=============================================================================
HRESULT CEnemy::Init()
{// ����������
	CObject3D::Init();
	m_nLife = 0;

	// 3D��`�̓����蔻��̐ݒ�
	m_pCollisionRectangle3D = CCollision_Rectangle3D::Create();
	m_pCollisionRectangle3D->SetParent(this);
	m_pCollisionRectangle3D->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCollisionRectangle3D->SetSize(D3DXVECTOR3(45.0f, 45.0f, 10.0f));
	m_nLife = 50;

	// �e�N�X�`�����W�̐ݒ�
	SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f / 2, 1.0f));
	LoadTex(18);

	return S_OK;
}

//=============================================================================
// �I��
// Author : ����]��
// �T�v : �G�l�~�[�̉��
//=============================================================================
void CEnemy::Uninit()
{
	// �I������
	CObject3D::Uninit();

	if (m_pCollisionRectangle3D != nullptr)
	{// 3D��`�̓����蔻��̏I������
		m_pCollisionRectangle3D->Uninit();
		m_pCollisionRectangle3D = nullptr;
	}

	// �G�l�~�[�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : ����]��
// �T�v : �G�l�~�[�X�V���s��
//=============================================================================
void CEnemy::Update()
{// �X�V����
	// ���̎擾
	CPlayer *pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 pos = GetPos();
	if (pPlayer != nullptr)
	{
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

		// �ǔ�
		float fRot = sqrtf((float)(pow(PlayerPos.x - pos.x, 2) + pow(PlayerPos.y - pos.y, 2)));
		m_move.x = (PlayerPos.x - pos.x) / (fRot / 1.0f);
		m_move.y = (PlayerPos.y - pos.y) / (fRot / 1.0f);
	}

	//�O��ʒu�̕ۑ�
	SetPosOld(pos);

	// �ʒu�̍X�V
	pos += m_move;
	SetPos(pos);

	if (m_move.x >= 0.0f)
	{// �e�N�X�`�����W�̐ݒ�
		SetTex(D3DXVECTOR2(0.5f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	}
	else if(m_move.x <= 0.0f)
	{// �e�N�X�`�����W�̐ݒ�
		SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f / 2, 1.0f));	
	}

	// �����蔻��
	//m_pCollisionRectangle3D->Collision(CObject::OBJETYPE_PLAYER, true);
	m_pCollisionRectangle3D->Collision(CObject::OBJETYPE_ENEMY, true);

	// ���C�t0�ȉ�����
	if (m_nLife <= 0)
	{
		// �X�R�A�̉��Z
		CScore *pScore = CGame::GetScore();
		pScore->AddScore(100);
		// �I������
		Uninit();
		CGame::SetEnemy(nullptr);

		return;
	}
}

//=============================================================================
// �`��
// Author : ����]��
// �T�v : �G�l�~�[�`����s��
//=============================================================================
void CEnemy::Draw()
{// �`�揈��
	CObject3D::Draw();
}