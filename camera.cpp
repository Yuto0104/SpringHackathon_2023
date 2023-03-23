//**************************************************************************************************
//
// �J��������(camera.h)
// Auther�F�������l
// �T�v : �J�����̐ݒ菈��
//
//**************************************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "camera.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "mouse.h"
#include "keyboard.h"
#include "move.h"
#include "calculation.h"
#include "object.h"
#include "debug_proc.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************
const float CCamera::CAMERA_NEAR = 10.0f;				// �j�A
const float CCamera::CAMERA_FUR = 100000.0f;			// �t�@�[

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CCamera::CCamera()
{
	m_pMove = nullptr;								// �ړ��N���X�̃C���X�^���X
	m_pRoll = nullptr;								// �ړ��N���X�̃C���X�^���X(�p�x)
	m_pTarget = nullptr;							// �^�[�Q�b�g
	m_pTargetPosR = nullptr;						// �^�[�Q�b�g(�����_)
	m_mtxWorld = {};								// ���[���h�}�g���b�N�X
	m_mtxProj = {};									// �v���W�F�N�V�����}�g���b�N�X
	m_mtxView = {};									// �r���[�}�g���b�N�X
	m_viewport = {};								// �r���[�|�[�g
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����_
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ������x�N�g��
	m_posVOffset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���_����
	m_posROffset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �����_����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
	m_rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ�����
	m_posRDiff = D3DXVECTOR2(0.0f, 0.0f);			// �����_�^�[�Q�b�g���̍���
	m_aspect = D3DXVECTOR2(0.0f, 0.0f);				// �A�X�y�N�g��̒l
	m_viewType = TYPE_CLAIRVOYANCE;					// ���e�̎��
	m_fViewing = 0.0f;								// ����p
	m_fRotMove = 0.0f;								// �ړ�����
	m_fCoeffFllow = 0.0f;							// �Ǐ]�̌����W��
	m_fShake = 0.0f;								// �h��̗�
	m_nCntShake = 0;								// �h��̃J�E���g
	m_bUseRollX = true;								// X���̉�]�̎g�p��
	m_bUseRollY = true;								// Y���̉�]�̎g�p��
	m_bFllow = false;								// �Ǐ]���s����
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�ƒ����_�̊Ԃ̋������Z�o����
//=============================================================================
HRESULT CCamera::Init()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			// �Œ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ����
	m_posVOffset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posROffset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �����_�^�[�Q�b�g���̍���
	m_posRDiff = D3DXVECTOR2(0.0f, 100.0f);			

	// ����p�̏����l�̑��
	m_fViewing = 45.0f;

	// �ړ��N���X�̃������m��
	m_pMove = new CMove;
	assert(m_pMove != nullptr);
	m_pMove->SetMoving(10.0f, 100.0f, 0.0f, 0.3f);

	// �ړ��N���X(�p�x)�̃������m��
	m_pRoll = new CMove;
	assert(m_pRoll != nullptr);
	m_pRoll->SetMoving(0.05f, 5.0f, 0.0f, 0.5f);

	// �A�X�y�N�g��̐ݒ�
	m_aspect = D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT);

	// �r���[�|�[�g�̑傫���ݒ�
	SetViewSize(0, 0, CRenderer::SCREEN_WIDTH, CRenderer::SCREEN_HEIGHT);

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �I��
//=============================================================================
void CCamera::Uninit(void)
{
	if (m_pMove != nullptr)
	{// �I������
	 // �������̉��
		delete m_pMove;
		m_pMove = nullptr;
	}

	if (m_pRoll != nullptr)
	{// �I������
	 // �������̉��
		delete m_pRoll;
		m_pRoll = nullptr;
	}
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V
//=============================================================================
void CCamera::Update(void)
{
	if (m_pTarget == nullptr)
	{
		Move();
	}
	if (m_pTargetPosR == nullptr)
	{
		Rotate();
	}
	
	CalMatrix();

#ifdef _DEBUG
	CDebugProc::Print("�J�����̎��_ | X : %.3f | Y : %.3f | Z : %.3f |\n", m_posV.x, m_posV.y, m_posV.z);
	CDebugProc::Print("�J�����̒����_ | X : %.3f | Y : %.3f | Z : %.3f |\n", m_posR.x, m_posR.y, m_posR.z);
	CDebugProc::Print("�J�����̌��� | X : %.3f | Y : %.3f | Z : %.3f |\n", m_rot.x, m_rot.y, m_rot.z);
	CDebugProc::Print("���_�̃I�t�Z�b�g | X : %.3f | Y : %.3f | Z : %.3f |\n", m_posVOffset.x, m_posVOffset.y, m_posVOffset.z);
	CDebugProc::Print("�����_�̃I�t�Z�b�g | X : %.3f | Y : %.3f | Z : %.3f |\n", m_posROffset.x, m_posROffset.y, m_posROffset.z);
#endif // _DEBUG
}

//=============================================================================
// �J�����̐ݒ�
// Author : �������l
// �T�v : �r���[�}�g���b�N�X�̐ݒ�
//=============================================================================
void CCamera::Set()
{// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);			// �s�񏉊����֐�

	//// ������x�N�g���̎Z�o
	//D3DXVECTOR3 rotAdd = m_rot + D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI * 0.5f, D3DX_PI * 0.5f);
	//rotAdd.x = CCalculation::RotNormalization(rotAdd.x);
	//rotAdd.y = CCalculation::RotNormalization(rotAdd.y);
	//rotAdd.z = CCalculation::RotNormalization(rotAdd.z);

	D3DXVECTOR3 adjust = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (m_nCntShake > 0)
	{
		m_nCntShake--;

		adjust.x = (float)(rand() % (int)(m_fShake * 200) / 100) - m_fShake;
		adjust.y = (float)(rand() % (int)(m_fShake * 200) / 100) - m_fShake;
		adjust.z = (float)(rand() % (int)(m_fShake * 200) / 100) - m_fShake;

		if (m_nCntShake <= 0)
		{
			m_nCntShake = 0;
		}
	}

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&(m_posV + adjust),
		&(m_posR + adjust),
		&m_vecU);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// �r���[�|�[�g�̓K��
	pDevice->SetViewport(&m_viewport);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProj);			// �s�񏉊����֐�

	switch (m_viewType)
	{
	case TYPE_CLAIRVOYANCE:
		// �v���W�F�N�V�����}�g���b�N�X�̍쐬(�������e)
		D3DXMatrixPerspectiveFovLH(&m_mtxProj,											// �v���W�F�N�V�����}�g���b�N�X
			D3DXToRadian(m_fViewing),													// ����p
			(float)CRenderer::SCREEN_WIDTH / (float)CRenderer::SCREEN_HEIGHT,			// �A�X�y�N�g��
			CAMERA_NEAR,																// �j�A
			CAMERA_FUR);																// �t�@�[
		break;

	case TYPE_PARALLEL:
		// �v���W�F�N�V�����}�g���b�N�X�̍쐬(���s���e)
		D3DXMatrixOrthoLH(&m_mtxProj,		// �v���W�F�N�V�����}�g���b�N�X
			m_aspect.x,						// ��
			m_aspect.y,						// ����
			CAMERA_NEAR,					// �j�A
			CAMERA_FUR);					// �t�@�[
		break;

	default:
		assert(false);
		break;
	}

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProj);
}

