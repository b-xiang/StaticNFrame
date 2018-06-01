// -------------------------------------------------------------------------
//    @FileName         :    NFServer.h
//    @Author           :    GaoYi
//    @Date             :    2018/06/01
//    @Email			:    445267987@qq.com
//    @Module           :    NFNetPlugin
//
// -------------------------------------------------------------------------
#pragma once

#include "NFComm/NFCore/NFPlatform.h"
#include "NFComm/NFPluginModule/NFIModule.h"
#include "NFNetDefine.h"

struct evconnlistener;
struct event_base;
class NetObject;

class NFServer : public NFIModule
{
public:
	/**
	 * @brief ���캯��
	 */
	NFServer(NF_SERVER_TYPES serverType, uint32_t serverId, const NFServerFlag& flag);

	/**
	* @brief ��������
	*/
	virtual ~NFServer();

	/**
	* @brief	���ΨһID
	*
	* @return
	*/
	uint32_t GetServerId() const;

	/**
	* @brief	��÷���������
	*
	* @return
	*/
	uint32_t GetServerType() const;

	/**
	* @brief	��ʼ��
	*
	* @return �Ƿ�ɹ�
	*/
	virtual bool Init() override;

	/**
	* @brief	�رտͻ����ͷ�����
	*
	* @return  �Ƿ�ɹ�
	*/
	virtual bool Shut() override;

	/**
	* @brief	������ÿִ֡��
	*
	* @return	�Ƿ�ɹ�
	*/
	virtual bool Execute() override;

	/**
	 * @brief ���һ�����õ�ID
	 *
	 * @return uint32_t
	 */
	virtual uint32_t GetFreeUnLinkId();

	/**
	* @brief ��õ�ǰ����������
	*
	* @return uint32_t
	*/
	virtual uint32_t GetNetObjectCount() const;

	/**
	* @brief ��õ�ǰ������Ӹ���
	*
	* @return uint32_t
	*/
	virtual uint32_t GetMaxConnectNum() const;

	/**
	 * @brief
	 *
	 * @return event_base*
	 */
	virtual event_base* GetEventBase() const;
private:
	/**
	* @brief libevent
	*/
	struct event_base* mBase;

	/**
	* @brief libevent������
	*/
	struct evconnlistener* mListener;

	/**
	* @brief ��������������
	*/
	NFServerFlag mFlag;

	/**
	* @brief ����������
	*/
	NF_SERVER_TYPES mServerType;

	/**
	* @brief ������Id��һ��һ��Ӧ�ó���һ�����������ͣ�һ��������ID
	*/
	uint32_t mServerId;

	/**
	* @brief ���Ӷ�������
	*/
	std::vector<NetObject*> mNetObjectArray;

	/**
	* @brief ���Ӷ�����ʵ��Ŀ
	*/
	uint32_t mNetObjectCount;
};

