//=============================================================================
//
// �e�N�X�`���A�j���[�V��������(tex_anim.h)
// Author : �������l
// �T�v : �e�N�X�`���[�A�j���[�V�������v�Z����
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "tex_anim.h"

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CTexAnim::CTexAnim()
{
	m_patternAnim.x = 0;							// �A�j���[�V�����̃p�^�[��(X���W)
	m_patternAnim.y = 0;							// �A�j���[�V�����̃p�^�[��(Y���W)
	m_numAnim.x = 0;								// �A�j���[�V�����̃p�^�[��No.(X���W)
	m_numAnim.y = 0;								// �A�j���[�V�����̃p�^�[��No.(y���W)
	m_addTex = D3DXVECTOR2(0.0f, 0.0f);				// �e�N�X�`�����W�̑�����
	m_nMaxCntAnim = 0;								// �A�j���[�V�����̐؂�ւ�
	m_nCntAnim = 0;									// �A�j���[�V�����J�E���g
	m_bLoop = false;								// ���[�v�̎g�p��
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CTexAnim::~CTexAnim()
{

}

//=============================================================================
// �A�j���[�V�����\���̂̐ݒ�
// Author : �������l
// �T�v : �A�j���[�V�����\���̂̐ݒ���s�����l��Ԃ�
//=============================================================================
void CTexAnim::SetAnim(int nPatternAnimX, int nPatternAnimY, int nLife, bool bLoop)
{
	// �A�j���[�V�����̃p�^�[��
	m_patternAnim.x = nPatternAnimX;
	m_patternAnim.y = nPatternAnimY;

	// �A�j���[�V�����̃p�^�[��No.
	m_numAnim.x = 0;	// �A�j���[�V�����̃p�^�[��No.(X���W)
	m_numAnim.y = 0;	// �A�j���[�V�����̃p�^�[��No.(y���W)

	// ���[�v���g�p���邩
	m_bLoop = bLoop;

	if (!m_bLoop)
	{// ���[�v���g�p���Ȃ�
		// �A�j���[�V�����p�^�[���̃R�s�[
		TEX_PATTERN patternAnimCopy = m_patternAnim;

		if (patternAnimCopy.x <= 1)
		{// 1.0f�ȉ��Ȃ�0.0������
			patternAnimCopy.x = 0;
		}
		if (patternAnimCopy.y <= 1)
		{// 1.0f�ȉ��Ȃ�0.0������
			patternAnimCopy.y = 0;
		}

		// �A�j���[�V�����̐؂�ւ�
		m_nMaxCntAnim = nLife / (int)(patternAnimCopy.x + patternAnimCopy.y);
	}
	else
	{// �A�j���[�V�����̐؂�ւ�
		m_nMaxCntAnim = nLife;
	}

	// �A�j���[�V�����J�E���g
	m_nCntAnim = 0;

	// �e�N�X�`�����W�̑����ʂ̎Z�o
	m_addTex = D3DXVECTOR2(1.0f / m_patternAnim.x, 1.0f / m_patternAnim.y);
}

//=============================================================================
// �A�j���[�V�����̍Đ�
// Author : �������l
// �T�v : �A�j���[�V�����̍Đ����s��
//=============================================================================
void CTexAnim::PlayAnim()
{
	// �A�j���[�V�����J�E���g�̃C���N�������g
	m_nCntAnim++;

	if (m_nCntAnim % m_nMaxCntAnim == 0)
	{// �J�E���g�����ٓ_�ɒB�����ꍇ
	 // �p�^�[���J�E���g�̍X�V(X��)
		m_numAnim.x += 1;

		if (m_numAnim.x >= m_patternAnim.x)
		{// �J�E���g��X���̃p�^�[������������
			m_numAnim.x = 0;

			// �p�^�[���J�E���g�̍X�V(Y��)
			m_numAnim.y += 1;

			if (m_numAnim.y >= m_patternAnim.y)
			{// �J�E���g��Y���̃p�^�[������������
				m_numAnim.y = 0;
			}
		}
	}
}
