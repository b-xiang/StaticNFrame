// -------------------------------------------------------------------------
//    @FileName         :    NFMyClient.h
//    @Author           :    GaoYi
//    @Date             :    2018/05/28
//    @Email			:    445267987@qq.com
//    @Module           :    NFNetPlugin
//
// -------------------------------------------------------------------------
#pragma once

#include "NFComm/NFCore/NFPlatform.h"
#include "NFSocket.h"
#include "NFPoll.h"

class NFMyClient
{
public:
	/**
	 * @brief ���캯��
	 */
	NFMyClient(uint32_t linkId);

	/**
	 * @brief ��������
	 */
	virtual ~NFMyClient();

	/**
	 * @brief ����
	 *
	 * @param  ip
	 * @param  port
	 * @return bool 
	 */
	virtual bool Connect(const std::string& ip, int port);
protected:
	/**
	 * @brief	����������ӵ�socket
	 */
	SOCKET m_nSocketId;

	/**
	 * @brief	����ͻ������ӵ�ΨһID
	 */
	uint32_t m_usLinkId;

	/**
	 * @brief �¼��ṹ����Ҫ��ȡ�����¼���־���Լ�����д�����¼��Ĵ���
	 */
	EventData* m_pEventData;
};
