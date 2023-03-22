//=============================================================================
//
// �ړ�����(move.h)
// Author : �������l
// �T�v : �ړ��Ɋւ���v�Z���s��
//
//=============================================================================
#ifndef _MOVE_H_		// ���̃}�N����`������ĂȂ�������
#define _MOVE_H_		// ��d�C���N���[�h�h�~�̃}�N����`

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

//=============================================================================
// �ړ��N���X
// Author : �������l
// �T�v : �ړ��ݒ���s���N���X
//=============================================================================
class CMove
{
public:
	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CMove();
	virtual ~CMove();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void SetMoving(float fSpeed, float fMaxSpeed, float fMinSpeed, float fFriction);	// �ړ����̏����ݒ�
	void SetMove(D3DXVECTOR3 move) { m_move = move; }									// �ړ��ʂ̐ݒ�
	void SetSpeed(const float fSpeed) { m_fSpeed = fSpeed; }							// ���x�̐ݒ�
	void SetMaxSpeed(const float fMaxSpeed) { m_fMaxSpeed = fMaxSpeed; }				// �ō����x�̐ݒ�
	void SetMinSpeed(const float fMinSpeed) { m_fMinSpeed = fMinSpeed; }				// �Œᑬ�x�̐ݒ�
	void SetFriction(const float fFriction) { m_fFriction = fFriction; }				// ���C�W���̐ݒ�
	void Moving(const D3DXVECTOR3 &moveDir);											// �����𔺂��ړ�
	void SetMoveVec(const D3DXVECTOR3 vec);												// �ړ������x�N�g���̐ݒ�
	D3DXVECTOR3 GetMove() { return m_move; }											// �ړ��x�N�g���̃Q�b�^�[
	float GetSpeed() { return m_fSpeed; }												// ���x�̎擾
	float GetMaxSpeed() { return m_fMaxSpeed; }											// �ō����x�̎擾
	float GetMinSpeed() { return m_fMinSpeed; }											// �Œᑬ�x�̎擾
	float GetFriction() { return m_fFriction; }											// ���C�W���̎擾
	float GetMoveLength() { return D3DXVec3Length(&m_move); }							// �ړ������̃Q�b�^�[

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	D3DXVECTOR3			m_move;					// �ړ���
	float				m_fSpeed;				// �ړ����x
	float				m_fMaxSpeed;			// �ō����x
	float				m_fMinSpeed;			// �Œᑬ�x
	float				m_fFriction;			// ���C�W��
};

#endif