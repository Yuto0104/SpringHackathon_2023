//=============================================================================
//
// �Փ˔���N���X(collision.cpp)
// Author : �������l
// �T�v : �Փ˔��萶�����s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "collision.h"
#include "renderer.h"
#include "application.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CCollision *CCollision::m_pTop = { nullptr };			// �擪�I�u�W�F�N�g�ւ̃|�C���^
CCollision *CCollision::m_pCurrent = { nullptr };		// ���݂�(��Ԍ��)�I�u�W�F�N�g�ւ̃|�C���^
int CCollision::m_nMax = 0;								// �g�p��

//=============================================================================
// �C���X�^���X�̉��
// Author : �������l
// �T�v : ���ׂẴC���X�^���X��������鏈��
//=============================================================================
void CCollision::ReleaseAll()
{
	if (m_pTop != nullptr)
	{// �ϐ��錾
		CCollision *pCollision = m_pTop;

		while (pCollision)
		{// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g��ۊ�
			CCollision *pCollisionNext = pCollision->m_pNext;

			if (!pCollision->m_bDeath)
			{// �I������
				pCollision->Uninit();

				// �I�u�W�F�N�g�̉��
				pCollision->Release();
			}

			// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���X�V
			pCollision = pCollisionNext;
		}
	}

	// ���ׂẴ��X�g����
	ReleaseListAll();
}

//=============================================================================
// ���ׂẴC���X�^���X�̍X�V
// Author : �������l
// �T�v : �g�p����Ă�C���X�^���X�̍X�V�������Ăяo��
//=============================================================================
void CCollision::UpdateAll(void)
{
	if (m_pTop != nullptr)
	{// �ϐ��錾
		CCollision *pCollision = m_pTop;

		while (pCollision)
		{// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g��ۊ�
			CCollision *pCollisionNext = pCollision->m_pNext;

			if (!pCollision->m_bDeath)
			{// �I�u�W�F�N�g�̍X�V
				pCollision->Update();
			}

			// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���X�V
			pCollision = pCollisionNext;
		}
	}
}

//=============================================================================
// ���ׂẴC���X�^���X�̕`��
// Author : �������l
// �T�v : �g�p����Ă�C���X�^���X�̕`�揈�����Ăяo��
//=============================================================================
void CCollision::DrawAll()
{
	if (m_pTop != nullptr)
	{// �ϐ��錾
		CCollision *pCollision = m_pTop;

		while (pCollision)
		{// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g��ۊ�
			CCollision *pCollisionNext = pCollision->m_pNext;

			if (!pCollision->m_bDeath)
			{// �I�u�W�F�N�g�̕`��
				pCollision->Draw();
			}

			// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���X�V
			pCollision = pCollisionNext;
		}
	}

	// ���ׂẴ��X�g����
	ReleaseListAll();
}

//=============================================================================
// ���ׂẴI�u�W�F�N�g�̃��X�g����
// Author : �������l
// �T�v : ���ׂẴI�u�W�F�N�g�̃��X�g�������Ăяo��
//=============================================================================
void CCollision::ReleaseListAll()
{
	if (m_pTop != nullptr)
	{// �ϐ��錾
		CCollision *pCollision = m_pTop;

		while (pCollision)
		{// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g��ۊ�
			CCollision *pCollisionNext = pCollision->m_pNext;

			if (pCollision->m_bDeath)
			{// �I�u�W�F�N�g�̃��X�g����
				pCollision->ReleaseList();
			}

			// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���X�V
			pCollision = pCollisionNext;
		}
	}
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CCollision::CCollision() : m_pPrev(nullptr),			// �O�̃I�u�W�F�N�g�ւ̃|�C���^
m_pNext(nullptr),										// ���̃I�u�W�F�N�g�ւ̃|�C���^
m_pCollidedObj(nullptr),								// �Փ˂����I�u�W�F�N�g�ւ̃|�C���^
m_pParent(nullptr),										// �e�̃I�u�W�F�N�g
m_pos(D3DXVECTOR3(0.0f,0.0f,0.0f)),						// �ʒu
m_bUse(true),											// �g�p��
m_bDeath(false)											// ���S�t���O
{
	// �g�p���̃C���N�������g
	m_nMax++;

	if (m_pTop == nullptr)
	{// �擪�|�C���^�[�̐ݒ�
		m_pTop = this;
	}
	else
	{// �ߋ��̍Ō���I�u�W�F�N�g�̎��̃I�u�W�F�N�g��ݒ�
		m_pCurrent->m_pNext = this;

		// �����̑O�̃I�u�W�F�N�g�̐ݒ�
		this->m_pPrev = m_pCurrent;
	}
	
	// ���������݂̃I�u�W�F�N�g�ɐݒ�
	m_pCurrent = this;
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CCollision::~CCollision()
{
	
}

//=============================================================================
// �C���X�^���X�̉��
// Author : �������l
// �T�v : ���ׂẴC���X�^���X��������鏈��
//=============================================================================
void CCollision::Release(void)
{
	if (!m_bDeath)
	{// �g�p���̃f�N�������g
		m_nMax--;

		// ���S�t���O�𗧂Ă�
		m_bDeath = true;
	}
}

//=============================================================================
// ���X�g�̉����Ɣj��
// Author : �������l
// �T�v : ���X�g�̉����Ɣj�������鏈��
//=============================================================================
void CCollision::ReleaseList(void)
{
	if (m_pTop == this)
	{// �擪�I�u�W�F�N�g�������̎��̃I�u�W�F�N�g�ɐݒ�
		m_pTop = m_pNext;
	}
	if (m_pCurrent == this)
	{// �Ō���I�u�W�F�N�g�������̑O�̃I�u�W�F�N�g�ɐݒ�
		m_pCurrent = m_pPrev;
	}

	if (m_pPrev != nullptr)
	{// �O�̃I�u�W�F�N�g�̑O�̃I�u�W�F�N�g�Ɏ����̎��̃I�u�W�F�N�g��ݒ�
		m_pPrev->m_pNext = m_pNext;
	}
	if (m_pNext != nullptr)
	{// �����̎��̃I�u�W�F�N�g�Ɏ����̑O�̃I�u�W�F�N�g��ݒ�
		m_pNext->m_pPrev = m_pPrev;
	}

	// �I�u�W�F�N�g�̉��
	delete this;
}

