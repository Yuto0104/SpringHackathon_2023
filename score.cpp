//=============================================================================
//
// �X�R�A�N���X(score.cpp)
// Author : �������l
// �T�v : �X�R�A�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>
#include <math.h>

#include "score.h"
#include "number.h"
#include "renderer.h"
#include "application.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************
const float CScore::ADD_COEFFICIENT = 0.15f;

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : �X�R�A�𐶐�����
//=============================================================================
CScore *CScore::Create(int nMaxDigit, bool bAddDigit)
{
	// �I�u�W�F�N�g�C���X�^���X
	CScore *pScore = nullptr;

	pScore = new CScore;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pScore != nullptr);

	// ���l�̏�����
	pScore->Init(nMaxDigit, bAddDigit);

	// �C���X�^���X��Ԃ�
	return pScore;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CScore::CScore(int nPriority /*= CObject::PRIORITY_LEVEL3*/) : CObject(nPriority)
{
	m_pNumber = nullptr;								// �i���o�[
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);				// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ߋ��̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �傫��
	m_wholeSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �S�̂̑傫��
	m_nDigit = 0;										// ����
	m_nScore = 0;										// �X�R�A
	m_nDestScore = 0;									// �ړI�̃X�R�A
	m_bAddDigit = false;								// �����������邩�ǂ���
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CScore::~CScore()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CScore::Init()
{
	return S_OK;
}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CScore::Init(int nDigit, bool bAddDigit)
{
	// �����������邩�ǂ���
	m_bAddDigit = bAddDigit;

	// �����̐ݒ�
	m_nMaxDigit = nDigit;

	if (m_bAddDigit)
	{
		m_nDigit = 1;
	}
	else
	{
		m_nDigit = m_nMaxDigit;
	}

	// �X�R�A�̐ݒ�
	m_nScore = 0;

	// �ʒu�̐ݒ�
	m_pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);

	// �����̐ݒ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �傫���̐ݒ�
	m_size = D3DXVECTOR3(30.0f, 50.0f, 0.0f);

	// �S�̂̑傫���̐ݒ�
	m_wholeSize = D3DXVECTOR3(300.0f, 50.0f, 0.0f);

	// �i���o�[�̐���
	SetDigitNumbers();

	// �i���o�[�̐ݒ�
	SetNumber();

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CScore::Uninit()
{
	if (m_pNumber != nullptr)
	{// �I������
		for (int nCntDigit = 0; nCntDigit < m_nDigit; nCntDigit++)
		{
			m_pNumber[nCntDigit]->Uninit();
		}

		// �������̉��
		delete[] m_pNumber;
		m_pNumber = nullptr;
	}

	// �X�R�A�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CScore::Update()
{
	// �X�R�A�̎Z�o
	CalScore();
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CScore::Draw()
{

}

//=============================================================================
// �ʒu�̃Z�b�^�[
// Author : �������l
// �T�v : �ʒu�̃����o�ϐ��Ɉ�������
//=============================================================================
void CScore::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;

	// �i���o�[�̐ݒ�
	SetNumber();
}

//=============================================================================
// �����̃Z�b�^�[
// Author : �������l
// �T�v : �����̃����o�ϐ��Ɉ�������
//=============================================================================
void CScore::SetRot(const D3DXVECTOR3 &rot)
{
	m_rot = rot;

	// �i���o�[�̐ݒ�
	SetNumber();
}

//=============================================================================
// �傫���̃Z�b�^�[
// Author : �������l
// �T�v : �傫���̃����o�ϐ��Ɉ�������
//=============================================================================
void CScore::SetSize(const D3DXVECTOR3 & size)
{
	m_size = size;

	// �i���o�[�̐ݒ�
	SetNumber();
}

//=============================================================================
// �S�̂̑傫���̃Z�b�^�[
// Author : �������l
// �T�v : �S�̂̑傫���̃����o�ϐ��Ɉ�������
//=============================================================================
void CScore::SetWholeSize(const D3DXVECTOR3 & wholeSize)
{
	m_wholeSize = wholeSize;

	// �i���o�[�̐ݒ�
	SetNumber();
}

//=============================================================================
// �F�̃Z�b�^�[
// Author : �������l
// �T�v : �F�̐ݒ���s��
//=============================================================================
void CScore::SetColor(const D3DXCOLOR & col)
{
	for (int nCntDigit = 0; nCntDigit < m_nDigit; nCntDigit++)
	{
		m_pNumber[nCntDigit]->SetCol(col);
	}
}

//=============================================================================
// �X�R�A�̃Z�b�^�[
// Author : �������l
// �T�v : �X�R�A�ɐ��l�������āA�i���o�[�̐ݒ�
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;

	for (int nCntDigit = 0; nCntDigit < m_nDigit; nCntDigit++)
	{
		int nNum0 = (int)pow(10, nCntDigit + 1);
		int nNum1 = (int)pow(10, nCntDigit);

		m_pNumber[nCntDigit]->SetNumber(m_nScore % nNum0 / nNum1);
	}
}

