//=============================================================================
//
// select_item.cpp
// Author : ���c�喲
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "select_item.h"
#include "object2D.h"
#include "renderer.h"
#include "application.h"
#include "keyboard.h"
#include "sound.h"
#include "fade.h"
#include "lille.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : �X�R�A�𐶐�����
//=============================================================================
CSelectItem *CSelectItem::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CSelectItem *pPause = nullptr;

	pPause = new CSelectItem;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pPause != nullptr);

	// ���l�̏�����
	pPause->Init();

	// �C���X�^���X��Ԃ�
	return pPause;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CSelectItem::CSelectItem(int nPriority /*= CObject::PRIORITY_LEVEL3*/) : CObject(nPriority)
{
	m_nextMode = MODE_SLOT;								// ���̃��[�h
	m_pSelectBGObj = nullptr;							// �Z���N�g�w�i�I�u�W�F�N�g
	m_pSlotObj = nullptr;								// �X���b�g�I�u�W�F�N�g
	m_pItemObj = nullptr;								// �A�C�e���I�u�W�F�N�g
	m_pLille = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ߋ��̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �傫
	
	m_fAddAlpha = 0.0f;									// �t���[�����̃J�E���g
	m_nCntFrame = 0;									// �t���[���J�E���g
	m_bPressEnter = true;								// �G���^�[�L�[�������邩
	m_bPause = false;									// �|�[�Y���Ă��邩
	m_bSelect = false;									// �I���̎g�p��
	m_bSlot = false;									// �X���b�g
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CSelectItem::~CSelectItem()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CSelectItem::Init()
{
	m_pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(400.0f, 400.0f, 0.0f);
	SetObjType(CObject::OBJTYPE_SELECT_ITEM);

	// �����t���O
	SetPermanent(true);

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CSelectItem::Uninit()
{
	// �X�R�A�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CSelectItem::Update()
{
	// ���͏��̎擾
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	if (CApplication::GetMode() == CApplication::MODE_GAME
		&& !CApplication::GetFade()->GetFadeSituation())
	{
		if (m_bSelect)
		{// �I�����
			Select();
		}

		if (m_bSlot
			&& m_pLille != nullptr
			&& pKeyboard->GetTrigger(DIK_RETURN))
		{
			m_pLille->StopScroll();
			m_nCntFrame = 0;
		}
		else if (m_bSlot
			&& m_pLille != nullptr
			&& !m_pLille->GetScroll())
		{
			m_nCntFrame++;

			if (m_nCntFrame % 60 == 0)
			{
				m_nCntFrame = 0;
				m_pLille->Uninit();
				m_pLille = nullptr;
				m_bSlot = false;
				SetPause(false, false);
			}
		}
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CSelectItem::Draw()
{

}

//=============================================================================
// �ʒu�̃Z�b�^�[
// Author : �������l
// �T�v : �ʒu�̃����o�ϐ��Ɉ�������
//=============================================================================
void CSelectItem::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}

//=============================================================================
// �����̃Z�b�^�[
// Author : �������l
// �T�v : �����̃����o�ϐ��Ɉ�������
//=============================================================================
void CSelectItem::SetRot(const D3DXVECTOR3 &rot)
{
	m_rot = rot;
}

//=============================================================================
// �傫���̃Z�b�^�[
// Author : �������l
// �T�v : �傫���̃����o�ϐ��Ɉ�������
//=============================================================================
void CSelectItem::SetSize(const D3DXVECTOR3 & size)
{
	m_size = size;
}

//=============================================================================
// �F�̃Z�b�^�[
// Author : �������l
// �T�v : �F�̐ݒ���s��
//=============================================================================
void CSelectItem::SetColor(const D3DXCOLOR & col)
{

}

//=============================================================================
// �|�[�Y�̃Z�b�^�[
// Author : �������l
// �T�v : �|�[�Y�̐ݒ���s��
//=============================================================================
void CSelectItem::SetPause(const bool bPause, const bool bSelect)
{
	m_bPause = bPause;
	CSuper::SetPause(m_bPause);

	if (m_bPause)
	{
		m_bSelect = true;

		// �Z���N�g�w�i�I�u�W�F�N�g
		m_pSelectBGObj = CObject2D::Create();
		m_pSelectBGObj->SetSize(m_size);
		m_pSelectBGObj->SetPos(m_pos);
		m_pSelectBGObj->LoadTex(-1);
		m_pSelectBGObj->SetCol(D3DXCOLOR(0.7f, 0.7f, 0.2f, 0.5f));
		m_pSelectBGObj->SetObjType(CObject::OBJTYPE_SELECT_ITEM);

		// �X���b�g�I�u�W�F�N�g
		m_pSlotObj = CObject2D::Create();
		m_pSlotObj->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 100.0f, m_pos.z));
		m_pSlotObj->SetSize(D3DXVECTOR3(300.0f, 150.0f, 0.0f));
		m_pSlotObj->LoadTex(13);
		m_pSlotObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pSlotObj->SetObjType(CObject::OBJTYPE_SELECT_ITEM);

		// �A�C�e���I�u�W�F�N�g
		m_pItemObj = CObject2D::Create();
		m_pItemObj->SetPos(D3DXVECTOR3(m_pos.x,m_pos.y - 100.0f,m_pos.z));
		m_pItemObj->SetSize(D3DXVECTOR3(300.0f, 150.0f, 0.0f));
		m_pItemObj->LoadTex(12);
		m_pItemObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pItemObj->SetObjType(CObject::OBJTYPE_SELECT_ITEM);
	}
	else
	{
		if (m_bSelect
			&& !m_bSlot)
		{
			m_bSelect = false;

			// �|�[�Y�w�i�I�u�W�F�N�g
			m_pSelectBGObj->Uninit();

			// �X���b�g�I�u�W�F�N�g
			m_pSlotObj->Uninit();

			// �A�C�e���I�u�W�F�N�g
			m_pItemObj->Uninit();
		}
	}
}

//=============================================================================
// �|�[�Y�̃Z�b�^�[
// Author : �������l
// �T�v : �|�[�Y�̐ݒ���s��
//=============================================================================
void CSelectItem::SetPause(const bool bPause)
{
	m_bPause = bPause;
	CSuper::SetPause(m_bPause);
	m_bSelect = false;
}

//=============================================================================
// �I�u�W�F�N�g�̓_��
// Author : �������l
// �T�v : �w��̃I�u�W�F�N�g��_�ł�����
//=============================================================================
void CSelectItem::FlashObj()
{
	CObject2D *pObj = nullptr;

	if (m_bPressEnter)
	{
		m_fAddAlpha += 0.07f;
	}
	else if (!m_bPressEnter)
	{
		m_fAddAlpha += 0.5f;
		m_nCntFrame++;
	}

	switch (m_nextMode)
	{
	case MODE_SLOT:
		pObj = m_pSlotObj;
		m_pItemObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;

	case MODE_ITEM:
		pObj = m_pItemObj;
		m_pSlotObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;

	default:
		assert(false);
		break;
	}

	pObj->SetCol(D3DXCOLOR(0.7f, 0.7f, 0.7f, sinf(m_fAddAlpha) * 3.0f));
}

//=============================================================================
// ���[�h�̑I��
// Author : �������l
// �T�v : ���[�h�̑I������
//=============================================================================
void CSelectItem::SelectMode()
{
	int nMode = (int)m_nextMode;

	// �T�E���h���̎擾
	CSound *pSound = CApplication::GetSound();

	// ���͏��̎擾
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_W))
	{
		//pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		nMode--;

		if (nMode < 0)
		{
			nMode = 1;
		}
	}
	else if (pKeyboard->GetTrigger(DIK_S))
	{
		//pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		nMode++;

		if (nMode > 1)
		{
			nMode = 0;
		}
	}

	m_nextMode = (NEXT_MODE)nMode;
}

