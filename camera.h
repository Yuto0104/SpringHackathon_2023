//**************************************************************************************************
//
// �J��������(camera.h)
// Auther�F�������l
// �T�v : �J�����̐ݒ菈��
//
//**************************************************************************************************
#ifndef _CAMERA_H_			// ���̃}�N����`������ĂȂ�������
#define _CAMERA_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include"main.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CMove;
class CObject;

//=============================================================================
// �J�����N���X
// Author : �������l
// �T�v : �J�����ݒ���s���N���X
//=============================================================================
class CCamera
{
private:
	//--------------------------------------------------------------------
	// �萔��`
	//--------------------------------------------------------------------
	static const float CAMERA_NEAR;			// �j�A�̍ő�l
	static const float CAMERA_FUR;			// �t�@�[�̍ő�l

public:
	//=============================================================================
	// ���e���@�̃^�C�v�񋓌^
	// Author : �������l
	// �T�v : ���e���@�̎��
	//=============================================================================
	enum VIEW_TYPE
	{
		TYPE_CLAIRVOYANCE = 0,		// �������e
		TYPE_PARALLEL,				// ���s���e
		MAX_VIEW_TYPE,				// �^�C�v�̍ő吔
	};

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CCamera();
	~CCamera();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init(void);														// ������
	void Uninit(void);														// �I��
	void Update(void);														// �X�V
	void Set(void);															// �ݒ�
	void SetViewType(VIEW_TYPE type);										// �^�C�v�̐ݒ�
	void Zoom();															// �J�����̊g�k
	D3DXVECTOR3 GetPosV() { return m_posV; }
	D3DXVECTOR3 GetPosR() { return m_posR; }
	D3DXVECTOR3 GetRot() { return m_rot; }
	D3DXMATRIX GetMtxView() { return m_mtxView; }
	D3DXMATRIX GetMtxProj() { return m_mtxProj; }
	CObject	*GetTarget() { return m_pTarget; }
	void SetPosVOffset(const D3DXVECTOR3 posVOffset);
	void SetPosROffset(const D3DXVECTOR3 posROffset);
	void SetRot(const D3DXVECTOR3 rot);
	void SetFollowTarget(CObject *pTarget, float fCoeffFllow);
	void SetFollowTarget(bool bUse);
	void SetTargetPosR(CObject *pTargetPosR);
	void SetTargetPosR(bool bUse);
	void SetViewing(const float fViewing) { m_fViewing = fViewing; }
	void SetPosRDiff(const D3DXVECTOR2 posRDiff) { m_posRDiff = posRDiff; }
	void SetAspect(D3DXVECTOR2 aspect) { m_aspect = aspect; }
	void SetUseRoll(bool X, bool Y);
	void SetViewSize(DWORD X, DWORD Y, int fWidth, int fHeight);
	CObject *GetTargetPosR() { return m_pTargetPosR; }
	void Shake(const int nTime, const float fShake);

private:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void CalMatrix();				// �}�g���b�N�X�v�Z
	void Rotate(void);				// ��]
	void Move(void);				// �ړ�

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CMove				*m_pMove;			// �ړ��N���X�̃C���X�^���X
	CMove				*m_pRoll;			// �ړ��N���X�̃C���X�^���X(�p�x)
	CObject				*m_pTarget;			// �^�[�Q�b�g(�ʒu)
	CObject				*m_pTargetPosR;		// �^�[�Q�b�g(�����_)
	D3DXMATRIX			m_mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXMATRIX			m_mtxProj;			// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX			m_mtxView;			// �r���[�}�g���b�N�X
	D3DVIEWPORT9        m_viewport;			// �r���[�|�[�g
	D3DXVECTOR3			m_pos;				// �ʒu
	D3DXVECTOR3			m_posV;				// ���_
	D3DXVECTOR3			m_posR;				// �����_
	D3DXVECTOR3			m_vecU;				// ������x�N�g��
	D3DXVECTOR3			m_posVOffset;		// ���_����
	D3DXVECTOR3			m_posROffset;		// �����_����
	D3DXVECTOR3			m_rot;				// ����
	D3DXVECTOR3			m_rotMove;			// �ړ�����
	D3DXVECTOR2			m_posRDiff;			// �����_�^�[�Q�b�g���̍���
	D3DXVECTOR2			m_aspect;			// �A�X�y�N�g��̒l
	VIEW_TYPE			m_viewType;			// ���e�̎��
	float				m_fViewing;			// ����p
	float				m_fRotMove;			// �ړ�����
	float				m_fCoeffFllow;		// �Ǐ]�̌����W��
	float				m_fShake;			// �h��̗�
	int					m_nCntShake;		// �h��̃J�E���g
	bool				m_bUseRollX;		// X���̉�]�̎g�p��
	bool				m_bUseRollY;		// Y���̉�]�̎g�p��
	bool				m_bFllow;			// �Ǐ]���s����
};

#endif
