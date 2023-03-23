//=============================================================================
//
// ���b�V���N���X(mesh.cpp)
// Author : �������l
// �T�v : ���b�V���������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "calculation.h"
#include "mesh.h"
#include "renderer.h"
#include "application.h"
#include "debug_proc.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 2D���b�V���𐶐�����
//=============================================================================
CMesh3D * CMesh3D::Create(void)
{
	// ���b�V���C���X�^���X
	CMesh3D *pMesh3D = nullptr;

	// �������̉��
	pMesh3D = new CMesh3D;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pMesh3D != nullptr);

	// ���l�̏�����
	pMesh3D->Init();

	// �C���X�^���X��Ԃ�
	return pMesh3D;
}

//=============================================================================
// �����蔻��
// Author : �������l
// �T�v : �����蔻��
//=============================================================================
bool CMesh3D::CollisonMesh(CObject *pTarget)
{
	bool bCollison = false;

	for (int nCntPriority = 0; nCntPriority < MAX_LEVEL; nCntPriority++)
	{
		// ���̎擾
		CSuper *pTop = CSuper::GetTop(nCntPriority);
		CSuper *pCurrent = CSuper::GetCurrent(nCntPriority);

		if (pTop != nullptr)
		{// �ϐ��錾
			CSuper *pSuper = pTop;

			while (pSuper)
			{// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g��ۊ�
				CSuper *pSuperNext = pSuper->GetNext();

				if (!pSuper->GetFlagDeath()
					&& pSuper->GetElement() == ELEMENT_OBJECT)
				{
					// �I�u�W�F�N�g�N���X�ɃL���X�g
					CObject *pObject = (CObject*)pSuper;

					if (pObject->GetObjType() == CObject::OBJETYPE_MESH)
					{
						// ���b�V���փL���X�g
						CMesh3D *pMesh = (CMesh3D*)pObject;

						if (pMesh->GetUseCollison())
						{// �����蔻����s��
							bCollison = pMesh->Collison(pTarget);
						}

						if (bCollison)
						{
							break;
						}
					}
				}

				// ���݂̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���X�V
				pSuper = pSuperNext;
			}
		}
	}

	return bCollison;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CMesh3D::CMesh3D()
{
	m_pVtxBuff = nullptr;								// ���_�o�b�t�@
	m_pIdxBuff = nullptr;								// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	m_mtxWorld = {};									// ���[���h�}�g���b�N�X
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);				// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �傫��
	m_blockSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �u���b�N�T�C�Y
	m_tex = D3DXVECTOR2(1.0f, 1.0f);					// �e�N�X�`�����W�̊�l
	m_addTex = D3DXVECTOR2(0.0f, 0.0f);					// �e�N�X�`�����W�̉��Z�l
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			// �J���[
	m_nNumTex = -1;										// �e�N�X�`���^�C�v
	m_block = DOUBLE_INT(0, 0);							// �u���b�N��
	m_line = DOUBLE_INT(0, 0);							// ��
	m_nLineVtxX = 0;									// �񒸓_��(X)
	m_nVtx = 0;											// ���_��
	m_nPolygon = 0;										// �|���S����
	m_nIndex = 0;										// �C���f�b�N�X��
	m_bSplitTex = false;								// �������邩�ǂ���
	m_bScrollTex = false;								// �e�N�X�`�����X�N���[�����邩�ǂ���
	m_bUseCollison = false;								// �����蔻����g�����ۂ�
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CMesh3D::~CMesh3D()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CMesh3D::Init()
{
	// �����o�ϐ��̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_size = D3DXVECTOR3(100.0f, 0.0f, 100.0f);			// �傫��
	m_block = DOUBLE_INT(2, 2);							// �u���b�N��

	// �u���b�N�������̑傫���̎Z�o
	m_blockSize = D3DXVECTOR3(m_size.x / m_block.x, 0.0f, m_size.z / m_block.y);

	// ���l�̌v�Z
	SetMeshInfo();

	// ���_���W�Ȃǂ̐ݒ�
	SetVtx();

	// �F�̐ݒ�
	SetCol(m_col);

	// �e�N�X�`���̐ݒ�
	SetTex();

	// �C���f�b�N�X�̐ݒ�
	SetIndexBuff();

	// �@���̌v�Z
	Normal();

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjType(CObject::OBJETYPE_MESH);

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CMesh3D::Uninit()
{
	//���_�o�b�t�@��j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();

		m_pVtxBuff = nullptr;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��	  
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();

		m_pIdxBuff = nullptr;
	}

	// ���b�V��3D�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : 2D�X�V���s��
//=============================================================================
void CMesh3D::Update()
{
	TexScroll();
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : 2D�`����s��
//=============================================================================
void CMesh3D::Draw()
{// �����_���[�̃Q�b�g
	CRenderer *pRenderer = CApplication::GetRenderer();

	// �e�N�X�`���|�C���^�̎擾
	CTexture *pTexture = CApplication::GetTexture();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��������[�s��]��[�P�ʍs��]�ɏ�����)
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����̔��f
	// �s���]�֐� (��������[���[(y)�s�b�`(x)���[��(z)]�����̉�]�s����쐬)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	// �s��|���Z�֐� (������ * ��O������������Ɋi�[)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);						// �s��|���Z�֐�

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_nNumTex));

	// ���b�V���t�B�[���h�`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVtx, 0, m_nPolygon);

	// �e�N�X�`���̉���
	pDevice->SetTexture(0, nullptr);
}