//=============================================================================
// �J�����̓��e���@�̐ݒ�
// Author : �������l
// �T�v : 
//=============================================================================
void CCamera::SetViewType(VIEW_TYPE type)
{
	m_viewType = type;
}

//=============================================================================
// �J�����̎��_�̐ݒ�
// Author : �������l
// �T�v : �������王�_��ݒ肷��
//=============================================================================
void CCamera::SetPosVOffset(const D3DXVECTOR3 posVOffset)
{
	// ���_�̐ݒ�
	m_posVOffset = posVOffset;
}

//=============================================================================
// �J�����̒����_�̐ݒ�
// Author : �������l
// �T�v : �������璍���_��ݒ肷��
//=============================================================================
void CCamera::SetPosROffset(const D3DXVECTOR3 posROffset)
{
	// �����_�̐ݒ�
	m_posROffset = posROffset;
}

//=============================================================================
// �J�����̎��_���璍���_�܂ł̋�����ݒ肷��
// Author : �������l
// �T�v : ���_���璍���_�܂ł̋������Z�o����
//=============================================================================
void CCamera::SetRot(const D3DXVECTOR3 rot)
{
	// �����̎Z�o
	m_rot = rot;
}

//=============================================================================
// �Ǐ]����̐ݒ�
// Author : �������l
// �T�v : �Ǐ]����̐ݒ�
//=============================================================================
void CCamera::SetFollowTarget(CObject *pTarget, float fCoeffFllow)
{
	m_pTarget = pTarget;
	m_fCoeffFllow = fCoeffFllow;
	m_bFllow = true;
}

