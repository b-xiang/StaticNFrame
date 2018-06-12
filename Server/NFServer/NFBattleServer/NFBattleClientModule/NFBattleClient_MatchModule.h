// -------------------------------------------------------------------------
//    @FileName         :    NFBattleClient_MatchModule.h
//    @Author           :    GaoYi
//    @Date             :    2018/06/11
//    @Email			:    445267987@qq.com
//    @Module           :    NFBattleClientModule
//
// -------------------------------------------------------------------------

#pragma once

#include "NFServer/NFServerCommon/NFIBattleClient_MatchModule.h"
#include <NFComm/NFPluginModule/NFINetClientModule.h>

enum eMsgType;

class NFCBattleClient_MatchModule : public NFIBattleClient_MatchModule
{
public:
	/**
	 * @brief ���캯��
	 */
	explicit NFCBattleClient_MatchModule(NFIPluginManager* p);

	/**
	 * @brief ��������
	 */
	virtual ~NFCBattleClient_MatchModule();

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
protected:
	/**
	 * @brief ��������
	 *
	 * @param  unLinkId
	 * @return void 
	 */
	void OnHandleConnected(const uint32_t unLinkId);

	/**
	 * @brief �������ӶϿ�
	 *
	 * @param  unLinkId
	 * @return void 
	 */
	void OnHnadleDisConnected(const uint32_t unLinkId);
private:
	NFINetClientModule* m_pNetClientModule;
	uint32_t mMatchServerUnlinkId;
};
