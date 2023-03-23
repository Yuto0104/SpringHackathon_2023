//=============================================================================
//
// �Փ˔���N���X(collision.h)
// Author : �������l
// �T�v : �Փ˔��萶�����s��
//
//=============================================================================
#ifndef _COLLISION_H_		// ���̃}�N����`������ĂȂ�������
#define _COLLISION_H_		// ��d�C���N���[�h�h�~�̃}�N����`

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
#include "object.h"

//=============================================================================
// �Փ˔���N���X
// Author : �������l
// �T�v : �Փ˔���N���X�������s��
//=============================================================================
class CCollision
{
public:
	//--------------------------------------------------------------------
	// �����蔻��̎��
	// Author : �������l
	// �T�v : �����蔻��̎��
	//--------------------------------------------------------------------
	enum COLLISION_TYPE
	{
		TYPE_RECTANGLE3D = 0,	// 3D��`
		TYPE_SPHERE,			// ��
		MAX_LEVEL				// �ő僌�x��
	};

	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static void ReleaseAll();									// ���ׂẴI�u�W�F�N�g�̉��
	static void UpdateAll();									// ���ׂẴI�u�W�F�N�g�̍X�V
	static void DrawAll();										// ���ׂẴI�u�W�F�N�g�̕`��
	static void ReleaseListAll();								// ���ׂẴI�u�W�F�N�g�̃��X�g����
	static CCollision *GetTop() { return m_pTop; }				// �擪�I�u�W�F�N�g�ւ̃|�C���^�̃Q�b�^�[
	static CCollision *GetCurrent() { return m_pCurrent; }		// ���݂�(��Ԍ��)�I�u�W�F�N�g�ւ̃|�C���^�̃Q�b�^�[

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	explicit CCollision();
	virtual ~CCollision();

	//--------------------------------------------------------------------
	// �������z�֐�
	//--------------------------------------------------------------------
	virtual HRESULT Init() = 0;														// ������
	virtual void Uninit() = 0;														// �I��
	virtual void Update() = 0;														// �X�V
	virtual void Draw() = 0;														// �`��
	virtual bool Collision(CObject::EObjectType objeType, bool bExtrude) = 0;		// �����蔻��	

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void Release(void);																	// �I�u�W�F�N�g�̉��
	void ReleaseList(void);																// �I�u�W�F�N�g�̃��X�g����
	void SetParent(CObject *pParent) { m_pParent = pParent; }							// �e�I�u�W�F�N�g�̐ݒ�
	void SetCollidedObj(CObject *pCollidedObj) { m_pCollidedObj = pCollidedObj; }		// ���������I�u�W�F�N�g�̃|�C���^�擾
	void SetCollidedObj() { m_pCollidedObj = nullptr; }									// ���������I�u�W�F�N�g�̃|�C���^�擾
	void SetType(COLLISION_TYPE type) { m_type = type; }								// �����蔻��̐ݒ�
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }										// �ʒu�̐ݒ�
	void SetSize(D3DXVECTOR3 size) { m_size = size; }									// �T�C�Y�̐ݒ�
	void SetUseFlag(bool bUse) { m_bUse = bUse; }										// �g�p�󋵂̐ݒ�
	CCollision *GetPrev() { return m_pPrev; }											// �O�̃I�u�W�F�N�g�ւ̃|�C���^�擾
	CCollision *GetNext() { return m_pNext; }											// ���̃I�u�W�F�N�g�ւ̃|�C���^�擾
	CObject *GetParent() { return m_pParent; }											// �e�I�u�W�F�N�g�̃|�C���^�擾
	CObject *GetCollidedObj() { return m_pCollidedObj; }								// ���������I�u�W�F�N�g�̃|�C���^�擾
	COLLISION_TYPE GetType() { return m_type; }											// �����蔻��̎擾
	D3DXVECTOR3 GetPos() { return m_pos; }												// �ʒu�̎擾
	D3DXVECTOR3 GetSize() { return m_size; }											// �T�C�Y�̎擾
	bool GetUseFlag() { return m_bUse; }												// �g�p�󋵂̎擾
	bool GetDeathFlag() { return m_bDeath; }											// ���S�t���O�̎擾

private:
	//--------------------------------------------------------------------
	// �ÓI�����o�ϐ�
	//--------------------------------------------------------------------
	static CCollision *m_pTop;			// �擪�I�u�W�F�N�g�ւ̃|�C���^
	static CCollision *m_pCurrent;		// ���݂�(��Ԍ��)�I�u�W�F�N�g�ւ̃|�C���^
	static int m_nMax;					// �g�p��

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CCollision *m_pPrev;			// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CCollision *m_pNext;			// ���̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pParent;				// �e�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pCollidedObj;		// �Փ˂����I�u�W�F�N�g�ւ̃|�C���^
	COLLISION_TYPE m_type;			// �����蔻��̎��
	D3DXVECTOR3 m_pos;				// �ʒu
	D3DXVECTOR3 m_size;				// �傫��
	bool m_bUse;					// �g�p��
	bool m_bDeath;					// ���S�t���O
};

#endif