//=============================================================================
// �Ǐ]����̐ݒ�
// Author : �������l
// �T�v : �Ǐ]����̐ݒ�
//=============================================================================
void CCamera::SetFollowTarget(bool bUse)
{
	if (!bUse)
	{// �Ǐ]�I��
		m_pTarget = nullptr;
		m_bFllow = bUse;
	}
}

//=============================================================================
// �^�[�Q�b�g(�����_)�̐ݒ�
// Author : �������l
// �T�v : �^�[�Q�b�g(�����_)�̐ݒ�
//=============================================================================
void CCamera::SetTargetPosR(CObject *pTargetPosR)
{
	m_pTargetPosR = pTargetPosR;
}

//=============================================================================
// �^�[�Q�b�g(�����_)�̐ݒ�
// Author : �������l
// �T�v : �^�[�Q�b�g(�����_)�̐ݒ�
//=============================================================================
void CCamera::SetTargetPosR(bool bUse)
{
	if (!bUse)
	{// �Ǐ]�I��
		m_pTargetPosR = nullptr;
	}
}

//=============================================================================
// ��]�̎g�p�󋵂̐ݒ�
// Author : �������l
// �T�v : ��]�̎g�p�󋵂̐ݒ�
//=============================================================================
void CCamera::SetUseRoll(bool X, bool Y)
{
	m_bUseRollX = X;	// X���̉�]�̎g�p��
	m_bUseRollY = Y;	// Y���̉�]�̎g�p��
}

//=============================================================================
// �r���[�|�[�g�T�C�Y�̐ݒ�
// Author : �������l
// �T�v : ��ʍ����0.0�ɉ�ʃT�C�Y��ݒ�
//=============================================================================
void CCamera::SetViewSize(DWORD X, DWORD Y, int fWidth, int fHeight)
{
	//��������
	m_viewport.X = X;					//�r���[�|�[�g�̍���X���W
	m_viewport.Y = Y;					//�r���[�|�[�g�̍���Y���W
	m_viewport.Width = fWidth;			//�r���[�|�[�g�̕�
	m_viewport.Height = fHeight;		//�r���[�|�[�g�̍���
}

//=============================================================================
// �}�g���b�N�X�v�Z���s��
// Author : �������l
// �T�v : 
//=============================================================================
void CCamera::Shake(const int nTime, const float fShake)
{
	m_nCntShake = nTime;
	m_fShake = fShake;
}

