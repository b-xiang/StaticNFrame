// -------------------------------------------------------------------------
//    @FileName         :    NFCWorldServerModule.cpp
//    @Author           :    GaoYi
//    @Date             :    2018/10/11
//    @Email			:    445267987@qq.com
//    @Module           :    NFCWorldServerModule
//
// -------------------------------------------------------------------------

#include "NFWorldServerModule.h"

#include "NFComm/NFPluginModule/NFIPluginManager.h"
#include <NFComm/NFPluginModule/NFConfigMgr.h>
#include "NFComm/NFPluginModule/NFLogMgr.h"
#include "NFComm/NFPluginModule/NFIHttpClientModule.h"
#include "NFComm/NFPluginModule/NFIHttpServerModule.h"
#include "NFServer/NFServerCommon/NFServerCommon.h"
#include "NFMessageDefine/NFMsgDefine.h"
#include "NFComm/NFPluginModule/NFEventDefine.h"

NFCWorldServerModule::NFCWorldServerModule(NFIPluginManager* p)
{
	pPluginManager = p;
	mWorldToMasterUnlinkId = 0;
}

NFCWorldServerModule::~NFCWorldServerModule()
{
}

bool NFCWorldServerModule::Init()
{
	//���������������¼�
	Subscribe(NFEVENT_WORLD_CONNECT_MASTER_SUCCESS, 0, NF_ST_MASTER, __FUNCTION__);
	Subscribe(NFEVENT_WORLD_CONNECT_MASTER_FAIL, 0, NF_ST_MASTER, __FUNCTION__);

	m_pNetClientModule = pPluginManager->FindModule<NFINetClientModule>();
	m_pNetServerModule = pPluginManager->FindModule<NFINetServerModule>();
	m_pNetServerModule->AddEventCallBack(NF_ST_WORLD, this, &NFCWorldServerModule::OnProxySocketEvent);
	m_pNetServerModule->AddReceiveCallBack(NF_ST_WORLD, this, &NFCWorldServerModule::OnHandleOtherMessage);

	m_pNetServerModule->AddReceiveCallBack(NF_ST_WORLD, EGMI_NET_PROXY_TO_WORLD_REGISTER, this, &NFCWorldServerModule::OnProxyServerRegisterProcess);
	m_pNetServerModule->AddReceiveCallBack(NF_ST_WORLD, EGMI_NET_GAME_TO_WORLD_REGISTER, this, &NFCWorldServerModule::OnGameServerRegisterProcess);

	m_pNetServerModule->AddReceiveCallBack(NF_ST_WORLD, EGMI_NET_PROXY_TO_WORLD_UNREGISTER, this, &NFCWorldServerModule::OnProxyServerUnRegisterProcess);
	m_pNetServerModule->AddReceiveCallBack(NF_ST_WORLD, EGMI_NET_GAME_TO_WORLD_UNREGISTER, this, &NFCWorldServerModule::OnGameServerUnRegisterProcess);

	m_pNetServerModule->AddReceiveCallBack(NF_ST_WORLD, EGMI_NET_PROXY_TO_WORLD_REFRESH, this, &NFCWorldServerModule::OnProxyServerRefreshProcess);
	m_pNetServerModule->AddReceiveCallBack(NF_ST_WORLD, EGMI_NET_GAME_TO_WORLD_REFRESH, this, &NFCWorldServerModule::OnGameServerRefreshProcess);

	m_pNetServerModule->AddReceiveCallBack(NF_ST_WORLD, EGMI_STS_SERVER_REPORT, this, &NFCWorldServerModule::OnServerReport);

	NFServerConfig* pConfig = NFServerCommon::GetAppConfig(pPluginManager, NF_ST_WORLD);
	if (pConfig)
	{
		uint32_t unlinkId = m_pNetServerModule->AddServer(NF_ST_WORLD, pConfig->mServerId, pConfig->mMaxConnectNum, pConfig->mServerPort);
		if (unlinkId != 0)
		{
			NFLogInfo("world server listen success, serverId:{}, maxConnectNum:{}, port:{}", pConfig->mServerId, pConfig->mMaxConnectNum, pConfig->mServerPort);
		}
		else
		{
			NFLogInfo("world server listen failed!, serverId:{}, maxConnectNum:{}, port:{}", pConfig->mServerId, pConfig->mMaxConnectNum, pConfig->mServerPort);
		}
	}
	else
	{
		NFLogError("I Can't get the World Server config!");
		return false;
	}

	return true;
}

bool NFCWorldServerModule::AfterInit()
{
	return true;
}

bool NFCWorldServerModule::Execute()
{
	return true;
}

bool NFCWorldServerModule::BeforeShut()
{
	return true;
}

bool NFCWorldServerModule::Shut()
{
	return true;
}

void NFCWorldServerModule::OnProxySocketEvent(const eMsgType nEvent, const uint32_t unLinkId)
{
	if (nEvent == eMsgType_CONNECTED)
	{

	}
	else if (nEvent == eMsgType_DISCONNECTED)
	{
		OnClientDisconnect(unLinkId);
	}
}

