//=============================================================================
//
// ���C�t�N���X(life.h)
// Author : ����]��
// �T�v : �I�u�W�F�N�g�������s��
//
//=============================================================================
#ifndef _LIFE_H_		// ���̃}�N����`������ĂȂ�������
#define _LIFE_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object2D.h"
#include "texture.h"

//=============================================================================
// ���C�t�N���X
// Author : ����]��
// �T�v : ���C�t�������s���N���X
//=============================================================================
class CLife : public CObject2D
{
public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CLife *Create(void);				// ���C�t�̐���
	static CLife *Create(int nPriority);	// ���C�t�̐���(�I�[�o�[���[�h)

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	explicit CLife(int nPriority = PRIORITY_LEVEL0);
	~CLife() override;

	//--------------------------------------------------------------------
	// �I�[�o�[���C�h�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;														// ������
	void Uninit() override;															// �I��
	void Update() override;															// �X�V
	void Draw() override;															// �`��

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	
};

#endif