//=============================================================================
//
// �W���C�p�b�h�N���X(joypad.cpp)
// Author : �������l
// Author : ��]����
// �T�v : �W���C�p�b�h�N���X�̊Ǘ����s��
//
//=============================================================================

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include <assert.h>
#include "joypad.h"
#include "debug_proc.h"

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CJoypad::CJoypad()
{
	m_pInput = nullptr;			// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	m_pDevJoypad = nullptr;		// ���̓f�o�C�X�i�L�[�{�[�h�i�R���g���[���[�p�͕ʂɍ��j�j�ւ̃|�C���^
	m_pJoyPad = nullptr;		// �W���C�p�b�h���
	m_nMax = 0;					// �R���g���[���[�̎g�p�\��
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CJoypad::~CJoypad()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CJoypad::Init(const int nMax)
{
	// XInput�̃X�e�[�g��ݒ�i�L���ɂ���j
	XInputEnable(true);

	// �R���g���[���[�̍ő吔
	m_nMax = nMax;

	// �������̊m��
	m_pJoyPad = new JOYPAD[m_nMax];
	assert(m_pJoyPad != nullptr);

	for (int nCnt = 0; nCnt < m_nMax; nCnt++)
	{
		//�������[�̃N���A
		memset(&m_pJoyPad[nCnt].press, 0, sizeof(XINPUT_STATE));
		memset(&m_pJoyPad[nCnt].trigger, 0, sizeof(XINPUT_STATE));

		// �W���C�p�b�h�̐U�������0�N���A
		memset(&m_pJoyPad[nCnt].vibration, 0, sizeof(XINPUT_VIBRATION));

		// �U������p�̏�����
		m_pJoyPad[nCnt].wStrength = 0;
		m_pJoyPad[nCnt].nTime = 0;
	}
	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CJoypad::Uninit(void)
{
	//XInput�̃X�e�[�g��ݒ�i�����ɂ���j
	XInputEnable(false);

	if (m_pJoyPad != nullptr)
	{
		delete[] m_pJoyPad;
		m_pJoyPad = nullptr;
	}
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CJoypad::Update(void)
{
	//�W���C�p�b�h���͏��
	XINPUT_STATE *pJoyKeyState = new XINPUT_STATE[m_nMax];	

	// �g�p���̃J�E���g
	int nCntUse = 0;

	for (int nCnt = 0; nCnt < m_nMax; nCnt++)
	{
		//�W���C�p�b�h�̏�Ԃ��擾
		if (XInputGetState(nCnt, &pJoyKeyState[nCnt]) == ERROR_SUCCESS)
		{
			// �g���K�[����ۑ�
			m_pJoyPad[nCnt].trigger.Gamepad.wButtons
				= ~m_pJoyPad[nCnt].press.Gamepad.wButtons
				& pJoyKeyState[nCnt].Gamepad.wButtons;		

			// �v���X����
			m_pJoyPad[nCnt].press = pJoyKeyState[nCnt];

			// �g�p���̑���
			nCntUse++;
		}

		//�W���C�p�b�h�̐U��
		m_pJoyPad[nCnt].vibration.wLeftMotorSpeed = m_pJoyPad[nCnt].wStrength;
		m_pJoyPad[nCnt].vibration.wRightMotorSpeed = m_pJoyPad[nCnt].wStrength;
		XInputSetState(nCnt, &m_pJoyPad[nCnt].vibration);

		if (m_pJoyPad[nCnt].nTime > 0)
		{
			m_pJoyPad[nCnt].nTime--;
		}
		else
		{
			m_pJoyPad[nCnt].wStrength = 0;
			m_pJoyPad[nCnt].nTime = 0;
		}
	}

	// �g�p���Ă���R���g���[���[���̍X�V
	m_nUseJoyPad = nCntUse;

	if (pJoyKeyState != nullptr)
	{
		delete[] pJoyKeyState;
		pJoyKeyState = nullptr;
	}
}

//=============================================================================
// �v���X����
// Author : �������l
// �T�v : �v���X���͌v�Z���s�����ʂ�Ԃ�
//=============================================================================
bool CJoypad::GetPress(JOYKEY Key, int nPlayer)
{
	return (m_pJoyPad[nPlayer].press.Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//=============================================================================
// �g���K�[����
// Author : �������l
// �T�v : �g���K�[���͌v�Z���s�����ʂ�Ԃ�
//=============================================================================
bool CJoypad::GetTrigger(JOYKEY Key, int nPlayer)
{
	return (m_pJoyPad[nPlayer].trigger.Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//=============================================================================
// �X�e�B�b�N���͏���
// Author : �������l
// �T�v : �X�e�B�b�N���͌v�Z���s�����ʂ�Ԃ�
//=============================================================================
D3DXVECTOR3 CJoypad::GetStick(JOYKEY Key, int nPlayer)
{
	switch (Key)
	{
	case JOYKEY_LEFT_STICK:
		m_pJoyPad[nPlayer].joyStickPos = D3DXVECTOR3(m_pJoyPad[nPlayer].press.Gamepad.sThumbLX / 32767.0f, - m_pJoyPad[nPlayer].press.Gamepad.sThumbLY / 32767.0f, 0.0f);

		break;
	case JOYKEY_RIGHT_STICK:
		m_pJoyPad[nPlayer].joyStickPos = D3DXVECTOR3(m_pJoyPad[nPlayer].press.Gamepad.sThumbRX / 32767.0f, - m_pJoyPad[nPlayer].press.Gamepad.sThumbRY / 32767.0f, 0.0f);
		break;
	}

	return m_pJoyPad[nPlayer].joyStickPos;
}


//=============================================================================
// �X�e�B�b�N�v���X����
// Author : �������l
// �T�v : �X�e�B�b�N���͌v�Z���s�����ʂ�Ԃ�
//=============================================================================
bool CJoypad::GetStickPress(JOYKEY Key, bool RightLeft, int nPlayer)
{
	JOYKEY stick = JOYKEY_LEFT_STICK;

	if (RightLeft)
	{// �E
		stick = JOYKEY_RIGHT_STICK;
	}
	else
	{// ��
		stick = JOYKEY_LEFT_STICK;
	}


	D3DXVECTOR3 pos = GetStick(stick, nPlayer);	//���݂̌X���̎擾
	pos.y *= -1.0f;//Y�𕪂���₷�����邽�߂Ɂ{�|�𔽓]

	if (pos.y > 0.5f
		&& JOYKEY_UP == Key)
	{
		return true;
	}
	else if (pos.x > 0.5f
		&& JOYKEY_RIGHT == Key)
	{
		return true;
	}
	else if (pos.y < -0.5f
		&& JOYKEY_DOWN == Key)
	{
		return true;
	}
	else if (pos.x < -0.5f
		&& JOYKEY_LEFT == Key)
	{
		return true;
	}

	return false;
}

//=============================================================================
// �X�e�B�b�N���͏���
// Author : �������l
// �T�v : �X�e�B�b�N���͌v�Z���s�����ʂ�Ԃ�
//=============================================================================
bool CJoypad::GetStickTrigger(JOYKEY Key, bool RightLeft, int nPlayer)
{
	if (GetStickPress(Key, RightLeft, nPlayer)
		&& Key != m_oldKey[nPlayer][RightLeft])
	{
		m_oldKey[nPlayer][RightLeft] = Key;
		return true;
	}
	else if (GetStickPress(Key, RightLeft, nPlayer)
		&& Key == m_oldKey[nPlayer][RightLeft])
	{
		return false;
	}
	else if (!GetStickPress(Key, RightLeft, nPlayer)
		&& Key != m_oldKey[nPlayer][RightLeft])
	{
		return false;
	}

	m_oldKey[nPlayer][RightLeft] = JOYKEY_MAX;
	return false;
}

//=============================================================================
// �y�_�����͏���
// Author : �������l
// �T�v : �y�_�����͌v�Z���s�����ʂ�Ԃ�
//=============================================================================
int  CJoypad::GetTriggerPedal(JOYKEY Key, int nPlayer)
{
	int nJoypadTriggerPedal = 0;
	switch (Key)
	{
	case JOYKEY_LEFT_TRIGGER:
		nJoypadTriggerPedal = m_pJoyPad[nPlayer].press.Gamepad.bLeftTrigger;
		break;
	case JOYKEY_RIGHT_TRIGGER:
		nJoypadTriggerPedal = m_pJoyPad[nPlayer].press.Gamepad.bRightTrigger;
		break;
	}

	return nJoypadTriggerPedal;
}

//=============================================================================
// �U���o�͏���
// Author : �������l
// �T�v : �U���o�͌v�Z���s�����ʂ�Ԃ�
//=============================================================================
void  CJoypad::Vibration(int nTime, WORD nStrength, int nPlayer)
{
	m_pJoyPad[nPlayer].nTime = nTime;			// �U����������
	m_pJoyPad[nPlayer].wStrength = nStrength;	// �U���̋���
}

//=============================================================================
// �W���C�X�e�B�b�N�̌X���擾����
// Author : �������l
// �T�v : �W���C�X�e�B�b�N�̌X���擾��Ԃ�
//=============================================================================
float CJoypad::GetStickAngle(JOYKEY Key, int nPlayer)
{
	switch (Key)
	{
	case JOYKEY_LEFT_STICK:
		// �X�e�B�b�N�̊p�x
		m_pJoyPad[nPlayer].fStickAngle = atan2f(m_pJoyPad[nPlayer].press.Gamepad.sThumbLX / 32767.0f, m_pJoyPad[nPlayer].press.Gamepad.sThumbLY / 32767.0f);

		break;
	case JOYKEY_RIGHT_STICK:
		m_pJoyPad[nPlayer].fStickAngle = atan2f(m_pJoyPad[nPlayer].press.Gamepad.sThumbRX / 32767.0f, m_pJoyPad[nPlayer].press.Gamepad.sThumbRY / 32767.0f);
		break;
	}
	
	return m_pJoyPad[nPlayer].fStickAngle;
}

//=============================================================================
// �W���C�X�e�B�b�N�̎g�p�󋵎擾����
// Author : �������l
// �T�v : �W���C�X�e�B�b�N�̎g�p�󋵎��Ԃ�
//=============================================================================
bool CJoypad::Stick(JOYKEY Key, int nPlayer, float fDeadZone)
{
	// �ϐ��錾
	bool bStick = false;
	D3DXVECTOR2 stickVec;

	switch (Key)
	{
	case JOYKEY_LEFT_STICK:
		// �X�e�B�b�N�̌X���̑傫���̎擾
		stickVec = D3DXVECTOR2(-m_pJoyPad[nPlayer].press.Gamepad.sThumbLX / 32767.0f, -m_pJoyPad[nPlayer].press.Gamepad.sThumbLY / 32767.0f);
		break;

	case JOYKEY_RIGHT_STICK:
		// �X�e�B�b�N�̌X���̑傫���̎擾
		stickVec = D3DXVECTOR2(-m_pJoyPad[nPlayer].press.Gamepad.sThumbRX / 32767.0f, -m_pJoyPad[nPlayer].press.Gamepad.sThumbRY / 32767.0f);
		break;
	}

	if (D3DXVec2Length(&stickVec) >= fDeadZone)
	{
		bStick = true;
	}

#ifdef _DEBUG
	CDebugProc::Print("�X���̑傫�� : %f\n", D3DXVec2Length(&stickVec));
#endif // _DEBUG


	return bStick;
}

//=============================================================================
// ���ׂẴ{�^���̔���擾
// Author : �������l
// �T�v : �ǂ����̃{�^���������ꂽ��true��Ԃ�
//=============================================================================
bool CJoypad::AnyButton(int nPlayer)
{
	bool bAnyButton = false;

	for (int nCntButton = 0; nCntButton < JOYKEY_MAX; nCntButton++)
	{
		bAnyButton = (m_pJoyPad[nPlayer].press.Gamepad.wButtons & (0x01 << nCntButton)) ? true : false;

		if (bAnyButton)
		{
			break;
		}
	}

	return bAnyButton;
}
