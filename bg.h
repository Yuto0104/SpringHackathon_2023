//=============================================================================
//
// �w�i�N���X(bg.h)
// Author : �������l
// �T�v : �w�i�������s��
//
//=============================================================================
#ifndef _BG_H_		// ���̃}�N����`������ĂȂ�������
#define _BG_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"
#include "texture.h"

//=============================================================================
// �w�i�N���X
// Author : �������l
// �T�v : �w�i�������s���N���X
//=============================================================================
class CBG : public CObject
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
	static CBG *Create(void);				// �w�i�̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CBG(int nPriority = PRIORITY_LEVEL0);
	~CBG() override;

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;														// ������
	void Uninit() override;															// �I��
	void Update() override;															// �X�V
	void Draw() override;															// �`��
	void SetPos(const D3DXVECTOR3 &pos) override { pos; }							// �ʒu�̃Z�b�^�[
	void SetPosOld(const D3DXVECTOR3 &posOld) override { posOld; }					// �ߋ��ʒu�̃Z�b�^�[
	void SetRot(const D3DXVECTOR3 &rot) override { rot; }							// �����̃Z�b�^�[
	void SetSize(const D3DXVECTOR3 &size) override { size; }						// �傫���̃Z�b�^�[
	D3DXVECTOR3 GetPos() override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }			// �ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetPosOld()  override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		// �ߋ��ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetRot()  override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		// �����̃Q�b�^�[
	D3DXVECTOR3 GetSize()  override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		// �傫���̃Q�b�^�[
	void SetCol(const D3DXCOLOR color);												// ���_�J���[�̐ݒ�
	void LoadTex(const int nNumTex) { m_nNumTex = nNumTex; }						// �e�N�X�`���̐ݒ�

private:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void SetVtx();															// ���_���W�Ȃǂ̐ݒ�
	void SetTex(const D3DXVECTOR2 &minTex, const D3DXVECTOR2 &maxTex);		// �e�N�X�`�����W�̐ݒ�

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	LPDIRECT3DVERTEXBUFFER9		 m_pVtxBuff;		// ���_�o�b�t�@
	D3DCOLOR					 m_col;				// �J���[
	int							 m_nNumTex;			// �e�N�X�`���̎��
};

#endif
