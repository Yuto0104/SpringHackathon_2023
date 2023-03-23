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

//=============================================================================
//�v���C���[�N���X
//=============================================================================
class CPlayer : public CObject3D
{
public:

	enum Parts
	{
		BODY = 0,								//��
		HEAD,									//��
		LEFT_ARM,								//���r
		LEFT_HAND,								//����
		RIGHT_ARM,								//�E�r
		RIGHT_HAND,								//�E��
		LEFT_LEG,								//����
		LEFT_FOOT,								//������
		RIGHT_LEG,								//�E��
		RIGHT_FOOT,								//�E����
		PARTS_MAX
	};

	CPlayer();															//�R���X�g���N�^
	~CPlayer() override;												//�f�X�g���N�^

	HRESULT Init(void) override;										//����������
	void Uninit(void) override;											//�I������
	void Update(void) override;											//�X�V����
	void Draw(void) override;											//�`�揈��

	static CPlayer* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	//��������

private:
	void  PlayerController(void);										//�v���C���[�̑���
	static const float m_MaxWalkingSpeed;								//�ő�̕����X�s�[�h

	D3DXVECTOR3 m_pos;													//�ʒu
	D3DXVECTOR3 m_move;													//���x
	D3DXVECTOR3 m_rot;													//����
	D3DXMATRIX  m_mtxWorld;												//���[���h�}�g���b�N�X
};

#endif