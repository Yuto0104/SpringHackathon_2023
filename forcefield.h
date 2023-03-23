//=============================================================================
//
// �t�H�[�X�t�B�[���h�N���X(forcefield.h)
// Author : �ē�����
// �T�v : �t�H�[�X�t�B�[���h
//
//=============================================================================
#ifndef _FORCEFIELD_H_		// ���̃}�N����`������ĂȂ�������
#define _FORCEFIELD_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "skill.h"

//*****************************************************************************
//	�O���錾
//*****************************************************************************

//=============================================================================
// �t�H�[�X�t�B�[���h�N���X
// Author : �ē�����
// �T�v : �t�H�[�X�t�B�[���h
//=============================================================================
class CForceField : public CSkill
{
public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CForceField *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// �n���̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CForceField();
	~CForceField();

	//--------------------------------------------------------------------
	// �I�[�o�[���C�h�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;								// ������
	void Uninit() override;									// �I��
	void Update() override;									// �X�V
	void Draw() override;									// �`��

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	int m_nDamage;											// �_���[�W��
	int m_AttackTime;										// �U������
};

#endif