//=============================================================================
//
// �I�u�W�F�N�g�N���X(object.h)
// Author : �������l
// �T�v : �I�u�W�F�N�g�������s��
//
//=============================================================================
#ifndef _OBJECT_H_		// ���̃}�N����`������ĂȂ�������
#define _OBJECT_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "super.h"

//=============================================================================
// �I�u�W�F�N�g�N���X
// Author : �������l
// �T�v : �I�u�W�F�N�g�������s���N���X
//=============================================================================
class CObject : public CSuper
{
public:
	//--------------------------------------------------------------------
	// �I�u�W�F�N�g�̎�ʂ̗񋓌^
	// Author : �������l
	// �T�v : �I�u�W�F�N�g�̎�ʏ����i�[
	//--------------------------------------------------------------------
	enum EObjectType
	{
		OBJTYPE_NONE = 0,			// �^�C�v����
		OBJTYPE_FADE,				// �t�F�[�h
		OBJTYPE_PAUSE,				// �|�[�Y
		OBJETYPE_PLAYER,			// �v���C���[
		OBJETYPE_ENEMY,				// �G�l�~�[
		OBJTYPE_3DMODEL,			// 3D���f��
		OBJETYPE_MESH,				// ���b�V��
		MAX_OBJTYPE,				// ��ʂ̍ő吔
	};

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	explicit CObject(int nPriority = PRIORITY_LEVEL0);
	virtual ~CObject();

	//--------------------------------------------------------------------
	// �������z�֐�
	//--------------------------------------------------------------------
	virtual void SetPos(const D3DXVECTOR3 &pos) = 0;							// �ʒu�̃Z�b�^�[
	virtual void SetPosOld(const D3DXVECTOR3 &posOld) = 0;						// �ߋ��ʒu�̃Z�b�^
	virtual void SetRot(const D3DXVECTOR3 &rot) = 0;							// �����̃Z�b�^�[
	virtual void SetSize(const D3DXVECTOR3 &size) = 0;							// �傫���̃Z�b�^�[
	virtual D3DXVECTOR3 GetPos() = 0;											// �ʒu�̃Q�b�^�[
	virtual D3DXVECTOR3 GetPosOld() = 0;										// �ߋ��ʒu�̃Q�b�^
	virtual D3DXVECTOR3 GetRot() = 0;											// �����̃Q�b�^�[
	virtual D3DXVECTOR3 GetSize() = 0;											// �傫���̃Q�b�^�[
	void SetObjType(EObjectType objectType) { m_objectType = objectType; }		// �I�u�W�F�N�g�̎�ʐݒ�
	EObjectType GetObjType() { return m_objectType; }							// �I�u�W�F�N�g�̎�ʐݒ�

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	EObjectType m_objectType;		// �I�u�W�F�N�g�̎��
};

#endif

