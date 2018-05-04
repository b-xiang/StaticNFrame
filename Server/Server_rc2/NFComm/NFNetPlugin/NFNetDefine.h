#pragma once

#include <stdint.h>
#include <string>
#include "NFComm/NFCore/NFSimpleBuffer.h"
#include "NFComm/NFCore/NFDataStream.h"
#include "NFComm/NFPluginModule/NFServerDefine.h"

#ifndef _WIN32
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <unistd.h>
#include <netinet/tcp.h>
#else
#include <winsock2.h>
#include <windows.h>
#include <Ws2tcpip.h>
#endif


#ifdef _WIN32
#define ArkGetLastError		    WSAGetLastError
typedef int Socklen_t;
#define WIN32_LEAN_AND_MEAN
#else
#define SOCKET				int
#define ArkGetLastError()	errno
#define closesocket			close
#define ioctlsocket			ioctl
typedef struct linger 		    LINGER;
#define SOCKET_ERROR		-1
#define INVALID_SOCKET		-1
#define SD_SEND				SHUT_WR
#endif

#define MAX_SEND_BUFFER_SIZE (1024 * 100)
#define MAX_RECV_BUFFER_SIZE (1024 * 100)

struct stMsgFlag
{
	uint32_t		nInitRcvBufSZ;			//������Ϣ�Ļ�������ʼֵ
	//uint32		nMaxRcvBufSZ;			//������Ϣ�Ļ��������ֵ
	uint32_t		nMaxRcvMsgSZ;			//������Ϣ�������ֵ
	uint32_t		nInitSendBufSZ;			//������Ϣ�Ļ�������ʼֵ
	uint32_t		nMaxCacheSize;             //��󻺴��С

	stMsgFlag() {
		nInitRcvBufSZ = 1024 * 4;
		nInitSendBufSZ = 1024 * 100;
		nMaxRcvMsgSZ = 1024 * 100;
		nMaxCacheSize = 0;
	}
};

struct stServerFlag
{
	stMsgFlag			flag;
	uint32_t			nMaxConnectNum;   //���������
	uint32_t			nInitConnectNum;  //��ʼ���Ӹ���
	uint32_t			nWorkThreadNum;   //�����̸߳���
	uint16_t			nPort;            //�˿�
	bool				bEncrypt;		  //�Ƿ����
	uint32_t			nMaxMsgNumMinPer; //ÿһ����������Ϣ����
	uint32_t			nTimeoutDisconnect;  //��ʱ�Ͽ����ӶϿ�����
	stServerFlag()
	{
		nInitConnectNum = 10;
		nWorkThreadNum = 1;
		nMaxConnectNum = 10000;
		bEncrypt = false;
		nPort = 0;
		nMaxMsgNumMinPer = 800;
		nTimeoutDisconnect = 0;
	}
};

struct stClientFlag
{
	stMsgFlag		flag;
	bool			bAutoConnect; //�Զ�����
	bool			bEncrypt;
	uint16_t		nPort;
	std::string		strIP;
	uint16_t		sSuspend;
	stClientFlag() {
		nPort = 0;
		bAutoConnect = false;
		bEncrypt = false;
		sSuspend = 0;
	}
};

class NFThreadNetMsg
{
public:
	NFThreadNetMsg()
	{
		usLink = 0;
		eType = eMsgType_Num;
		nMsgId = 0;
		nValue = 0;
	}

	uint32_t	usLink;       //������ײ�ͨ�ŵĽӿ�
	uint32_t	nMsgId;
	uint64_t	nValue;
	eMsgType	eType;       //��Ϣ�Ǵ���������
	NFSimpleBuffer nBuffer;
};