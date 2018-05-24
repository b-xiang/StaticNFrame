#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <algorithm>
#include <stdint.h>

#include "event2/bufferevent.h"
#include "event2/event.h"
#include "event2/util.h"
#include "event2/buffer.h"
#include <event2/http.h>
#include <event2/http_struct.h>
#include <event2/keyvalq_struct.h>
#include <event2/listener.h>
#include <event2/event_compat.h>

#include "NFComm/NFPluginModule/NFIModule.h"
#include "NFComm/NFPluginModule/NFServerDefine.h"
#include "NFNetDefine.h"
#include "NFComm/NFCore/NFBuffer.h"

#include <vector>

struct stMsg;
struct bufferevent;
class NFThreadClient;
class NFClient;

/**
* @brief ������󣬴���һ������
*/
class NetObject : public NFIModule
{
	friend NFThreadClient;
	friend NFClient;
public:
	/**
	 * @brief	���캯��
	 */
	NetObject();

	/**
	 * @brief	��������
	 */
	virtual ~NetObject();
public:
	/**
	 * @brief	��������
	 *
	 * @return	�Ƿ�ɹ�
	 */
	virtual bool OnRecvData(bufferevent* pBufEv);

	/**
	 * @brief	ȡ�����ݣ������д���
	 *
	 * @return	< 0, ��ʾ��������������, = 0, ��ʾ�������ݼ�������> 0��ʾ���ݴ������
	 */
	virtual int	Dismantle();

	/**
	 * @brief	����socket������socket�����Դ���, ������
	 *
	 * @return
	 */
	virtual void SetSocketId(SOCKET nSocket);

	/**
	 * @brief	��������
	 *
	 * @param pData		���͵�����, ����������Ѿ�����������ͷ
	 * @param unSize	���ݵĴ�С
	 * @return
	 */
	virtual bool Send(const void* pData, uint32_t unSize);

	/**
	 * @brief	��ö�д���ݽṹ��
	 *
	 * @return
	 */
	struct bufferevent* GetBev() const;

	/**
	 * @brief	���ΨһID
	 *
	 * @return
	 */
	uint32_t GetLinkId() const;

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
	virtual void OnHandleMsgPeer(eMsgType type, uint32_t usLink, char* pBuf, uint32_t sz, uint32_t nMsgId, uint64_t nValue) = 0;

	/**
	 * @brief	�����һ�ν������ݵ�ʱ��
	 * @return
	 */
	uint64_t GetLastRecvTime() const;

	/**
	 * @brief	������һ�ν������ݵ�ʱ��
	 * @return
	 */
	void SetLastRecvTime(uint64_t val);

	/**
	 * @brief	�����һ��ping��ʱ��
	 * @return
	 */
	uint64_t GetLastPingTime() const;

	/**
	 * @brief	������һ��ping��ʱ��
	 * @return
	 */
	void SetLastPingTime(uint64_t val);

	/**
	 * @brief	�������״̬
	 * @return
	 */
	eConnectStatus GetStatus() const;

	/**
	 * @brief	������״̬
	 * @return
	 */
	void SetStatus(eConnectStatus val);

	/**
	 * @brief	�Ƿ�������״̬
	 * @return
	 */
	bool IsConnectOK() const;
protected:
	/**
	 * @brief	libevent�������Ӷ�д�¼�����
	 */
	struct bufferevent* m_pBev;

	/**
	 * @brief	����������ӵ�socket
	 */
	SOCKET m_nSocketId;
	/**
	 * @brief	����ͻ������ӵ�ΨһID
	 */
	uint32_t m_usLinkId;

	/**
	 * @brief	�����������緢��������ʱ����
	 */
	NFBuffer m_buffer;

	/**
	 * @brief	����״̬
	 */
	eConnectStatus m_eStatus;

	/**
	 * @brief	�ϴν������ݵ�ʱ��
	 */
	uint64_t m_lastRecvTime;

	/**
	 * @brief	�ϴζϿ����ӵ�ʱ��
	 */
	uint64_t m_lastDisconnetTime;

	/**
	 * @brief	�ϴ�ping��ʱ��
	 */
	uint64_t m_lastPingTime;
};
