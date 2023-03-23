//=============================================================================
//
// ���f���I�u�W�F�N�g�N���X(model_obj.h)
// Author : �������l
// �T�v : ���f���I�u�W�F�N�g�������s��
//
//=============================================================================
#ifndef _MODEL_OBJ_H_			// ���̃}�N����`������ĂȂ�������
#define _MODEL_OBJ_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CModel3D;
class CCollision_Rectangle3D;

//=============================================================================
// ���f���I�u�W�F�N�g�N���X
// Author : �������l
// �T�v : ���f���I�u�W�F�N�g�������s���N���X
//=============================================================================
class CModelObj : public CObject
{
public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CModelObj *Create();							// ���f���I�u�W�F�N�g�̐���
	static void LoadFile(const char *pFileName);		// �t�@�C���̓ǂݍ���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CModelObj();
	~CModelObj();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;																							// ������
	void Uninit() override;																								// �I��
	void Update() override;																								// �X�V
	void Draw() override;																								// �`��
	void SetPos(const D3DXVECTOR3 &pos) override { m_pos = pos; };														// �ʒu�̃Z�b�^�[
	void SetPosOld(const D3DXVECTOR3 &posOld) override { m_posOld = posOld; }											// �ߋ��ʒu�̃Z�b�^�[
	void SetRot(const D3DXVECTOR3 &rot) override { m_rot = rot; };														// �����̃Z�b�^�[
	void SetSize(const D3DXVECTOR3 &size) override { m_size = size; }													// �傫���̃Z�b�^�[
	D3DXVECTOR3 GetPos() override { return m_pos; }																		// �ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetPosOld()  override { return m_posOld; }																// �ߋ��ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetRot()  override { return m_rot; }																	// �����̃Q�b�^�[
	D3DXVECTOR3 GetSize()  override { return m_size; }																	// �傫���̃Q�b�^�[
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }													// ���[���h�}�g���b�N�X�̃Z�b�^�[
	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }																		// ���[���h�}�g���b�N�X�̃Q�b�^�[
	void SetType(const int nType);																						// �^�C�v�̐ݒ�
	CModel3D *GetModel() { return m_pModel; }																			// ���f�����̎擾
	void *SetCollision(CCollision_Rectangle3D *pColliRectangle3D) { m_pColliRectangle3D = pColliRectangle3D; }			// �����蔻��̐ݒ�
	CCollision_Rectangle3D *GetCollision() { return m_pColliRectangle3D; }												// �����蔻��̎擾

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CModel3D					*m_pModel;				// ���f�����
	CCollision_Rectangle3D		*m_pColliRectangle3D;	// �����蔻��
	D3DXMATRIX					m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3					m_pos;					// �ʒu
	D3DXVECTOR3					m_posOld;				// �ߋ��ʒu
	D3DXVECTOR3					m_rot;					// ����
	D3DXVECTOR3					m_size;					// �傫��
	int							m_nType;				// ���f���̃^�C�v
};

#endif