//=============================================================================
// �i���o�[�̐ݒ�
// Author : �������l
// �T�v : �i���o�[�̐ݒ���s��
//=============================================================================
void CScore::SetNumber()
{
	// �T�C�Y�̎Z�o���ʂ���
	D3DXVECTOR3 size = m_size;
	float fFullSize = m_size.x * m_nDigit;

	if (m_wholeSize.x <= (m_size.x * m_nDigit))
	{
		size = D3DXVECTOR3(m_wholeSize.x / m_nDigit, m_size.y, 0.0f);
		fFullSize = m_wholeSize.x;
	}

	float fSpX = m_pos.x - (m_nDigit - 1) * 0.5f * size.x;

	for (int nCntDigit = 0; nCntDigit < m_nDigit; nCntDigit++)
	{
		int nNumDigit = (m_nDigit - 1) - nCntDigit;

		if (m_bAddDigit)
		{// �ʒu�̐ݒ�
			m_pNumber[nNumDigit]->SetPos(D3DXVECTOR3(fSpX + size.x * nCntDigit, m_pos.y, 0.0f));
		}
		else
		{// �ʒu�̐ݒ�
			m_pNumber[nNumDigit]->SetPos(D3DXVECTOR3(m_pos.x - fFullSize + (size.x * nCntDigit), m_pos.y, 0.0f));
		}

		// �����̐ݒ�
		m_pNumber[nNumDigit]->SetRot(m_rot);

		// �傫���̐ݒ�
		m_pNumber[nNumDigit]->SetSize(size);
	}
}

//=============================================================================
// �X�R�A�̉��Z
// Author : �������l
// �T�v : �X�R�A�����Z����
//=============================================================================
void CScore::AddScore(int nAdd)
{
	m_nDestScore += nAdd;
}

//=============================================================================
// �X�R�A���Z�o����
// Author : �������l
// �T�v : �X�R�A���Z�o����
//=============================================================================
void CScore::CalScore()
{
	if (m_nDestScore != m_nScore)
	{
		int add = (m_nDestScore - m_nScore) * 0.15f;

		if (add == 0)
		{
			add = 1;
		}

		m_nScore += add;

		if (add > 0
			&& m_nDestScore <= m_nScore)
		{
			m_nScore = m_nDestScore;
		}
		else if (add < 0
			&& m_nDestScore >= m_nScore)
		{
			m_nScore = m_nDestScore;
		}

		if (m_bAddDigit)
		{
			AddDigit();
		}
	}

	SetScore(m_nScore);
}

//=============================================================================
// �����̐���
// Author : �������l
// �T�v : �����𐶐�����
//=============================================================================
void CScore::SetDigitNumbers()
{
	if (m_pNumber == nullptr)
	{// �i���o�[�̃������m��
		m_pNumber = new CNumber*[m_nDigit];
		assert(m_pNumber != nullptr);

		for (int nCntDigit = 0; nCntDigit < m_nDigit; nCntDigit++)
		{// �i���o�[�̐ݒ�
			m_pNumber[nCntDigit] = CNumber::Create();
		}
	}
}

//=============================================================================
// �����𑝂₷
// Author : �������l
// �T�v : �����𑝂₷
//=============================================================================
void CScore::AddDigit()
{
	if (m_nScore >= (int)pow(10, m_nDigit))
	{
		if (m_pNumber != nullptr)
		{// �I������
			for (int nCntDigit = 0; nCntDigit < m_nDigit; nCntDigit++)
			{
				m_pNumber[nCntDigit]->Uninit();
			}

			// �������̉��
			delete[] m_pNumber;
			m_pNumber = nullptr;
		}

		// �����̉��Z
		m_nDigit += 1;

		if (m_nMaxDigit <= m_nDigit)
		{
			m_nDigit = m_nMaxDigit;
		}

		// �i���o�[�̐���
		SetDigitNumbers();

		// �i���o�[�̐ݒ�
		SetNumber();
	}
	else if (m_nScore < (int)pow(10, m_nDigit - 1))
	{
		if (m_pNumber != nullptr)
		{// �I������
			for (int nCntDigit = 0; nCntDigit < m_nDigit; nCntDigit++)
			{
				m_pNumber[nCntDigit]->Uninit();
			}

			// �������̉��
			delete[] m_pNumber;
			m_pNumber = nullptr;
		}

		// �����̉��Z
		m_nDigit -= 1;

		if (1 >= m_nDigit)
		{
			m_nDigit = 1;
		}

		// �i���o�[�̐���
		SetDigitNumbers();

		// �i���o�[�̐ݒ�
		SetNumber();
	}
}
