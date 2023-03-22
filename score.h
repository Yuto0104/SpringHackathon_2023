//=============================================================================
//
// �X�R�A�N���X(score.h)
// Author : �������l
// �T�v : �X�R�A�������s��
//
//=============================================================================
#ifndef _SCORE_H_		// ���̃}�N����`������ĂȂ�������
#define _SCORE_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;

//=============================================================================
// �X�R�A�N���X
// Author : �������l
// �T�v : �X�R�A�������s���N���X
//=============================================================================
class CScore : public CObject
{
private:
	//--------------------------------------------------------------------
	// �萔��`
	//--------------------------------------------------------------------
	static const float ADD_COEFFICIENT;			// ���Z�W��

public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CScore *Create(int nMaxDigit, bool bAddDigit);		// �X�R�A�̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CScore(int nPriority = CObject::PRIORITY_LEVEL3);
	~CScore() override;

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;														// ������
	HRESULT Init(int nDigit, bool bAddDigit);										// ������(�I�[�o�[���[�h)
	void Uninit() override;															// �I��
	void Update() override;															// �X�V
	void Draw() override;															// �`��
	void SetPos(const D3DXVECTOR3 &pos) override;									// �ʒu�̃Z�b�^�[
	void SetPosOld(const D3DXVECTOR3 &posOld) override { m_posOld = posOld; }		// �ߋ��ʒu�̃Z�b�^�[
	void SetRot(const D3DXVECTOR3 &rot) override;									// �����̃Z�b�^�[
	void SetSize(const D3DXVECTOR3 &size) override;									// �傫���̃Z�b�^�[
	void SetWholeSize(const D3DXVECTOR3 &wholeSize);								// �S�̂̑傫���̃Z�b�^�[
	void SetColor(const D3DXCOLOR &col);										
	D3DXVECTOR3 GetPos() override { return m_pos; }									// �ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetPosOld()  override { return m_posOld; }							// �ߋ��ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetRot()  override { return m_rot; }								// �����̃Q�b�^�[
	D3DXVECTOR3 GetSize()  override { return m_size; }								// �傫���̃Q�b�^�[
	D3DXVECTOR3 GetWholeSize() { return m_wholeSize; }								// �S�̂̑傫���̃Q�b�^�[
	void SetScore(int nScore);														// �X�R�A�̃Z�b�^�[
	void SetNumber();																// �i���o�[�̐ݒ�
	void AddScore(int nAdd);														// �X�R�A�̉��Z
	void CalScore();																// �X�R�A�̎Z�o
	void SetDestScore(const int nScore) { m_nDestScore = nScore; }					// �ړI�̃X�R�A�̐ݒ�
	int GetScore() { return m_nDestScore; }											// �X�R�A�̎擾

private:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void SetDigitNumbers();
	void AddDigit();

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CNumber				**m_pNumber;		// �i���o�[
	D3DXVECTOR3			m_pos;				// �ʒu
	D3DXVECTOR3			m_posOld;			// �ߋ��̈ʒu
	D3DXVECTOR3			m_rot;				// ����
	D3DXVECTOR3			m_size;				// �傫��
	D3DXVECTOR3			m_wholeSize;		// �S�̂̑傫��
	int					m_nMaxDigit;		// �ő包��
	int					m_nDigit;			// ����
	int					m_nScore;			// �X�R�A
	int					m_nDestScore;		// �ړI�̃X�R�A
	bool				m_bAddDigit;		// �����������邩�ǂ���
};

#endif