//=============================================================================
// �ʒu�̃Z�b�^�[
// Author : �������l
// �T�v : �ʒu�̃����o�ϐ��Ɉ�������
//=============================================================================
void CMesh3D::SetPos(const D3DXVECTOR3 &pos)
{
	// �ʒu�̐ݒ�
	m_pos = pos;

	// ���_���W�Ȃǂ̐ݒ�
	SetVtx();

	// �F�̐ݒ�
	SetCol(m_col);

	// �e�N�X�`���̐ݒ�
	SetTex();

	// �C���f�b�N�X�̐ݒ�
	SetIndexBuff();

	// �@���̌v�Z
	Normal();
}

//=============================================================================
// �����̃Z�b�^�[
// Author : �������l
// �T�v : �����̃����o�ϐ��Ɉ�������
//=============================================================================
void CMesh3D::SetRot(const D3DXVECTOR3 &rot)
{
	// �ʒu�̐ݒ�
	m_rot = rot;

	// ���_���W�Ȃǂ̐ݒ�
	SetVtx();

	// �F�̐ݒ�
	SetCol(m_col);

	// �e�N�X�`���̐ݒ�
	SetTex();

	// �C���f�b�N�X�̐ݒ�
	SetIndexBuff();

	// �@���̌v�Z
	Normal();
}

//=============================================================================
// �傫���̃Z�b�^�[
// Author : �������l
// �T�v : �傫���̃����o�ϐ��Ɉ�������
//=============================================================================
void CMesh3D::SetSize(const D3DXVECTOR3 & size)
{
	// �傫���̐ݒ�
	m_size = size;

	// ���l�̌v�Z
	SetMeshInfo();

	// ���_���W�Ȃǂ̐ݒ�
	SetVtx();

	// �F�̐ݒ�
	SetCol(m_col);

	// �e�N�X�`���̐ݒ�
	SetTex();

	// �C���f�b�N�X�̐ݒ�
	SetIndexBuff();

	// �@���̌v�Z
	Normal();
}

//=============================================================================
// �u���b�N���̐ݒ�
// Author : �������l
// �T�v : �u���b�N���̐ݒ�
//=============================================================================
void CMesh3D::SetBlock(DOUBLE_INT block)
{
	m_block = block;

	// ���l�̌v�Z
	SetMeshInfo();

	// ���_���W�Ȃǂ̐ݒ�
	SetVtx();

	// �F�̐ݒ�
	SetCol(m_col);

	// �e�N�X�`���̐ݒ�
	SetTex();

	// �C���f�b�N�X�̐ݒ�
	SetIndexBuff();

	// �@���̌v�Z
	Normal();
}

//=============================================================================
// �e�N�X�`���������邩�̃Z�b�^�[
// Author : �������l
// �T�v : �e�N�X�`���������邩�̐ݒ�
//=============================================================================
void CMesh3D::SetSplitTex(bool bSplitTex)
{
	m_bSplitTex = bSplitTex;

	// �e�N�X�`���̐ݒ�
	SetTex();
}

