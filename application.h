//=============================================================================
//
// �A�v���P�[�V�����N���X(application.h)
// Author : �������l
// �T�v : �e�N���X�̌Ăяo�����s���N���X
//
//=============================================================================
#ifndef _APPLICATION_H_		// ���̃}�N����`������ĂȂ�������
#define _APPLICATION_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// ���C�u�����[�����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")			// �`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")		// [d3d9.lib]�̊g�����C�u����

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <Windows.h>
#include "d3dx9.h"							// �`�揈���ɕK�v

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRenderer;
class CDebugProc;
class CKeyboard;
class CMouse;
class CTexture;
class CCamera;
class CSceneMode;
class CFade;
class CLight;
class CSound;
class CPause;
class CJoypad;

//=============================================================================
// �A�v���P�[�V�����N���X
// Author : �������l
// �T�v : �e�N���X�̌Ăяo�����s���N���X
//=============================================================================
class CApplication
{
public:
	//--------------------------------------------------------------------
	// �V�[�����[�h�̗񋓌^
	// Author : �������l
	// �T�v : �V�[�����[�h�����ʂ���
	//--------------------------------------------------------------------
	enum SCENE_MODE
	{
		MODE_TITLE = 0,			// �^�C�g��
		MODE_GAME,				// �Q�[��
		MODE_RESULT,			// ���U���g
		MODE_TUTORIAL,			// �`���[�g���A��
		MODE_SELECTITEM,		// �A�C�e���Z���N�g
		MAX_MODE,				// �V�[���̍ő吔
		MODE_NONE,				// �V�[������
	};

	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static HWND GetWnd() { return m_hWnd; }												// �E�B���h�E�̎擾
	static CRenderer *GetRenderer() { return m_pRenderer; }								// �����_���[�̃Q�b�^�[
	static CKeyboard *GetKeyboard() { return m_pKeyboard; }								// �L�[�{�[�h�̃Q�b�^�[
	static CMouse *GetMouse() { return m_pMouse; }										// �}�E�X�̃Q�b�^�[
	static CTexture *GetTexture() { return m_pTexture; }								// �e�N�X�`���̃Q�b�^�[
	static CCamera *GetCamera() { return m_pCamera; }									// �J�����̃Q�b�^�[
	static CFade *GetFade() { return m_pFade; }											// �t�F�[�h�̃Q�b�^�[
	static CLight *GetLight() { return m_pLight; }										// ���C�g�̎擾
	static CSound *GetSound() { return m_pSound; }										// �T�E���h�̃Q�b�^�[
	static CPause *GetPause() { return m_pPause; }										// �|�[�Y�̎擾
	static CSceneMode *GetSceneMode() { return pSceneMode; }							// �V�[�����[�h�̎擾
	static CJoypad *GetJoy() { return m_pJoy; }											// �W���C�p�b�h�̃Q�b�^�[
	static D3DXVECTOR3 ScreenCastWorld(const D3DXVECTOR3 &pos);							// ���[���h���W���X�N���[�����W�ɃL���X�g����
	static D3DXVECTOR3 WorldCastScreen(const D3DXVECTOR3 &pos);							// ���[���h���W���X�N���[�����W�ɃL���X�g����
	static void SetNextMode(SCENE_MODE mode) { m_nextMode = mode; }						// ���̃��[�h�̐ݒ�
	static void SetMode(SCENE_MODE mode);												// ���[�h�̐ݒ�
	static SCENE_MODE GetMode() { return m_mode; }										// ���[�h�̎擾
	static void SetScore(const int nScore) { m_nScore = nScore; }						// �X�R�A�̐ݒ�
	static int GetScore() { return m_nScore; }											// �X�R�A�̎擾

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CApplication();
	~CApplication();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		// ������
	void Uninit();										// �I��
	void Update();										// �X�V
	void Draw();										// �`��

private:
	//--------------------------------------------------------------------
	// �ÓI�����o�ϐ�
	//--------------------------------------------------------------------
	static HWND	m_hWnd;							// �E�B���h�E
	static CDebugProc *m_pDebugProc;			// �f�o�b�N�\��
	static CRenderer *m_pRenderer;				// renderer�N���X
	static CKeyboard *m_pKeyboard;				// �L�[�{�[�h�N���X
	static CMouse *m_pMouse;					// �}�E�X�N���X
	static CTexture *m_pTexture;				// �e�N�X�`���N���X
	static CCamera *m_pCamera;					// �Q�[���J�����N���X
	static SCENE_MODE m_mode;					// ���݂̃��[�h�̊i�[
	static SCENE_MODE m_nextMode;				// ���ɐݒ肷�郂�[�h
	static CSceneMode *pSceneMode;				// �V�[�����[�h���i�[
	static CFade *m_pFade;						// �t�F�[�h�N���X
	static CLight *m_pLight;					// ���C�g�N���X
	static CSound *m_pSound;					// �T�E���h�N���X
	static CPause *m_pPause;					// �|�[�Y�N���X
	static CJoypad *m_pJoy;						// �W���C�p�b�h�N���X
	static int m_nPriority;						// �v���C�I���e�B�ԍ�
	static int m_nScore;						// ���݂̃X�R�A
	static bool m_bWireFrame;					// ���C���[�t���[�����g����
};

#endif

