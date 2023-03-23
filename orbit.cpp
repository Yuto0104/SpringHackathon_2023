//=============================================================================
//
// �O�ՃN���X(orbit.cpp)
// Author : �������l
// �T�v : �O�Ր������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "orbit.h"
#include "calculation.h"
#include "renderer.h"
#include "application.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : �O�Ղ𐶐�����
//=============================================================================
COrbit * COrbit::Create(void)
{
	// �O�ՃC���X�^���X
	COrbit *pOrbit = nullptr;

	// �������̉��
	pOrbit = new COrbit;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pOrbit != nullptr);

	// ���l�̏�����
	pOrbit->Init();

	// �C���X�^���X��Ԃ�
	return pOrbit;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
COrbit::COrbit()
{
	m_pParentMtx = nullptr;							// �e�̃}�g���b�N�X
	m_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu�̍���
	m_EBlendMode = BLEND_MODE::MODE_NORMAL;			// ���u�����h�̕��@
	m_nDivision = 0;								// ������
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
COrbit::~COrbit()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT COrbit::Init()
{
	// ������
	CMesh3D::Init();

	// �e�N�X�`���̐ݒ�
	LoadTex(-1);

	// �ʒu�̍���
	m_offset = D3DXVECTOR3(0.0f, 100.0f, 0.0f);		

	// ������
	m_nDivision = 1;				

	// �u���b�N���̐ݒ�
	SetBlock(CMesh3D::DOUBLE_INT(m_nDivision, 1));						

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void COrbit::Uninit()
{// �I��
	CMesh3D::Uninit();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : 2D�X�V���s��
//=============================================================================
void COrbit::Update()
{// �X�V
	CMesh3D::Update();

	// ���_���W�̎Z�o
	SetVtx();
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : 2D�`����s��
//=============================================================================
void COrbit::Draw()
{// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// ���C�g�𖳌�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �J�����O�͂��Ȃ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	switch (m_EBlendMode)
	{
	case BLEND_MODE::MODE_NORMAL:
		break;

	case BLEND_MODE::MODE_ADD:
		// ���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;

	case BLEND_MODE::MODE_SUB:
		// ���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;

	default:
		break;
	}

	// �`��
	CMesh3D::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �J�����O�ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// ���C�g��L��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// ���_���W�Ȃǂ̐ݒ�
// Author : �������l
// �T�v : 3D���_���W�Anor�A���_�J���[��ݒ肷��
//=============================================================================
void COrbit::SetVtx()
{
	// ���̎擾
	DOUBLE_INT block = GetBlock();
	DOUBLE_INT line = GetLine();
	D3DXVECTOR3 offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXCOLOR col = GetCol();
	int nMaxVtx = GetVtx();
	int nDivision = GetVtx() / 2;

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_pParentMtx != nullptr)
	{
		for (int nCntDivision = nDivision - 1; nCntDivision >= 0; nCntDivision--)
		{
			if (nCntDivision <= 0)
			{// �e�}�g���b�N�X���猻�݈ʒu���Z�o
				D3DXVec3TransformCoord(&pVtx[nCntDivision].pos, &offset, m_pParentMtx);
				D3DXVec3TransformCoord(&pVtx[nDivision + nCntDivision].pos, &m_offset, m_pParentMtx);
			}
			else
			{// �ЂƂO�̒��_�ʒu����
				pVtx[nCntDivision].pos = pVtx[nCntDivision - 1].pos;
				pVtx[nDivision + nCntDivision].pos = pVtx[nDivision + nCntDivision - 1].pos;
			}
		}
	}
	else
	{
		for (int nCntVtx = 0; nCntVtx < nMaxVtx; nCntVtx++)
		{// ������
			pVtx[nCntVtx].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
void COrbit::SetTex()
{
	// ���̎擾
	DOUBLE_INT block = GetBlock();
	DOUBLE_INT line = GetLine();
	D3DXVECTOR2 tex = GetTex();

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < line.y; nCntZ++)
	{
		for (int nCntX = 0; nCntX < line.x; nCntX++)
		{// �ϐ��錾
			int nCntVtx = nCntX + (nCntZ *  line.x);

			if (GetSplitTex())
			{// �e�N�X�`�����W�̐ݒ�
				pVtx[nCntVtx].tex = D3DXVECTOR2(1.0f * nCntX + tex.x, 1.0f * (line.y - nCntZ) + tex.y);
			}
			else
			{// �e�N�X�`�����W�̐ݒ�
				pVtx[nCntVtx].tex = D3DXVECTOR2(1.0f / block.x * nCntX + tex.x, 1.0f / block.y * (line.y - nCntZ) + tex.y);
			}
		}
	}

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �������̐ݒ�
// Author : �������l
// �T�v : 3D���b�V���̕�������ݒ肷��
//=============================================================================
void COrbit::SetDivision(const int nDivision)
{
	// �������̐ݒ�
	m_nDivision = nDivision;

	// �u���b�N���̐ݒ�
	SetBlock(CMesh3D::DOUBLE_INT(m_nDivision, 1));
}
