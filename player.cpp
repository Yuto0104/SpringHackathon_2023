//=============================================================================
//
// player.cpp
// Author : ���c�喲
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "player.h"
#include "camera.h"
#include "application.h"
#include "score.h"
#include "keyboard.h"
#include "debug_proc.h"

//=============================================================================
//							�ÓI�ϐ��̏�����
//=============================================================================
const float CPlayer::m_MaxWalkingSpeed = 1.0f;			//�ő�����X�s�[�h

//�R���X�g���N�^
CPlayer::CPlayer()
{
	//�����o�[�ϐ����N���A����
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);			//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���x�̏���������
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
}

//�f�X�g���N�^
CPlayer::~CPlayer()
{

}

//����������
HRESULT CPlayer::Init(void)
{
	//�����o�[�ϐ��̏���������
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���x�̏���������
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����

	CObject3D::Init();

	return S_OK;
}

//�I������
void CPlayer::Uninit(void)
{
	CObject3D::Uninit();

	//���
	Release();
}

//�X�V����
void CPlayer::Update(void)
{
	PlayerController();

	m_pos = CObject3D::GetPos();
	m_rot = CObject3D::GetRot();

	m_pos += m_move;

	SetPos(m_pos);
	SetRot(m_rot);

	//�ړ��ʂ��X�V(����������)
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.y += (0.0f - m_move.y) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

#ifdef _DEBUG
	CDebugProc::Print("�v���C���[�̈ʒu | X : %.3f | Y : %.3f | Z : %.3f |\n", m_pos.x, m_pos.y, m_pos.z);
#endif // _DEBUG
}

void CPlayer::Draw(void)
{
	CObject3D::Draw();
}

//��������
CPlayer* CPlayer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	CPlayer* pPlayer = new CPlayer;		//�C���X�^���X�𐶐�����

	pPlayer->Init();
	pPlayer->SetPos(pos);
	pPlayer->SetSize(size);
	
	//���������C���X�^���X��Ԃ�
	return pPlayer;
}

//�v���C���[�̃L�[����
void CPlayer::PlayerController(void)
{
	CKeyboard *pKeyboard = CApplication::GetKeyboard();
	D3DXVECTOR3 cameraRot = CApplication::GetCamera()->GetRot();	//�J�����̌����̎擾����

	//�ړ��ʂƖړI�̊p�x�̌v�Z
	if (pKeyboard->GetPress(DIK_UP))
	{//W�L�[�������ꂽ�ꍇ
		if (pKeyboard->GetPress(DIK_LEFT))
		{//A�L�[�������ꂽ�ꍇ
			m_move.x -= sinf(D3DX_PI * 0.75f + cameraRot.y) * m_MaxWalkingSpeed;
			m_move.y -= cosf(D3DX_PI * 0.75f + cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y - D3DX_PI * 0.25f;
		}
		else if (pKeyboard->GetPress(DIK_RIGHT))
		{//D�L�[�������ꂽ�ꍇ
			m_move.x += sinf(D3DX_PI * 0.25f + cameraRot.y) * m_MaxWalkingSpeed;
			m_move.y += cosf(D3DX_PI * 0.25f + cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y + D3DX_PI * 0.25f;
		}
		else
		{//W�L�[�����������ꂽ�ꍇ
			m_move.x += sinf(cameraRot.y) * m_MaxWalkingSpeed;
			m_move.y += cosf(cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y;
		}
	}
	else if (pKeyboard->GetPress(DIK_DOWN))
	{//S�L�[�������ꂽ�ꍇ
		if (pKeyboard->GetPress(DIK_LEFT))
		{//A�L�[�������ꂽ�ꍇ
			m_move.x -= sinf(D3DX_PI * 0.25f + cameraRot.y) * m_MaxWalkingSpeed;
			m_move.y -= cosf(D3DX_PI * 0.25f + cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y - D3DX_PI * 0.75f;
		}
		else if (pKeyboard->GetPress(DIK_RIGHT))
		{//D�L�[�������ꂽ�ꍇ
			m_move.x += sinf(D3DX_PI * 0.75f + cameraRot.y) * m_MaxWalkingSpeed;
			m_move.y += cosf(D3DX_PI * 0.75f + cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y + D3DX_PI * 0.75f;
		}
		else
		{//S�L�[�����������ꂽ�ꍇ
			m_move.x -= sinf(cameraRot.y) * m_MaxWalkingSpeed;
			m_move.y -= cosf(cameraRot.y) * m_MaxWalkingSpeed;

			m_rot.y = cameraRot.y - D3DX_PI;
		}
	}
	else if (pKeyboard->GetPress(DIK_RIGHT))
	{//D�L�[���������ꂽ�ꍇ
		m_move.x += sinf(D3DX_PI * 0.5f + cameraRot.y) * m_MaxWalkingSpeed;
		m_move.y += cosf(D3DX_PI * 0.5f + cameraRot.y) * m_MaxWalkingSpeed;

		m_rot.y = cameraRot.y + D3DX_PI* 0.5f;
	}
	else if (pKeyboard->GetPress(DIK_LEFT))
	{//A�L�[���������ꂽ�ꍇ
		m_move.x -= sinf(D3DX_PI * 0.5f + cameraRot.y) * m_MaxWalkingSpeed;
		m_move.y -= cosf(D3DX_PI * 0.5f + cameraRot.y) * m_MaxWalkingSpeed;

		m_rot.y = cameraRot.y - D3DX_PI * 0.5f;
	}
}