//============================================
//
//	bullet.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _BULLET_H_
#define _BULLET_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object3D.h"

//============================================
// �}�N����`
//============================================
#define BOMB_SIZE			(9.0f)				//���e�̃T�C�Y
#define BOMB_HIT_SIZE		(75.0f)				//�{�X�̒e�̓����蔻��T�C�Y

//============================================
// �O���錾
//============================================
class CEnemy;
class CFade;

//============================================
// �e�N���X
//============================================
class CBullet : public CObject3D
{
public:
	CBullet();									//�R���X�g���N�^
	~CBullet()override;							//�f�X�g���N�^

	HRESULT Init(void)override;					//�e�̏���������
	void Uninit(void)override;					//�e�̏I������
	void Update(void)override;					//�e�̍X�V����
	void Draw(void)override;					//�e�̕`�揈��

	void HitEnemy(D3DXVECTOR3 pos);														//�e�ƓG�̓����蔻��
	void BulletLife();																	//�e�̗̑�

																						//getter
	D3DXVECTOR3 GetBulletPos(void) { return m_BulletPos; }								//�e�̈ʒu�̎擾����
	int GetBulletLife(void) { return m_nLife; }											//�e�̗̑͂̎擾����
	int GetTotalEnemy(void) { return m_TotalEnemy; }									//�G�̑����̎擾����
	bool GetBossDeathFlag(void) { return m_BossDeathFlag; }								//�{�X�����񂾂̂��t���O�̎擾����

																						//setter
	void SetLife(int life);																//�e�̃��C�t�̐ݒ菈��
	void SetBulletPos(D3DXVECTOR3 pos) { m_BulletPos = pos; }							//�e�̈ʒu�̐ݒ�
	void SetGimmickUninitFlag(bool flag) { m_GimmickUninitFlag = flag; }				//�M�~�b�N���������̂��t���O�̐ݒ菈��
	void SetBossDeathFlag(bool flag) { m_BossDeathFlag = flag; }						//�{�X�����񂾂̂��t���O�̐ݒ菈��

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife);		//����

private:
	D3DXVECTOR3 m_BulletSize;						//�T�C�Y
	D3DXVECTOR3 m_BulletPos;						//�ʒu
	D3DXVECTOR3 m_BulletPosOld;						//�O��̈ʒu
	D3DXVECTOR3 m_BulletRot;						//����
	D3DXVECTOR3	m_BulletMove;						//�ړ�

	CEnemy *m_pEnemy;								//�G�̃C���X�^���X
	CFade *m_pFade;									//�t�F�[�h�̃C���X�^���X

	int m_nLife;									//�̗�
	int m_TotalEnemy;								//�G�̑���
	int m_ExplosionTime;							//��������܂ł̎���

	bool m_RandFlag;								//�����_���t���O
	bool m_ExplosionFlag;							//���������̂��̃t���O
	bool m_EnemyDeathFlag;							//�G�����񂾂̂��t���O
	bool m_GimmickUninitFlag;						//�M�~�b�N���������̂��t���O
	bool m_BossDeathFlag;							//�{�X�����񂾂̂��̃t���O
};

#endif

