//=============================================================================
//
// ���͏���(input.cpp)
// Author : �������l
// �T�v : �I�u�W�F�N�g�������s��
//
//=============================================================================

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include <assert.h>
#include <stdio.h>

#include "keyboard.h"

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CKeyboard::CKeyboard()
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		m_aKeyState[nCntKey] = NULL;
		m_aKeyStateTrigger[nCntKey] = NULL;
		m_aKeyStateRelease[nCntKey] = NULL;
	}
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CKeyboard::~CKeyboard()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : �L�[�{�[�h�̃A�N�Z�X�����l���ł����ꍇ�A�������p������
//=============================================================================
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �e�N���X�̃����o�ϐ����擾
	LPDIRECTINPUTDEVICE8 pDevice = GetDevice();
	LPDIRECTINPUT8 pInput = GetInput();

	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&pInput, NULL)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(pInput->CreateDevice(GUID_SysKeyboard, &pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

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
// �T�v : �L�[�{�[�h�̃A�N�Z�X����������A�f�o�C�X�ƃI�u�W�F�N�g���������
//=============================================================================
void CKeyboard::Uninit(void)
{
	// �C���v�b�g�̏I��
	CInput::Uninit();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �L�[�{�[�h�̓��͂��ꂽ����ۑ�����
//=============================================================================
void CKeyboard::Update(void)
{
	// �e�N���X�̃����o�ϐ����擾
	LPDIRECTINPUTDEVICE8 pDevice = GetDevice();

	//�ϐ��錾
	BYTE aKeyState[NUM_KEY_MAX];	//�L�[�{�[�h�̓��͏��
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			// �L�[�{�[�h�̃g���K�[����ۑ�
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];

			// �L�[�{�[�h�̃����[�X����ۑ�
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & m_aKeyState[nCntKey];

			// �L�[�{�[�h�̃v���X����ۑ�
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
		pDevice->Acquire();
	}

	// Device�̐ݒ�
	SetDevice(pDevice);
}

//=============================================================================
//  �L�[�{�[�h�v���X���̎擾
// Author : �������l
// �T�v : �����̃L�[�̏���Ԃ�
//=============================================================================
bool CKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�g���K�[���̎擾
// Author : �������l
// �T�v : �����̃L�[�̏���Ԃ�
//=============================================================================
bool CKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�����[�X���̎擾
// Author : �������l
// �T�v : �����̃L�[�̏���Ԃ�
//=============================================================================
bool CKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