//=============================================================================
// �}�g���b�N�X�v�Z���s��
// Author : �������l
// �T�v : 
//=============================================================================
void CCamera::CalMatrix()
{
	if (m_pTarget != nullptr)
	{
		m_pos = m_pTarget->GetPos();
	}

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);											// �s�񏉊����֐�

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);			// �s���]�֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);						// �s��|���Z�֐� 

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				// �s��ړ��֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);					// �s��|���Z�֐�

	// ���[���h�}�g���b�N�X�����[�J���ϊ�
	if (m_pTargetPosR != nullptr)
	{// �����_�̐ݒ�
		m_posR = m_pTargetPosR->GetPos();

		// �����x�N�g���̌v�Z
		D3DXVECTOR3 diff = m_pTargetPosR->GetPos() - m_pos;

		// ���_�̐ݒ�
		D3DXVec3TransformCoord(&m_posV, &m_posVOffset, &m_mtxWorld);
		D3DXVECTOR3 vec = m_posR - m_posV;
		D3DXVec3Normalize(&vec, &vec);
		D3DXVECTOR3 rightAngle = D3DXVECTOR3(vec.z, vec.y, vec.x * -1);

		// ���_�̎Z�o
		m_posV += -vec * m_posRDiff.y;
		m_posV += -rightAngle * m_posRDiff.x;

		// �����̎Z�o
		//m_rot.x = atan2f(diff.y, fDiffLength);
		m_rot.y = atan2f(diff.x, diff.z);
	}
	else
	{
		D3DXVec3TransformCoord(&m_posV, &m_posVOffset, &m_mtxWorld);
		D3DXVec3TransformCoord(&m_posR, &m_posROffset, &m_mtxWorld);
	}

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
}

//=============================================================================
// �J�����̉�]
// Author : �������l
// �T�v : 
//=============================================================================
void CCamera::Rotate(void)
{
	// ���͏��̎擾
	const float MIN_MOUSE_MOVED = 1.0f;

	CMouse *pMouse = CApplication::GetMouse();
	D3DXVECTOR3 rollDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �}�E�X�̈ړ��ʂ̎擾
	D3DXVECTOR3 mouseMove = D3DXVECTOR3(pMouse->GetMouseMove().y, pMouse->GetMouseMove().x, pMouse->GetMouseMove().z);

	if (D3DXVec3Length(&mouseMove) > MIN_MOUSE_MOVED || D3DXVec3Length(&mouseMove) < -MIN_MOUSE_MOVED)
	{// �}�E�X�̈ړ������̃m�[�}���C�Y
		D3DXVec3Normalize(&mouseMove, &mouseMove);

		// �ړ������̎Z�o
		rollDir = mouseMove * (D3DX_PI / 180.0f);

		if (!m_bUseRollX)
		{
			rollDir.x = 0.0f;
		}
		if (!m_bUseRollY)
		{
			rollDir.y = 0.0f;
		}
	}

	// ���C�W���̌v�Z
	m_pRoll->Moving(rollDir);
	rollDir = m_pRoll->GetMove();

	// �J�����̌����̐��K��
	rollDir.x = CCalculation::RotNormalization(rollDir.x);
	rollDir.y = CCalculation::RotNormalization(rollDir.y);
	rollDir.z = CCalculation::RotNormalization(rollDir.z);

	// ��]
	m_rot += rollDir;

	if (m_rot.y < -D3DX_PI)
	{// ������-D3DX_PI�����̎�
		m_rot.y += D3DX_PI * 2;
	}
	if (m_rot.y > D3DX_PI)
	{// ������D3DX_PI�ȏ�̎�
		m_rot.y -= D3DX_PI * 2;
	}
	if (m_rot.x < -D3DX_PI * 0.5f + 0.1f)
	{// ������-D3DX_PI�����̎�
		m_rot.x = -D3DX_PI * 0.5f + 0.1f;
	}
	if (m_rot.x > D3DX_PI * 0.5f - 0.1f)
	{// ������D3DX_PI�ȏ�̎�
		m_rot.x = D3DX_PI * 0.5f - 0.1f;
	}
}

