//=============================================================================
//
// �I�u�W�F�N�g�N���X(object.h)
// Author : �������l
// �T�v : �I�u�W�F�N�g�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "object3D.h"
#include "renderer.h"
#include "application.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 2D�I�u�W�F�N�g�𐶐�����
//=============================================================================
CObject3D * CObject3D::Create(void)
{
	// �I�u�W�F�N�g�C���X�^���X
	CObject3D *pObject3D = nullptr;

	// �������̉��
	pObject3D = new CObject3D;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pObject3D != nullptr);

	// ���l�̏�����
	pObject3D->Init();

	// �C���X�^���X��Ԃ�
	return pObject3D;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CObject3D::CObject3D()
{
	m_pVtxBuff = nullptr;								// ���_�o�b�t�@
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �傫��
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		// �J���[
	m_fAngle = 0.0f;									// �Ίp���̊p�x
	m_fLength = 0.0f;									// �Ίp���̒���
	m_nNumTex = -1;										// �e�N�X�`���^�C�v
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CObject3D::~CObject3D()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CObject3D::Init()
{// �����_���[�̃Q�b�g
	CRenderer *pRenderer = CApplication::GetRenderer();

	//���_�o�b�t�@�̐���
	pRenderer->GetDevice()->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,		// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,														// ���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// �|���S�����̐ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �傫��
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �J���[
	m_zFunc = D3DCMP_LESS;							// Z�e�X�g�̗D��x
	m_nAlphaValue = 100;							// �A���t�@�e�X�g�̓��ߗ�
	m_nNumTex = -1;									// �e�N�X�`���^�C�v
	m_bBillboard = false;							// �r���{�[�h���ǂ���

	// ���_���W�Ȃǂ̐ݒ�
	SetVtx();

	// ���_�J���[��ݒ�
	SetCol();

	// �e�N�X�`�����W�̐ݒ�
	SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CObject3D::Uninit()
{
	//���_�o�b�t�@��j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();

		m_pVtxBuff = nullptr;
	}

	// �I�u�W�F�N�g3D�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : 2D�X�V���s��
//=============================================================================
void CObject3D::Update()
{

}

//=============================================================================
// �`��
// Author : �������l
// �T�v : 2D�`����s��
//=============================================================================
void CObject3D::Draw()
{// �����_���[�̃Q�b�g
	CRenderer *pRenderer = CApplication::GetRenderer();

	// �e�N�X�`���|�C���^�̎擾
	CTexture *pTexture = CApplication::GetTexture();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxView;

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��������[�s��]��[�P�ʍs��]�ɏ�����)
	D3DXMatrixIdentity(&m_mtxWorld);

	if (m_bBillboard)
	{// �r���{�[�h�ł���
		// ���C�g�𖳌�
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// �r���[�}�g���b�N�X�̐ݒ�
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		// �J�����t�s���ݒ�
		D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);
		m_mtxWorld._41 = 0.0f;
		m_mtxWorld._42 = 0.0f;
		m_mtxWorld._43 = 0.0f;
	}
	else
	{// �����̔��f
		// �s���]�֐� (��������[���[(y)�s�b�`(x)���[��(z)]�����̉�]�s����쐬)
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

		// �s��|���Z�֐� (������ * ��O������������Ɋi�[)
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	}

	// �ʒu�𔽉f
	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);						// �s��|���Z�֐�

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_nNumTex));

	// Z�e�X�g���g�p����
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZFUNC, m_zFunc);

	// ���e�X�g���g�p����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// ���e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, m_nAlphaValue);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// �|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// ���C�g��L��	
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// Z�e�X�g�̏I��
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// ���e�X�g�̏I��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// �e�N�X�`���̉���
	pDevice->SetTexture(0, nullptr);
}

//=============================================================================
// �ʒu�̃Z�b�^�[
// Author : �������l
// �T�v : �ʒu�̃����o�ϐ��Ɉ�������
//=============================================================================
void CObject3D::SetPos(const D3DXVECTOR3 &pos)
{
	// �ʒu�̐ݒ�
	m_pos = pos;

	// ���_���W�Ȃǂ̐ݒ�
	SetVtx();
}

//=============================================================================
// �����̃Z�b�^�[
// Author : �������l
// �T�v : �����̃����o�ϐ��Ɉ�������
//=============================================================================
void CObject3D::SetRot(const D3DXVECTOR3 &rot)
{
	// �ʒu�̐ݒ�
	m_rot = rot;

	// ���_���W�Ȃǂ̐ݒ�
	SetVtx();
}

//=============================================================================
// �傫���̃Z�b�^�[
// Author : �������l
// �T�v : �傫���̃����o�ϐ��Ɉ�������
//=============================================================================
void CObject3D::SetSize(const D3DXVECTOR3 & size)
{
	// �傫���̐ݒ�
	m_size = size;

	// ���_���W�Ȃǂ̐ݒ�
	SetVtx();
}

//=============================================================================
// �F�̐ݒ�
// Author : �������l
// �T�v : �F��ݒ肷��
//=============================================================================
void CObject3D::SetColor(D3DXCOLOR color)
{
	// �F�̐ݒ�
	m_color = color;

	// ���_�J���[�̐ݒ�
	SetCol();
}

//=============================================================================
// ���_���W�Ȃǂ̐ݒ�
// Author : �������l
// �T�v : 3D���_���W�Arhw�A���_�J���[��ݒ肷��
//=============================================================================
void CObject3D::SetVtx()
{
	//���_���ւ̃|�C���^�𐶐�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_size.x, -m_size.y, 0.0f);

	// �e���_�̖@���̐ݒ�(*�x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ���_�J���[�̐ݒ�
// Author : �������l
// �T�v : ���_�J���[��ݒ肷��
//=============================================================================
void CObject3D::SetCol()
{
	//���_���ւ̃|�C���^�𐶐�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
// Author : �������l
// �T�v : 3D�I�u�W�F�N�g�̃e�N�X�`�����W��ݒ肷��
//=============================================================================
void CObject3D::SetTex(const D3DXVECTOR2 &minTex, const D3DXVECTOR2 &maxTex)
{
	//���_���ւ̃|�C���^�𐶐�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(minTex.x, minTex.y);
	pVtx[1].tex = D3DXVECTOR2(maxTex.x, minTex.y);
	pVtx[2].tex = D3DXVECTOR2(minTex.x, maxTex.y);
	pVtx[3].tex = D3DXVECTOR2(maxTex.x, maxTex.y);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
