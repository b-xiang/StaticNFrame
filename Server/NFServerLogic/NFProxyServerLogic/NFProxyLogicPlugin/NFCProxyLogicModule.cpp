

#include "NFCProxyLogicModule.h"
#include "NFComm/NFPluginModule/NFEventDefine.h"
#include "NFComm/NFPluginModule/NFIPluginManager.h"
#include "NFServer/NFServerCommon/NFServerCommon.h"
#include "NFComm/NFCore/NFJson.h"

NFCProxyLogicModule::NFCProxyLogicModule(NFIPluginManager* p)
{
	pPluginManager = p;
}

NFCProxyLogicModule::~NFCProxyLogicModule()
{

}

bool NFCProxyLogicModule::Init()
{
	//���������������¼�
	Subscribe(NFEVENT_PROXY_CONNECT_WORLD_SUCCESS, 0, NF_ST_WORLD, __FUNCTION__);
	Subscribe(NFEVENT_PROXY_CONNECT_WORLD_FAIL, 0, NF_ST_WORLD, __FUNCTION__);

	m_pNetServerModule = pPluginManager->FindModule<NFINetServerModule>();
	m_pNetClientModule = pPluginManager->FindModule<NFINetClientModule>();
	m_pProxyClient_GameModule = pPluginManager->FindModule<NFIProxyClient_GameModule>();

	m_pNetServerModule->AddEventCallBack(NF_ST_PROXY, this, &NFCProxyLogicModule::OnProxySocketEvent);
	m_pNetServerModule->AddReceiveCallBack(NF_ST_PROXY, EGMI_NET_MSG_JSON_MSG, this, &NFCProxyLogicModule::OnHandleJsonMessage);
	return true;
}

bool NFCProxyLogicModule::AfterInit()
{
	return true;
}

bool NFCProxyLogicModule::Execute()
{
	return true;
}

bool NFCProxyLogicModule::BeforeShut()
{
	return true;
}

bool NFCProxyLogicModule::Shut()
{
	return true;
}

void NFCProxyLogicModule::OnExecute(uint16_t nEventID, uint64_t nSrcID, uint8_t bySrcType, NFEventContext* pEventContext)
{
	if (nEventID == NFEVENT_PROXY_CONNECT_GAME_SUCCESS)
	{
		//m_gameServerUnlinkId = (uint32_t)nSrcID;
	}
	else if (nEventID == NFEVENT_PROXY_CONNECT_GAME_FAIL)
	{
		//m_gameServerUnlinkId = 0;
	}
	else if (nEventID == NFEVENT_PROXY_CONNECT_WORLD_SUCCESS)
	{
		m_worldServerUnlinkId = (uint32_t)nSrcID;
	}
	else if (nEventID == NFEVENT_PROXY_CONNECT_WORLD_FAIL)
	{
		m_worldServerUnlinkId = 0;
	}
}

void NFCProxyLogicModule::OnHandleJsonMessage(const uint32_t unLinkId, const uint64_t playerId, const uint32_t nMsgId, const char* msg, const uint32_t nLen)
{
	NFMsg::ProxyCmdMessage cmdMessage;
	std::string jsonMsg = std::string(msg, nLen);
	if (NFServerCommon::JsonStringToMessage(jsonMsg, cmdMessage) == false)
	{
		return;
	}

	if (cmdMessage.cmd_name() == "Pmd.UserLoginTokenLoginUserPmd_C")
	{
		NFMsg::UserLoginTokenLoginUserPmd_C msg;
		if (NFServerCommon::JsonStringToMessage(jsonMsg, msg) == false)
		{
			return;
		}
		OnHandleUser_LoginTokenLoginUserPmd(unLinkId, msg);
	}
	else if (cmdMessage.cmd_name() == "Pmd.UserJsMessageForwardUserPmd_CS")
	{
		NFMsg::UserJsMessageForwardUserPmd_CS msg;
		if (NFServerCommon::JsonStringToMessage(jsonMsg, msg) == false)
		{
			return;
		}
		OnHandleUser_UserJsMessageForwardUserPmd(unLinkId, msg);
	}
	NFLogWarning("msg:{} not handled!", cmdMessage.cmd_name());
	NFLogWarning("{}", jsonMsg);
}

void NFCProxyLogicModule::OnHandleUser_UserJsMessageForwardUserPmd(const uint32_t unLinkId, const NFMsg::UserJsMessageForwardUserPmd_CS& msg)
{
	ProxyPlayerData* pData = GetPlayerDataByLinkId(unLinkId);
	if (pData == nullptr)
	{
		NFLogError("Can't find player data, unLinkId:{}", unLinkId);
		return;
	}

	auto pServerData = m_pProxyClient_GameModule->GetServerData(pData->gameServerId);
	m_pNetClientModule->SendByServerID(pServerData->mUnlinkId, 0, msg.msg(), pData->uid);
}

void NFCProxyLogicModule::OnHandleUser_LoginTokenLoginUserPmd(const uint32_t unLinkId, const NFMsg::UserLoginTokenLoginUserPmd_C& msg)
{
	ProxyPlayerData* pData = GetPlayerDataByLinkId(unLinkId);
	if (pData == nullptr)
	{
		pData = NF_NEW ProxyPlayerData();
		pData->uid = msg.accountid();
		pData->gameServerId = msg.zoneid();
		mUnlinkIdPlayerData.AddElement(unLinkId, pData);
	}

	auto pPlayerData = GetPlayerData(msg.accountid());
	if (pPlayerData == nullptr)
	{
		mPlayerData.AddElement(msg.accountid(), pData);
	}

	pData->unlinkId = unLinkId;

	auto pServerData = m_pProxyClient_GameModule->GetServerData(pData->gameServerId);
	if (pServerData == nullptr) return;

	std::string ip = m_pNetServerModule->GetLinkIp(unLinkId);
	NFMsg::AccountConnectGameServer_C account;
	account.set_uid(pData->uid);
	account.set_ip(ip);
	
	m_pNetClientModule->SendToServerByPB(pServerData->mUnlinkId, EGMI_NET_PROXY_TO_GAME_ACCOUNT_CONNECT, account, pData->uid);
}

void NFCProxyLogicModule::OnProxySocketEvent(const eMsgType nEvent, const uint32_t unLinkId)
{
	if (nEvent == eMsgType_CONNECTED)
	{

	}
	else if (nEvent == eMsgType_DISCONNECTED)
	{
		OnAccountDisconnect(unLinkId);
	}
}

void NFCProxyLogicModule::OnAccountDisconnect(const uint32_t unLinkId)
{
	ProxyPlayerData* pData = GetPlayerDataByLinkId(unLinkId);
	if (pData)
	{
		mUnlinkIdPlayerData.RemoveElement(unLinkId);

		auto pServerData = m_pProxyClient_GameModule->GetServerData(pData->gameServerId);
		if (pServerData == nullptr) return;

		std::string ip = m_pNetServerModule->GetLinkIp(unLinkId);
		NFMsg::AccountConnectGameServer_C account;
		account.set_uid(pData->uid);

		m_pNetClientModule->SendToServerByPB(pServerData->mUnlinkId, EGMI_NET_PROXY_TO_GAME_ACCOUNT_DISCONNECT, account, pData->uid);
	}
}