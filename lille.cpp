//=============================================================================
//
// 2D���[��(lille.cpp)
// Author : �������l
// �T�v : 2D���[���������s��
//
//=============================================================================

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define UDATE_FRAME (7)
#define DIGITS (10)

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "lille.h"
#include "renderer.h"
#include "application.h"
#include "calculation.h"
#include "number.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 2D�o���b�g�𐶐�����
//=============================================================================
CLille * CLille::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CLille *pLille = nullptr;

	pLille = new CLille;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pLille != nullptr);

	// ���l�̏�����
	pLille->Init();

	// �C���X�^���X��Ԃ�
	return pLille;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CLille::CLille(int nPriority) : CObject2D(nPriority)
{
	m_pNumDest = nullptr;		// �ڕW�̔ԍ�
	m_pNumber = nullptr;		// �ԍ�
	m_nNumDest = 0;				// �ڕW�̔ԍ�
	m_nNumber = 0;				// �ڕW�̔ԍ�
	m_nCntFrame = 0;			// �t���[���J�E���g
	bool m_bScroll = true;		// �X�N���[��
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CLille::~CLille()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : �e�N�X�`���̐ݒ肵�A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CLille::Init()
{
	// �I�u�W�F�N�g2D�̏I��
	CObject2D::Init();

	// �X�N���[�����s��
	m_bScroll = true;		

	// ����
	m_pNumDest = CNumber::Create();
	m_pNumber = CNumber::Create();

	// �ڕW�̔ԍ�
	m_nNumDest = CCalculation::Rand(10);
	m_pNumDest->SetNumber(m_nNumDest);
	m_pNumDest->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.2f, 1.0f));

	// ���݂̔ԍ�
	m_nNumber = CCalculation::Rand(10);
	m_pNumber->SetNumber(m_nNumber);

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CLille::Uninit()
{
	m_pNumDest->Uninit();
	m_pNumber->Uninit();

	// �I�u�W�F�N�g2D�̏I��
	CObject2D::Uninit();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : 2D�X�V���s��
//=============================================================================
void CLille::Update()
{
	// �I�u�W�F�N�g2D�̍X�V
	CObject2D::Update();

	if (m_bScroll)
	{
		Scroll();
	}
	else if (!m_bScroll)
	{
		if (m_nNumber == m_nNumDest)
		{// ������
		
		}

		m_nCntFrame++;

		if (m_nCntFrame % 150 == 0)
		{
			Uninit();
		}
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : 2D�`����s��
//=============================================================================
void CLille::Draw()
{// �v���C���[2D�̕`��
	CObject2D::Draw();
}

//=============================================================================
// ���[���̐ݒ�
// Author : �������l
// �T�v : ���[���̉�]���s��
//=============================================================================
void CLille::SetLille(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	SetPos(pos);
	SetSize(D3DXVECTOR3(0.0f,0.0f,0.0f));

	m_pNumDest->SetSize(D3DXVECTOR3(size.x / 2.0f, size.y / 2.0f, 0.0f));
	m_pNumber->SetSize(D3DXVECTOR3(size.x / 1.5f, size.y / 1.5f, 0.0f));

	m_pNumDest->SetPos(D3DXVECTOR3(pos.x, pos.y - size.y + size.y / 3.0f, 0.0f));
	m_pNumber->SetPos(D3DXVECTOR3(pos.x, pos.y + size.y - size.y / 1.5f, 0.0f));
}

//=============================================================================
// �X�N���[��
// Author : �������l
// �T�v : ���[���̉�]���s��
//=============================================================================
void CLille::Scroll()
{
	m_nCntFrame++;

	if (m_nCntFrame % UDATE_FRAME == 0)
	{
		m_pNumber->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_nNumber++;

		if (m_nNumber >= DIGITS)
		{
			m_nNumber = 0;
		}

		if (m_nNumber == m_nNumDest)
		{
			m_pNumber->SetCol(D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f));
		}

		m_pNumber->SetNumber(m_nNumber);
	}
}


