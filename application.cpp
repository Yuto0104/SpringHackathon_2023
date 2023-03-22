//=============================================================================
//
// �A�v���P�[�V�����N���X(application.h)
// Author : �������l
// �T�v : �e�N���X�̌Ăяo�����s���N���X
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "application.h"

#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "super.h"
#include "renderer.h"
#include "debug_proc.h"
#include "keyboard.h"
#include "mouse.h"
#include "texture.h"
#include "sound.h"
#include "object.h"
#include "object2D.h"
#include "scene_mode.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "pause.h"
#include "tutorial.h"
#include "joypad.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
HWND CApplication::m_hWnd = nullptr;								// �E�B���h�E
CDebugProc *CApplication::m_pDebugProc = nullptr;					// �f�o�b�N�\��
CRenderer *CApplication::m_pRenderer = nullptr;						// �����_���[�C���X�^���X
CKeyboard *CApplication::m_pKeyboard = {};							// �L�[�{�[�h�C���X�^���X
CMouse *CApplication::m_pMouse = {};								// �}�E�X�C���X�^���X
CTexture *CApplication::m_pTexture = nullptr;						// �e�N�X�`���C���X�^���X
CApplication::SCENE_MODE CApplication::m_mode = MODE_NONE;			// ���݂̃��[�h�̊i�[
CApplication::SCENE_MODE CApplication::m_nextMode = MODE_TITLE;		// ���̃��[�h�̊i�[
CSceneMode *CApplication::pSceneMode = nullptr;						// �V�[�����[�h���i�[
CFade *CApplication::m_pFade = nullptr;								// �t�F�[�h�N���X
CSound *CApplication::m_pSound = nullptr;							// �T�E���h�N���X
CPause *CApplication::m_pPause = nullptr;							// �|�[�Y�N���X
CJoypad *CApplication::m_pJoy = nullptr;							// �W���C�p�b�h�N���X
int CApplication::m_nPriority = 0;									// �v���C�I���e�B�ԍ�
int CApplication::m_nScore = 0;										// ���݂̃X�R�A
bool CApplication::m_bWireFrame = false;							// ���C���[�t���[�����g����

