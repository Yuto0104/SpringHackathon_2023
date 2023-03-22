//=============================================================================
//
// 2D�I�u�W�F�N�g�N���X(object2D.h)
// Author : �������l
// �T�v : �I�u�W�F�N�g�������s��
//
//=============================================================================
#ifndef _OBJECT2D_H_		// ���̃}�N����`������ĂȂ�������
#define _OBJECT2D_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"
#include "texture.h"

//=============================================================================
// 2D�I�u�W�F�N�g�N���X
// Author : �������l
// �T�v : 2D�I�u�W�F�N�g�������s���N���X
//=============================================================================
class CObject2D : public CObject
{
public:
	// ���_�t�H�[�}�b�g
	const unsigned int	FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	//*****************************************************************************
	// �\���̒�`
	//*****************************************************************************
	// ���_�f�[�^
	struct VERTEX_2D
	{
		D3DXVECTOR3		pos;		// �ʒu
		float			rhw;		// rhw
		D3DCOLOR		col;		// �J���[
		D3DXVECTOR2		tex;		// �e�N�X�`�����W
	};

	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CObject2D *Create(void);				// 2D�I�u�W�F�N�g�̐���
	static CObject2D *Create(int nPriority);	// 2D�I�u�W�F�N�g�̐���(�I�[�o�[���[�h)

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	explicit CObject2D(int nPriority = PRIORITY_LEVEL0);
	~CObject2D() override;

	//--------------------------------------------------------------------
	// �I�[�o�[���C�h�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;														// ������
	void Uninit() override;															// �I��
	void Update() override;															// �X�V
	void Draw() override;															// �`��
	void SetPos(const D3DXVECTOR3 &pos) override;									// �ʒu�̃Z�b�^�[
	void SetPosOld(const D3DXVECTOR3 &posOld) override { m_posOld = posOld; }		// �ߋ��ʒu�̃Z�b�^�[
	void SetRot(const D3DXVECTOR3 &rot) override;									// �����̃Z�b�^�[
	void SetSize(const D3DXVECTOR3 &size) override;									// �傫���̃Z�b�^�[
	D3DXVECTOR3 GetPos() override { return m_pos; }									// �ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetPosOld()  override { return m_posOld; }							// �ߋ��ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetRot()  override { return m_rot; }								// �����̃Q�b�^�[
	D3DXVECTOR3 GetSize()  override { return m_size; }								// �傫���̃Q�b�^�[
	void LoadTex(const int nNumTex) { m_nNumTex = nNumTex; }						// �e�N�X�`���̐ݒ�
	void SetCol(const D3DCOLOR &col);												// �F�̃Z�b�^�[

protected:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void SetVtx();															// ���_���W�Ȃǂ̐ݒ�
	void SetTex(const D3DXVECTOR2 &minTex, const D3DXVECTOR2 &maxTex);		// �e�N�X�`�����W�̐ݒ�

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;			// ���_�o�b�t�@
	D3DXVECTOR3						m_pos;				// �ʒu
	D3DXVECTOR3						m_posOld;			// �ߋ��̈ʒu
	D3DXVECTOR3						m_rot;				// ����
	D3DXVECTOR3						m_size;				// �傫��
	D3DCOLOR						m_col;				// �J���[
	int								m_nNumTex;			// �e�N�X�`���̎�ʔԍ�
	float							m_fAngle;			// �Ίp���̊p�x
	float							m_fLength;			// �Ίp���̒���
};

#endif


