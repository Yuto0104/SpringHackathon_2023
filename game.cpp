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
#include "mine.h"
#include "pause.h"
#include "calculation.h"
#include "select_item.h"
#include "lille.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CScore *CGame::m_pScore = nullptr;						// �X�R�A�C���X�^���X
CTime *CGame::m_pTime = nullptr;						// �^�C��
CEnemy *CGame::m_pEnemy = nullptr;						// �G�l�~�[
CPlayer *CGame::m_pPlayer = nullptr;					// �v���C���[
CLille *CGame::m_pLille = nullptr;						// ���[��
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
	//pSound->PlaySound(CSound::SOUND_LABEL_BGM000);

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

	// �v���C���[����
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f));

	// �J�����̒Ǐ]�ݒ�(�ڕW : �v���C���[)
	CCamera *pCamera = CApplication::GetCamera();
	pCamera->SetViewType(CCamera::TYPE_PARALLEL);
	pCamera->SetFollowTarget(m_pPlayer, 1.0);
	pCamera->SetPosVOffset(D3DXVECTOR3(0.0f, 0.0f, -1600.0f));
	pCamera->SetPosROffset(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pCamera->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pCamera->SetUseRoll(false, false);

	// ���b�V���̐ݒu
	CMesh3D *pMesh = CMesh3D::Create();
	assert(pMesh != nullptr);
	pMesh->SetPos(D3DXVECTOR3(0.0f, 0.0f, 1000.0f));
	pMesh->SetRot(D3DXVECTOR3(D3DX_PI * -0.5f, 0.0f, 0.0f));
	pMesh->SetSize(D3DXVECTOR3(10000.0f, 0.0f, 10000.0f));
	pMesh->LoadTex(2);
	pMesh->SetBlock(CMesh3D::DOUBLE_INT(30, 30));
	pMesh->SetSplitTex(true);
	//pMesh->SetScrollTex(move, bScrollTex);
	//pMesh->SetUseCollison(bCollison);

	// �n��
	CMine::Create(D3DXVECTOR3(100.0f, 50.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f),1);
	CMine::Create(D3DXVECTOR3(200.0f, 50.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f),1);
	CMine::Create(D3DXVECTOR3(300.0f, 50.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f),2);

	// �G�l�~�[
	m_pEnemy = CEnemy::Create(D3DXVECTOR3(100.0f,0.0f,0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f),2);

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

	//������
	m_bGame = true;
	m_nSpawnTime = 0;

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

	CCamera *pCamera = CApplication::GetCamera();
	pCamera->SetFollowTarget(false);

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
	CPause *pPause = CApplication::GetPause();
	CSelectItem *pSelect = CApplication::GetSelectItem();

	if (pKeyboard->GetPress(DIK_LSHIFT))
	{
		pCamera->Zoom();
	}

	if (!pPause->GetPause()
		&& pKeyboard->GetTrigger(DIK_P))
	{
		pPause->SetPause(true, true);
	}
	else if (pPause->GetPause()
		&& pKeyboard->GetTrigger(DIK_P))
	{
		pPause->SetPause(false, false);
	}

	if (!pSelect->GetPause()
		&& pKeyboard->GetTrigger(DIK_H))
	{
		pSelect->SetPause(true, true);

	}
	else if (pSelect->GetPause()
		&& pKeyboard->GetTrigger(DIK_H))
	{
		pSelect->SetPause(false, false);
	}

	if (m_nSpawnTime < 60
		&& !pSelect->GetPause())
	{//�X�|�[�����Ԃ����ȉ��Ȃ���Z����
		m_nSpawnTime++;
	}
	else if (m_nSpawnTime >= 60)
	{//���ȏ�Ȃ�X�|�[��������0�ɂ���
		EnemySpawn();
		m_nSpawnTime = 0;
	}

	if (m_pTime->GetTimeEnd()
		&& m_bGame)
	{
		m_bGame = false;

		// �J�����̒Ǐ]�ݒ�
		pCamera = CApplication::GetCamera();
		pCamera->SetFollowTarget(false);
		pCamera->SetFollowTarget(false);

		// �X�R�A�̐ݒ�
		CApplication::SetScore(m_pScore->GetScore());
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

//=============================================================================
// �G�l�~�[�̃X�|�[��
// Author : ����]��
// �T�v : �G���o��������
//=============================================================================
void CGame::EnemySpawn()
{
	// �X�|�[���������
	int Spawn = 0;
	if (m_pPlayer != nullptr)
	{
		// �v���C���[�̈ʒu���擾
		D3DXVECTOR3 pos = m_pPlayer->GetPos();
		D3DXVECTOR3 EnemyPos;
		// �����_���œG�̃X�|�[��������������߂�
		Spawn = CCalculation::Rand(4);
		// �����_���œG��x��y��ς���
		int rand = CCalculation::Rand(5,-2);

		switch (Spawn)
		{// �G�l�~�[�̃X�|�[��
		case 0:
			// ��
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(pos.x - (CRenderer::SCREEN_WIDTH / 2), pos.y + (125.0f * rand), 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), 3);
			break;

		case 1:
			// �E
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(pos.x + (CRenderer::SCREEN_WIDTH / 2), pos.y + (125.0f * rand), 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), 3);
			break;

		case 2:
			// ��
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(pos.x + (245.0f * rand), pos.y + (CRenderer::SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), 3);
			break;

		case 3:
			// ��
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(pos.x + (245.0f * rand), pos.y - (CRenderer::SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), 3);
			break;

		default:
			break;
		}
	}
}