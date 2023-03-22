//=============================================================================
//
// �W���C�p�b�h�N���X(joypad.h)
// Author : �������l
// Author : ��]����
// �T�v : �W���C�p�b�h�N���X�̊Ǘ����s��
//
//=============================================================================
#ifndef _JOYPAD_H_		//���̃}�N����`������Ȃ�������
#define _JOYPAD_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//----------------------------------------------------------------------------
//���C�u�����[�t�@�C���̃����N
//----------------------------------------------------------------------------
#pragma comment(lib,"dinput8.lib")		// ���͏����ɕK�v(�L�[�{�[�h)
#pragma comment(lib,"xinput.lib")		// ���͏����ɕK�v�i�W���C�p�b�g�j
#pragma comment(lib,"dxguid.lib")		// DirectX�R���|�[�l���g�Ɏg�p

//----------------------------------------------------------------------------
//�C���N���[�h
//----------------------------------------------------------------------------
#include <Windows.h>
#pragma push_macro("new")
#undef new
#include <d3dx9.h>
#pragma pop_macro("new")
#define	 DIRECTINPUT_VERSION (0x0800)	// �r���h���̌x���΍��p�}�N��(���̈ʒu���瓮�����Ȃ�)
#include <Xinput.h>						// �W���C�p�b�g����
#include <dinput.h>						// ���͏����ɕK�v

//=============================================================================
// �W���C�p�b�h�N���X
// Author : �������l
// Author : ��]����
// �T�v : �W���C�p�b�h�N���X�������s���N���X
//=============================================================================
class CJoypad
{
public:
	//--------------------------------------------------------------------
	// �L�[��ނ̗񋓌^
	//--------------------------------------------------------------------
	typedef enum
	{
		JOYKEY_UP = 0,				// �\���{�^����
		JOYKEY_DOWN,				// �\���{�^����
		JOYKEY_LEFT,				// �\���{�^����
		JOYKEY_RIGHT,				// �\���{�^���E
		JOYKEY_START,				// �X�^�[�g�{�^��
		JOYKEY_BACK,				// �o�b�N�{�^��
		JOYKEY_LEFT_THUMB,			// ���X�e�B�b�N������
		JOYKEY_RIGHT_THUMB,			// �E�X�e�B�b�N������
		JOYKEY_LEFT_SHOULDER,		// L�P�{�^��
		JOYKEY_RIGHT_SHOULDER,		// R�P�{�^��
		JOYKEY_LEFT_TRIGGER,		// L�Q�g���K�[
		JOYKEY_RIGHT_TRIGGER,		// R�Q�g���K�[
		JOYKEY_A,					// A�{�^��
		JOYKEY_B,					// B�{�^��
		JOYKEY_X,					// X�{�^��
		JOYKEY_Y,					// Y�{�^��
		JOYKEY_LEFT_STICK,			// ���X�e�B�b�N
		JOYKEY_RIGHT_STICK,			// �E�X�e�B�b�N
		JOYKEY_MAX
	}JOYKEY;

	//--------------------------------------------------------------------
	// �W���C�p�b�h���̍\����
	//--------------------------------------------------------------------
	struct JOYPAD
	{
		XINPUT_STATE		press;				// �W���C�p�b�g�̃v���X���
		XINPUT_STATE		trigger;			// �W���C�p�b�g�̃g���K�[���
		XINPUT_VIBRATION	vibration;			// �W���C�p�b�h�̃o�C�u���[�V����
		D3DXVECTOR3			joyStickPos;		// �W���C�X�e�B�b�N�̌X��
		WORD				wStrength;			// �U���̋��� (0 - 65535)
		int					nTime;				// �U����������
		float				fStickAngle;		// �X�e�B�b�N�̌���
	};

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CJoypad();
	~CJoypad();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init(const int nMax);										// ������
	void Uninit(void);													// �I��
	void Update(void);													// �X�V
	bool GetPress(JOYKEY Key, int nPlayer);								// �v���X
	bool GetTrigger(JOYKEY Key, int nPlayer);							// �g���K�[
	D3DXVECTOR3 GetStick(JOYKEY Key, int nPlayer);						// �X�e�B�b�N
	bool GetStickPress(JOYKEY Key, bool RightLeft, int nPlayer);		// �X�e�B�b�N�v���X
	bool GetStickTrigger(JOYKEY Key, bool RightLeft, int nPlayer);		// �X�e�B�b�N�g���K�[
	int GetTriggerPedal(JOYKEY Key, int nPlayer);						// �g���K�[�y�_��
	void Vibration(int nTime, WORD nStrength, int nPlayer);				// �U������
	int GetUseJoyPad() { return m_nUseJoyPad; }							// �g�p���̎擾
	float GetStickAngle(JOYKEY Key, int nPlayer);						// �X�e�B�b�N�̌X���̎擾
	bool Stick(JOYKEY Key, int nPlayer, float fDeadZone);				// �X�e�B�b�N�̎g�p�󋵂̎擾
	bool AnyButton(int nPlayer);										// ���ׂẴ{�^���̔���擾

private:	
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	LPDIRECTINPUT8			m_pInput;					// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8	m_pDevJoypad;				// ���̓f�o�C�X�i�L�[�{�[�h�i�R���g���[���[�p�͕ʂɍ��j�j�ւ̃|�C���^
	JOYPAD					*m_pJoyPad;					// �W���C�p�b�h���
	JOYKEY					m_oldKey[4][2];				//�W���C�X�e�B�b�N�̑O��̌X��
	int						m_nMax;						// �R���g���[���[�̎g�p�\��
	int						m_nUseJoyPad;				// �g�p���Ă���R���g���[���[��
};

#endif