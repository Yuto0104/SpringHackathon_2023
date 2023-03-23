//=============================================================================
//
// �|�[�Y�N���X(pause.cpp)
// Author : �������l
// �T�v : �|�[�Y�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "pause.h"
#include "object2D.h"
#include "renderer.h"
#include "application.h"
#include "keyboard.h"
#include "sound.h"
#include "fade.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : �X�R�A�𐶐�����
//=============================================================================
CPause *CPause::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CPause *pPause = nullptr;

	pPause = new CPause;

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
CPause::CPause(int nPriority /*= CObject::PRIORITY_LEVEL3*/) : CObject(nPriority)
{
	m_nextMode = MODE_RETURN;							// ���̃��[�h
	m_pPauseBGObj = nullptr;							// �|�[�Y�w�i�I�u�W�F�N�g
	m_pReturnObj = nullptr;								// ���^�[���I�u�W�F�N�g
	m_pNewGameObj = nullptr;							// �j���[�Q�[���I�u�W�F�N�g
	m_pTitleObj = nullptr;								// �^�C�g���I�u�W�F�N�g
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ߋ��̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �傫
	m_fAddAlpha = 0.0f;									// �t���[�����̃J�E���g
	m_nCntFrame = 0;									// �t���[���J�E���g
	m_bPressEnter = true;								// �G���^�[�L�[�������邩��
	m_bPause = false;									// �|�[�Y���Ă��邩
	m_bSelect = false;									// �I���̎g�p��
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CPause::~CPause()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CPause::Init()
{
	m_pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				
	m_size = D3DXVECTOR3(400.0f, 400.0f, 0.0f);
	SetObjType(CObject::OBJTYPE_PAUSE);

	// �����t���O
	SetPermanent(true);

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CPause::Uninit()
{
	// �X�R�A�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CPause::Update()
{
	if (CApplication::GetMode() == CApplication::MODE_GAME
		&& !CApplication::GetFade()->GetFadeSituation())
	{
		if (m_bSelect)
		{// �I�����
			Select();
		}
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CPause::Draw()
{

}

//=============================================================================
// �ʒu�̃Z�b�^�[
// Author : �������l
// �T�v : �ʒu�̃����o�ϐ��Ɉ�������
//=============================================================================
void CPause::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}

//=============================================================================
// �����̃Z�b�^�[
// Author : �������l
// �T�v : �����̃����o�ϐ��Ɉ�������
//=============================================================================
void CPause::SetRot(const D3DXVECTOR3 &rot)
{
	m_rot = rot;
}

//=============================================================================
// �傫���̃Z�b�^�[
// Author : �������l
// �T�v : �傫���̃����o�ϐ��Ɉ�������
//=============================================================================
void CPause::SetSize(const D3DXVECTOR3 & size)
{
	m_size = size;
}

//=============================================================================
// �F�̃Z�b�^�[
// Author : �������l
// �T�v : �F�̐ݒ���s��
//=============================================================================
void CPause::SetColor(const D3DXCOLOR & col)
{
	
}

//=============================================================================
// �|�[�Y�̃Z�b�^�[
// Author : �������l
// �T�v : �|�[�Y�̐ݒ���s��
//=============================================================================
void CPause::SetPause(const bool bPause, const bool bSelect)
{
	m_bPause = bPause;
	CSuper::SetPause(m_bPause);

	if (m_bPause)
	{
		m_bSelect = true;

		// �|�[�Y�w�i�I�u�W�F�N�g
		m_pPauseBGObj = CObject2D::Create();
		m_pPauseBGObj->SetSize(m_size);
		m_pPauseBGObj->SetPos(m_pos);
		m_pPauseBGObj->LoadTex(-1);
		m_pPauseBGObj->SetCol(D3DXCOLOR(0.7f, 0.7f, 0.2f, 0.5f));
		m_pPauseBGObj->SetObjType(CObject::OBJTYPE_PAUSE);

		// ���^�[���I�u�W�F�N�g
		m_pReturnObj = CObject2D::Create();					
		m_pReturnObj->SetSize(D3DXVECTOR3(300.0f, 100.0f, 0.0f));
		m_pReturnObj->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y - m_pReturnObj->GetSize().y - 20.0f, 0.0f));
		m_pReturnObj->LoadTex(-1);
		m_pReturnObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pReturnObj->SetObjType(CObject::OBJTYPE_PAUSE);

		// �j���[�Q�[���I�u�W�F�N�g
		m_pNewGameObj = CObject2D::Create();
		m_pNewGameObj->SetPos(m_pos);
		m_pNewGameObj->SetSize(D3DXVECTOR3(400.0f, 100.0f, 0.0f));
		m_pNewGameObj->LoadTex(-1);
		m_pNewGameObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pNewGameObj->SetObjType(CObject::OBJTYPE_PAUSE);

		// �^�C�g���I�u�W�F�N�g
		m_pTitleObj = CObject2D::Create();
		m_pTitleObj->SetSize(D3DXVECTOR3(300.0f, 100.0f, 0.0f));
		m_pTitleObj->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + m_pTitleObj->GetSize().y + 20.0f, 0.0f));
		m_pTitleObj->LoadTex(-1);
		m_pTitleObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pTitleObj->SetObjType(CObject::OBJTYPE_PAUSE);
	}
	else
	{
		if (m_bSelect)
		{
			m_bSelect = false;

			// �|�[�Y�w�i�I�u�W�F�N�g
			m_pPauseBGObj->Uninit();

			// ���^�[���I�u�W�F�N�g
			m_pReturnObj->Uninit();

			// �j���[�Q�[���I�u�W�F�N�g
			m_pNewGameObj->Uninit();

			// �^�C�g���I�u�W�F�N�g
			m_pTitleObj->Uninit();
		}
	}
}

//=============================================================================
// �|�[�Y�̃Z�b�^�[
// Author : �������l
// �T�v : �|�[�Y�̐ݒ���s��
//=============================================================================
void CPause::SetPause(const bool bPause)
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
void CPause::FlashObj()
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
	case MODE_RETURN:
		pObj = m_pReturnObj;
		m_pNewGameObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pTitleObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;

	case MODE_GAME:
		pObj = m_pNewGameObj;
		m_pReturnObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pTitleObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;

	case MODE_TITLE:
		pObj = m_pTitleObj;
		m_pReturnObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pNewGameObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
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
void CPause::SelectMode()
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
			nMode = 2;
		}
	}
	else if (pKeyboard->GetTrigger(DIK_S))
	{
		//pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		nMode++;

		if (nMode > 2)
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
void CPause::Select()
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
			&& m_nCntFrame >= 40)
		{
			m_bPressEnter = true;
			m_nCntFrame = 0;

			switch (m_nextMode)
			{
			case MODE_RETURN:
				SetPause(false, false);
				break;

			case MODE_GAME:
				SetPause(false, false);
				CApplication::SetNextMode(CApplication::MODE_GAME);
				break;

			case MODE_TITLE:
				SetPause(false, false);
				CApplication::SetNextMode(CApplication::MODE_TITLE);
				break;

			default:
				assert(false);
				break;
			}
		}
	}
}

