//=============================================================================
//
// �Q�[���N���X(game.h)
// Author : �������l
// �T�v : �Q�[���N���X�̊Ǘ����s��
//
//=============================================================================
#ifndef _GAME_H_		// ���̃}�N����`������ĂȂ�������
#define _GAME_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "scene_mode.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScore;
class CTime;
class CEnemy;
class CPlayer;
class CLille;

//=============================================================================
// �Q�[���N���X
// Author : �������l
// �T�v : �Q�[���������s���N���X
//=============================================================================
class CGame : public CSceneMode
{
public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CScore *GetScore() { return m_pScore; }					// �X�R�A
	static CTime *GetTime() { return m_pTime; }						// �^�C��
	static CEnemy *GetEnemy() { return m_pEnemy; }					// �G�l�~�[
	static CPlayer *GetPlayer() { return m_pPlayer; }				// �v���C���[
	static void SetGame(const bool bGame) { m_bGame = bGame; }		// �Q�[���̏󋵂̐ݒ�
	static void SetEnemy(CEnemy *enemy) { m_pEnemy = enemy; }

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CGame();
	~CGame() override;

	//--------------------------------------------------------------------
	// �ÓI�����o�ϐ�
	//--------------------------------------------------------------------
	static CScore *m_pScore;						// �X�R�A
	static CTime *m_pTime;							// �^�C��
	static CEnemy *m_pEnemy;						// �G�l�~�[
	static CPlayer *m_pPlayer;						// �v���C���[
	static CLille *m_pLille;						// ���[��
	static D3DXCOLOR fogColor;						// �t�H�O�J���[
	static float fFogStartPos;						// �t�H�O�̊J�n�_
	static float fFogEndPos;						// �t�H�O�̏I���_
	static float fFogDensity;						// �t�H�O�̖��x
	static bool m_bGame;							// �Q�[���̏�

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;					// ������
	void Uninit() override;						// �I��
	void Update() override;						// �X�V
	void Draw() override;						// �`��

	void EnemySpawn();							// �G��N������
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	int m_nSpawnTime;							// �X�|�[������
	bool m_bSelectItem;							// �A�C�e���I��
	bool m_bSelectItem2;						// �A�C�e���I��
	bool m_bSelectItem3;						// �A�C�e���I��
};

#endif



