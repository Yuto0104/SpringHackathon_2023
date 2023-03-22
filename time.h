//=============================================================================
//
// �^�C���N���X(time.h)
// Author : �������l
// �T�v : �^�C���������s��
//
//=============================================================================
#ifndef _TIME_H_		// ���̃}�N����`������ĂȂ�������
#define _TIME_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;

//=============================================================================
// �^�C���N���X
// Author : �������l
// �T�v : �^�C���������s���N���X
//=============================================================================
class CTime : public CObject
{
public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CTime *Create(int nMaxDigit);		// �^�C���̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CTime(int nPriority = CObject::PRIORITY_LEVEL3);
	~CTime() override;

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;														// ������
	HRESULT Init(int nDigit);														// ������(�I�[�o�[���[�h)
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
	void SetTime(int nTime);														// �^�C���̃Z�b�^�[
	void SetNumber();																// �i���o�[�̐ݒ�
	void CalTime();																	// �^�C���̎Z�o
	void SetTimeAdd(bool bAdd) { m_bAdd = bAdd; }									// ���Z
	bool GetTimeEnd() { return m_bTimeEnd; }										// ���Ԑ؂�

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
	int					m_nTime;			// �^�C��
	int					m_nCntFrame;		// �t���[���J�E���g
	bool				m_bAdd;				// ���Z
	bool				m_bTimeEnd;			// ���Ԑ؂�
};

#endif


