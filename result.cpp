//=============================================================================
//
// ���U���g�N���X(result.cpp)
// Author : �������l
// �T�v : ���U���g�N���X�̊Ǘ����s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "result.h"
#include "keyboard.h"
#include "object2D.h"
#include "score.h"
#include "ranking.h"
#include "sound.h"

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CResult::CResult()
{
	m_nextMode = CApplication::MODE_NONE;		// ���ɐݒ肷�郂�[�h
	m_pTitleObj = nullptr;						// �^�C�g���I�u�W�F�N�g
	m_pGameObj = nullptr;						// �Q�[���I�u�W�F�N�g
	m_pScore = nullptr;							// �X�R�A�N���X
	m_pRanking = nullptr;						// �����L���O�N���X
	m_fAddAlpha = 0.0f;							// �A���t�@�̉��Z�l
	m_nCntFrame = 0;							// �t���[���J�E���g
	m_bPressEnter = true;						// �v���X�G���^�[���g�p�ł��邩
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CResult::Init()
{
	//SE
	CApplication::GetSound()->Play(CSound::SOUND_LABEL_BGM_BGM002);
	// ���ɍs�����[�h�̐ݒ�
	m_nextMode = CApplication::MODE_TITLE;

	m_pTitleObj = CObject2D::Create();
	m_pTitleObj->SetPos(D3DXVECTOR3(340.0f, 650.0f, 0.0f));
	m_pTitleObj->SetSize(D3DXVECTOR3(300.0f, 100.0f, 0.0f));
	m_pTitleObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pTitleObj->LoadTex(-1);

	m_pGameObj = CObject2D::Create();
	m_pGameObj->SetPos(D3DXVECTOR3(940.0f, 650.0f, 0.0f));
	m_pGameObj->SetSize(D3DXVECTOR3(320.0f, 100.0f, 0.0f));
	m_pGameObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pGameObj->LoadTex(-1);

	m_pScore = CScore::Create(10, false);
	m_pScore->SetDestScore(CApplication::GetScore());
	m_pScore->SetScore(CApplication::GetScore());
	m_pScore->SetPos(D3DXVECTOR3(900.0f, 530.0, 0.0f));
	m_pScore->SetSize(D3DXVECTOR3(80.0f, 80.0, 0.0f));
	m_pScore->SetWholeSize(D3DXVECTOR3(480.0f, 70.0, 0.0f));

	m_pRanking = CRanking::Create(5, CApplication::GetScore());
	m_pRanking->SetPos(D3DXVECTOR3(660.0f, 280.0f, 0.0f));
	m_pRanking->SetWholeSize(D3DXVECTOR3(500.0f, 300.0f, 0.0f));

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CResult::Uninit()
{
	// �T�E���h���̎擾
	CSound *pSound = CApplication::GetSound();

	// �T�E���h�I��
	pSound->Stop();

	// �X�R�A�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CResult::Update()
{
	// �T�E���h���̎擾
	CSound *pSound = CApplication::GetSound();

	AutoTransition();

	if (m_bPressEnter)
	{
		SelectMode();
	}

	FlashObj();

	// ���͏��̎擾
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	if (m_bPressEnter
		&& pKeyboard->GetTrigger(DIK_RETURN))
	{
		//pSound->PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
		m_bPressEnter = false;
	}

	if (!m_bPressEnter
		&& m_nCntFrame >= 40)
	{
		CApplication::SetNextMode(m_nextMode);
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CResult::Draw()
{

}

//=============================================================================
// �I�u�W�F�N�g�̓_��
// Author : �������l
// �T�v : �w��̃I�u�W�F�N�g��_�ł�����
//=============================================================================
void CResult::FlashObj()
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
	case CApplication::MODE_TITLE:
		pObj = m_pTitleObj;
		m_pGameObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;

	case CApplication::MODE_GAME:
		pObj = m_pGameObj;
		m_pTitleObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
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
void CResult::SelectMode()
{
	int nMode = (int)m_nextMode;

	// ���͏��̎擾
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	// �T�E���h���̎擾
	CSound *pSound = CApplication::GetSound();

	if (pKeyboard->GetTrigger(DIK_A))
	{
		//pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		nMode--;

		if (nMode < 0)
		{
			nMode = 1;
		}
	}
	else if (pKeyboard->GetTrigger(DIK_D))
	{
		//pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		nMode++;

		if (nMode > 1)
		{
			nMode = 0;
		}
	}

	m_nextMode = (CApplication::SCENE_MODE)nMode;
}

//=============================================================================
// �����J��
// Author : �������l
// �T�v : �����ŉ�ʑJ�ڂ���
//=============================================================================
void CResult::AutoTransition()
{
	m_nCntFrame++;

	if (m_nCntFrame >= 1800)
	{
		m_bPressEnter = false;
		m_nextMode = CApplication::MODE_TITLE;
		m_nCntFrame = 0;
	}
}

