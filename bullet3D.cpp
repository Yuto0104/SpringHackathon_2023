//=============================================================================
//
// 3D�o���b�g�N���X(bullet3D.cpp)
// Author : �������l
// �T�v : �I�u�W�F�N�g�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "bullet3D.h"
#include "renderer.h"
#include "application.h"

#include "motion_player3D.h"
#include "enemy3D.h"
#include "motion_boss.h"
#include "score.h"
#include "effect3D.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 3D�o���b�g�𐶐�����
//=============================================================================
CBullet3D * CBullet3D::Create(void)
{
	// �I�u�W�F�N�g�C���X�^���X
	CBullet3D *pBullet3D = nullptr;

	// �������̉��
	pBullet3D = new CBullet3D;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pBullet3D != nullptr);

	// ���l�̏�����
	pBullet3D->Init();

	// �C���X�^���X��Ԃ�
	return pBullet3D;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CBullet3D::CBullet3D()
{
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);					// �ړ���
	m_moveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ړ�����
	m_fSpeed = 0.0f;										// ���x
	m_nAttack = 0;											// �U����

	// �I�u�W�F�N�g�̎�ʐݒ�
	SetObjType(CObject::OBJTYPE_3DBULLET);
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CBullet3D::~CBullet3D()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CBullet3D::Init()
{
	// ������
	CObject3D::Init();

	// �e�N�X�`���̐ݒ�
	LoadTex(0);

	// �r���{�[�h�I��
	SetBillboard(true);

	// �U��
	m_nAttack = 20;

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CBullet3D::Uninit()
{
	// �I��
	CObject3D::Uninit();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : 2D�X�V���s��
//=============================================================================
void CBullet3D::Update()
{
	// �ʒu�̎擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();
	COLOR_TYPE MyColorType = GetColorType();

	// �ړ��ʂ̎Z�o
	m_move.z = sinf(m_moveVec.x) * cosf(m_moveVec.y) * m_fSpeed;
	m_move.x = sinf(m_moveVec.x) * sinf(m_moveVec.y) * m_fSpeed;
	m_move.y = cosf(m_moveVec.x) * m_fSpeed;

	// �ʒu�̍X�V
	pos += m_move;

	// �G�t�F�N�g�̐���
	CEffect3D *pEffect3D = CEffect3D::Create();
	pEffect3D->SetPos(pos);
	pEffect3D->SetSize(D3DXVECTOR3(size.x * 1.5f, size.y * 1.5f, 0.0f));

	if (MyColorType == CObject::TYPE_WHITE)
	{// �G�t�F�N�g�̐F�̐ݒ�
		pEffect3D->SetRenderMode(CEffect3D::MODE_ADD);
		pEffect3D->SetColor(D3DXCOLOR(0.5f, 0.7f, 1.0f, 1.0f));
	}
	else if (MyColorType == CObject::TYPE_BLACK)
	{// �G�t�F�N�g�̐F�̐ݒ�
		pEffect3D->SetRenderMode(CEffect3D::MODE_ADD);
		pEffect3D->SetColor(D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f));
	}

	pEffect3D->SetLife(10);

	// �ʒu�̍X�V
	SetPos(pos);

	if (CollisionScreen()
		|| Collision())
	{
		Uninit();
	}
	else
	{// �X�V
		CObject3D::Update();
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : 2D�`����s��
//=============================================================================
void CBullet3D::Draw()
{
	// �`��
	CObject3D::Draw();
}

//=============================================================================
// �Փ˔���
// Author : �������l
// �T�v : �Փ˔���
//=============================================================================
bool CBullet3D::Collision()
{
	bool bCollision = false;

	for (int nCntPriority = 0; nCntPriority < CObject::MAX_LEVEL; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			// �I�u�W�F�N�g�C���X�^���X�̎擾
			CObject *pObject = CObject::MyGetObject(nCntPriority, nCntObj);

			if (pObject != nullptr)
			{
				if ((pObject->GetObjType() == CObject::OBJTYPE_3DENEMY
					|| pObject->GetObjType() == CObject::OBJTYPE_3DPLAYER
					|| pObject->GetObjType() == CObject::OBJTYPE_3DBOSS)
					&& pObject->GetObjType() != CObject::OBJTYPE_3DBULLET)
				{// �^�C�v����v�����ꍇ
					if (pObject->GetObjType() == CObject::OBJTYPE_3DENEMY
						&& m_parent != CObject::OBJTYPE_3DENEMY
						&& ColisonSphere3D(pObject, D3DXVECTOR3(GetSize().x, GetSize().y, GetSize().x), pObject->GetColisonSize(), true))
					{
						// �G�I�u�W�F�N�g�ɃL���X�g
						CEnemy3D *pEnemy3D = dynamic_cast<CEnemy3D*>(pObject);

						// �G�ւ̍U������
						pEnemy3D->Hit(GetColorType(), m_nAttack);

						bCollision = true;
						break;
					}

					if (pObject->GetObjType() == CObject::OBJTYPE_3DBOSS
						&& m_parent != CObject::OBJTYPE_3DBOSS
						&& ColisonSphere3D(pObject, D3DXVECTOR3(GetSize().x, GetSize().y, GetSize().x), pObject->GetColisonSize(), true))
					{
						// �{�X�I�u�W�F�N�g�ɃL���X�g
						CMotionBoss *pMotionBoss = dynamic_cast<CMotionBoss*>(pObject);

						// �G�ւ̍U������
						pMotionBoss->Hit(GetColorType(), m_nAttack);

						bCollision = true;
						break;
					}

					if (pObject->GetObjType() == CObject::OBJTYPE_3DPLAYER
						&& m_parent != CObject::OBJTYPE_3DPLAYER
						&& ColisonSphere3D(pObject, D3DXVECTOR3(GetSize().x, GetSize().y, GetSize().x), pObject->GetColisonSize(), true))
					{
						// �v���C���[�I�u�W�F�N�g�ɃL���X�g
						CMotionPlayer3D *pPlayer = (CMotionPlayer3D*)pObject;

						if (pPlayer->GetColorType() != GetColorType())
						{// �v���C���[�ւ̍U������
							pPlayer->Hit();
						}
						else
						{// �v���C���[�̃G�l���M�[�z��
							pPlayer->Charge(1);
						}

						bCollision = true;
						break;
					}
				}
			}
		}
	}

	return bCollision;
}

//=============================================================================
// �X�N���[���Փ˔���
// Author : �������l
// �T�v : �X�N���[���O�ɂł���ture
//=============================================================================
bool CBullet3D::CollisionScreen()
{
	bool bCollision = false;

	// �ʒu�̎擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();
	D3DXVECTOR3 worldPos;

	// �X�N���[�����W�ɃL���X�g
	D3DXVECTOR3 screenPos = CApplication::ScreenCastWorld(pos);

	if (screenPos.x + size.x < 0.0f)
	{// �I��
		bCollision = true;
	}
	else if (screenPos.x - size.x >(float)CRenderer::SCREEN_WIDTH)
	{// �I��
		bCollision = true;
	}

	if (screenPos.y + size.y < 0.0f)
	{// �I��
		bCollision = true;
	}
	else if (screenPos.y - size.y >(float)CRenderer::SCREEN_HEIGHT)
	{// �I��
		bCollision = true;
	}

	return bCollision;
}
