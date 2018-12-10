// -------------------------------------------------------------------------
//    @FileName         :    NFServerCommon.h
//    @Author           :    GaoYi
//    @Date             :    2018/06/11
//    @Email			:    445267987@qq.com
//    @Module           :    NFServerCommon
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFCore/NFPlatform.h"
#include "NFComm/NFPluginModule/NFConfigMgr.h"
#include "NFMessageDefine/NFMsgDefine.h"

class NFServerCommon
{
public:
	static NFServerConfig* GetServerConfig(NFIPluginManager* pPluginManager, NF_SERVER_TYPES eServerType);
	static NFServerConfig* GetAppConfig(NFIPluginManager* pPluginManager, NF_SERVER_TYPES eServerType);

	static bool MessageToJsonString(const google::protobuf::Message& message, std::string& json);
	static bool JsonStringToMessage(const string& json, google::protobuf::Message& message);
};

class NFProxyData
{
public:
	NFProxyData()
	{
		mUnlinkId = 0;
	}

	uint32_t mUnlinkId;
	NFMsg::ServerInfoReport mServerInfo;
};

//������֮����ڲ�Э���1-1000, ���漰ҵ��
enum NF_EGMI_MsgId
{
	EGMI_NET_MSG_BEGIN = 0,

	//0��Э���������JSONЭ��,������JSON�ַ���
	EGMI_NET_MSG_JSON_MSG = 0,
	//1��Э���Ƿ������ڴ�����Э��
	EGMI_STS_HEART_BEAT = 1,

	EGMI_STS_SERVER_REPORT = 2,
	////////////////////////////////////////////
	
	EGMI_NET_PROXY_TO_WORLD_REGISTER = 11,	//���ط�����	ע��	���������Э��
	EGMI_NET_GAME_TO_WORLD_REGISTER = 12,	//��Ϸ������	ע��	���������Э��
	EGMI_NET_LOGIN_TO_MASTER_REGISTER = 13,	//��¼������	ע��	MASTER������Э��
	EGMI_NET_WORLD_TO_MASTER_REGISTER = 14,	//���������	ע��	MASTER������Э��
	EGMI_NET_PROXY_TO_GAME_REGISTER = 15,	//���ط�����	ע��	��Ϸ������Э��

	EGMI_NET_PROXY_TO_WORLD_UNREGISTER = 16,	//���ط����� ע��  ���������Э��
	EGMI_NET_GAME_TO_WORLD_UNREGISTER = 17,	//��Ϸ������	ע��	���������Э��
	EGMI_NET_LOGIN_TO_MASTER_UNREGISTER = 18,	//��¼������	ע��	MASTER������Э��
	EGMI_NET_WORLD_TO_MASTER_UNREGISTER = 19,	//���������	ע��	MASTER������Э��
	EGMI_NET_PROXY_TO_GAME_UNREGISTER = 20,	//���ط�����	ע��	��Ϸ������Э��

	EGMI_NET_PROXY_TO_WORLD_REFRESH = 21,	//���ط����� ˢ��  ���������Э��
	EGMI_NET_GAME_TO_WORLD_REFRESH = 22,	//��Ϸ������	ˢ��	���������Э��
	EGMI_NET_LOGIN_TO_MASTER_REFRESH = 23,	//��¼������	ˢ��	MASTER������Э��
	EGMI_NET_WORLD_TO_MASTER_REFRESH = 24,	//���������	ˢ��	MASTER������Э��
	EGMI_NET_PROXY_TO_GAME_REFRESH = 25,	//���ط�����	ˢ��	��Ϸ������Э��

	EGMI_NET_WORLD_TO_PROXY_SEND_GAME = 26, //���������������Ϸ��������Ϣ�����ط�����
	EGMI_NET_MASTER_TO_LOGIN_SEND_WORLD = 26, //Master����������World��������Ϣ��Login������

	EGMI_NET_PROXY_TO_GAME_ACCOUNT_CONNECT = 50, //proxy ���� �˺���������
	EGMI_NET_PROXY_TO_GAME_ACCOUNT_DISCONNECT = 50, //proxy ���� �˺���������
	EGMI_NET_MSG_END = 1000,
};

//////////////////////////////////////////////////////////////////////////
class NFServerData
{
public:
	NFServerData()
	{
		mUnlinkId = 0;
	}

	~NFServerData()
	{
		mUnlinkId = 0;
	}

	uint32_t mUnlinkId;
	NFMsg::ServerInfoReport mServerInfo;
};