void NFCWorldServerModule::OnClientDisconnect(uint32_t unLinkId)
{
	NF_SHARE_PTR<NFServerData> pServerData = mGameMap.First();
	while (pServerData)
	{
		if (unLinkId == pServerData->mUnlinkId)
		{
			pServerData->mServerInfo.set_server_state(NFMsg::EST_CRASH);
			pServerData->mUnlinkId = 0;

			NFLogError("the game server disconnect from world server, serverName:{}, serverId:{}, serverIp:{}, serverPort:{}"
				, pServerData->mServerInfo.server_name(), pServerData->mServerInfo.server_id(), pServerData->mServerInfo.server_ip(), pServerData->mServerInfo.server_port());

			SynGameToProxy();
			return;
		}

		pServerData = mGameMap.Next();
	}

	//////////////////////////////////////////////////////////////////////////

	int nServerID = 0;
	pServerData = mProxyMap.First();
	while (pServerData)
	{
		if (unLinkId == pServerData->mUnlinkId)
		{
			nServerID = pServerData->mServerInfo.server_id();

			NFLogError("the login server disconnect from master server, serverName:{}, serverId:{}, serverIp:{}, serverPort:{}"
				, pServerData->mServerInfo.server_name(), pServerData->mServerInfo.server_id(), pServerData->mServerInfo.server_ip(), pServerData->mServerInfo.server_port());
			break;
		}

		pServerData = mProxyMap.Next();
	}

	mProxyMap.RemoveElement(nServerID);
}

void NFCWorldServerModule::OnHandleOtherMessage(const uint32_t unLinkId, const uint64_t playerId, const uint32_t nMsgId, const char* msg, const uint32_t nLen)
{
	NFLogWarning("msg:{} not handled!", nMsgId);
}

void NFCWorldServerModule::OnProxyServerRegisterProcess(const uint32_t unLinkId, const uint64_t playerId, const uint32_t nMsgId, const char* msg, const uint32_t nLen)
{
	NFMsg::ServerInfoReportList xMsg;                                           
	CLIENT_MSG_PROCESS_NO_OBJECT(nMsgId, msg, nLen, xMsg);

	for (int i = 0; i < xMsg.server_list_size(); ++i)
	{
		const NFMsg::ServerInfoReport& xData = xMsg.server_list(i);

		NF_SHARE_PTR<NFServerData> pServerData = mProxyMap.GetElement(xData.server_id());
		if (!pServerData)
		{
			pServerData = NF_SHARE_PTR<NFServerData>(NF_NEW NFServerData());
			mProxyMap.AddElement(xData.server_id(), pServerData);
		}

		pServerData->mUnlinkId = unLinkId;
		pServerData->mServerInfo = xData;

		SynGameToProxy(unLinkId);

		NFLogInfo("Proxy Server Register World Server Success, serverName:{}, serverId:{}, ip:{}, port:{}", xData.server_name(), xData.server_id(), xData.server_ip(), xData.server_port())
	}
}

void NFCWorldServerModule::OnProxyServerUnRegisterProcess(const uint32_t unLinkId, const uint64_t playerId, const uint32_t nMsgId, const char* msg, const uint32_t nLen)
{
	NFMsg::ServerInfoReportList xMsg;
	CLIENT_MSG_PROCESS_NO_OBJECT(nMsgId, msg, nLen, xMsg);

	for (int i = 0; i < xMsg.server_list_size(); ++i)
	{
		const NFMsg::ServerInfoReport& xData = xMsg.server_list(i);

		mProxyMap.RemoveElement(xData.server_id());

		NFLogInfo("Proxy Server UnRegister World Server Success, serverName:{}, serverId:{}, ip:{}, port:{}", xData.server_name(), xData.server_id(), xData.server_ip(), xData.server_port())
	}
}

void NFCWorldServerModule::OnProxyServerRefreshProcess(const uint32_t unLinkId, const uint64_t playerId, const uint32_t nMsgId, const char* msg, const uint32_t nLen)
{
	NFMsg::ServerInfoReportList xMsg;
	CLIENT_MSG_PROCESS_NO_OBJECT(nMsgId, msg, nLen, xMsg);

	for (int i = 0; i < xMsg.server_list_size(); ++i)
	{
		const NFMsg::ServerInfoReport& xData = xMsg.server_list(i);

		NF_SHARE_PTR<NFServerData> pServerData = mProxyMap.GetElement(xData.server_id());
		if (!pServerData)
		{
			pServerData = NF_SHARE_PTR<NFServerData>(NF_NEW NFServerData());
			mProxyMap.AddElement(xData.server_id(), pServerData);
		}

		pServerData->mUnlinkId = unLinkId;
		pServerData->mServerInfo = xData;

		SynGameToProxy(unLinkId);

		//NFLogInfo("Proxy Server Refresh World Server Success, serverName:{}, serverId:{}, ip:{}, port:{}", xData.server_name(), xData.server_id(), xData.server_ip(), xData.server_port());
	}
}

