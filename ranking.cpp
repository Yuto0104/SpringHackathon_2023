//=============================================================================
//
// �����L���O�N���X(score.cpp)
// Author : �������l
// �T�v : �����L���O�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>
#include <stdio.h>
#include <thread>

#include "application.h"
#include "tcp_client.h"
#include "ranking.h"
#include "score.h"
#include "renderer.h"
#include "object2D.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : �����L���O�𐶐�����
//=============================================================================
CRanking *CRanking::Create(int nMaxRanking, int nNewScore)
{
	// �I�u�W�F�N�g�C���X�^���X
	CRanking *pRanking = nullptr;

	pRanking = new CRanking;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pRanking != nullptr);

	// ���l�̏�����
	pRanking->Init(nMaxRanking, nNewScore);

	// �C���X�^���X��Ԃ�
	return pRanking;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CRanking::CRanking(int nPriority /*= CObject::PRIORITY_LEVEL3*/) : CObject(nPriority)
{
	m_pScore = nullptr;											// �X�R�A
	pFailObj = nullptr;											// ���s���̃A�i�E���X�p�̃I�u�W�F�N�g
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ߋ��̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �傫��
	m_wholeSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �S�̂̑傫��
	m_nMaxRanking = 0;											// �����L���O��
	m_nDigit = 0;												// ����
	m_aRankingData = nullptr;									// �����L���O�f�[�^
	m_nPortNum = 0;												// �|�[�g�ԍ�
	m_nNewScore = 0;											// �V�����X�R�A
	m_UpdateRank = -1;											// �X�V���ꂽ�����N
	m_fAddAlpha = 0.0f;											// �A���t�@�̉��Z�l
	memset(&m_nIpAddress[0],0,sizeof(m_nIpAddress));			// IP�A�h���X
	m_bUpdatingRanking = true;									// �ʐM���Ă邩�ۂ�
	m_bRankingUpdatedSuccess = true;							// �������Ă邩�ۂ�
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CRanking::~CRanking()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CRanking::Init()
{
	return S_OK;
}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CRanking::Init(int nMaxRanking, int nNewScore)
{
	// �t�@�C���̓ǂݍ���
	LoadFile();

	// �����L���O���̐ݒ�
	m_nMaxRanking = nMaxRanking;

	// �X�R�A�̍X�V
	m_nNewScore = nNewScore;

	// �����L���O�f�[�^�̊m��
	m_aRankingData = new int[m_nMaxRanking];
	assert(m_aRankingData != nullptr);

	// �����L���O�̓ǂݍ���
	LoadRanking();

	// �����̐ݒ�
	m_nDigit = 10;

	// �ʒu�̐ݒ�
	m_pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);

	// �����̐ݒ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �傫���̐ݒ�
	m_size = D3DXVECTOR3(30.0f, 50.0f, 0.0f);

	// �S�̂̑傫���̐ݒ�
	m_wholeSize = D3DXVECTOR3(300.0f, 300.0f, 0.0f);

	if (m_bRankingUpdatedSuccess)
	{// �X�R�A�̐���
		CreateScore();

		// �X�R�A�̐ݒ�
		SetScore();

		// �����L���O�X�R�A�̐ݒ�
		SetScoreNomber();
	}
	else if (!m_bRankingUpdatedSuccess)
	{
		pFailObj = CObject2D::Create();
		pFailObj->SetPos(m_pos);
		pFailObj->SetRot(m_rot);
		pFailObj->SetSize(D3DXVECTOR3(500.0f, 70.0f, 0.0f));
		pFailObj->LoadTex(-1);
		pFailObj->SetCol(D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f));
	}

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CRanking::Uninit()
{
	if (m_pScore != nullptr)
	{// �I������
		for (int nCntRanking = 0; nCntRanking < m_nMaxRanking; nCntRanking++)
		{
			m_pScore[nCntRanking]->Uninit();
			m_pScore[nCntRanking] = nullptr;
		}

		// �������̉��
		delete[] m_pScore;
		m_pScore = nullptr;
	}

	// �����L���O�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CRanking::Update()
{
	if (m_bRankingUpdatedSuccess)
	{
		FlashScore();
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CRanking::Draw()
{

}

//=============================================================================
// �ʒu�̃Z�b�^�[
// Author : �������l
// �T�v : �ʒu�̃����o�ϐ��Ɉ�������
//=============================================================================
void CRanking::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;

	SetScore();
}

//=============================================================================
// �����̃Z�b�^�[
// Author : �������l
// �T�v : �����̃����o�ϐ��Ɉ�������
//=============================================================================
void CRanking::SetRot(const D3DXVECTOR3 &rot)
{
	m_rot = rot;

	SetScore();
}

//=============================================================================
// �傫���̃Z�b�^�[
// Author : �������l
// �T�v : �傫���̃����o�ϐ��Ɉ�������
//=============================================================================
void CRanking::SetSize(const D3DXVECTOR3 & size)
{
	m_size = size;

	SetScore();
}

//=============================================================================
// �S�̂̑傫���̃Z�b�^�[
// Author : �������l
// �T�v : �S�̂̑傫���̃����o�ϐ��Ɉ�������
//=============================================================================
void CRanking::SetWholeSize(const D3DXVECTOR3 & wholeSize)
{
	m_wholeSize = wholeSize;

	SetScore();
}

//=============================================================================
// �����L���O�̎擾
// Author : �������l
// �T�v : �����L���O�̎擾
//=============================================================================
void CRanking::GetRanking()
{
	// �ϐ��錾
	char aReceiveData[128] = {};
	char aResponseData[128] = {};
	WSADATA wsaData;

	// �N���C�A���g�̃C���X�^���X�̐���
	CTCPClient *pTCPClient = new CTCPClient;
	assert(pTCPClient != nullptr);

	// WinSock�̏�����
	if (WSAStartup(WINSOCK_VERSION, &wsaData) != 0)
	{
		printf("WinSock���������s\n");
	}

	// �ڑ�����
	if (pTCPClient != nullptr
		&& pTCPClient->Init(&m_nIpAddress[0], m_nPortNum))
	{
		// �R�}���h�̐ݒ�
		aResponseData[0] = COMMAND_TYPE_GET;

		// �f�[�^�𑗐M����
		if (pTCPClient->Send(&aResponseData[0], sizeof(aResponseData[0])) <= 0)
		{// �ڑ����肪�ؒf���ꂽ
			assert(false);
		}

		if (pTCPClient->Recv(&aReceiveData[0], sizeof(aReceiveData)) <= 0)
		{// �ڑ����肪�ؒf���ꂽ
			assert(false);
		}

		for (int nCntData = 0; nCntData < m_nMaxRanking; nCntData++)
		{
			memcpy(&m_aRankingData[nCntData], &aReceiveData[sizeof(int) * nCntData], sizeof(int));

			// �G���f�B�A���ϊ�(network to host)
			m_aRankingData[nCntData] = ntohl(m_aRankingData[nCntData]);
		}
	}
	else
	{
		m_bRankingUpdatedSuccess = false;
	}

	if (pTCPClient != nullptr)
	{// �I��
		pTCPClient->Uninit();

		// �������̉��
		delete pTCPClient;
		pTCPClient = nullptr;
	}

	// WinSock�̏I������
	WSACleanup();
}

//=============================================================================
// �����L���O�̐ݒ�
// Author : �������l
// �T�v : �����L���O�̐ݒ�
//=============================================================================
int CRanking::SetRanking(const int nTime)
{
	// �ϐ��錾
	char aReceiveData[128] = {};
	char aResponseData[128] = {};
	WSADATA wsaData;
	int nCopyTime = nTime;
	int nRank = 0;

	// �N���C�A���g�̃C���X�^���X�̐���
	CTCPClient *pTCPClient = new CTCPClient;
	assert(pTCPClient != nullptr);

	// WinSock�̏�����
	if (WSAStartup(WINSOCK_VERSION, &wsaData) != 0)
	{
		printf("WinSock���������s\n");
	}

	// �ڑ�����
	if (pTCPClient != nullptr
		&& pTCPClient->Init(&m_nIpAddress[0], m_nPortNum))
	{
		// �R�}���h�̐ݒ�
		aResponseData[0] = COMMAND_TYPE_SET;

		// ���l�̑��
		nCopyTime = htonl(nCopyTime);
		memcpy(&aResponseData[1], &nCopyTime, sizeof(nCopyTime));

		// �f�[�^�𑗐M����
		if (pTCPClient->Send(&aResponseData[0], 1 + sizeof(int)) <= 0)
		{// �ڑ����肪�ؒf���ꂽ
			assert(false);
		}

		if (pTCPClient->Recv(&aReceiveData[0], sizeof(aReceiveData)) <= 0)
		{// �ڑ����肪�ؒf���ꂽ
			assert(false);
		}

		memcpy(&nRank, &aReceiveData[0], sizeof(int));

		// �G���f�B�A���ϊ�(network to host)
		nRank = ntohl(nRank);
	}
	else
	{
		m_bRankingUpdatedSuccess = false;
	}

	if (pTCPClient != nullptr)
	{// �I��
		pTCPClient->Uninit();

		// �������̉��
		delete pTCPClient;
		pTCPClient = nullptr;
	}

	// WinSock�̏I������
	WSACleanup();

	return nRank;
}

//=============================================================================
// �X�R�A�̐���
// Author : �������l
// �T�v : �X�R�A�𐶐�����
//=============================================================================
void CRanking::CreateScore()
{
	// �X�R�A�̊m��
	m_pScore = new CScore*[m_nMaxRanking];
	assert(m_pScore != nullptr);

	for (int nCntRanking = 0; nCntRanking < m_nMaxRanking; nCntRanking++)
	{// �i���o�[�̐ݒ�
		m_pScore[nCntRanking] = CScore::Create(m_nDigit, false);
	}
}

//=============================================================================
// �X�R�A�̐ݒ�
// Author : �������l
// �T�v : �X�R�A�̈ʒu��A�傫���̐ݒ�
//=============================================================================
void CRanking::SetScore()
{
	if (m_pScore != nullptr)
	{
		for (int nCntRanking = 0; nCntRanking < m_nMaxRanking; nCntRanking++)
		{// �i���o�[�̐ݒ�
			m_pScore[nCntRanking]->SetWholeSize(D3DXVECTOR3(m_wholeSize.x, m_wholeSize.y / m_nMaxRanking, 0.0f));

			D3DXVECTOR3 scoreWholeSize = m_pScore[nCntRanking]->GetWholeSize();
			m_pScore[nCntRanking]->SetSize(D3DXVECTOR3(scoreWholeSize.x / m_nDigit, scoreWholeSize.y, 0.0f));

			D3DXVECTOR3 size = m_pScore[nCntRanking]->GetSize();
			m_pScore[nCntRanking]->SetPos(D3DXVECTOR3(m_pos.x + m_wholeSize.x / 2.0f, m_pos.y - m_wholeSize.y / 2.0f + (size.y / 2.0f) + (size.y * nCntRanking), 0.0f));
		}
	}
	else
	{
		SetFailObj();
	}
}

//=============================================================================
// �����L���O�̓ǂݍ���
// Author : �������l
// �T�v : �X�R�A�̈ʒu��A�傫���̐ݒ�
//=============================================================================
void CRanking::LoadRanking()
{
	// �����L���O�̍X�V
	m_UpdateRank = SetRanking(m_nNewScore);

	// �����L���O�̎擾
	GetRanking();

	m_bUpdatingRanking = false;
}

//=============================================================================
// �t�@�C���̓ǂݍ���
// Author : �������l
// �T�v : �t�@�C������IP�A�h���X����|�[�g�ԍ����擾����
//=============================================================================
void CRanking::LoadFile()
{
	// �ϐ��錾
	char aStr[128];

	// �t�@�C���̓ǂݍ���
	FILE *pFile = fopen("data/FILE/server.txt", "r");

	if (pFile != nullptr)
	{
		while (fscanf(pFile, "%s", &aStr[0]) != EOF)
		{// "EOF"��ǂݍ��ނ܂� 

			if (strstr(&aStr[0], "IPADDRESS") != NULL)
			{
				fscanf(pFile, "%s", &aStr[0]);
				fscanf(pFile, "%s", &m_nIpAddress[0]);
			}

			if (strstr(&aStr[0], "PORT_NUM") != NULL)
			{
				fscanf(pFile, "%s", &aStr[0]);
				fscanf(pFile, "%d", &m_nPortNum);
			}
		}
	}
	else
	{
		printf("�t�@�C���ǂݍ��ݎ��s\n");
	}
}

//=============================================================================
// �����L���O�X�R�A�̐ݒ�
// Author : �������l
// �T�v : �����L���O�X�R�A�̐ݒ���s��
//=============================================================================
void CRanking::SetScoreNomber()
{
	for (int nCntRank = 0; nCntRank < m_nMaxRanking; nCntRank++)
	{
		m_pScore[nCntRank]->SetDestScore(m_aRankingData[nCntRank]);
		m_pScore[nCntRank]->SetScore(m_aRankingData[nCntRank]);
	}
}

//=============================================================================
// �����L���O�X�R�A�̓_�ŏ���
// Author : �������l
// �T�v : �����L���O�X�R�A��_�ł�����
//=============================================================================
void CRanking::FlashScore()
{
	if (m_UpdateRank >= 0)
	{
		m_fAddAlpha += 0.5f;
		m_pScore[m_UpdateRank]->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.2f, sinf(m_fAddAlpha) * 3.0f));
	}
}

//=============================================================================
// �ʐM�G���[�\������
// Author : �������l
// �T�v : �ʐM�G���[�\��������
//=============================================================================
void CRanking::SetFailObj()
{
	if (pFailObj != nullptr)
	{
		pFailObj->SetPos(m_pos);
		pFailObj->SetRot(m_rot);
	}
}
