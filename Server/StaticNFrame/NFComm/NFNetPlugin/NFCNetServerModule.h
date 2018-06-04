// -------------------------------------------------------------------------
//    @FileName         :    NFCNetServerModule.h
//    @Author           :    GaoYi
//    @Date             :    2017-10-16
//    @Module           :    NFCNetServerModule
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFPluginModule/NFINetServerModule.h"
#include "NFComm/NFPluginModule/NFIPluginManager.h"
#include "NFServer.h"

class NFCNetServerModule : public NFINetServerModule
{
public:
    /**
     * @brief ���캯��
     */
    NFCNetServerModule(NFIPluginManager* p);

    /**
     * @brief ��������
     */
	virtual ~NFCNetServerModule();

    /**
     * @brief
     *
     * @return bool 
     */
    virtual bool Init() override;

    /**
     * @brief
     *
     * @return bool 
     */
    virtual bool AfterInit() override;

    /**
     * @brief
     *
     * @return bool 
     */
    virtual bool BeforeShut() override;

    /**
     * @brief
     *
     * @return bool 
     */
    virtual bool Shut() override;

	/**
	 * @brief �ͷ�����
	 *
	 * @return bool 
	 */
	virtual bool Finalize() override;

    /**
     * @brief
     *
     * @return bool 
     */
    virtual bool Execute() override;

    /**
     * @brief ��ӷ�����
     *
     * @param  eType		����������
     * @param  nServerID	������ID
     * @param  nMaxClient	������������ӿͻ�����
     * @param  nPort		�����������˿�
     * @return int			����0����
     */
    virtual uint32_t AddServer(const NF_SERVER_TYPES eType, uint32_t nServerID, uint32_t nMaxClient, uint32_t nPort) override;

	/**
	 * @brief
	 *
	 * @param  nServerID
	 * @return void 
	 */
	virtual void CloseServer(const uint32_t nServerID) override;

	/**
	 * @brief
	 *
	 * @param  eServerType
	 * @return void 
	 */
	virtual void CloseServerByServerType(NF_SERVER_TYPES eServerType) override;

	/**
	 * @brief
	 *
	 * @return void 
	 */
	virtual void CloseAllServer() override;

	/**
	 * @brief
	 *
	 * @param  eServerType
	 * @param  nMsgID
	 * @param  strData
	 * @param  nPlayerID
	 * @return void 
	 */
	virtual void SendByServerID(NF_SERVER_TYPES eServerType, const uint32_t nMsgID, const std::string& strData, const uint64_t nPlayerID) override;

	/**
	 * @brief
	 *
	 * @param  eServerType
	 * @param  nMsgID
	 * @param  msg
	 * @param  nLen
	 * @param  nPlayerID
	 * @return void 
	 */
	virtual void SendByServerID(NF_SERVER_TYPES eServerType, const uint32_t nMsgID, const char* msg, const uint32_t nLen, const uint64_t nPlayerID) override;

	/**
	 * @brief
	 *
	 * @param  eServerType
	 * @param  nMsgID
	 * @param  xData
	 * @param  nPlayerID
	 * @return void 
	 */
	virtual void SendToServerByPB(NF_SERVER_TYPES eServerType, const uint32_t nMsgID, const google::protobuf::Message& xData, const uint64_t nPlayerID) override;

	/**
	 * @brief
	 *
	 * @param  eServerType
	 * @param  strData
	 * @param  nPlayerID
	 * @return void 
	 */
	virtual void SendToAllServer(NF_SERVER_TYPES eServerType, const std::string& strData, const uint64_t nPlayerID) override;

	/**
	 * @brief
	 *
	 * @param  eServerType
	 * @param  msg
	 * @param  nLen
	 * @param  nPlayerID
	 * @return void 
	 */
	virtual void SendToAllServer(NF_SERVER_TYPES eServerType, const char* msg, const uint32_t nLen, const uint64_t nPlayerID) override;

	/**
	 * @brief
	 *
	 * @param  eServerType
	 * @param  xData
	 * @param  nPlayerID
	 * @return void 
	 */
	virtual void SendToAllServerByPB(NF_SERVER_TYPES eServerType, const google::protobuf::Message& xData, const uint64_t nPlayerID) override;

	/**
	 * @brief
	 *
	 * @param  eServerType
	 * @param  nMsgID
	 * @param  strData
	 * @param  nPlayerID
	 * @return void 
	 */
	virtual void SendToAllServer(NF_SERVER_TYPES eServerType, uint32_t nMsgID, const std::string& strData, const uint64_t nPlayerID) override;

	/**
	 * @brief
	 *
	 * @param  eServerType
	 * @param  nMsgID
	 * @param  msg
	 * @param  nLen
	 * @param  nPlayerID
	 * @return void 
	 */
	virtual void SendToAllServer(NF_SERVER_TYPES eServerType, const uint32_t nMsgID, const char* msg, const uint32_t nLen, const uint64_t nPlayerID) override;

	/**
	 * @brief
	 *
	 * @param  eServerType
	 * @param  nMsgID
	 * @param  xData
	 * @param  nPlayerID
	 * @return void 
	 */
	virtual void SendToAllServerByPB(NF_SERVER_TYPES eServerType, const uint32_t nMsgID, const google::protobuf::Message& xData, const uint64_t nPlayerID) override;
private:
	std::vector<NFServer*> mServerArray;
};

