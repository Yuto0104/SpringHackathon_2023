//=============================================================================
//
// �w�i�N���X(object.h)
// Author : �������l
// �T�v : �w�i�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "bg.h"
#include "renderer.h"
#include "application.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 3D���f���𐶐�����
//=============================================================================
CBG * CBG::Create(void)
{
	// �I�u�W�F�N�g�C���X�^���X
	CBG *pBG = nullptr;

	// �������̉��
	pBG = new CBG;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pBG != nullptr);

	// ���l�̏�����
	pBG->Init();

	// �C���X�^���X��Ԃ�
	return pBG;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CBG::CBG(int nPriority/* = PRIORITY_LEVEL0*/) : CObject(nPriority)
{
	m_pVtxBuff = nullptr;								// ���_�o�b�t�@
	m_col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);				// �J���[
	m_nNumTex = -1;										// �e�N�X�`���̎��
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CBG::~CBG()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CBG::Init()
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
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �J���[
	m_nNumTex = 9;									// �e�N�X�`���^�C�v

	// ���_���W�̐ݒ�
	SetVtx();

	// ���_�J���[�̐ݒ�
	SetCol(m_col);

	// �e�N�X�`�����W�̐ݒ�
	SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CBG::Uninit()
{
	//���_�o�b�t�@��j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();

		m_pVtxBuff = nullptr;
	}

	// �w�i3D�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : 2D�X�V���s��
//=============================================================================
void CBG::Update()
{

}

//=============================================================================
// �`��
// Author : �������l
// �T�v : 2D�`����s��
//=============================================================================
void CBG::Draw()
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
// ���_�J���[�̐ݒ�
// Author : �������l
// �T�v : 2D�|���S���̒��_�J���[��ݒ肷��
//=============================================================================
void CBG::SetCol(const D3DXCOLOR color)
{
	// �J���[�̐ݒ�
	m_col = color;

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
// ���_���W�Ȃǂ̐ݒ�
// Author : �������l
// �T�v : 2D�|���S���̒��_���W�Arhw�A���_�J���[��ݒ肷��
//=============================================================================
void CBG::SetVtx()
{
	//���_���ւ̃|�C���^�𐶐�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, (float)CRenderer::SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
// Author : �������l
// �T�v : 2D�I�u�W�F�N�g�̃e�N�X�`�����W��ݒ肷��
//=============================================================================
void CBG::SetTex(const D3DXVECTOR2 &minTex, const D3DXVECTOR2 &maxTex)
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