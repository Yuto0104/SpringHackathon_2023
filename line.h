//=============================================================================
//
// ���C���`�揈��(line.h)
// Author : �������l
// �T�v : ���C���������s��
//
//=============================================================================
#ifndef _LINE_H_		// ���̃}�N����`������ĂȂ�������
#define _LINE_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"

//=============================================================================
// ���C���N���X
// Author : �������l
// �T�v : ���C���������s���N���X
//=============================================================================
class CLine : public CObject
{
public:
	// ���_�t�H�[�}�b�g
	const unsigned int	FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE);

	//*****************************************************************************
	// �\���̒�`
	//*****************************************************************************
	// ���_�f�[�^
	typedef struct
	{
		D3DXVECTOR3			pos;			// ���_���W
		D3DXVECTOR3			nor;			// �@���x�N�g��
		D3DCOLOR			col;			// ���_�J���[
	}VERTEX_3D;

	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CLine *Create(void);				// �I�u�W�F�N�g�̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	explicit CLine();
	~CLine();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;																				// ������
	void Uninit() override;																					// �I��
	void Update() override;																					// �X�V
	void Draw() override;																					// �`��
	void SetPos(const D3DXVECTOR3 &pos) override;															// �ʒu�̃Z�b�^�[
	void SetPosOld(const D3DXVECTOR3 &posOld) override { m_posOld = posOld; }								// �ߋ��ʒu�̃Z�b�^�[
	void SetRot(const D3DXVECTOR3 &rot) override;															// �����̃Z�b�^�[
	void SetSize(const D3DXVECTOR3 &size) override;															// �傫���̃Z�b�^�[
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }										// ���[���h�}�g���b�N�X�̃Z�b�^�[
	D3DXVECTOR3 GetPos() override { return m_pos; }															// �ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetPosOld()  override { return m_posOld; }													// �ߋ��ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetRot()  override { return m_rot; }														// �����̃Q�b�^�[
	D3DXVECTOR3 GetSize()  override { return m_size; }														// �傫���̃Q�b�^�[
	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }															// ���[���h�}�g���b�N�X�̃Q�b�^�[
	void SetVtx();																							// ���_���W�Ȃǂ̐ݒ�
	void SetCol(const D3DXCOLOR color);																		// ���_�J���[�̐ݒ�
	void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 start, D3DXVECTOR3 goal, D3DXCOLOR col);		// ���C���̐ݒu

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;			// ���_�o�b�t�@
	D3DXMATRIX						m_mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3						m_pos;				// �ʒu
	D3DXVECTOR3						m_posOld;			// �ߋ��ʒu
	D3DXVECTOR3						m_rot;				// ����
	D3DXVECTOR3						m_size;				// �傫��
	D3DXVECTOR3						m_start;			// �n�_
	D3DXVECTOR3						m_goal;				// �I�_
};

#endif




