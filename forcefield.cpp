//=============================================================================
//
// �t�H�[�X�t�B�[���h�N���X(forcefield.h)
// Author : �ē�����
// �T�v : �t�H�[�X�t�B�[���h
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "forcefield.h"
#include "collision_rectangle3D.h"
#include "renderer.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "sound.h"
#include "application.h"

//=============================================================================
// �C���X�^���X����
// Author : �ē�����
// �T�v : �t�H�[�X�t�B�[���h�𐶐�����
//=============================================================================
CForceField * CForceField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �I�u�W�F�N�g�C���X�^���X
	CForceField *pForceField = nullptr;

	// �������̉��
	pForceField = new CForceField;
	// �������̊m�ۂ��ł��Ȃ�����
	assert(pForceField != nullptr);

	// �G�l�~�[�̏�����
	pForceField->Init();
	pForceField->SetPos(pos);
	pForceField->SetSize(size);
	pForceField->m_pCollisionRectangle3D->SetSize(D3DXVECTOR3(size.x * 2.0f, size.y * 2.0f, 10.0f));

	// �C���X�^���X��Ԃ�
	return pForceField;
}

//=============================================================================
// �R���X�g���N�^
// Author : �ē�����
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CForceField::CForceField()
{
	// �^�C�v�̕t�^
	SetObjType(OBJETYPE_FORCEFIELD);
}

//=============================================================================
// �f�X�g���N�^
// Author : �ē�����
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CForceField::~CForceField()
{

}

//=============================================================================
// ������
// Author : �ē�����
// �T�v : ������
//=============================================================================
HRESULT CForceField::Init()
{// ����������
	// �����o�ϐ��̏�����
	m_nDamage = 1;
	m_AttackTime = 0;

	CSkill::Init();

	LoadTex(4);

	return S_OK;
}

//=============================================================================
// �I��
// Author : �ē�����
// �T�v : �t�H�[�X�t�B�[���h�̉��
//=============================================================================
void CForceField::Uninit()
{
	// �I������
	CSkill::Uninit();

	// �t�H�[�X�t�B�[���h�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �ē�����
// �T�v : �t�H�[�X�t�B�[���h���X�V���s��
//=============================================================================
void CForceField::Update()
{// �X�V����
	CPlayer *pPlayer = CGame::GetPlayer();
	if (pPlayer != nullptr)
	{
		//�ʒu�̎擾
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

		m_AttackTime--;

		if (m_AttackTime <= 0)
		{
			// �����蔻��
			if (m_pCollisionRectangle3D->Collision(CObject::OBJETYPE_ENEMY, false))
			{
				// ������������̏��������Ă����
				CEnemy *pEnemy = (CEnemy*)m_pCollisionRectangle3D->GetCollidedObj();
				//���C�t�̌���
				pEnemy->SetLife(pEnemy->GetLife() - m_nDamage);
				// �T�E���h���̎擾
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_HIT);

				m_AttackTime = 50;
			}
		}
		SetPos(PlayerPos);
	}
}

//=============================================================================
// �`��
// Author : �ē�����
// �T�v : �t�H�[�X�t�B�[���h��`����s��
//=============================================================================
void CForceField::Draw()
{// �`�揈��
	CSkill::Draw();
}
