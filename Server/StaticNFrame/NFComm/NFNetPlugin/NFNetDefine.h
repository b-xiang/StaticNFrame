// -------------------------------------------------------------------------
//    @FileName         :    NFNetDefine.h
//    @Author           :    GaoYi
//    @Date             :    2018/05/25
//    @Email			:    445267987@qq.com
//    @Module           :    NFNetPlugin
//
// -------------------------------------------------------------------------
#pragma once

#include <stdint.h>
#include <string>
#include "NFComm/NFCore/NFPlatform.h"
#include "NFComm/NFCore/NFSimpleBuffer.h"
#include "NFComm/NFCore/NFDataStream.h"
#include "NFComm/NFPluginModule/NFServerDefine.h"

#if NF_PLATFORM == NF_PLATFORM_WIN
#include <winsock2.h>
#include <windows.h>
#include <Ws2tcpip.h>
#else
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <unistd.h>
#include <netinet/tcp.h>
#endif

#if NF_PLATFORM == NF_PLATFORM_WIN
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

enum eConnectStatus
{
	eConnectStatus_Disconnect, //断开连接
	eConnectStatus_Connecting, //连接中
	eConnectStatus_ConnectOk, //连接OK
	eConnectStatus_RECONNECT, //断开连接
	eConnectStatus_REMOVE, //删除
};

enum eWebSocketFrameType {
	ERROR_FRAME = 0xff,
	CONTINUATION_FRAME = 0x00,
	TEXT_FRAME = 0x01,
	BINARY_FRAME = 0x02,
	CLOSE_FRAME = 0x08,
	PING_FRAME = 0x09,
	PONG_FRAME = 0x0A
};

struct stMsgFlag
{
	uint32_t nInitRcvBufSZ; //接受消息的缓冲区初始值
	//uint32		nMaxRcvBufSZ;			//接受消息的缓冲区最大值
	uint32_t nMaxRcvMsgSZ; //接受消息包的最大值
	uint32_t nInitSendBufSZ; //接受消息的缓冲区初始值
	uint32_t nMaxCacheSize; //最大缓存大小

	stMsgFlag()
	{
		nInitRcvBufSZ = 1024 * 4;
		nInitSendBufSZ = 1024 * 100;
		nMaxRcvMsgSZ = 1024 * 100;
		nMaxCacheSize = 0;
	}
};

struct NFServerFlag
{
	uint32_t nMaxConnectNum; //最大链接数
	uint32_t nInitConnectNum; //初始链接个数
	uint32_t nWorkThreadNum; //工作线程个数
	uint16_t nPort; //端口
	bool bEncrypt; //是否加密
	bool bWebSocket; //是否是websocket
	uint32_t nMaxMsgNumMinPer; //每一分钟最大的消息包数
	uint32_t nTimeoutDisconnect; //超时断开连接断开连接
	NFServerFlag()
	{
		nInitConnectNum = 10;
		nWorkThreadNum = 1;
		nMaxConnectNum = 10000;
		bEncrypt = false;
		nPort = 0;
		nMaxMsgNumMinPer = 800;
		nTimeoutDisconnect = 0;
		bWebSocket = false;
	}
};

struct NFClientFlag
{
	bool bAutoConnect; //自动重连
	bool bEncrypt;
	bool bWebSocket;
	uint16_t nPort;
	std::string strIP;
	uint16_t sSuspend;
	std::string origin;

	NFClientFlag()
	{
		nPort = 0;
		bAutoConnect = false;
		bEncrypt = false;
		bWebSocket = false;
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

	uint32_t usLink; //和网络底层通信的接口
	uint32_t nMsgId;
	uint64_t nValue;
	eMsgType eType; //消息是从哪里来的
	NFSimpleBuffer nBuffer;
};