void NFCWorldServerModule::OnGameServerUnRegisterProcess(const uint32_t unLinkId, const uint64_t playerId, const uint32_t nMsgId, const char* msg, const uint32_t nLen)
{
	NFMsg::ServerInfoReportList xMsg;
	CLIENT_MSG_PROCESS_NO_OBJECT(nMsgId, msg, nLen, xMsg);

	for (int i = 0; i < xMsg.server_list_size(); ++i)
	{
		const NFMsg::ServerInfoReport& xData = xMsg.server_list(i);

		mGameMap.RemoveElement(xData.server_id());

		NFLogInfo("Game Server UnRegister World Server Success, serverName:{}, serverId:{}, ip:{}, port:{}", xData.server_name(), xData.server_id(), xData.server_ip(), xData.server_port());
	}
}

void NFCWorldServerModule::OnGameServerRefreshProcess(const uint32_t unLinkId, const uint64_t playerId, const uint32_t nMsgId, const char* msg, const uint32_t nLen)
{
	NFMsg::ServerInfoReportList xMsg;
	CLIENT_MSG_PROCESS_NO_OBJECT(nMsgId, msg, nLen, xMsg);

	for (int i = 0; i < xMsg.server_list_size(); ++i)
	{
		const NFMsg::ServerInfoReport& xData = xMsg.server_list(i);
		NF_SHARE_PTR<NFServerData> pServerData = mGameMap.GetElement(xData.server_id());
		if (!pServerData)
		{
			pServerData = NF_SHARE_PTR<NFServerData>(NF_NEW NFServerData());
			mGameMap.AddElement(xData.server_id(), pServerData);
		}

		pServerData->mUnlinkId = unLinkId;
		pServerData->mServerInfo = xData;

		//NFLogInfo("Game Server Refresh World Server Success, serverName:{}, serverId:{}, ip:{}, port:{}", xData.server_name(), xData.server_id(), xData.server_ip(), xData.server_port());
	}
	SynGameToProxy();
}

void NFCWorldServerModule::OnGameServerRegisterProcess(const uint32_t unLinkId, const uint64_t playerId, const uint32_t nMsgId, const char* msg, const uint32_t nLen)
{
	NFMsg::ServerInfoReportList xMsg;
	CLIENT_MSG_PROCESS_NO_OBJECT(nMsgId, msg, nLen, xMsg);

	for (int i = 0; i < xMsg.server_list_size(); ++i)
	{
		const NFMsg::ServerInfoReport& xData = xMsg.server_list(i);
		NF_SHARE_PTR<NFServerData> pServerData = mGameMap.GetElement(xData.server_id());
		if (!pServerData)
		{
			pServerData = NF_SHARE_PTR<NFServerData>(NF_NEW NFServerData());
			mGameMap.AddElement(xData.server_id(), pServerData);
		}

		pServerData->mUnlinkId = unLinkId;
		pServerData->mServerInfo = xData;

		NFLogInfo("Game Server Register World Server Success, serverName:{}, serverId:{}, ip:{}, port:{}", xData.server_name(), xData.server_id(), xData.server_ip(), xData.server_port());
	}
	SynGameToProxy();
}

void NFCWorldServerModule::SynGameToProxy()
{
	NFMsg::ServerInfoReportList xData;

	NF_SHARE_PTR<NFServerData> pServerData = mProxyMap.First();
	while (pServerData)
	{
		SynGameToProxy(pServerData->mUnlinkId);

		pServerData = mProxyMap.Next();
	}
}

void NFCWorldServerModule::SynGameToProxy(uint32_t linkId)
{
	if (mGameMap.Count() <= 0) return;

	NFMsg::ServerInfoReportList xData;

	NF_SHARE_PTR<NFServerData> pServerData = mGameMap.First();
	while (pServerData)
	{
		NFMsg::ServerInfoReport* pData = xData.add_server_list();
		*pData = pServerData->mServerInfo;

		pServerData = mGameMap.Next();
	}

	m_pNetServerModule->SendToServerByPB(linkId, EGMI_NET_WORLD_TO_PROXY_SEND_GAME, xData, 0);
}

void NFCWorldServerModule::OnExecute(uint16_t nEventID, uint64_t nSrcID, uint8_t bySrcType, NFEventContext* pEventContext)
{
	if (nEventID == NFEVENT_WORLD_CONNECT_MASTER_SUCCESS)
	{
		mWorldToMasterUnlinkId = (uint32_t)nSrcID;
	}
	else if (nEventID == NFEVENT_WORLD_CONNECT_MASTER_FAIL)
	{
		mWorldToMasterUnlinkId = 0;
	}
}

void NFCWorldServerModule::OnServerReport(const uint32_t unLinkId, const uint64_t playerId, const uint32_t nMsgId, const char* msg, const uint32_t nLen)
{
	NFMsg::ServerInfoReportList xMsg;
	CLIENT_MSG_PROCESS_NO_OBJECT(nMsgId, msg, nLen, xMsg);

	m_pNetClientModule->SendToServerByPB(mWorldToMasterUnlinkId, EGMI_STS_SERVER_REPORT, xMsg, 0);
}
