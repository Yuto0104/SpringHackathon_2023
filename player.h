//=============================================================================
//
// player.h
// Author : ���c�喲
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object3D.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCollision_Rectangle3D;

//=============================================================================
//�v���C���[�N���X
//=============================================================================
class CPlayer : public CObject3D
{
public:
	CPlayer();															//�R���X�g���N�^
	~CPlayer() override;												//�f�X�g���N�^

	HRESULT Init(void) override;										//����������
	void Uninit(void) override;											//�I������
	void Update(void) override;											//�X�V����
	void Draw(void) override;											//�`�揈��

	static CPlayer* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	//��������

	int GetLife() { return m_nLife; }
	void SetLife(int life) { m_nLife = life; }

private:
	void  PlayerController(void);										//�v���C���[�̑���
	static const float m_MaxWalkingSpeed;								//�ő�̕����X�s�[�h

	CCollision_Rectangle3D *m_pCollisionRectangle3D;					//3D��`�̓����蔻��
	D3DXVECTOR3 m_pos;													//�ʒu
	D3DXVECTOR3 m_move;													//���x
	D3DXVECTOR3 m_rot;													//����
	D3DXMATRIX  m_mtxWorld;												//���[���h�}�g���b�N�X
	int m_nMineCT;														//�n���̃N�[���^�C��
	int m_nLife;														//�̗�
	int m_nBulletCreateTime;

	bool m_bTex;				
	bool m_SkillFlag;														//�X�L���̃t���O
	int m_nInvincibleCnt;												//���G����
};

#endif