//=============================================================================
// �J�����̈ړ�
// Author : �������l
// �T�v : �J�����̈ړ�
//=============================================================================
void CCamera::Move(void)
{
	const float CAMERA_MOVE_SPEED = 5.0f;
	CKeyboard *pKeyboard = CApplication::GetKeyboard();
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (pKeyboard->GetPress(DIK_W) == true
		|| pKeyboard->GetPress(DIK_A) == true
		|| pKeyboard->GetPress(DIK_D) == true
		|| pKeyboard->GetPress(DIK_S) == true)
	{// �ړ��L�[�������ꂽ
	 // �O�㍶�E�ړ�
		if (pKeyboard->GetPress(DIK_W) == true)
		{// [W]�L�[�������ꂽ��
			if (pKeyboard->GetPress(DIK_A) == true)
			{// [A]�L�[�������ꂽ��
			 // �ړ������̍X�V
				m_rotMove.y = D3DX_PI * -0.25f;
				m_rotMove.x = D3DX_PI * -0.25f;
			}
			else if (pKeyboard->GetPress(DIK_D) == true)
			{// [D]�L�[�������ꂽ��
			 // �ړ������̍X�V
				m_rotMove.y = D3DX_PI * 0.25f;
				m_rotMove.x = D3DX_PI * 0.25f;
			}
			else
			{// �ړ������̍X�V
				m_rotMove.y = D3DX_PI * 0.0f;
				m_rotMove.x = D3DX_PI * 0.0f;
			}
		}
		else if (pKeyboard->GetPress(DIK_S) == true)
		{// [S]�L�[�������ꂽ��
			if (pKeyboard->GetPress(DIK_A) == true)
			{// [A]�L�[�������ꂽ��
			 // �ړ������̍X�V
				m_rotMove.y = D3DX_PI * -0.75f;
				m_rotMove.x = D3DX_PI * -0.75f;
			}
			else if (pKeyboard->GetPress(DIK_D) == true)
			{// [D]�L�[�������ꂽ��
			 // �ړ������̍X�V
				m_rotMove.y = D3DX_PI * 0.75f;
				m_rotMove.x = D3DX_PI * 0.75f;
			}
			else
			{// �ړ������̍X�V
				m_rotMove.y = 0.0f;
				m_rotMove.x = D3DX_PI;
			}
		}
		else if (pKeyboard->GetPress(DIK_A) == true)
		{// [A]�L�[�������ꂽ��
		 // �ړ������̍X�V
			m_rotMove.y = D3DX_PI * -0.5f;
			m_rotMove.x = D3DX_PI * 0.0f;
		}
		else if (pKeyboard->GetPress(DIK_D) == true)
		{// [D]�L�[�������ꂽ��
		 // �ړ������̍X�V
			m_rotMove.y = D3DX_PI * 0.5f;
			m_rotMove.x = D3DX_PI * 0.0f;
		}

		// �ړ������̎Z�o
		m_rotMove.x += m_rot.x;

		if (m_rotMove.x > D3DX_PI)
		{// �ړ������̐��K��
			m_rotMove.x -= D3DX_PI * 2;
		}
		else if (m_rotMove.x < -D3DX_PI)
		{// �ړ������̐��K��
			m_rotMove.x += D3DX_PI * 2;
		}

		m_rotMove.y += m_rot.y;

		if (m_rotMove.y > D3DX_PI)
		{// �ړ������̐��K��
			m_rotMove.y -= D3DX_PI * 2;
		}
		else if (m_rotMove.y < -D3DX_PI)
		{// �ړ������̐��K��
			m_rotMove.y += D3DX_PI * 2;
		}

		// ���_�ʒu�̍X�V
		move.z = sinf(m_rotMove.x) * cosf(m_rotMove.y);
		move.x = sinf(m_rotMove.x) * sinf(m_rotMove.y);
		move.y = cosf(m_rotMove.x);
	}

	// ���C�W���̌v�Z
	m_pMove->Moving(move);
	m_pos += m_pMove->GetMove();
}

//=============================================================================
// �J�����̊g�k����
// Author : �������l
// �T�v : �}�E�X�z�C�[���ŃJ�����̊g�k���s��
//=============================================================================
void CCamera::Zoom()
{// �}�E�X���̎擾
	CMouse *pMouse = CApplication::GetMouse();

	m_posVOffset.z += (float)pMouse->GetMouseWheel() * 1.0f;
}


