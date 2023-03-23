//=============================================================================
//
// 2D���[��(lille.h)
// Author : �������l
// �T�v : 2D���[���������s��
//
//=============================================================================
#ifndef _LILLE _H_		// ���̃}�N����`������ĂȂ�������
#define _LILLE_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object2D.h"

//=============================================================================
// 2D���[���N���X
// Author : �������l
// �T�v : 2D���[���������s���N���X
//=============================================================================
class CLille : public CObject2D
{
public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	// 2D���[���̐���
	static CLille *Create();

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	explicit CLille(int nPriority = CObject::PRIORITY_LEVEL3);
	~CLille() override;

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;									// ������
	void Uninit() override;										// �I��
	void Update() override;										// �X�V
	void Draw() override;										// �`��
	void SetRatio(const int nRatio) { m_nRatio = nRatio; }		// �m���̐ݒ�
	bool Lottery();												// ���I

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	int m_nRatio;				// �m���̐ݒ�
	bool m_bScroll;				// �X�N���[��
};

#endif