//=============================================================================
// �I�����
// Author : �������l
// �T�v : �I�����
//=============================================================================
void CSelectItem::Select()
{
	// �T�E���h���̎擾
	CSound *pSound = CApplication::GetSound();

	// ���͏��̎擾
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	if (m_bPause)
	{
		if (m_bPressEnter)
		{
			SelectMode();
		}

		FlashObj();

		if (m_bPressEnter
			&& pKeyboard->GetTrigger(DIK_RETURN))
		{
			//pSound->PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
			m_bPressEnter = false;
		}

		if (!m_bPressEnter
			&& m_nCntFrame >= 40
			&& !m_bSlot)
		{
			m_bPressEnter = true;
			m_nCntFrame = 0;

			switch (m_nextMode)
			{
			case MODE_SLOT:

				m_pLille = CLille::Create();
				m_pLille->SetLille(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(300.0f, 400.0f, 0.0f));
				m_bSlot = true;

				m_bSelect = false;

				// �|�[�Y�w�i�I�u�W�F�N�g
				m_pSelectBGObj->Uninit();

				// �X���b�g�I�u�W�F�N�g
				m_pSlotObj->Uninit();

				// �A�C�e���I�u�W�F�N�g
				m_pItemObj->Uninit();

				break;

			case MODE_ITEM:
				SetPause(false, false);
				// �v���C���[�̗͉̑�
				break;

			default:
				assert(false);
				break;
			}
		}
	}
}