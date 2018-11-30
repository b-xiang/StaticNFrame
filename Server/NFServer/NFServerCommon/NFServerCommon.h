// -------------------------------------------------------------------------
//    @FileName         :    NFServerCommon.h
//    @Author           :    GaoYi
//    @Date             :    2018/06/11
//    @Email			:    445267987@qq.com
//    @Module           :    NFServerCommon
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFPluginModule/NFConfigMgr.h"
#include "NFMessageDefine/NFMsgDefine.h"

class NFServerCommon
{
public:
	static NFServerConfig* GetServerConfig(NFIPluginManager* pPluginManager, NF_SERVER_TYPES eServerType);
};

class NFProxyData
{
public:
	NFProxyData()
	{
		mServerId = 0;
		mLinkId = 0;
	}

	uint32_t mServerId;
	uint32_t mLinkId;

	virtual void print() { }
};

//������֮����ڲ�Э���1-1000, ���漰ҵ��
enum NF_EGMI_MsgId
{
	EGMI_NET_MSG_BEGIN = 0,

	//0��Э���������JSONЭ��,������JSON�ַ���
	EGMI_NET_MSG_JSON_MSG = 0,
	//1��Э���Ƿ������ڴ�����Э��
	EGMI_NET_MSG_HEART_KEEP_ALIVE = 1,

	////////////////////////////////////////////
	
	EGMI_NET_PROXY_TO_WORLD_REGISTER = 11,	//���ط�����ע�����������Э��
	EGMI_NET_GAME_TO_WORLD_REGISTER = 12,	//��Ϸ������ע�����������Э��
	EGMI_NET_LOGIN_TO_MASTER_REGISTER = 13,	//��¼������ע��MASTER������Э��
	EGMI_NET_WORLD_TO_MASTER_REGISTER = 14,	//���������ע��MASTER������Э��

	EGMI_NET_PROXY_TO_GAME_REGISTER = 14,	//���ط�����ע����Ϸ������Э��

	EGMI_NET_MSG_END = 1000,
};

//////////////////////////////////////////////////////////////////////////
class NFServerData
{
	NFServerData()
	{
		mUnlinkId = 0;
	}

	~NFServerData()
	{
		mUnlinkId = 0;
	}

	uint32_t mUnlinkId;
	NFMsg::ServerInfoReport pData;
};