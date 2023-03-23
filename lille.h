//=============================================================================
//
// 2D���[��(lille.h)
// Author : �������l
// �T�v : 2D���[���������s��
//
//=============================================================================
#ifndef _LILLE_H_		// ���̃}�N����`������ĂȂ�������
#define _LILLE_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object2D.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;

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
	void SetLille(D3DXVECTOR3 pos , D3DXVECTOR3 size);			// ���[���̐ݒ�
	void StopScroll() { m_bScroll = false; 
						m_nCntFrame = 0; }					// �X�N���[���̒�~
	bool GetScroll() { return m_bScroll; }

private:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void Scroll();

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CNumber *m_pNumDest;		// �ڕW�̔ԍ�
	CNumber *m_pNumber;			// �ԍ�
	int m_nNumDest;				// �ڕW�̔ԍ�
	int m_nNumber;				// �ڕW�̔ԍ�
	int m_nCntFrame;			// �t���[���J�E���g
	bool m_bScroll;				// �X�N���[��
	bool m_SkillFlag;			//�X�L���̃t���O
};

#endif