//=============================================================================
// �e�N�X�`���X�N���[���̐ݒ�
// Author : �������l
// �T�v : �e�N�X�`���X�N���[���̐ݒ�
//=============================================================================
void CMesh3D::SetScrollTex(D3DXVECTOR2 addTex, bool bScrollTex)
{
	m_addTex = addTex;
	m_bScrollTex = bScrollTex;
}

//=============================================================================
// ���_���W�Ȃǂ̐ݒ�
// Author : �������l
// �T�v : 3D���_���W�Arhw�A���_�J���[��ݒ肷��
//=============================================================================
void CMesh3D::SetVtx()
{
	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < m_line.y; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_line.x; nCntX++)
		{// �ϐ��錾
			int nCntVtx = nCntX + (nCntZ *  m_line.x);

			// ���_���W�̐ݒ�
			pVtx[nCntVtx].pos.x = (nCntVtx % m_line.x * m_blockSize.x) - m_size.x / 2.0f;
			pVtx[nCntVtx].pos.y = 0.0f;
			pVtx[nCntVtx].pos.z = (nCntVtx / m_line.x * -m_blockSize.z) + m_size.z / 2.0f;
		}
	}

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
// Author : �������l
// �T�v : 3D���b�V���̃e�N�X�`�����W��ݒ肷��
//=============================================================================
void CMesh3D::SetTex()
{
	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < m_line.y; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_line.x; nCntX++)
		{// �ϐ��錾
			int nCntVtx = nCntX + (nCntZ *  m_line.x);

			if (m_bSplitTex)
			{// �e�N�X�`�����W�̐ݒ�
				pVtx[nCntVtx].tex = D3DXVECTOR2(1.0f * nCntX + m_tex.x, 1.0f * nCntZ + m_tex.y);
			}
			else
			{// �e�N�X�`�����W�̐ݒ�
				pVtx[nCntVtx].tex = D3DXVECTOR2(1.0f / m_block.x * nCntX + m_tex.x, 1.0f / m_block.y * nCntZ + m_tex.y);
			}	
		}
	}

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �F�̐ݒ�
// Author : �������l
// �T�v : 3D���b�V���̐F��ݒ肷��
//=============================================================================
void CMesh3D::SetCol(const D3DXCOLOR &col)
{
	m_col = col;

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < m_line.y; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_line.x; nCntX++)
		{// �ϐ��錾
			int nCntVtx = nCntX + (nCntZ *  m_line.x);

			// ���_�J���[�̐ݒ�
			pVtx[nCntVtx].col = m_col;
		}
	}

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �C���f�b�N�X�o�b�t�@�̐ݒ�
// Author : �������l
// �T�v : �C���f�b�N�X�o�b�t�@�̐��l��ݒ肷��
//=============================================================================
void CMesh3D::SetIndexBuff()
{
	// �C���f�b�N�X�o�b�t�@�����b�N
	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// �C���f�b�N�X�̐ݒ�
	for (int nCntZ = 0; nCntZ < m_block.y; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_line.x; nCntX++)
		{// �C���f�b�N�X���̐ݒ�
			pIdx[0] = (WORD)(m_line.x + nCntX + nCntZ * m_line.x);
			pIdx[1] = (WORD)(m_line.x + nCntX + nCntZ * m_line.x - m_line.x);

			pIdx += 2;
		}

		if (nCntZ != m_block.y - 1)
		{// �ő吔�ȉ��̎�
		 // �k�ރ|���S���C���f�b�N�X���̐ݒ�
			pIdx[0] = (WORD)(m_line.x * nCntZ + m_block.x);
			pIdx[1] = (WORD)(m_line.x * (nCntZ + 2));

			pIdx += 2;
		}
	}

	// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();
}

//=============================================================================
// ���b�V���̐��l�̌v�Z
// Author : �������l
// �T�v : ���C����,1�񕪂̒��_��(X),���_��,�|���S����,�C���f�b�N�X���̌v�Z
//=============================================================================
void CMesh3D::SetMeshInfo()
{// �f�o�C�X�̃Q�b�g
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	m_line = DOUBLE_INT(m_block.x + 1, m_block.y + 1);									// ���C����
	m_nLineVtxX = m_block.x * 2 + 2;													// 1�񕪂̒��_��(X)
	m_nVtx = m_line.x * m_line.y;														// ���_��
	m_nPolygon = (m_block.x * m_block.y * 2) + (((m_block.y - 1) * 2) * 2);				// �|���S����
	m_nIndex = (m_nLineVtxX * m_block.y) + ((m_block.y - 1) * 2);						// �C���f�b�N�X��

	// �u���b�N�������̑傫���̎Z�o
	m_blockSize = D3DXVECTOR3(m_size.x / m_block.x, 0.0f, m_size.z / m_block.y);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);
}

