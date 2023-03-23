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
#include "camera.h"
#include "light.h"
#include "sound.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "model3D.h"
#include "scene_mode.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "collision.h"
#include "pause.h"
#include "select_item.h"
#include "tutorial.h"
#include "joypad.h"
#include "select_item.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
HWND CApplication::m_hWnd = nullptr;								// �E�B���h�E
CDebugProc *CApplication::m_pDebugProc = nullptr;					// �f�o�b�N�\��
CRenderer *CApplication::m_pRenderer = nullptr;						// �����_���[�C���X�^���X
CKeyboard *CApplication::m_pKeyboard = {};							// �L�[�{�[�h�C���X�^���X
CMouse *CApplication::m_pMouse = {};								// �}�E�X�C���X�^���X
CTexture *CApplication::m_pTexture = nullptr;						// �e�N�X�`���C���X�^���X
CCamera *CApplication::m_pCamera = nullptr;							// �J�����C���X�^���X
CApplication::SCENE_MODE CApplication::m_mode = MODE_NONE;			// ���݂̃��[�h�̊i�[
CApplication::SCENE_MODE CApplication::m_nextMode = MODE_TITLE;		// ���̃��[�h�̊i�[
CSceneMode *CApplication::pSceneMode = nullptr;						// �V�[�����[�h���i�[
CFade *CApplication::m_pFade = nullptr;								// �t�F�[�h�N���X
CLight *CApplication::m_pLight = nullptr;							// ���C�g�N���X
CSound *CApplication::m_pSound = nullptr;							// �T�E���h�N���X
CPause *CApplication::m_pPause = nullptr;							// �|�[�Y�N���X
CSelectItem *CApplication::m_pSelectItem = nullptr;					// �Z���N�g�A�C�e��
CJoypad *CApplication::m_pJoy = nullptr;							// �W���C�p�b�h�N���X
int CApplication::m_nPriority = 0;									// �v���C�I���e�B�ԍ�
int CApplication::m_nScore = 0;										// ���݂̃X�R�A
bool CApplication::m_bWireFrame = false;							// ���C���[�t���[�����g����

//=============================================================================
// �X�N���[�����W�����[���h���W�ɃL���X�g����
// Author : �������l
// �T�v : 
//=============================================================================
D3DXVECTOR3 CApplication::ScreenCastWorld(const D3DXVECTOR3 &pos)
{
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtx, mtxTrans, mtxView, mtxPrj, mtxViewPort;

	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	// �J�����̃r���[�}�g���b�N�X�̎擾
	mtxView = m_pCamera->GetMtxView();

	// �J�����̃v���W�F�N�V�����}�g���b�N�X�̎擾
	mtxPrj = m_pCamera->GetMtxProj();

	// �}�g���b�N�X�̏�Z
	mtx = mtxTrans * mtxView * mtxPrj;

	// �r���[�|�[�g�s��i�X�N���[���s��j�̍쐬
	float w = (float)CRenderer::SCREEN_WIDTH / 2.0f;
	float h = (float)CRenderer::SCREEN_HEIGHT / 2.0f;

	mtxViewPort = {
		w , 0 , 0 , 0 ,
		0 ,-h , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		w , h , 0 , 1
	};

	// �}�g���b�N�X��XYZ
	D3DXVECTOR3 vec = D3DXVECTOR3(mtx._41, mtx._42, mtx._43);

	D3DXVec3TransformCoord(&vec, &vec, &mtxViewPort);

	return vec;
}

//=============================================================================
// ���[���h���W���X�N���[�����W�ɃL���X�g����
// Author : �������l
// �T�v : 
//=============================================================================
D3DXVECTOR3 CApplication::WorldCastScreen(const D3DXVECTOR3 &pos)
{
	// �v�Z�p�x�N�g��
	D3DXVECTOR3 vec = pos;

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtx, mtxTrans, mtxView, mtxPrj, mtxViewPort;

	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	// �J�����̃r���[�}�g���b�N�X�̎擾
	mtxView = m_pCamera->GetMtxView();

	// �J�����̃v���W�F�N�V�����}�g���b�N�X�̎擾
	mtxPrj = m_pCamera->GetMtxProj();
	
	// �r���[�|�[�g�s��i�X�N���[���s��j�̍쐬
	D3DXMatrixIdentity(&mtxViewPort);
	float w = (float)CRenderer::SCREEN_WIDTH / 2.0f;
	float h = (float)CRenderer::SCREEN_HEIGHT / 2.0f;
	mtxViewPort = {
		w , 0 , 0 , 0 ,
		0 ,-h , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		w , h , 0 , 1
	};

	// �t�s��̎Z�o
	D3DXMatrixInverse(&mtxView, NULL, &mtxView);
	D3DXMatrixInverse(&mtxPrj, NULL, &mtxPrj);
	D3DXMatrixInverse(&mtxViewPort, NULL, &mtxViewPort);

	// �t�ϊ�
	mtx = mtxViewPort * mtxPrj * mtxView;
	D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(vec.x, vec.y, vec.z), &mtx);

	return vec;
}

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

	// �����蔻��̏I��
	CCollision::ReleaseAll();

	m_mode = mode;

	if (m_pSound != nullptr && m_mode != MODE_TUTORIAL)
	{// �g�p���̃T�E���h��~
		m_pSound->Stop();
	}

	switch (m_mode)
	{
	case CApplication::MODE_TITLE:
		pSceneMode = new CTitle;
		m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
		break;

	case CApplication::MODE_GAME:
		pSceneMode = new CGame;
		m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		break;

	case CApplication::MODE_RESULT:
		pSceneMode = new CResult;
		m_pSound->Play(CSound::SOUND_LABEL_BGM_RESULT);
		break;

	case CApplication::MODE_TUTORIAL:
		pSceneMode = new CTutorial;
		m_pSound->Play(CSound::SOUND_LABEL_BGM_TUTORIAL);
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
	assert(m_pCamera == nullptr); 
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
	m_pCamera = new CCamera;
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

	// ����������
	assert(m_pCamera != nullptr);
	m_pCamera->Init();
	m_pCamera->SetViewType(CCamera::TYPE_CLAIRVOYANCE);

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

	// ���f�����̏�����
	CModel3D::InitModel();

	// ���C�g�̍쐬
	m_pLight = CLight::Create(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CLight::Create(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �t�F�[�h�̐ݒ�
	m_pFade = CFade::Create();

	// �|�[�Y�̐���
	m_pPause = CPause::Create();
	m_pPause->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));

	// �A�C�e���Z���N�g�̐���
	m_pSelectItem = CSelectItem::Create();
	m_pSelectItem->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));

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

	// �����蔻��̏I��
	CCollision::ReleaseAll();

	// ���f�����̏I��
	CModel3D::UninitModel();

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

	if (m_pCamera != nullptr)
	{// �I������
		m_pCamera->Uninit();

		// �������̉��
		delete m_pCamera;
		m_pCamera = nullptr;
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

	// ���C�g�̉��
	CLight::ReleaseAll();
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

	if (!CSuper::GetPause())
	{
		m_pCamera->Update();
	}

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
