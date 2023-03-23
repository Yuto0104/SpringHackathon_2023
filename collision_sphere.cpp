//=============================================================================
//
// ���̏Փ˔���N���X(collision_sphere.cpp)
// Author : �������l
// �T�v : ���̏Փ˔��萶�����s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "collision_sphere.h"
#include "application.h"
#include "renderer.h"
#include "object.h"
#include "model3D.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : �C���X�^���X�𐶐�����
//=============================================================================
CCollision_Sphere * CCollision_Sphere::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CCollision_Sphere *pCollisionSphere = nullptr;

	// �������̉��
	pCollisionSphere = new CCollision_Sphere;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pCollisionSphere != nullptr);

	// ���l�̏�����
	pCollisionSphere->Init();

	// �C���X�^���X��Ԃ�
	return pCollisionSphere;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CCollision_Sphere::CCollision_Sphere()
{
#ifdef _DEBUG
	m_pModel = nullptr;		// ���f�����
	m_mtxWorld = {};
#endif // _DEBUG
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CCollision_Sphere::~CCollision_Sphere()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CCollision_Sphere::Init()
{
	// �����蔻��̎擾
	SetType(TYPE_SPHERE);

	// �ʒu�̎擾
	SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �T�C�Y�̎擾
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

#ifdef _DEBUG
	// ���f���N���X�̃������m��
	m_pModel = CModel3D::Create();
	assert(m_pModel != nullptr);
	m_pModel->Init();
	m_pModel->SetModelID(0);
	m_pModel->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f));
	m_pModel->SetShadow(false);
#endif // _DEBUG

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CCollision_Sphere::Uninit()
{
#ifdef _DEBUG
	if (m_pModel != nullptr)
	{// �I������
		m_pModel->Uninit();

		// �������̉��
		delete m_pModel;
		m_pModel = nullptr;
	}
#endif // _DEBUG

	// �X�R�A�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CCollision_Sphere::Update()
{
#ifdef _DEBUG
	// ���f���̍X�V
	m_pModel->Update();
#endif // _DEBUG
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CCollision_Sphere::Draw()
{
#ifdef _DEBUG
	// �ʒu�̎擾
	D3DXVECTOR3 pos = GetParent()->GetPos() + GetPos();

	// ���f���̃T�C�Y�̐ݒ�
	m_pModel->SetSize(GetSize());

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);									// �s�񏉊����֐�

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);				// �s��ړ��֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);			// �s��|���Z�֐�

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���f���̕`��
	m_pModel->Draw(m_mtxWorld);
#endif // _DEBUG
}

//=============================================================================
// �����蔻��
// Author : �������l
// �T�v : �����蔻��
//=============================================================================
bool CCollision_Sphere::Collision(CObject::EObjectType objeType, bool bExtrude)
{
	// �擪�C���X�^���X�̎擾
	CCollision *pCollision = CCollision::GetTop();
	bool bCollision = false;

	if (pCollision != nullptr)
	{
		while (pCollision)
		{// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g��ۊ�
			CCollision *pCollisionNext = pCollision->GetNext();
			CObject::EObjectType myObjeType = pCollision->GetParent()->GetObjType();

			if (myObjeType == objeType
				&& pCollision != this
				&& !pCollision->GetDeathFlag())
			{
				switch (pCollision->GetType())
				{
				case CCollision::TYPE_RECTANGLE3D:
				case CCollision::TYPE_SPHERE:
					bCollision = ToSphere(pCollision, bExtrude);
					break;

				default:
					assert(false);
					break;
				}
			}

			// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���X�V
			pCollision = pCollisionNext;
		}
	}

	return bCollision;
}

//=============================================================================
// ���Ƃ̓����蔻��
// Author : �������l
// �T�v : ���Ƃ̓����蔻��
//=============================================================================
bool CCollision_Sphere::ToSphere(CCollision * pTarget, bool bExtrude)
{
	// �ϐ��錾
	bool bCollision = false;

	// �����̏����擾����
	D3DXVECTOR3 pos = GetParent()->GetPos() + GetPos();
	D3DXVECTOR3 size = GetSize() / 2.0f;

	// �ڕW�̏��擾
	D3DXVECTOR3 posTarget = pTarget->GetParent()->GetPos() + pTarget->GetPos();
	D3DXVECTOR3 sizeTarget = pTarget->GetSize() / 2.0f;

	// ������s���������Z�o
	float fJudgeDistance = sqrtf((size.x * size.x) + (size.y * size.y) + (size.z * size.z));
	fJudgeDistance += sqrtf((sizeTarget.x * sizeTarget.x) + (sizeTarget.y * sizeTarget.y) + (sizeTarget.z * sizeTarget.z));

	// ���݂��̈ʒu�̍����Z�o
	D3DXVECTOR3 distance = posTarget - pos;
	float fDistance = sqrtf((distance.x * distance.x) + (distance.y * distance.y) + (distance.z * distance.z));

	if (fDistance <= fJudgeDistance)
	{// �ʒu�̍���������s���������Z���ꍇ
		bCollision = true;

		if (bExtrude)
		{
			// �p�x�̎Z�o
			D3DXVECTOR3 rotDiff;
			rotDiff.y = atan2f(distance.x, distance.z);
			rotDiff.x = atan2f(sqrtf((distance.x * distance.x) + (distance.z * distance.z)), distance.y);
			rotDiff.z = 0.0f;

			// �ʒu�̎Z�o
			pos.z = posTarget.z - sinf(rotDiff.x) * cosf(rotDiff.y) * fJudgeDistance;
			pos.x = posTarget.x - sinf(rotDiff.x) * sinf(rotDiff.y) * fJudgeDistance;
			pos.y = posTarget.y - cosf(rotDiff.x) * fJudgeDistance;
		}
	}

	if (bCollision)
	{// �ʒu�̐ݒ�
		CObject *pParent = GetParent();
		pParent->SetPos(pos - GetPos());
	}

	return bCollision;
}