//=============================================================================
// �e�N�X�`���X�N���[��
// Author : �������l
// �T�v : �e�N�X�`���X�N���[��
//=============================================================================
void CMesh3D::TexScroll()
{
	if (m_bScrollTex)
	{
		m_tex += m_addTex;
		SetTex();
	}
}

//=============================================================================
// �@���̌v�Z
// Author : �������l
// �T�v : �ʖ@���x�N�g�����v�Z���A��������@�����Z�o����
//=============================================================================
void CMesh3D::Normal()
{
	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �C���f�b�N�X�o�b�t�@�����b�N
	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// �v�Z�p�ϐ�
	D3DXVECTOR3 aVtx[3] = { D3DXVECTOR3(0.0f,0.0f,0.0f) };
	D3DXVECTOR3 aVecLine[2] = { D3DXVECTOR3(0.0f,0.0f,0.0f) };

	for (int nCnt = 0; nCnt < m_nVtx; nCnt++)
	{
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	for (int nCntPolygon = 0; nCntPolygon < m_nPolygon; nCntPolygon++)
	{
		for (int nCntVtx = 0; nCntVtx < 3; nCntVtx++)
		{// ���_���W�̎擾
			aVtx[nCntVtx] = pVtx[pIdx[nCntPolygon + nCntVtx]].pos;
			aVtx[nCntVtx] = CCalculation::WorldCastVtx(aVtx[nCntVtx], m_pos, m_rot);
		}

		if (aVtx[0] == aVtx[1]
			|| aVtx[0] == aVtx[2]
			|| aVtx[1] == aVtx[2])
		{// �k�ރ|���S�����΂�
			continue;
		}

		// �|���S���̕Ӄx�N�g��
		aVecLine[0] = aVtx[1] - aVtx[0];
		aVecLine[1] = aVtx[2] - aVtx[0];

		// �ʖ@���x�N�g��
		D3DXVECTOR3 norVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if (nCntPolygon % 2 == 0)
		{// �ʖ@���x�N�g��
			D3DXVec3Cross(&norVec, &aVecLine[0], &aVecLine[1]);
		}
		else
		{// �ʖ@���x�N�g��
			D3DXVec3Cross(&norVec, &aVecLine[1], &aVecLine[0]);
		}

		// �ʖ@���x�N�g���̐��K��
		D3DXVec3Normalize(&norVec, &norVec);

		for (int nCntVtx = 0; nCntVtx < 3; nCntVtx++)
		{// �ʖ@���x�N�g���̉��Z
			pVtx[pIdx[nCntPolygon + nCntVtx]].nor += norVec;

			// �@���x�N�g���̐��K��
			D3DXVec3Normalize(&pVtx[pIdx[nCntPolygon + nCntVtx]].nor, &pVtx[pIdx[nCntPolygon + nCntVtx]].nor);
		}
	}

	// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �����蔻��
// Author : �������l
// �T�v : �����蔻����s��
//=============================================================================
bool CMesh3D::Collison(CObject *pTarget)
{
	// �����蔻��
	bool bCollison = false;

	if (!pTarget->GetFlagDeath())
	{
		// ���_���̎擾
		VERTEX_3D *pVtx = NULL;

		// ���_�o�b�t�@�����b�N
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �C���f�b�N�X�o�b�t�@�����b�N
		WORD *pIdx;
		m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

		// �^�[�Q�b�g���̐錾
		D3DXVECTOR3 posTarget = pTarget->GetPos();

		// �v�Z�p�ϐ�
		D3DXVECTOR3 aVtx[3] = { D3DXVECTOR3(0.0f,0.0f,0.0f) };
		D3DXVECTOR3 aVecLine[3] = { D3DXVECTOR3(0.0f,0.0f,0.0f) };
		D3DXVECTOR3 aVecPos[3] = { D3DXVECTOR3(0.0f,0.0f,0.0f) };
		float fInnerProduct[3] = { 0.0f };

		for (int nCntPolygon = 0; nCntPolygon < m_nPolygon; nCntPolygon++)
		{
			for (int nCntVtx = 0; nCntVtx < 3; nCntVtx++)
			{// ���_���W�̎擾
				aVtx[nCntVtx] = pVtx[pIdx[nCntPolygon + nCntVtx]].pos;
				aVtx[nCntVtx] = CCalculation::WorldCastVtx(aVtx[nCntVtx], m_pos, m_rot);
			}
			
			if (aVtx[0] == aVtx[1]
				|| aVtx[0] == aVtx[2]
				|| aVtx[1] == aVtx[2])
			{// �k�ރ|���S�����΂�
				continue;
			}

			// �|���S���̕Ӄx�N�g��
			aVecLine[0] = aVtx[1] - aVtx[0];
			aVecLine[1] = aVtx[2] - aVtx[1];
			aVecLine[2] = aVtx[0] - aVtx[2];

			for (int nCntVtx = 0; nCntVtx < 3; nCntVtx++)
			{// ���_�ƃ^�[�Q�b�g�̃x�N�g��
				aVecPos[nCntVtx] = posTarget - aVtx[nCntVtx];

				// ���_�ƃ^�[�Q�b�g�̃x�N�g���ƃ|���S���̕Ӄx�N�g���̓��ς��Z�o
				fInnerProduct[nCntVtx] = (aVecLine[nCntVtx].z * aVecPos[nCntVtx].x) - (aVecLine[nCntVtx].x * aVecPos[nCntVtx].z);
			}
			
			if ((0.0f <= fInnerProduct[0]
				&& 0.0f <= fInnerProduct[1]
				&& 0.0f <= fInnerProduct[2])
				|| (0.0f >= fInnerProduct[0]
				&& 0.0f >= fInnerProduct[1]
				&& 0.0f >= fInnerProduct[2]))
			{
				// �ʖ@���x�N�g��
				D3DXVECTOR3 norVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				// �ʖ@���x�N�g��
				D3DXVec3Cross(&norVec, &aVecLine[0], &aVecLine[1]);

				// �ʖ@���x�N�g���̐��K��
				D3DXVec3Normalize(&norVec, &norVec);
				
				// �����̌����_�̎Z�o
				float fIntersection = aVtx[0].y - ((posTarget.x - aVtx[0].x) * norVec.x + (posTarget.z - aVtx[0].z) * norVec.z) / norVec.y;

				if (fIntersection >= posTarget.y)
				{// �ʒu�̐ݒ�
					posTarget.y = fIntersection;

					// ����̐ݒ�
					bCollison = true;
				}
				
				// �^�[�Q�b�g�̐ݒ�
				pTarget->SetPos(posTarget);

#ifdef _DEBUG
				CDebugProc::Print("���ɂ���|���S�� : %d\n", nCntPolygon);
				CDebugProc::Print("���_%d�̖@�� | X : %.3f | Y : %.3f | Z : %.3f |\n", nCntPolygon, pVtx[pIdx[nCntPolygon]].nor.x, pVtx[pIdx[nCntPolygon]].nor.y, pVtx[pIdx[nCntPolygon]].nor.z);
				CDebugProc::Print("���_%d�̖@�� | X : %.3f | Y : %.3f | Z : %.3f |\n", nCntPolygon + 1, pVtx[pIdx[nCntPolygon + 1]].nor.x, pVtx[pIdx[nCntPolygon + 1]].nor.y, pVtx[pIdx[nCntPolygon + 1]].nor.z);
				CDebugProc::Print("���_%d�̖@�� | X : %.3f | Y : %.3f | Z : %.3f |\n", nCntPolygon + 2, pVtx[pIdx[nCntPolygon + 2]].nor.x, pVtx[pIdx[nCntPolygon + 2]].nor.y, pVtx[pIdx[nCntPolygon + 2]].nor.z);

				pVtx[pIdx[nCntPolygon]].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[pIdx[nCntPolygon + 1]].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
				pVtx[pIdx[nCntPolygon + 2]].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
#endif // DEBUG
				break;
			}
		}

		// �C���f�b�N�X�o�b�t�@�̃A�����b�N
		m_pIdxBuff->Unlock();

		// ���_�o�b�t�@�̃A�����b�N
		m_pVtxBuff->Unlock();
	}

	return bCollison;
}