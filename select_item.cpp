//=============================================================================
//
// select_item.cpp
// Author : ���c�喲
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "select_item.h"
#include "calculation.h"
#include "keyboard.h"
#include "mouse.h"
#include "application.h"
#include "renderer.h"
#include "object.h"
#include "bg.h"
#include "score.h"
#include "time.h"
#include "sound.h"
#include "object2D.h"
#include "fade.h"
#include "debug_proc.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
D3DXCOLOR CSelectItem::fogColor;							// �t�H�O�J���[
float CSelectItem::fFogStartPos;							// �t�H�O�̊J�n�_
float CSelectItem::fFogEndPos;								// �t�H�O�̏I���_
float CSelectItem::fFogDensity;								// �t�H�O�̖��x

//=============================================================================
// �R���X�g���N�^
// Author : ���c�喲
//=============================================================================
CSelectItem::CSelectItem() : m_pSelectItem(nullptr)
{

}

//=============================================================================
// �f�X�g���N�^
// Author : ���c�喲
//=============================================================================
CSelectItem::~CSelectItem()
{

}

//=============================================================================
// ������
// Author : ���c�喲
//=============================================================================
HRESULT CSelectItem::Init()
{// �}�E�X�̎擾
	CMouse *pMouse = CApplication::GetMouse();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �T�E���h���̎擾
	CSound *pSound = CApplication::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM003);

	// �d�͂̒l��ݒ�
	CCalculation::SetGravity(0.2f);

	// �}�E�X�J�[�\��������
	pMouse->SetShowCursor(false);

	// �t�H�O�̐��l�ݒ�
	fogColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �t�H�O�J���[
	fFogStartPos = 1.0f;								// �t�H�O�̊J�n�_
	fFogEndPos = 100000.0f;								// �t�H�O�̏I���_
	fFogDensity = 0.00001f;								// �t�H�O�̖��x

	// �t�H�O�̗L���ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	// �t�H�O�J���[�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGCOLOR, fogColor);

	// �t�H�O�͈̔͐ݒ�
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&fFogStartPos));
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&fFogEndPos));

	// �t�H�O�̖��x�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&fFogDensity));

	m_pSelectItem = CObject2D::Create();
	m_pSelectItem->SetPos(D3DXVECTOR3(500.0f, 350.0f, 0.0f));
	m_pSelectItem->SetSize(D3DXVECTOR3(300.0f, 350.0f, 0.0f));
	m_pSelectItem->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pSelectItem->LoadTex(-1);

	m_pSelectItem2 = CObject2D::Create();
	m_pSelectItem2->SetPos(D3DXVECTOR3(800.0f, 350.0f, 0.0f));
	m_pSelectItem2->SetSize(D3DXVECTOR3(300.0f, 350.0f, 0.0f));
	m_pSelectItem2->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pSelectItem2->LoadTex(-1);

	return S_OK;
}

//=============================================================================
// �I��
// Author : ���c�喲
//=============================================================================
void CSelectItem::Uninit()
{// �}�E�X�̎擾
	CMouse *pMouse = CApplication::GetMouse();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �T�E���h���̎擾
	CSound *pSound = CApplication::GetSound();

	// �T�E���h�I��
	pSound->StopSound();

	// �t�H�O�̗L���ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	// �}�E�X�J�[�\�����o��
	pMouse->SetShowCursor(true);

	// �X�R�A�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : ���c�喲
//=============================================================================
void CSelectItem::Update()
{
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	//���_�J���[�̍X�V
	if (m_Menu == 0)
	{
		m_pSelectItem->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pSelectItem2->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}
	else if (m_Menu == 1)
	{
		m_pSelectItem->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_pSelectItem2->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (pKeyboard->GetTrigger(DIK_A))
	{//�������͂��ꂽ�Ƃ�
	 //�T�E���h�̍Đ�
		//PlaySound(SOUND_LABEL_SE_SEL);

		m_Menu--;
		if (m_Menu < 0)
		{
			m_Menu = 0;
		}
	}
	else if (pKeyboard->GetTrigger(DIK_D))
	{//�������͂��ꂽ�Ƃ�
	 //�T�E���h�̍Đ�
		//PlaySound(SOUND_LABEL_SE_SEL);

		m_Menu++;
		if (m_Menu >= 2)
		{
			m_Menu = 1;
		}
	}

	//���j���[�I���Ńt�F�[�h�ڍs
	switch (m_Menu)
	{
	case 0:
		if (pKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			//�T�E���h�̍Đ�
			//PlaySound(SOUND_LABEL_SE_DEC);

			//���[�h�̃Z�b�g����
			CApplication::SetNextMode(CApplication::MODE_GAME);
			break;
		}
	case 1:
		if (pKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			//�T�E���h�̍Đ�
			//PlaySound(SOUND_LABEL_SE_DEC);

			//���[�h�̃Z�b�g����
			CApplication::SetNextMode(CApplication::MODE_TUTORIAL);
			break;
		}
	}

#ifdef _DEBUG
	//CDebugProc::Print("���j���[ | 1 | 2 |\n", m_Menu);
#endif // _DEBUG
}

//=============================================================================
// �`��
// Author : ���c�喲
//=============================================================================
void CSelectItem::Draw()
{

}