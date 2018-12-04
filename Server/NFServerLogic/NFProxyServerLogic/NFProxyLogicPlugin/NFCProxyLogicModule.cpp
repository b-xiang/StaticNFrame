

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
	NFJson json;
	std::string errString;
	json.parse(std::string(msg, nLen), errString);

	if (errString.empty() == false)
	{
		NFLogError("json error | {}", errString);
		return;
	}
}