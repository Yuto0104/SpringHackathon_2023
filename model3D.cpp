//=============================================================================
//
// 3D���f���N���X(model3D.h)
// Author : �������l
// �T�v : 3D���f���������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <stdio.h>
#include <assert.h>

#include "model3D.h"
#include "renderer.h"
#include "application.h"
#include "texture.h"
#include "light.h"

//--------------------------------------------------------------------
// �ÓI�����o�ϐ���`
//--------------------------------------------------------------------
CModel3D::MODEL_MATERIAL *CModel3D::m_material = nullptr;		// �}�e���A�����
int CModel3D::m_nMaxModel = 0;									// ���f����		

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 3D���f���𐶐�����
//=============================================================================
CModel3D * CModel3D::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CModel3D *pModel3D = nullptr;

	// �������̉��
	pModel3D = new CModel3D;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pModel3D != nullptr);

	// ���l�̏�����
	pModel3D->Init();

	// �C���X�^���X��Ԃ�
	return pModel3D;
}

//=============================================================================
// ���f�����̏�����
// Author : �������l
// �T�v : �ǂݍ��񂾃��f����������3D���f���𐶐�����
//=============================================================================
void CModel3D::InitModel()
{
	// �����_���[�̃Q�b�g
	CRenderer *pRenderer = CApplication::GetRenderer();

	// �e�N�X�`���|�C���^�̎擾
	CTexture *pTexture = CApplication::GetTexture();

	// �e�N�X�`�����̎擾
	CTexture::TEXTURE *pTextureData = pTexture->GetTextureData();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �t�@�C���ǂݍ���
	LoadModel("data/FILE/data.txt");

	// �e�N�X�`���̎g�p���̃Q�b�g
	int nMaxTex = pTexture->GetMaxTexture();

	for (int nCntModel = 0; nCntModel < m_nMaxModel; nCntModel++)
	{// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(&m_material[nCntModel].aFileName[0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_material[nCntModel].pBuffer,
			NULL,
			&m_material[nCntModel].nNumMat,
			&m_material[nCntModel].pMesh);

		// �}�e���A���̃e�N�X�`�����̃������m��
		m_material[nCntModel].pNumTex = new int[m_material[nCntModel].nNumMat];
		assert(m_material[nCntModel].pNumTex != nullptr);

		// �o�b�t�@�̐擪�|�C���^��D3DXMATERIAL�ɃL���X�g���Ď擾
		D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_material[nCntModel].pBuffer->GetBufferPointer();

		// �e���b�V���̃}�e���A�������擾����
		for (int nCntMat = 0; nCntMat < (int)m_material[nCntModel].nNumMat; nCntMat++)
		{
			// �}�e���A���̃e�N�X�`�����̏�����
			m_material[nCntModel].pNumTex[nCntMat] = -1;

			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				for (int nCntTexture = 0; nCntTexture < nMaxTex; nCntTexture++)
				{
					if (strcmp(pMat[nCntMat].pTextureFilename, pTextureData[nCntTexture].aFileName) == 0)
					{
						m_material[nCntModel].pNumTex[nCntMat] = nCntTexture;
						break;
					}
				}
			}
		}

		// ���_���W�̍ŏ��l�E�ő�l�̎Z�o
		int		nNumVtx;	// ���_��
		DWORD	sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE	*pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^

		// ���_���̎擾
		nNumVtx = m_material[nCntModel].pMesh->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
		sizeFVF = D3DXGetFVFVertexSize(m_material[nCntModel].pMesh->GetFVF());

		// ���_�o�b�t�@�̃��b�N
		m_material[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		// �ł��傫�Ȓ��_
		D3DXVECTOR3 vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
		D3DXVECTOR3 vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			// ���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			if (vtx.x < vtxMin.x)
			{// ��r�Ώۂ����݂̒��_���W(X)�̍ŏ��l��菬����
				vtxMin.x = vtx.x;
			}
			if (vtx.y < vtxMin.y)
			{// ��r�Ώۂ����݂̒��_���W(Y)�̍ŏ��l��菬����
				vtxMin.y = vtx.y;
			}
			if (vtx.z < vtxMin.z)
			{// ��r�Ώۂ����݂̒��_���W(Z)�̍ŏ��l��菬����
				vtxMin.z = vtx.z;
			}

			if (vtx.x > vtxMax.x)
			{// ��r�Ώۂ����݂̒��_���W(X)�̍ő�l���傫��
				vtxMax.x = vtx.x;
			}
			if (vtx.y > vtxMax.y)
			{// ��r�Ώۂ����݂̒��_���W(Y)�̍ő�l���傫��
				vtxMax.y = vtx.y;
			}
			if (vtx.z > vtxMax.z)
			{// ��r�Ώۂ����݂̒��_���W(Z)�̍ő�l���傫��
				vtxMax.z = vtx.z;
			}

			// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		// ���_�o�b�t�@�̃A�����b�N
		m_material[nCntModel].pMesh->UnlockVertexBuffer();

		// �傫���̐ݒ�
		m_material[nCntModel].size = vtxMax - vtxMin;
	}
}

