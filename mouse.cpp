//=============================================================================
//
// �}�E�X���͏���(mouse.h)
// Author : �������l
// �T�v : �}�E�X�������s��
//
//=============================================================================

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include <assert.h>
#include <stdio.h>

#include "mouse.h"

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CMouse::CMouse()
{
	memset(&m_aKeyState, 0, sizeof(m_aKeyState));
	memset(&m_aKeyStateTrigger, 0, sizeof(m_aKeyStateTrigger));
	memset(&m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CMouse::~CMouse()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : �}�E�X�̃A�N�Z�X�����l���ł����ꍇ�A�������p������
//=============================================================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �e�N���X�̃����o�ϐ����擾
	LPDIRECTINPUTDEVICE8 pDevice = GetDevice();
	LPDIRECTINPUT8 pInput = GetInput();

	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&pInput, NULL)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X�i�}�E�X�j�̐���
	if (FAILED(pInput->CreateDevice(GUID_SysMouse, &pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(pDevice->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(pDevice->SetCooperativeLevel(hWnd, 
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �E�B���h�E�n���h���̊i�[
	m_hWnd = hWnd;

	// Device�ւ̃A�N�Z�X�����l��
	pDevice->Acquire();

	// Device�̐ݒ�
	SetDevice(pDevice);

	// �C���v�b�g�̐ݒ�
	SetInput(pInput);

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �}�E�X�̃A�N�Z�X����������A�f�o�C�X�ƃI�u�W�F�N�g���������
//=============================================================================
void CMouse::Uninit(void)
{
	// �C���v�b�g�̏I��
	CInput::Uninit();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �}�E�X���͂��ꂽ����ۑ�����
//=============================================================================
void CMouse::Update(void)
{
	// �e�N���X�̃����o�ϐ����擾
	LPDIRECTINPUTDEVICE8 pDevice = GetDevice();

	// �ϐ��錾
	DIMOUSESTATE2 aKeyState;		// �}�E�X���͏��
	int nCntKey;

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState)))
	{
		for (nCntKey = 0; nCntKey < MAX_MOUSE_KEY; nCntKey++)
		{
			// �}�E�X�g���K�[����ۑ�
			m_aKeyStateTrigger.rgbButtons[nCntKey] = (m_aKeyState.rgbButtons[nCntKey] ^ aKeyState.rgbButtons[nCntKey]) & aKeyState.rgbButtons[nCntKey];

			// �}�E�X�����[�X����ۑ�
			m_aKeyStateRelease.rgbButtons[nCntKey] = (m_aKeyState.rgbButtons[nCntKey] ^ aKeyState.rgbButtons[nCntKey]) & m_aKeyState.rgbButtons[nCntKey];

			// �}�E�X�v���X����ۑ�
			m_aKeyState = aKeyState;
		}
	}
	else
	{
		// �}�E�X�ւ̃A�N�Z�X�����l��
		pDevice->Acquire();
	}

	// Device�̐ݒ�
	SetDevice(pDevice);
}

//=============================================================================
//  �}�E�X�v���X���̎擾
// Author : �������l
// �T�v : �����̃L�[�̏���Ԃ�
//=============================================================================
bool CMouse::GetPress(int nKey)
{
	return (m_aKeyState.rgbButtons[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �}�E�X�g���K�[���̎擾
// Author : �������l
// �T�v : �����̃L�[�̏���Ԃ�
//=============================================================================
bool CMouse::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger.rgbButtons[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �}�E�X�����[�X���̎擾
// Author : �������l
// �T�v : �����̃L�[�̏���Ԃ�
//=============================================================================
bool CMouse::GetRelease(int nKey)
{
	return (m_aKeyStateRelease.rgbButtons[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �}�E�X�J�[�\���̈ʒu�̎擾
// Author : �������l
// �T�v : �}�E�X�J�[�\���̈ʒu���擾���A���l��Ԃ�
//=============================================================================
D3DXVECTOR3 CMouse::GetMouseCursor(void)
{
	// �X�N���[�����W��̃}�E�X�J�[�\���̈ʒu�̎擾
	GetCursorPos(&m_mouseCursor);

	// �E�B���h�E��̃}�E�X�J�[�\���̈ʒu�̎擾
	ScreenToClient(m_hWnd, &m_mouseCursor);

	return D3DXVECTOR3((float)m_mouseCursor.x, (float)m_mouseCursor.y, 0.0f);
}

//=============================================================================
// �}�E�X�z�C�[���̈ړ��ʎ擾
// Author : �������l
// �T�v : �}�E�X�z�C�[���̈ړ��ʂ̐��l��Ԃ�
//=============================================================================
int CMouse::GetMouseWheel(void)
{
	return (int)m_aKeyState.lZ;
}

//=============================================================================
// �}�E�X�̈ړ��ʎ擾
// Author : �������l
// �T�v : �}�E�X�̈ړ��ʂ̐��l��Ԃ�
//=============================================================================
D3DXVECTOR3 CMouse::GetMouseMove(void)
{
	return D3DXVECTOR3((float)(m_aKeyState.lX), (float)(m_aKeyState.lY), (float)(m_aKeyState.lZ));
}
