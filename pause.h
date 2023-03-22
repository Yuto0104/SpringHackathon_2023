//=============================================================================
//
// �|�[�Y�N���X(pause.h)
// Author : �������l
// �T�v : �|�[�Y�������s��
//
//=============================================================================
#ifndef _PAUSE_H_		// ���̃}�N����`������ĂȂ�������
#define _PAUSE_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject2D;

//=============================================================================
// �|�[�Y�N���X
// Author : �������l
// �T�v : �|�[�Y�������s���N���X
//=============================================================================
class CPause : public CObject
{
public:
	//--------------------------------------------------------------------
	// ���[�h�̗񋓌^
	// Author : �������l
	// �T�v : ���[�h�����ʂ���
	//--------------------------------------------------------------------
	enum NEXT_MODE
	{
		MODE_RETURN = 0,		// ���^�[��
		MODE_GAME,				// �Q�[��
		MODE_TITLE,				// �^�C�g��
		MAX_MODE,				// �V�[���̍ő吔
		MODE_NONE,				// �V�[������
	};

	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CPause *Create();		// �|�[�Y�̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CPause(int nPriority = CObject::PRIORITY_LEVEL3);
	~CPause() override;

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;														// ������
	void Uninit() override;															// �I��
	void Update() override;															// �X�V
	void Draw() override;															// �`��
	void SetPos(const D3DXVECTOR3 &pos) override;									// �ʒu�̃Z�b�^�[
	void SetPosOld(const D3DXVECTOR3 &posOld) override { m_posOld = posOld; }		// �ߋ��ʒu�̃Z�b�^�[
	void SetRot(const D3DXVECTOR3 &rot) override;									// �����̃Z�b�^�[
	void SetSize(const D3DXVECTOR3 &size) override;									// �傫���̃Z�b�^�[
	void SetColor(const D3DXCOLOR &col);											// �F�̐ݒ�
	void SetPause(const bool bPause);												// �|�[�Y�̎g�p��
	D3DXVECTOR3 GetPos() override { return m_pos; }									// �ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetPosOld()  override { return m_posOld; }							// �ߋ��ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetRot()  override { return m_rot; }								// �����̃Q�b�^�[
	D3DXVECTOR3 GetSize()  override { return m_size; }								// �傫���̃Q�b�^�[
	bool GetPause() { return m_bPause; }											// �|�[�Y�̎g�p�󋵂̃Q�b�^�[

private:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void FlashObj();
	void SelectMode();

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	NEXT_MODE		m_nextMode;			// ���̃��[�h
	CObject2D		*m_pPauseBGObj;		// �|�[�Y�w�i�I�u�W�F�N�g
	CObject2D		*m_pReturnObj;		// ���^�[���I�u�W�F�N�g
	CObject2D		*m_pNewGameObj;		// �j���[�Q�[���I�u�W�F�N�g
	CObject2D		*m_pTitleObj;		// �^�C�g���I�u�W�F�N�g
	D3DXVECTOR3		m_pos;				// �ʒu
	D3DXVECTOR3		m_posOld;			// �ߋ��̈ʒu
	D3DXVECTOR3		m_rot;				// ����
	D3DXVECTOR3		m_size;				// �傫��
	float			m_fAddAlpha;		// �t���[�����̃J�E���g
	int				m_nCntFrame;		// �t���[���J�E���g
	bool			m_bPressEnter;		// �G���^�[�L�[�������邩
	bool			m_bPause;			// �|�[�Y���Ă��邩
};

#endif


