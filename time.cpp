//=============================================================================
//
// �^�C���N���X(time.h)
// Author : �������l
// �T�v : �^�C���������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>
#include <math.h>

#include "time.h"
#include "number.h"
#include "renderer.h"
#include "application.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : �^�C���𐶐�����
//=============================================================================
CTime *CTime::Create(int nMaxDigit)
{
	// �I�u�W�F�N�g�C���X�^���X
	CTime *pTime = nullptr;

	pTime = new CTime;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pTime != nullptr);

	// ���l�̏�����
	pTime->Init(nMaxDigit);

	// �C���X�^���X��Ԃ�
	return pTime;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CTime::CTime(int nPriority /*= CObject::PRIORITY_LEVEL3*/) : CObject(nPriority)
{
	m_pNumber = nullptr;								// �i���o�[
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);				// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ߋ��ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �傫��
	m_wholeSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �S�̂̑傫��
	m_nDigit = 0;										// ����
	m_nTime = 0;										// �^�C��
	m_nCntFrame = 0;									// �t���[���J�E���g
	m_bAdd = true;										// ���Z
	m_bTimeEnd = false;									// ���Ԑ؂�
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CTime::~CTime()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CTime::Init()
{
	return S_OK;
}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CTime::Init(int nDigit)
{
	// �����̐ݒ�
	m_nMaxDigit = nDigit;
	m_nDigit = 1;

	// �^�C���̐ݒ�
	m_nTime = 0;

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
void CTime::Uninit()
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

	// �^�C���̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CTime::Update()
{
	CalTime();
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CTime::Draw()
{

}

//=============================================================================
// �ʒu�̃Z�b�^�[
// Author : �������l
// �T�v : �ʒu�̃����o�ϐ��Ɉ�������
//=============================================================================
void CTime::SetPos(const D3DXVECTOR3 &pos)
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
void CTime::SetRot(const D3DXVECTOR3 &rot)
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
void CTime::SetSize(const D3DXVECTOR3 & size)
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
void CTime::SetWholeSize(const D3DXVECTOR3 & wholeSize)
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
void CTime::SetColor(const D3DXCOLOR & col)
{
	for (int nCntDigit = 0; nCntDigit < m_nDigit; nCntDigit++)
	{
		m_pNumber[nCntDigit]->SetCol(col);
	}
}

//=============================================================================
// �^�C���̃Z�b�^�[
// Author : �������l
// �T�v : �^�C���ɐ��l�������āA�i���o�[�̐ݒ�
//=============================================================================
void CTime::SetTime(int nTime)
{
	m_nTime = nTime;

	AddDigit();

	for (int nCntDigit = 0; nCntDigit < m_nDigit; nCntDigit++)
	{
		int nNum0 = (int)pow(10, nCntDigit + 1);
		int nNum1 = (int)pow(10, nCntDigit);

		m_pNumber[nCntDigit]->SetNumber(m_nTime % nNum0 / nNum1);
	}
}

//=============================================================================
// �i���o�[�̐ݒ�
// Author : �������l
// �T�v : �i���o�[�̐ݒ���s��
//=============================================================================
void CTime::SetNumber()
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

		// �ʒu�̐ݒ�
		m_pNumber[nNumDigit]->SetPos(D3DXVECTOR3(fSpX + size.x * nCntDigit, m_pos.y, 0.0f));

		// �����̐ݒ�
		m_pNumber[nNumDigit]->SetRot(m_rot);

		// �傫���̐ݒ�
		m_pNumber[nNumDigit]->SetSize(size);
	}
}

//=============================================================================
// ���Ԃ̐ݒ�
// Author : �������l
// �T�v : ���Ԃ̐ݒ���s��
//=============================================================================
void CTime::CalTime()
{
	m_nCntFrame++;

	if (m_nCntFrame % 60 == 0)
	{
		if (m_bAdd)
		{
			m_nTime++;
		}
		else
		{
			m_nTime--;

			if (m_nTime < 0)
			{
				m_nTime = 0;
				m_bTimeEnd = true;
			}
		}

		SetTime(m_nTime);
	}
}

//=============================================================================
// �����̐���
// Author : �������l
// �T�v : �����𐶐�����
//=============================================================================
void CTime::SetDigitNumbers()
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
void CTime::AddDigit()
{
	while (1)
	{
		if (m_nTime >= (int)pow(10, m_nDigit))
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
		else if (m_nTime < (int)pow(10, m_nDigit - 1))
		{
			bool bBreak = false;

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
				bBreak = true;
			}

			// �i���o�[�̐���
			SetDigitNumbers();

			// �i���o�[�̐ݒ�
			SetNumber();

			if (bBreak)
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
}