//=============================================================================
// ���f�����̏I��
// Author : �������l
// �T�v : ���f�����̏I��
//=============================================================================
void CModel3D::UninitModel()
{
	for (int nCnt = 0; nCnt < m_nMaxModel; nCnt++)
	{
		// ���b�V���̔j��
		if (m_material[nCnt].pMesh != nullptr)
		{
			m_material[nCnt].pMesh->Release();
			m_material[nCnt].pMesh = nullptr;
		}

		// �}�e���A���̔j��
		if (m_material[nCnt].pBuffer != nullptr)
		{
			m_material[nCnt].pBuffer->Release();
			m_material[nCnt].pBuffer = nullptr;
		}

		// �������̉��
		delete[] m_material[nCnt].pNumTex;
		m_material[nCnt].pNumTex = nullptr;
	}

	// �������̉��
	delete[] m_material;
	m_material = nullptr;
}

//=============================================================================
// X�t�@�C���̓ǂݍ���
// Author : �������l
// �T�v : X�t�@�C���̓ǂݍ��݂��s��
//=============================================================================
void CModel3D::LoadModel(const char *pFileName)
{
	// �ϐ��錾
	char aStr[128];
	int nCntModel = 0;

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

			if (strstr(&aStr[0], "MAX_TYPE") != NULL)
			{
				fscanf(pFile, "%s", &aStr[0]);
				fscanf(pFile, "%d", &m_nMaxModel);
				m_material = new CModel3D::MODEL_MATERIAL[m_nMaxModel];
				assert(m_material != nullptr);
			}

			if (strstr(&aStr[0], "MODEL_FILENAME") != NULL)
			{
				fscanf(pFile, "%s", &aStr[0]);
				fscanf(pFile, "%s", &m_material[nCntModel].aFileName[0]);
				nCntModel++;
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
CModel3D::CModel3D()
{
	m_pParent = nullptr;										// �e���f���̏��
	m_mtxWorld = {};											// ���[���h�}�g���b�N�X
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �傫��
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);				// �J���[
	m_nModelID = -1;											// ���f��ID
	m_bColor = false;											// �J���[���g�p����
	m_bShadow = true;											// �e�̎g�p��
	m_bLighting = true;											// ���C�g�̎g�p��
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CModel3D::~CModel3D()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CModel3D::Init()
{
	// �����o�ϐ��̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ����
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);					// �傫��
	m_nModelID = -1;										// ���f��ID

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CModel3D::Uninit()
{

}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : 2D�X�V���s��
//=============================================================================
void CModel3D::Update()
{

}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �e���f�����w�肳��Ă�ꍇ�A�e�̃��[���h�}�g���b�N�X���ɕ`�悷��
//=============================================================================
void CModel3D::Draw()
{
	if (m_nModelID >= 0
		&& m_nModelID < m_nMaxModel)
	{
		// �f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

		// �e�̃��[���h�}�g���b�N�X
		D3DXMATRIX mtxParent = {};

		// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxRot, mtxTrans, mtxScaling;

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);											// �s�񏉊����֐�

		// �����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);			// �s���]�֐�
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);						// �s��|���Z�֐� 

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				// �s��ړ��֐�
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);					// �s��|���Z�֐�

		if (m_pParent != nullptr)
		{
			mtxParent = m_pParent->GetMtxWorld();

			// �s��|���Z�֐�
			D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);
		}

		if (m_bShadow)
		{// �e�̐���
			Shadow();
		}
		
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// �}�e���A���`��
		DrawMaterial();
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CModel3D::Draw(D3DXMATRIX mtxParent)
{
	if (m_nModelID >= 0
		&& m_nModelID < m_nMaxModel)
	{
		// �f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

		// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxRot, mtxTrans, mtxScaling;

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);											// �s�񏉊����֐�

		// �T�C�Y�̔��f
		D3DXMatrixScaling(&mtxScaling, m_size.x, m_size.y, m_size.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScaling);					// �s��|���Z�֐�

		// �����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);			// �s���]�֐�
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);						// �s��|���Z�֐� 

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				// �s��ړ��֐�
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);					// �s��|���Z�֐�

		// �s��|���Z�֐�
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

		if (m_bShadow)
		{// �e�̐���
			Shadow();
		}

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// �}�e���A���`��
		DrawMaterial();
	}
}

