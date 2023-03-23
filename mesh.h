//=============================================================================
//
// 3D���b�V���N���X(mesh.h)
// Author : �������l
// �T�v : �I�u�W�F�N�g�������s��
//
//=============================================================================
#ifndef _MESH3D_H_		// ���̃}�N����`������ĂȂ�������
#define _MESH3D_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"
#include "texture.h"

//=============================================================================
// 3D���b�V���N���X
// Author : �������l
// �T�v : 3D�I�u�W�F�N�g�������s���N���X
//=============================================================================
class CMesh3D : public CObject
{
public:
	//--------------------------------------------------------------------
	// DOUBLE_INT�ϐ��̒ǉ�
	// Author : �������l
	// �T�v : �e�N�X�`���A�j���[�V�����̃p�^�[�����ݒ�Ɏg�p
	//--------------------------------------------------------------------
	struct DOUBLE_INT
	{
		// �ϐ��錾
		int   x, y;

		constexpr DOUBLE_INT() : x(0), y(0) { }
		constexpr DOUBLE_INT(int _x, int _y) : x(_x), y(_y) { }

		// ���Z
		DOUBLE_INT operator +(const DOUBLE_INT &texPattern) {
			DOUBLE_INT pattern;
			pattern.x = x + texPattern.x;
			pattern.y = y + texPattern.y;
			return pattern;
		}

		// ���Z(+=)
		DOUBLE_INT &operator +=(const DOUBLE_INT &texPattern) {
			x += texPattern.x;
			y += texPattern.y;
			return *this;
		}

		// ���Z
		DOUBLE_INT operator -(const DOUBLE_INT &texPattern) {
			DOUBLE_INT pattern;
			pattern.x = x - texPattern.x;
			pattern.y = y - texPattern.y;
			return pattern;
		}

		// ���Z(-=)
		DOUBLE_INT &operator -=(const DOUBLE_INT &texPattern) {
			x -= texPattern.x;
			y -= texPattern.y;
			return *this;
		}

		// ��Z
		DOUBLE_INT operator *(const DOUBLE_INT &texPattern) {
			DOUBLE_INT pattern;
			pattern.x = x * texPattern.x;
			pattern.y = y * texPattern.y;
			return pattern;
		}

		// ��Z(*=)
		DOUBLE_INT &operator *=(const DOUBLE_INT &texPattern) {
			x *= texPattern.x;
			y *= texPattern.y;
			return *this;
		}

		// ���
		DOUBLE_INT &operator =(const DOUBLE_INT &texPattern) {
			x = texPattern.x;
			y = texPattern.y;
			return *this;
		}
	};

	// ���_�t�H�[�}�b�g
	const unsigned int	FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	//*****************************************************************************
	// �\���̒�`
	//*****************************************************************************
	// ���_�f�[�^
	typedef struct
	{
		D3DXVECTOR3			pos;			// ���_���W
		D3DXVECTOR3			nor;			// �@���x�N�g��
		D3DCOLOR			col;			// ���_�J���[
		D3DXVECTOR2			tex;			// �e�N�X�`�����W
	}VERTEX_3D;

	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CMesh3D *Create(void);					// 2D�I�u�W�F�N�g�̐���
	static bool CollisonMesh(CObject *pTarget);		// �����蔻��

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CMesh3D();
	~CMesh3D();

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
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }				// ���[���h�}�g���b�N�X�̃Z�b�^�[
	void SetBlock(DOUBLE_INT block);												// �u���b�N���̃Z�b�^�[
	D3DXVECTOR3 GetPos() override { return m_pos; }									// �ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetPosOld() override { return m_posOld; }							// �ߋ��ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetRot() override { return m_rot; }									// �����̃Q�b�^�[
	D3DXVECTOR3 GetSize() override { return m_size; }								// �傫���̃Q�b�^�[
	D3DXVECTOR3 GetBlockSize() { return m_blockSize; }								// �u���b�N�T�C�Y�̃Q�b�^�[
	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }									// ���[���h�}�g���b�N�X�̃Q�b�^�[
	DOUBLE_INT GetBlock() { return m_block; }										// �u���b�N���̃Q�b�^�[
	DOUBLE_INT GetLine() { return m_line; }											// ���C�����̃Q�b�^�[
	int GetVtx() { return m_nVtx; }													// ���_���̃Q�b�^�[
	void SetSplitTex(bool bSplitTex);												// �e�N�X�`���������邩�̃Z�b�^�[
	bool GetSplitTex() { return m_bSplitTex; }										// �e�N�X�`���������邩�̃Q�b�^�[
	void SetScrollTex(D3DXVECTOR2 addTex, bool bScrollTex);							// �e�N�X�`���X�N���[���̐ݒ�
	void LoadTex(const int nNumTex) { m_nNumTex = nNumTex; }						// �e�N�X�`���̐ݒ�
	void SetCol(const D3DXCOLOR &col);												// �F�̐ݒ�
	D3DXCOLOR GetCol() { return m_col; }											// �F�̎擾
	D3DXVECTOR2 GetTex() { return m_tex; }											// �e�N�X�`���̃Q�b�^�[
	bool Collison(CObject *pTarget);												// �����蔻��
	void SetUseCollison(bool bUseCollison) { m_bUseCollison = bUseCollison; }		// �����蔻��̎g�p�󋵂̐ݒ�
	bool GetUseCollison() { return m_bUseCollison; }								// �����蔻��̎g�p�󋵂̎擾

protected:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	virtual void SetVtx();									// ���_���W�Ȃǂ̐ݒ�
	virtual void SetTex();									// �e�N�X�`�����W�̐ݒ�
	void SetIndexBuff();									// �C���f�b�N�X�o�b�t�@�̐ݒ�
	void SetMeshInfo();										// ���b�V���̐��l�̌v�Z
	void TexScroll();										// �e�N�X�`���X�N���[��
	void Normal();											// �@��

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;			 // ���_�o�b�t�@

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	LPDIRECT3DINDEXBUFFER9			m_pIdxBuff;							// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX						m_mtxWorld;							// ���[���h�}�g���b�N�X
	D3DXVECTOR3						m_pos;								// �ʒu
	D3DXVECTOR3						m_posOld;							// �ߋ��ʒu
	D3DXVECTOR3						m_rot;								// ����
	D3DXVECTOR3						m_size;								// �傫��
	D3DXVECTOR3						m_blockSize;						// �u���b�N�T�C�Y
	D3DXVECTOR2						m_tex;								// �e�N�X�`�����W�̊�l
	D3DXVECTOR2						m_addTex;							// �e�N�X�`�����W�̉��Z�l
	D3DXCOLOR						m_col;								// �J���[
	DOUBLE_INT						m_block;							// �u���b�N��
	DOUBLE_INT						m_line;								// ��
	int 							m_nNumTex;							// �e�N�X�`���̎��
	int								m_nLineVtxX;						// �񒸓_��(X)
	int								m_nVtx;								// ���_��
	int								m_nPolygon;							// �|���S����
	int								m_nIndex;							// �C���f�b�N�X��
	bool							m_bSplitTex;						// �e�N�X�`���̕������邩
	bool							m_bScrollTex;						// �e�N�X�`�����X�N���[�����邩�ǂ���
	bool							m_bUseCollison;						// �����蔻����g�����ۂ�
};

#endif



