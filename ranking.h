//=============================================================================
//
// �����L���O�N���X(ranking.h)
// Author : �������l
// �T�v : �����L���O�������s��
//
//=============================================================================
#ifndef _RANKING_H_		// ���̃}�N����`������ĂȂ�������
#define _RANKING_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScore;
class CObject2D;

//=============================================================================
// �����L���O�N���X
// Author : �������l
// �T�v : �����L���O�������s���N���X
//=============================================================================
class CRanking : public CObject
{
public:
	//--------------------------------------------------------------------
	// �R�}���h�^�C�v�̐ݒ�
	// Author : �������l
	// �T�v : 
	//--------------------------------------------------------------------
	enum COMMAND_TYPE
	{
		COMMAND_TYPE_NONE = 0,		// �^�C�v����
		COMMAND_TYPE_SET,			// �Z�b�^�[�R�}���h
		COMMAND_TYPE_GET,			// �Q�b�^�[�R�}���h
		COMMAND_TYPE_MAX			// �R�}���h�̍ő吔
	};

	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CRanking *Create(int nMaxRanking, int nNewScore);		// �����L���O�̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CRanking(int nPriority = CObject::PRIORITY_LEVEL3);
	~CRanking() override;

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;														// ������
	HRESULT Init(int nMaxRanking, int nNewScore);									// ������(�I�[�o�[���[�h)
	void Uninit() override;															// �I��
	void Update() override;															// �X�V
	void Draw() override;															// �`��
	void SetPos(const D3DXVECTOR3 &pos) override;									// �ʒu�̃Z�b�^�[
	void SetPosOld(const D3DXVECTOR3 &posOld) override { m_posOld = posOld; }		// �ߋ��ʒu�̃Z�b�^�[
	void SetRot(const D3DXVECTOR3 &rot) override;									// �����̃Z�b�^�[
	void SetSize(const D3DXVECTOR3 &size) override;									// �傫���̃Z�b�^�[
	void SetWholeSize(const D3DXVECTOR3 &wholeSize);								// �S�̂̑傫���̃Z�b�^�[
	D3DXVECTOR3 GetPos() override { return m_pos; }									// �ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetPosOld()  override { return m_posOld; }							// �ߋ��ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetRot()  override { return m_rot; }								// �����̃Q�b�^�[
	D3DXVECTOR3 GetSize()  override { return m_size; }								// �傫���̃Q�b�^�[
	D3DXVECTOR3 GetWholeSize() { return m_wholeSize; }								// �S�̂̑傫���̃Q�b�^�[
	void GetRanking();																// �����L���O�̎擾
	int SetRanking(const int nTime);												// �����L���O�̐ݒ�

private:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void CreateScore();
	void SetScore();
	void LoadRanking();
	void LoadFile();
	void SetScoreNomber();
	void FlashScore();
	void SetFailObj();

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CScore				**m_pScore;								// �X�R�A
	CObject2D			*pFailObj;								// ���s���̃A�i�E���X�p�̃I�u�W�F�N�g
	D3DXVECTOR3			m_pos;									// �ʒu
	D3DXVECTOR3			m_posOld;								// �ߋ��̈ʒu
	D3DXVECTOR3			m_rot;									// ����
	D3DXVECTOR3			m_size;									// �傫��
	D3DXVECTOR3			m_wholeSize;							// �S�̂̑傫��
	int					m_nMaxRanking;							// �����L���O��
	int					m_nDigit;								// ����
	int					*m_aRankingData;						// �����L���O�f�[�^
	int					m_nPortNum;								// �|�[�g�ԍ�
	int					m_nNewScore;							// �V�����X�R�A
	int					m_UpdateRank;							// �X�V���ꂽ�����N
	float				m_fAddAlpha;							// �A���t�@�̉��Z�l
	char				m_nIpAddress[128];						// IP�A�h���X
	bool				m_bUpdatingRanking;						// �ʐM���Ă邩�ۂ�
	bool				m_bRankingUpdatedSuccess;				// �������Ă邩�ۂ�
};

#endif

