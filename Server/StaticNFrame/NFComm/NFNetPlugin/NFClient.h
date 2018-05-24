// -------------------------------------------------------------------------
//    @FileName         :    NFClient.h
//    @Author           :    GaoYi
//    @Date             :    2018-05-24
//    @Email			:    445267987@qq.com
//    @Module           :    NFNetPlugin
//
// -------------------------------------------------------------------------

#pragma once

#include <cstdint>
#include <string>
#include "NFNetDefine.h"
#include "NFComm/NFPluginModule/NFIModule.h"
#include "NFComm/NFCore/NFBuffer.h"
#include "NFComm/NFPluginModule/NFServerDefine.h"
#include "NetObject.h"

/////////////////////////////////////////////////
/**
 *@file   NFClient.h
 *@brief  ���߳�libevent����ͻ��˷�װ��.
 *
 */
 /////////////////////////////////////////////////

/**
*@brief  ���߳�libevent����ͻ��˷�װ��.
*/
class NFClient : public NetObject
{
public:
	/**
	 *@brief  ���캯��.
	 */
	NFClient();

	/**
	 *@brief  ���캯��.
	 */
	NFClient(uint32_t nId, const NFClientFlag& flag);

	/**
	 *@brief  ��������.
	 */
	virtual ~NFClient();

	/**
	 *@brief  ���ý��ջص�.
	 */
	template <typename BaseType>
	void SetRecvCB(BaseType* pBaseType, void (BaseType::*handleRecieve)(const uint32_t unLinkId, const uint64_t valueId, const uint32_t nMsgId, const char* msg, const uint32_t nLen))
	{
		mRecvCB = std::bind(handleRecieve, pBaseType, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5);
	}

	/**
	 *@brief  ���������¼��ص�.
	 */
	template <typename BaseType>
	void SetEventCB(BaseType* pBaseType, void (BaseType::*handleEvent)(const eMsgType nEvent, const uint32_t unLinkId))
	{
		mEventCB = std::bind(handleEvent, pBaseType, std::placeholders::_1, std::placeholders::_2);
	}

	/**
	 * @brief libevent�����ݻص�
	 *
	 * @param pEv   libevent��д������
	 * @param pArg  ����Ĳ���
	 * @return
	 */
	static void conn_recvcb(struct bufferevent* pEv, void* pArg);

	/**
	 * @brief libevent�����¼��ص�
	 *
	 * @param pEv		libevent��д������
	 * @param events	�¼�
	 * @param pArg		����Ĳ���
	 * @return
	 */
	static void conn_eventcb(struct bufferevent* pEv, short events, void* pArg);

	/**
	 * @brief libeventд���ݻص�
	 *
	 * @param pEv   libevent��д������
	 * @param pArg  ����Ĳ���
	 * @return
	 */
	static void conn_writecb(struct bufferevent* pEv, void* pArg);

	/**
	 * @brief log�ص�
	 *
	 * @param severity
	 * @param msg		Ҫ��ӡ����Ϣ
	 * @return
	 */
	static void log_cb(int severity, const char* msg);

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
	 * @brief	�Խ������������ݽ��д���
	 *
	 * @param type    �������ͣ���Ҫ��Ϊ�˺Ͷ��߳�ͳһ����, ��Ҫ�н������ݴ������ӳɹ������Ͽ����Ӵ���
	 * @param usLink  ���ͻ��˵�Ψһid
	 * @param pBuf    ����ָ��
	 * @param sz      ���ݴ�С
	 * @param nMsgId  ������������Ϣid
	 * @param nValue  ��ϢͷЯ����ֵ�����������ID��Ҳ�����ǶԷ��ͻ������ӵ�Ψһid
	 * @return
	 */
	virtual void OnHandleMsgPeer(eMsgType type, uint32_t usLink, char* pBuf, uint32_t sz, uint32_t nMsgId, uint64_t nValue) override;

	/**
	 * @brief	�������ӳɹ�
	 *
	 * @param nSocket	ϵͳ�����socket
	 * @return
	 */
	virtual void OnHandleConnect(SOCKET nSocket);

	/**
	 * @brief	����Ͽ�����
	 *
	 * @return
	 */
	virtual void OnHandleDisConnect();

	/**
	 * @brief	���ӷ����
	 *
	 * @return  ���ӳɹ����
	 */
	virtual bool Connect();

	/**
	 * @brief	�رտͻ�������, ��Conenct��Ӧ
	 * @return
	 */
	virtual void Close();

	/**
	 * @brief	���libevent�����ݽṹ
	 * @return
	 */
	event_base* GetMainBase() const;

	/**
	 * @brief	��÷���������
	 *
	 * @return
	 */
	const string& GetName() const;

	/**
	 * @brief	���ؿͻ�����������
	 *
	 * @return
	 */
	const NFClientFlag& GetFlag() const;

	/**
	 * @brief	��������
	 * @return	�Ƿ�ɹ�
	 */
	virtual bool Reconnect();

	/**
	 * @brief	�������
	 * @return
	 */
	virtual void CheckConnect();
protected:
	/**
	 * @brief	libevent��react���ݽṹ
	 */
	event_base* m_pMainBase;

	/**
	 * @brief	����������ݵĻص�
	 */
	NET_RECEIVE_FUNCTOR mRecvCB;

	/**
	 * @brief	�����¼��ص�
	 */
	NET_EVENT_FUNCTOR mEventCB;

	/**
	 * @brief	������������
	 */
	NFClientFlag m_flag;

	/**
	 * @brief	����������
	 */
	std::string m_strName;
};