//=============================================================================
// �}�e���A���`��
// Author : �������l
// �T�v : �}�e���A���`��
//=============================================================================
void CModel3D::DrawMaterial()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �e�N�X�`���|�C���^�̎擾
	CTexture *pTexture = CApplication::GetTexture();

	// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	if (!m_bLighting && !m_bColor)
	{// ���C�g�𖳌�
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	}

	// ���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	if (m_material[m_nModelID].pBuffer != nullptr)
	{// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_material[m_nModelID].pBuffer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_material[m_nModelID].nNumMat; nCntMat++)
		{
			if (m_bColor)
			{// �}�e���A�����̐ݒ�
				D3DMATERIAL9  matD3D = pMat[nCntMat].MatD3D;

				// ������F�ɐݒ�
				matD3D.Diffuse = m_color;

				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&matD3D);
			}
			else
			{// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			}
			
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTexture->GetTexture(m_material[m_nModelID].pNumTex[nCntMat]));

			// ���f���p�[�c�̕`��
			m_material[m_nModelID].pMesh->DrawSubset(nCntMat);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, nullptr);
		}
	}

	// �ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	// ���C�g��L��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// �ʒu�̃Z�b�^�[
// Author : �������l
// �T�v : �ʒu�̃����o�ϐ��Ɉ�������
//=============================================================================
void CModel3D::SetPos(const D3DXVECTOR3 &pos)
{
	// �ʒu�̐ݒ�
	m_pos = pos;
}

//=============================================================================
// �����̃Z�b�^�[
// Author : �������l
// �T�v : �����̃����o�ϐ��Ɉ�������
//=============================================================================
void CModel3D::SetRot(const D3DXVECTOR3 &rot)
{
	// �ʒu�̐ݒ�
	m_rot = rot;
}

//=============================================================================
// �傫���̃Z�b�^�[
// Author : �������l
// �T�v : �傫���̃����o�ϐ��Ɉ�������
//=============================================================================
void CModel3D::SetSize(const D3DXVECTOR3 & size)
{
	// �傫���̐ݒ�
	m_size = size;
}

//=============================================================================
// �J���[�̐ݒ�
// Author : �������l
// �T�v : �J���[��ݒ肵�A�J���[�g�p��
//=============================================================================
void CModel3D::SetColor(const D3DXCOLOR color)
{
	// �F�̐ݒ�
	m_color = color;
	m_bColor = true;
}

//=============================================================================
// �e�̐���
// Author : �������l
// �T�v : ���f���̉e�𐶐�����
//=============================================================================
void CModel3D::Shadow()
{
	// �ϐ��錾
	D3DXMATRIX		mtxShadow = {};													// �V���h�E�}�g���b�N�X
	D3DXPLANE		planeField = {};												// ���ʉ��p�ϐ�
	D3DXVECTOR4		vecLight = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);					// ���C�g�����̋t�x�N�g��
	D3DXVECTOR3		posShadow = D3DXVECTOR3(0.0f, 1.0f, 0.0f);;						// �e�̈ʒu
	D3DXVECTOR3		norShadow = D3DXVECTOR3(0.0f, 1.0f, 0.0f);;						// �e�̖@��
	D3DXVECTOR3		lightVec = CApplication::GetLight()->GetLightVec()  * -1;		// ���C�g����

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	// �V���h�E�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);	// �s�񏉊����֐�

	// ���C�g�����̋t�x�N�g���̐ݒ�
	vecLight = D3DXVECTOR4(lightVec.x, lightVec.y, lightVec.z, 0.0f);

	// ���ʉ��p�ϐ��̐ݒ�
	D3DXPlaneFromPointNormal(&planeField, &posShadow, &norShadow);

	// �V���h�E�}�g���b�N�X�̐ݒ�
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	// �s��|���Z�֐�
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	// �V���h�E�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	// ���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	if (m_material[m_nModelID].pBuffer != nullptr)
	{// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_material[m_nModelID].pBuffer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_material[m_nModelID].nNumMat; nCntMat++)
		{// �}�e���A�����̐ݒ�
			D3DMATERIAL9  matD3D = pMat[nCntMat].MatD3D;

			// ������F�ɐݒ�
			matD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
			matD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);

			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&matD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, nullptr);

			// ���f���p�[�c�̕`��
			m_material[m_nModelID].pMesh->DrawSubset(nCntMat);
		}
	}

	// �ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
