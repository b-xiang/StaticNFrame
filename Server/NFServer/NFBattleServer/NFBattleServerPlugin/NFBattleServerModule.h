// -------------------------------------------------------------------------
//    @FileName         :    NFBattleServerModule.h
//    @Author           :    GaoYi
//    @Date             :    2018/06/11
//    @Email			:    445267987@qq.com
//    @Module           :    
//
// -------------------------------------------------------------------------

#pragma once

#include "NFServer/NFServerCommon/NFIBattleServerModule.h"

enum eMsgType;
class NFIPluginManager;
class NFINetServerModule;

class NFCBattleServerModule : public NFIBattleServerModule
{
public:
	/**
	 * @brief ���캯��
	 */
	explicit NFCBattleServerModule(NFIPluginManager* p);

	/**
	 * @brief ��������
	 */
	virtual ~NFCBattleServerModule();

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
	virtual bool Shut() override;

	/**
	 * @brief
	 *
	 * @return bool 
	 */
	virtual bool Execute() override;

	/**
	 * @brief BattleServer�����¼�������Ҫ�ǿͻ��˵�������Ͽ�
	 *
	 * @param  nEvent	�¼�eMsgType_CONNECTED���ӣ�eMsgType_DISCONNECTED�Ͽ�
	 * @param  unLinkId �������ӵ�ΨһID
	 * @return void 
	 */
	void OnNetSocketEvent(const eMsgType nEvent, const uint32_t unLinkId);

	/**
	 * @brief ����δע�����Ϣ
	 *
	 * @param  unLinkId
	 * @param  playerId
	 * @param  nMsgId
	 * @param  msg
	 * @param  nLen
	 * @return void 
	 */
	void OnHandleOtherMessage(const uint32_t unLinkId, const uint64_t playerId, const uint32_t nMsgId, const char* msg, const uint32_t nLen);
protected:
	/**
	 * @brief ��������
	 *
	 * @param  unLinkId
	 * @return void 
	 */
	void OnHandleConnected(const uint32_t unLinkId);

	/**
	 * @brief ����˿�
	 *
	 * @param  unLinkId
	 * @return void 
	 */
	void OnHnadleDisConnected(const uint32_t unLinkId);
private:
	NFINetServerModule* m_pNetServerModule;
};
