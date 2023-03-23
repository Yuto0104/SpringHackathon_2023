//=============================================================================
//
// �I�u�W�F�N�g�N���X(Super.h)
// Author : �������l
// �T�v : �I�u�W�F�N�g�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "super.h"
#include "debug_proc.h"
#include "renderer.h"
#include "application.h"
#include "object.h"
#include "camera.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CSuper *CSuper::m_pTop[MAX_LEVEL] = { nullptr };		// �擪�I�u�W�F�N�g�ւ̃|�C���^
CSuper *CSuper::m_pCurrent[MAX_LEVEL] = { nullptr };	// ���݂�(��Ԍ��)�I�u�W�F�N�g�ւ̃|�C���^
int CSuper::m_nMax = 0;									// �g�p��
int CSuper::m_nPriorityMax[MAX_LEVEL] = { 0 };			// �v���C�I���e�B���Ƃ̃I�u�W�F�N�g��
bool CSuper::m_bPause = false;							// �|�[�Y���g�p���Ă��邩�ǂ���

//=============================================================================
// �C���X�^���X�̉��
// Author : �������l
// �T�v : ���ׂẴC���X�^���X��������鏈��
//=============================================================================
void CSuper::ReleaseAll(bool bPermanent)
{
	for (int nCntPriority = 0; nCntPriority < MAX_LEVEL; nCntPriority++)
	{
		if (m_pTop[nCntPriority] != nullptr)
		{// �ϐ��錾
			CSuper *pSuper = m_pTop[nCntPriority];

			while (pSuper)
			{// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g��ۊ�
				CSuper *pSuperNext = pSuper->m_pNext;
				if (bPermanent)
				{
					if (!pSuper->m_bDeath)
					{// �I������
						pSuper->Uninit();

						// �I�u�W�F�N�g�̉��
						pSuper->Release();
					}
				}
				else
				{
					if (!pSuper->m_bDeath
						&& !pSuper->m_bPermanent)
					{// �I������
						pSuper->Uninit();

						// �I�u�W�F�N�g�̉��
						pSuper->Release();
					}
				}

				// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���X�V
				pSuper = pSuperNext;
			}
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
void CSuper::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_LEVEL; nCntPriority++)
	{
		if (m_pTop[nCntPriority] != nullptr)
		{// �ϐ��錾
			CSuper *pSuper = m_pTop[nCntPriority];

			while (pSuper)
			{// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g��ۊ�
				CSuper *pSuperNext = pSuper->m_pNext;

				if (!pSuper->m_bDeath)
				{// �I�u�W�F�N�g�̍X�V
					if (pSuper->GetElement() != ELEMENT_OBJECT)
					{
						pSuper->Update();
					}
					if (pSuper->GetElement() == ELEMENT_OBJECT)
					{
						CObject *pObject = (CObject*)pSuper;
					
						if (!m_bPause)
						{
							pSuper->Update();
						}
						else if (m_bPause
							&& pObject->GetObjType() == CObject::OBJTYPE_PAUSE)
						{
							pSuper->Update();
						}
						else if (m_bPause
							&& pObject->GetObjType() == CObject::OBJTYPE_SELECT_ITEM)
						{
							pSuper->Update();
						}
					}
				}
				
				// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���X�V
				pSuper = pSuperNext;
			}
		}
	}
}

//=============================================================================
// ���ׂẴC���X�^���X�̕`��
// Author : �������l
// �T�v : �g�p����Ă�C���X�^���X�̕`�揈�����Ăяo��
//=============================================================================
void CSuper::DrawAll()
{
	// �J�����|�C���^
	CCamera *pCamera = CApplication::GetCamera();

	// �J�����̕`��
	pCamera->Set();

	for (int nCntPriority = 0; nCntPriority < MAX_LEVEL; nCntPriority++)
	{
		if (m_pTop[nCntPriority] != nullptr)
		{// �ϐ��錾
			CSuper *pSuper = m_pTop[nCntPriority];

			while (pSuper)
			{// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g��ۊ�
				CSuper *pSuperNext = pSuper->m_pNext;

				if (!pSuper->m_bDeath)
				{// �I�u�W�F�N�g�̕`��
					pSuper->Draw();
				}

				// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���X�V
				pSuper = pSuperNext;
			}
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
void CSuper::ReleaseListAll()
{
	for (int nCntPriority = 0; nCntPriority < MAX_LEVEL; nCntPriority++)
	{
		if (m_pTop[nCntPriority] != nullptr)
		{// �ϐ��錾
			CSuper *pSuper = m_pTop[nCntPriority];

			while (pSuper)
			{// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g��ۊ�
				CSuper *pSuperNext = pSuper->m_pNext;

				if (pSuper->m_bDeath)
				{// �I�u�W�F�N�g�̃��X�g����
					pSuper->ReleaseList();
				}

				// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���X�V
				pSuper = pSuperNext;
			}
		}
	}
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CSuper::CSuper(int nPriority/* = PRIORITY_LEVEL0*/) : m_pPrev(nullptr),			// �O�̃I�u�W�F�N�g�ւ̃|�C���^
m_pNext(nullptr),																// ���̃I�u�W�F�N�g�ւ̃|�C���^
m_EElement(ELEMENT_NONE),														// �v�f
m_nLevPriority(nPriority),														// �v���C�I���e�B�̃��x��
m_bDeath(false)																	// ���S�t���O
{
	// �g�p���̃C���N�������g
	m_nMax++;
	m_nPriorityMax[m_nLevPriority]++;

	if (m_pTop[m_nLevPriority] == nullptr)
	{// �擪�|�C���^�[�̐ݒ�
		m_pTop[m_nLevPriority] = this;
	}
	else
	{// �ߋ��̍Ō���I�u�W�F�N�g�̎��̃I�u�W�F�N�g��ݒ�
		m_pCurrent[m_nLevPriority]->m_pNext = this;

		// �����̑O�̃I�u�W�F�N�g�̐ݒ�
		this->m_pPrev = m_pCurrent[m_nLevPriority];
	}
	
	// ���������݂̃I�u�W�F�N�g�ɐݒ�
	m_pCurrent[m_nLevPriority] = this;
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CSuper::~CSuper()
{
	
}

//=============================================================================
// �C���X�^���X�̉��
// Author : �������l
// �T�v : ���ׂẴC���X�^���X��������鏈��
//=============================================================================
void CSuper::Release(void)
{
	if (!m_bDeath)
	{// �g�p���̃f�N�������g
		m_nMax--;
		m_nPriorityMax[m_nLevPriority]--;

		// ���S�t���O�𗧂Ă�
		m_bDeath = true;
	}
}

//=============================================================================
// ���X�g�̉����Ɣj��
// Author : �������l
// �T�v : ���X�g�̉����Ɣj�������鏈��
//=============================================================================
void CSuper::ReleaseList(void)
{
	if (m_pTop[m_nLevPriority] == this)
	{// �擪�I�u�W�F�N�g�������̎��̃I�u�W�F�N�g�ɐݒ�
		m_pTop[m_nLevPriority] = m_pNext;
	}
	if (m_pCurrent[m_nLevPriority] == this)
	{// �Ō���I�u�W�F�N�g�������̑O�̃I�u�W�F�N�g�ɐݒ�
		m_pCurrent[m_nLevPriority] = m_pPrev;
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

