//=============================================================================
//
// 3D���f���N���X(model3D.h)
// Author : �������l
// �T�v : 3D���f���������s��
//
//=============================================================================
#ifndef _MODEL_H_			// ���̃}�N����`������ĂȂ�������
#define _MODEL_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"
#include "main.h"

//=============================================================================
// 3D���f���N���X
// Author : �������l
// �T�v : 3D���f���������s���N���X
//=============================================================================
class CModel3D
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
	// ���f���̃}�e���A�����
	// Author : �������l
	// �T�v : ���f���̃}�e���A�����̐ݒ�
	//--------------------------------------------------------------------
	struct MODEL_MATERIAL
	{
		LPD3DXMESH		pMesh;				// ���b�V�����ւ̃|�C���^
		LPD3DXBUFFER	pBuffer;			// �}�e���A�����ւ̃|�C���^
		DWORD			nNumMat;			// �}�e���A�����̐�
		D3DXVECTOR3		size;				// ���f���̑傫��
		int				*pNumTex;			// �e�N�X�`���^�C�v
		char			aFileName[0xff];	// X�t�@�C���̃p�X
	};

	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CModel3D *Create();										// 3D���f���̐���
	static void InitModel();										// ���f���̏�����
	static void UninitModel();										// ���f���̏I��
	static void LoadModel(const char *pFileName);					// ���f���̓ǂݍ���
	static MODEL_MATERIAL *GetMaterial() { return m_material; }		// �}�e���A�����̎擾
	static int GetMaxModel() { return m_nMaxModel; }				// ���f���� 

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CModel3D();
	~CModel3D();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init();															// ������
	void Uninit();															// �I��
	void Update();															// �X�V
	void Draw();															// �`��
	void Draw(D3DXMATRIX mtxParent);										// �`��(�I�[�o�[���[�h)
	void DrawMaterial();													// �}�e���A���`��
	void SetPos(const D3DXVECTOR3 &pos);									// �ʒu�̃Z�b�^�[
	void SetRot(const D3DXVECTOR3 &rot);									// �����̃Z�b�^�[
	void SetSize(const D3DXVECTOR3 &size);									// �傫���̃Z�b�^�[
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }		// ���[���h�}�g���b�N�X�̐ݒ�
	void SetParent(CModel3D *pParent) { m_pParent = pParent; }				// �e���f���̃Z�b�^�[
	void SetModelID(const int nModelID) { m_nModelID = nModelID; }			// ���f��ID
	void SetColor(const D3DXCOLOR color);									// �J���[�̐ݒ�
	void SetColor(bool bColor) { m_bColor = bColor; }						// �J���[�̐ݒ�(�I�[�o�[���[�h)
	void SetShadow(bool bShadow) { m_bShadow = bShadow; }					// �e�̎g�p�󋵂̐ݒ�
	void SetLighting(bool bLighting) { m_bLighting = bLighting; }			// ���C�g���g�p�󋵂̐ݒ�
	D3DXVECTOR3 GetPos() { return m_pos; }									// �ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetRot() { return m_rot; }									// �����̃Q�b�^�[
	D3DXVECTOR3 GetSize() { return m_size; }								// �傫���̃Q�b�^�[
	MODEL_MATERIAL GetMyMaterial() { return m_material[m_nModelID]; }		// �}�e���A�����̎擾
	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }							// ���[���h�}�g���b�N�X�̎擾
	CModel3D *GetParent() { return m_pParent; }								// �e���f���̃Q�b�^�[

private:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void Shadow();		// �e�̕`��

	//--------------------------------------------------------------------
	// �ÓI�����o�ϐ�
	//--------------------------------------------------------------------
	static MODEL_MATERIAL	*m_material;		// �}�e���A�����
	static int				m_nMaxModel;		// ���f����			

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CModel3D			*m_pParent;			// �e���f���̏��
	D3DXMATRIX			m_mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3			m_pos;				// �ʒu
	D3DXVECTOR3			m_rot;				// ����
	D3DXVECTOR3			m_size;				// �傫��
	D3DXCOLOR			m_color;			// �J���[
	int					m_nModelID;			// ���f��ID
	bool				m_bColor;			// �J���[���g�p����
	bool				m_bShadow;			// �e�̎g�p��
	bool				m_bLighting;		// ���C�g�̎g�p��
};

#endif