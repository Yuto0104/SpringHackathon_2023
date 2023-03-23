//=============================================================================
//
// �Q�[���N���X(game.cpp)
// Author : �������l
// �T�v : �Q�[���N���X�̊Ǘ����s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "game.h"
#include "calculation.h"
#include "keyboard.h"
#include "mouse.h"
#include "application.h"
#include "renderer.h"
#include "object.h"
#include "bg.h"
#include "debug_proc.h"
#include "score.h"
#include "time.h"
#include "camera.h"
#include "enemy.h"
#include "mesh.h"
#include "sound.h"
#include "player.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CScore *CGame::m_pScore = nullptr;						// �X�R�A�C���X�^���X
CTime *CGame::m_pTime = nullptr;						// �^�C��
CEnemy *CGame::m_pEnemy = nullptr;						// �G�l�~�[
D3DXCOLOR CGame::fogColor;								// �t�H�O�J���[
float CGame::fFogStartPos;								// �t�H�O�̊J�n�_
float CGame::fFogEndPos;								// �t�H�O�̏I���_
float CGame::fFogDensity;								// �t�H�O�̖��x
bool CGame::m_bGame = false;							// �Q�[���̏�

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CGame::CGame()
{

}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CGame::Init()
{// �}�E�X�̎擾
	CMouse *pMouse = CApplication::GetMouse();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �T�E���h���̎擾
	CSound *pSound = CApplication::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM001);

	// �d�͂̒l��ݒ�
	CCalculation::SetGravity(0.2f);

	// �X�R�A
	m_pScore = CScore::Create(10, false);
	m_pScore->SetScore(0);
	m_pScore->SetPos(D3DXVECTOR3(1280.0f, m_pScore->GetSize().y / 2.0f, 0.0f));

	// �^�C��
	m_pTime = CTime::Create(3);
	m_pTime->SetTime(120);
	m_pTime->SetTimeAdd(false);
	m_pTime->SetPos(D3DXVECTOR3(640.0f, m_pTime->GetSize().y / 2.0f, 0.0f));

	// �J�����̒Ǐ]�ݒ�(�ڕW : �v���C���[)
	CCamera *pCamera = CApplication::GetCamera();
	pCamera->SetViewType(CCamera::TYPE_PARALLEL);
	//pCamera->SetFollowTarget(m_pPlayer, 1.0);
	pCamera->SetPosVOffset(D3DXVECTOR3(0.0f, 0.0f, -200.0f));
	pCamera->SetPosROffset(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pCamera->SetUseRoll(true, false);

	// ���b�V���̐ݒu
	CMesh3D *pMesh = CMesh3D::Create();
	assert(pMesh != nullptr);
	// ���l�̐ݒ�
	pMesh->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pMesh->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pMesh->SetSize(D3DXVECTOR3(10000.0f, 0.0f, 10000.0f));
	pMesh->SetCol(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	//pMesh->LoadTex(nType);
	//pMesh->SetBlock(block);
	//pMesh->SetSplitTex(bSplitTex);
	//pMesh->SetScrollTex(move, bScrollTex);
	//pMesh->SetUseCollison(bCollison);

	CPlayer::Create(D3DXVECTOR3(50.0f, 0.0f, 100.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f));

	// �G�l�~�[
	m_pEnemy = CEnemy::Create(D3DXVECTOR3(100.0f,0.0f,100.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f));

	// �}�E�X�J�[�\��������
	pMouse->SetShowCursor(false);

	// �t�H�O�̐��l�ݒ�
	fogColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �t�H�O�J���[
	fFogStartPos = 1.0f;								// �t�H�O�̊J�n�_
	fFogEndPos = 100000.0f;								// �t�H�O�̏I���_
	fFogDensity = 0.00001f;								// �t�H�O�̖��x

	// �t�H�O�̗L���ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	// �t�H�O�J���[�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGCOLOR, fogColor);

	// �t�H�O�͈̔͐ݒ�
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&fFogStartPos));
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&fFogEndPos));

	// �t�H�O�̖��x�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&fFogDensity));

	m_bGame = true;

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CGame::Uninit()
{// �}�E�X�̎擾
	CMouse *pMouse = CApplication::GetMouse();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �T�E���h���̎擾
	CSound *pSound = CApplication::GetSound();

	// �T�E���h�I��
	pSound->StopSound();

	// �t�H�O�̗L���ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	// �}�E�X�J�[�\�����o��
	pMouse->SetShowCursor(true);

	// �X�R�A�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CGame::Update()
{
	// �L�[�{�[�h�̎擾
	CKeyboard *pKeyboard = CApplication::GetKeyboard();
	CCamera *pCamera = CApplication::GetCamera();

	if (pKeyboard->GetPress(DIK_LSHIFT))
	{
		pCamera->Zoom();
	}

	if (!m_bGame)
	{
		CApplication::SetNextMode(CApplication::MODE_RESULT);
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CGame::Draw()
{

}
