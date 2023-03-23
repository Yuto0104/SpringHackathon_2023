//=============================================================================
//
// ���f���I�u�W�F�N�g�N���X(model_obj.cpp)
// Author : �������l
// �T�v : ���f���I�u�W�F�N�g�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>
#include <stdio.h>

#include "model3D.h"
#include "model_obj.h"
#include "renderer.h"
#include "application.h"
#include "collision_rectangle3D.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : ���[�V�����L�����N�^�[3D�𐶐�����
//=============================================================================
CModelObj * CModelObj::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CModelObj *pModelObj = nullptr;

	// �������̉��
	pModelObj = new CModelObj;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pModelObj != nullptr);

	// ���l�̏�����
	pModelObj->Init();

	// �C���X�^���X��Ԃ�
	return pModelObj;
}

//=============================================================================
// �t�@�C����ǂݍ��ݏ���
// Author : �������l
// �T�v : �t�@�C����ǂݍ��݃��f���𐶐�����
//=============================================================================
void CModelObj::LoadFile(const char *pFileName)
{
	// �ϐ��錾
	char aStr[128];
	int nCntSetModel = 0;

	// �t�@�C���̓ǂݍ���
	FILE *pFile = fopen(pFileName, "r");

	if (pFile != nullptr)
	{
		while (fscanf(pFile, "%s", &aStr[0]) != EOF)
		{// "EOF"��ǂݍ��ނ܂� 
			if (strncmp(&aStr[0], "#", 1) == 0)
			{// ���ǂݍ���
				fgets(&aStr[0], sizeof(aStr), pFile);
			}

			if (strstr(&aStr[0], "MODELSET") != NULL)
			{
				// ���f���̐ݒu
				CModelObj *pModelObj = Create();
				assert(pModelObj != nullptr);
				CCollision_Rectangle3D *pCollision = pModelObj->GetCollision();
				CModel3D *pModel = pModelObj->GetModel();

				while (strstr(&aStr[0], "END_MODELSET") == NULL)
				{
					fscanf(pFile, "%s", &aStr[0]);

					if (strncmp(&aStr[0], "#", 1) == 0)
					{// ���ǂݍ���
						fgets(&aStr[0], sizeof(aStr), pFile);
					}
					else if (strcmp(&aStr[0], "POS") == 0)
					{// ���f���̃t�@�C�����̐ݒ�
						D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%f", &pos.x);
						fscanf(pFile, "%f", &pos.y);
						fscanf(pFile, "%f", &pos.z);
						pModelObj->SetPos(pos);
					}

					if (strstr(&aStr[0], "ROT") != NULL)
					{// ���f���̃t�@�C�����̐ݒ�
						D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%f", &rot.x);
						fscanf(pFile, "%f", &rot.y);
						fscanf(pFile, "%f", &rot.z);
						pModelObj->SetRot(rot);
					}

					if (strcmp(&aStr[0], "TYPE") == 0)
					{// �L�[���̓ǂݍ���
						int nID = 0;
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%d", &nID);
						pModelObj->SetType(nID);
					}

					if (strcmp(&aStr[0], "SHADOW") == 0)
					{// �L�[���̓ǂݍ���
						int nUse = 0;
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%d", &nUse);
						pModel->SetShadow(nUse);
					}

					if (strcmp(&aStr[0], "COLLISION_POS") == 0)
					{// �L�[���̓ǂݍ���
						D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%f", &pos.x);
						fscanf(pFile, "%f", &pos.y);
						fscanf(pFile, "%f", &pos.z);
						pCollision->SetPos(pos);
					}

					if (strcmp(&aStr[0], "COLLISION_SIZE") == 0)
					{// �L�[���̓ǂݍ���
						D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%f", &size.x);
						fscanf(pFile, "%f", &size.y);
						fscanf(pFile, "%f", &size.z);
						pCollision->SetSize(size);
					}
				}

				nCntSetModel++;
			}
		}
	}
	else
	{
		assert(false);
	}
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CModelObj::CModelObj() : m_pModel(nullptr),					// ���f�����
m_pColliRectangle3D(nullptr),								// �����蔻��
m_mtxWorld(D3DXMATRIX()),									// ���[���h�}�g���b�N�X
m_pos(D3DXVECTOR3()),										// �ʒu
m_posOld(D3DXVECTOR3()),									// �ߋ��ʒu
m_rot(D3DXVECTOR3()),										// ����
m_size(D3DXVECTOR3()),										// �傫��
m_nType(-1)													// ���f���̃^�C�v
{

}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CModelObj::~CModelObj()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CModelObj::Init()
{
	// �ϐ��̏�����
	m_mtxWorld = {};										// ���[���h�}�g���b�N�X
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ߋ��ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ����
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);					// �傫��
	m_nType = -1;											// ���f���̃^�C�v

	// �I�u�W�F�N�g�^�C�v�̓���
	SetObjType(OBJTYPE_3DMODEL);

	// ���f���N���X�̃������m��
	m_pModel = CModel3D::Create();
	assert(m_pModel != nullptr);
	m_pModel->SetModelID(m_nType);

	// 3D��`�̓����蔻��̐ݒ�
	m_pColliRectangle3D = CCollision_Rectangle3D::Create();
	m_pColliRectangle3D->SetParent(this);

	return E_NOTIMPL;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CModelObj::Uninit()
{
	if (m_pModel != nullptr)
	{// �I������
		m_pModel->Uninit();

		// �������̉��
		delete m_pModel;
		m_pModel = nullptr;
	}

	if (m_pColliRectangle3D != nullptr)
	{// �I������
		m_pColliRectangle3D->Uninit();
		m_pColliRectangle3D = nullptr;
	}

	// �I�u�W�F�N�g�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CModelObj::Update()
{
	// ���f���̍X�V
	m_pModel->Update();
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CModelObj::Draw()
{
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

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���f���̕`��
	m_pModel->Draw(m_mtxWorld);
}

//=============================================================================
// ���f���̃^�C�v�̐ݒ�
// Author : �������l
// �T�v : ���f���̃^�C�v�̐ݒ�
//=============================================================================
void CModelObj::SetType(const int nType)
{
	// ���f���̃^�C�v
	m_nType = nType;

	// ���f���N���X��ID�ݒ�
	m_pModel->SetModelID(m_nType);
}