//=============================================================================
// �V�[���̐ݒ�
// Author : �������l
// �T�v : ���݂̃V�[�����I�����A�V�����V�[����ݒ肷��
//=============================================================================
void CApplication::SetMode(SCENE_MODE mode)
{
	if (pSceneMode != nullptr)
	{
		pSceneMode->Uninit();
		pSceneMode = nullptr;
	}

	// �I�u�W�F�N�g�̉��
	CSuper::ReleaseAll(false);

	m_mode = mode;

	switch (m_mode)
	{
	case CApplication::MODE_TITLE:
		pSceneMode = new CTitle;
		break;

	case CApplication::MODE_GAME:
		pSceneMode = new CGame;
		break;

	case CApplication::MODE_RESULT:
		pSceneMode = new CResult;
		break;

	case CApplication::MODE_TUTORIAL:
		pSceneMode = new CTutorial;
		break;

	default:
		break;
	}

	if (pSceneMode != nullptr)
	{
		pSceneMode->Init();
	}
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CApplication::CApplication()
{
	// �^�������̏�����
	srand((unsigned int)time(NULL));
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CApplication::~CApplication()
{
	assert(m_pRenderer == nullptr);
	assert(m_pKeyboard == nullptr);
	assert(m_pMouse == nullptr);
	assert(m_pJoy == nullptr);
	assert(m_pTexture == nullptr);
	assert(m_pSound == nullptr);
}

//=============================================================================
// ������
// Author : �������l
// �T�v : �����o�ϐ���������A���N���X�̃N���G�C�g�֐����Ăяo��
//=============================================================================
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �E�B���h�E
	m_hWnd = hWnd;

	// �������̊m��	
	m_pRenderer = new CRenderer;
	m_pDebugProc = new CDebugProc;
	m_pTexture = new CTexture;
	m_pSound = new CSound;
	m_pJoy = new CJoypad;

	// ���̓f�o�C�X�̃������m��
	m_pKeyboard = new CKeyboard;
	m_pMouse = new CMouse;

	// ����������
	assert(m_pRenderer != nullptr);

	//if (FAILED(m_pRenderer->Init(m_hWnd, TRUE)) != 0)
	//{//���������������s�����ꍇ
	//	return-1;
	//}

#ifdef _DEBUG
	if (FAILED(m_pRenderer->Init(m_hWnd, TRUE)) != 0)
	{//���������������s�����ꍇ
		return-1;
	}
#else
	if (FAILED(m_pRenderer->Init(m_hWnd, FALSE)) != 0)
	{//���������������s�����ꍇ
		return-1;
	}
#endif

	// ����������
	assert(m_pTexture != nullptr);
	m_pTexture->Init();

	// ������
	assert(m_pDebugProc != nullptr);
	m_pDebugProc->Init();

	// ����������
	assert(m_pSound != nullptr);
	m_pSound->Init(m_hWnd);

	// ����������
	assert(m_pKeyboard != nullptr);
	if (FAILED(m_pKeyboard->Init(hInstance, m_hWnd)))
	{
		return E_FAIL;
	}

	// ����������
	assert(m_pMouse != nullptr);
	if (FAILED(m_pMouse->Init(hInstance, m_hWnd)))
	{
		return E_FAIL;
	}

	if (FAILED(m_pJoy->Init(1)))
	{
		return E_FAIL;
	}

	// �t�F�[�h�̐ݒ�
	m_pFade = CFade::Create();

	// �|�[�Y�̐���
	m_pPause = CPause::Create();
	m_pPause->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �������̉���ƃ����[�X�֐����Ăяo��
//=============================================================================
void CApplication::Uninit()
{
	// �I�u�W�F�N�g�̉��
	CSuper::ReleaseAll(true);

	if (m_pRenderer != nullptr)
	{// �I������
		m_pRenderer->Uninit();

		// �������̉��
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pDebugProc != nullptr)
	{// �I������
		m_pDebugProc->Uninit();

		// �������̉��
		delete m_pDebugProc;
		m_pDebugProc = nullptr;
	}

	if (m_pKeyboard != nullptr)
	{// �I������
		m_pKeyboard->Uninit();

		// �������̉��
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	if (m_pMouse != nullptr)
	{// �I������
		m_pMouse->Uninit();

		// �������̉��
		delete m_pMouse;
		m_pMouse = nullptr;
	}

	if (m_pTexture != nullptr)
	{// �I������
		m_pTexture->Uninit();

		// �������̉��
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_pSound != nullptr)
	{// �I������
		m_pSound->Uninit();

		// �������̉��
		delete m_pSound;
		m_pSound = nullptr;
	}

	if (m_pJoy != nullptr)
	{// �I������
		m_pJoy->Uninit();

		delete m_pJoy;
		m_pJoy = nullptr;
	}
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V
//=============================================================================
void CApplication::Update()
{
	if (m_nextMode != MODE_NONE)
	{
		m_pFade->SetFade(m_nextMode);
		m_nextMode = MODE_NONE;
	}

	m_pKeyboard->Update();
	m_pMouse->Update();
	m_pJoy->Update();

	m_pRenderer->Update();

#ifdef _DEBUG
	CDebugProc::Print("FPS : %d\n", GetFps());
	CDebugProc::Print("���݂̃V�[�� : %d\n", (int)m_mode);
	CDebugProc::Print("�R���g���[���[�̎g�p�� : %d\n", m_pJoy->GetUseJoyPad());

	if (m_pKeyboard->GetTrigger(DIK_F1))
	{
		bool bDrawFlag = CDebugProc::GetDrawFlag();
		bDrawFlag ^= 1;
		CDebugProc::SetDrawFlag(bDrawFlag);
	}

	if (m_pKeyboard->GetTrigger(DIK_F2))
	{
		m_bWireFrame ^= 1;
	}

	if (m_bWireFrame)
	{
		m_pRenderer->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else
	{
		m_pRenderer->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

#endif // DEBUG
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`��
//=============================================================================
void CApplication::Draw()
{
	m_pRenderer->Draw();
}
