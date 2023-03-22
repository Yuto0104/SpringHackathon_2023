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

#include "object2D.h"
#include "renderer.h"
#include "application.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 2D�I�u�W�F�N�g�𐶐�����
//=============================================================================
CObject2D * CObject2D::Create(void)
{
	// �I�u�W�F�N�g�C���X�^���X
	CObject2D *pObject2D = nullptr;

	// �������̉��
	pObject2D = new CObject2D;

	if (pObject2D != nullptr)
	{// ���l�̏�����
		pObject2D->Init();
	}
	else
	{// �������̊m�ۂ��ł��Ȃ�����
		assert(false);
	}

	// �C���X�^���X��Ԃ�
	return pObject2D;
}

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 2D�I�u�W�F�N�g�𐶐�����
//=============================================================================
CObject2D * CObject2D::Create(int nPriority)
{
	// �I�u�W�F�N�g�C���X�^���X
	CObject2D *pObject2D = nullptr;

	// �������̉��
	pObject2D = new CObject2D(nPriority);

	if (pObject2D != nullptr)
	{// ���l�̏�����
		pObject2D->Init();
	}
	else
	{// �������̊m�ۂ��ł��Ȃ�����
		assert(false);
	}

	// �C���X�^���X��Ԃ�
	return pObject2D;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CObject2D::CObject2D(int nPriority/* = PRIORITY_LEVEL0*/) : CObject(nPriority)
{
	m_pVtxBuff = nullptr;								// ���_�o�b�t�@
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �傫��
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);			// �J���[
	m_fAngle = 0.0f;									// �Ίp���̊p�x
	m_fLength = 0.0f;									// �Ίp���̒���
	m_nNumTex = -1;										// �e�N�X�`���^�C�v
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CObject2D::~CObject2D()
{
	
}

//=============================================================================
// �|���S���̏�����
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CObject2D::Init()
{// �����_���[�̃Q�b�g
	CRenderer *pRenderer = CApplication::GetRenderer();

	//���_�o�b�t�@�̐���
	pRenderer->GetDevice()->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,		// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,														// ���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// �|���S�����̐ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
	m_size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);		// �傫��
	m_nNumTex = -1;									// �e�N�X�`���^�C�v
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �F�̐ݒ�

	// �F�̐ݒ�
	SetCol(m_col);

	// �e�N�X�`�����W�̐ݒ�
	SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// �|���S���̏I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CObject2D::Uninit()
{ 
	//���_�o�b�t�@��j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();

		m_pVtxBuff = nullptr;
	}

	// �I�u�W�F�N�g2D�̉��
	Release();
}

//=============================================================================
// �|���S���̍X�V
// Author : �������l
// �T�v : 2D�|���S���̍X�V���s��
//=============================================================================
void CObject2D::Update()
{
	
}

//=============================================================================
// �|���S���̕`��
// Author : �������l
// �T�v : 2D�|���S���̕`����s��
//=============================================================================
void CObject2D::Draw()
{// �����_���[�̃Q�b�g
	CRenderer *pRenderer = CApplication::GetRenderer();
	
	// �e�N�X�`���|�C���^�̎擾
	CTexture *pTexture = CApplication::GetTexture();

	//�e�N�X�`���̐ݒ�
	pRenderer->GetDevice()->SetTexture(0, nullptr);

	//�e�N�X�`���̐ݒ�
	pRenderer->GetDevice()->SetTexture(0, pTexture->GetTexture(m_nNumTex));

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pRenderer->GetDevice()->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pRenderer->GetDevice()->SetFVF(FVF_VERTEX_2D);

	//�|���S���`��
	pRenderer->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�e�N�X�`���̐ݒ�
	pRenderer->GetDevice()->SetTexture(0, nullptr);
}

//=============================================================================
// �ʒu�̃Z�b�^�[
// Author : �������l
// �T�v : �ʒu�̃����o�ϐ��Ɉ�������
//=============================================================================
void CObject2D::SetPos(const D3DXVECTOR3 &pos)
{
	// �ʒu�̐ݒ�
	m_pos = pos;

	// ���_���W�Ȃǂ̐ݒ�
	SetVtx();

	// �F�̐ݒ�
	SetCol(m_col);
}

//=============================================================================
// �����̃Z�b�^�[
// Author : �������l
// �T�v : �����̃����o�ϐ��Ɉ�������
//=============================================================================
void CObject2D::SetRot(const D3DXVECTOR3 &rot)
{
	// �����̐ݒ�
	m_rot = rot;

	// ���_���W�Ȃǂ̐ݒ�
	SetVtx();

	// �F�̐ݒ�
	SetCol(m_col);
}

//=============================================================================
// �傫���̃Z�b�^�[
// Author : �������l
// �T�v : �傫���̃����o�ϐ��Ɉ�������
//=============================================================================
void CObject2D::SetSize(const D3DXVECTOR3 & size)
{
	// �傫���̐ݒ�
	m_size = size;

	// ���_���W�Ȃǂ̐ݒ�
	SetVtx();

	// �F�̐ݒ�
	SetCol(m_col);
}

//=============================================================================
// ���_���W�Ȃǂ̐ݒ�
// Author : �������l
// �T�v : 2D�|���S���̒��_���W�Arhw�A���_�J���[��ݒ肷��
//=============================================================================
void CObject2D::SetVtx()
{
	//���_���ւ̃|�C���^�𐶐�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�Ίp���̒������Z�o����
	m_fLength = sqrtf((m_size.x * m_size.x) + (m_size.y * m_size.y)) / 2.0f;

	//�Ίp���̊p�x���Z�o
	m_fAngle = atan2f(m_size.x, m_size.y);

	// ���_����ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) *  m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) *  m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - (0 + m_fAngle)) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - (0 + m_fAngle)) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z - (0 - m_fAngle)) *  m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z - (0 - m_fAngle)) *  m_fLength;
	pVtx[3].pos.z = 0.0f;

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �F�̐ݒ�
// Author : �������l
// �T�v : ���_�J���[��ݒ肷��
//=============================================================================
void CObject2D::SetCol(const D3DCOLOR &col)
{
	m_col = col;

	//���_���ւ̃|�C���^�𐶐�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
// Author : �������l
// �T�v : 2D�I�u�W�F�N�g�̃e�N�X�`�����W��ݒ肷��
//=============================================================================
void CObject2D::SetTex(const D3DXVECTOR2 &minTex, const D3DXVECTOR2 &maxTex)
{
	//���_���ւ̃|�C���^�𐶐�
	VERTEX_2D *pVtx;

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
