//=============================================================================
//
// �X�[�p�[�N���X(super.h)
// Author : �������l
// �T�v : �I�u�W�F�N�g�������s��
//
//=============================================================================
#ifndef _SUPER_H_		// ���̃}�N����`������ĂȂ�������
#define _SUPER_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// ���C�u�����[�����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")			// �`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")		// [d3d9.lib]�̊g�����C�u����

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <Windows.h>
#include "d3dx9.h"							// �`�揈���ɕK�v

//=============================================================================
// �X�[�p�[�N���X
// Author : �������l
// �T�v : �X�[�p�[�N���X�������s��
//=============================================================================
class CSuper
{
public:
	//--------------------------------------------------------------------
	// �v���C�I���e�B�̃��x��
	// Author : �������l
	// �T�v : �v���C�I���e�B�̃��x����ݒ�
	//--------------------------------------------------------------------
	enum PRIORITY_LEVEL
	{
		PRIORITY_LEVEL0 = 0,	// ���x��0
		PRIORITY_LEVEL1,		// ���x��1
		PRIORITY_LEVEL2,		// ���x��2
		PRIORITY_LEVEL3,		// ���x��3
		PRIORITY_LEVEL4,		// ���x��4
		MAX_LEVEL				// �ő僌�x��
	};

	//--------------------------------------------------------------------
	// �v�f�̎�ʂ̗񋓌^
	// Author : �������l
	// �T�v : �v�f�̎�ʏ����i�[
	//--------------------------------------------------------------------
	enum EElementType
	{
		ELEMENT_NONE = 0,			// �^�C�v����
		ELEMENT_OBJECT,				// �I�u�W�F�N�g
		ELEMENT_MANAGER,			// �}�l�[�W���[
		ELEMENT_SCENE,				// �V�[��
		MAX_ELEMENT,				// ��ʂ̍ő吔
	};

	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static void ReleaseAll(bool bPermanent);										// ���ׂẴI�u�W�F�N�g�̉��
	static void UpdateAll();														// ���ׂẴI�u�W�F�N�g�̍X�V
	static void DrawAll();															// ���ׂẴI�u�W�F�N�g�̕`��
	static void ReleaseListAll();													// ���ׂẴI�u�W�F�N�g�̃��X�g����
	static CSuper *GetTop(int nPriority) { return m_pTop[nPriority]; }				// �擪�I�u�W�F�N�g�ւ̃|�C���^�̎擾
	static CSuper *GetCurrent(int nPriority) { return m_pCurrent[nPriority]; }		// ���݂�(��Ԍ��)�I�u�W�F�N�g�ւ̃|�C���^�̎擾
	static void SetPause(const bool bPause) { m_bPause = bPause; }					// �|�[�Y��Ԃ̃Z�b�^�[
	static bool GetPause() { return m_bPause; }										// �|�[�Y��Ԃ̃Q�b�^�[

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	explicit CSuper(int nPriority = PRIORITY_LEVEL0);
	virtual ~CSuper();

	//--------------------------------------------------------------------
	// �������z�֐�
	//--------------------------------------------------------------------
	virtual HRESULT Init() = 0;													// ������
	virtual void Uninit() = 0;													// �I��
	virtual void Update() = 0;													// �X�V
	virtual void Draw() = 0;													// �`��
	void SetElement(const EElementType EElement) { m_EElement = EElement; }		// �v�f�̐ݒ�
	void SetPermanent(bool bPermanent) { m_bPermanent = bPermanent; }			// �V�[�������t���O�̐ݒ�
	CSuper *GetPrev() { return m_pPrev; }										// �O�̃I�u�W�F�N�g
	CSuper *GetNext() { return m_pNext; }										// �O�̃I�u�W�F�N�g
	EElementType GetElement() { return m_EElement; }							// �v�f�̎擾
	bool GetPermanent() { return m_bPermanent; }								// �V�[�������t���O�̎擾
	bool GetFlagDeath() { return m_bDeath; }									// ���S�t���O�̎擾

protected:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void Release(void);			// �I�u�W�F�N�g�̉��
	void ReleaseList(void);		// �I�u�W�F�N�g�̃��X�g����

private:
	//--------------------------------------------------------------------
	// �ÓI�����o�ϐ�
	//--------------------------------------------------------------------
	static CSuper *m_pTop[MAX_LEVEL];			// �擪�I�u�W�F�N�g�ւ̃|�C���^
	static CSuper *m_pCurrent[MAX_LEVEL];		// ���݂�(��Ԍ��)�I�u�W�F�N�g�ւ̃|�C���^
	static int m_nMax;							// �g�p��
	static int m_nPriorityMax[MAX_LEVEL];		// �v���C�I���e�B���Ƃ̃I�u�W�F�N�g��
	static bool m_bPause;						// �|�[�Y���g�p���Ă��邩�ǂ���

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CSuper *m_pPrev;				// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CSuper *m_pNext;				// ���̃I�u�W�F�N�g�ւ̃|�C���^
	EElementType m_EElement;		// �v�f
	int	 m_nLevPriority;			// �v���C�I���e�B�̃��x��
	bool m_bPermanent;				// �V�[�������t���O
	bool m_bDeath;					// ���S�t���O
};

#endif


