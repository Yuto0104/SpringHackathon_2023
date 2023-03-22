//****************************************************************************************************************
//
// �N���C�A���g��TCP����M����(tcp_client.cpp)
// Auther : �������l
// �T�v : �N���C�A���gTCP����M�N���X�̊Ǘ�
//
//****************************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "tcp_client.h"
#include <stdio.h>

//===========================================================
// �R���X�g���N�^
// Auther : �������l
// �T�v : �����o�ϐ��̃N���A������
//===========================================================
CTCPClient::CTCPClient()
{
	// �\�P�b�g�̃N���A
	m_sock = INVALID_SOCKET;

	// �A�h���X�̏�����	
	memset(&m_addr, 0, sizeof(m_addr));
}

//===========================================================
// �f�X�g���N�^
// Auther : �������l
// �T�v : 
//===========================================================
CTCPClient::~CTCPClient()
{

}

//===========================================================
// ������
// Auther : �������l
// �T�v : �\�P�b�g���쐬���A�T�[�o�[�Ɛڑ���������Ԃ�
//===========================================================
bool CTCPClient::Init(const char * pIpAddres, int nPortNum)
{
	// �\�P�b�g�̍쐬
	m_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (m_sock == INVALID_SOCKET)
	{// �\�P�b�g�쐬���s
		printf("�\�P�b�g�쐬���s\n");
		return false;
	}
	else
	{// �\�P�b�g�쐬����
		printf("�\�P�b�g�쐬����\n");
	}

	// �A�h���X�̐ݒ�
	m_addr.sin_family = AF_INET;													// IPV4�̐ݒ�
	m_addr.sin_port = htons(nPortNum);												// �|�[�g�ԍ��̐ݒ�
	m_addr.sin_addr.S_un.S_addr = inet_addr(pIpAddres);								// IP�A�h���X�̐ݒ�

	// �ڑ�����
	if (connect(m_sock, (struct sockaddr*)&m_addr, sizeof(m_addr)) != 0)
	{// �ڑ����s
		printf("�ڑ����s\n");
		return false;
	}
	else
	{// �ڑ�����
		printf("�ڑ�����\n");
		return true;
	}
}

//===========================================================
// �I�[�o�[���[�h���ꂽ������
// Auther : �������l
// �T�v : �����̃\�P�b�g�������o�ϐ��ɑ�����ANULL�`�F�b�N
//===========================================================
bool CTCPClient::Init(SOCKET sock)
{
	// �\�P�b�g�̍쐬
	m_sock = sock;

	return true;
}

//===========================================================
// ���M
// Auther : �������l
// �T�v : send�֐����g���ăT�[�o�[�Ƀf�[�^�[�𑗐M
//===========================================================
int CTCPClient::Send(char *pSendData, int nSendDataSize)
{
	if (m_sock == INVALID_SOCKET)
	{// �\�P�b�g���g�p����ĂȂ��ꍇ
		return 0;
	}
	else
	{// �\�P�b�g���g�p����Ă�
		// �Ԃ�l�p�̕ϐ��錾
		int nSendByte = 0;

		// �f�[�^�̑��M
		printf("%s�𑗐M\n", pSendData);

		// �f�[�^�𑗐M����
		nSendByte =  send(m_sock, pSendData, nSendDataSize, 0);

		return nSendByte;
	}
}

//===========================================================
// ��M
// Auther : �������l
// �T�v : recv�֐����g���ăT�[�o�[�Ƀf�[�^�[����M���A��M�ʂ�Ԃ�
//===========================================================
int CTCPClient::Recv(char *pRecvData, int nRecvDataSize)
{
	if (m_sock == INVALID_SOCKET)
	{// �\�P�b�g���g�p����ĂȂ��ꍇ
		return 0;
	}
	else
	{// �\�P�b�g���g�p����Ă�
		// �Ԃ�l�p�̕ϐ��錾
		int nRecvByte = 0;

		// �f�[�^����M����
		nRecvByte =  recv(m_sock, pRecvData, nRecvDataSize, 0);

		if (nRecvByte <= 0)
		{// 0�ȉ��̐��l����M�����ꍇ
			Uninit();
		}
		else
		{// ��M�f�[�^�̏o��
			printf("%s����M\n", pRecvData);
		}

		return nRecvByte;
	}
}

//===========================================================
// �I��
// Auther : �������l
// �T�v : �\�P�b�g�̉�����s��
//===========================================================
void CTCPClient::Uninit(void)
{
	if (m_sock == INVALID_SOCKET)
	{
		return;
	}
	else
	{
		// �\�P�b�g���������
		closesocket(m_sock);
		m_sock = INVALID_SOCKET;
		printf("�ڑ����ؒf����܂���\n");
	}
}
