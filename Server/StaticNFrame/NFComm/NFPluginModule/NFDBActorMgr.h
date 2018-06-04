#pragma once

#include "NFComm/NFCore/NFQueue.hpp"
#include "NFComm/NFCore/NFSingleton.hpp"
#include "NFActorMgr.h"
#include "NFDBActor.h"

#include <vector>


class NFTask;

/**
* @brief �첽����DB������
*/
class NFDBActorMgr : public NFActorMgr<NFDBActor>, public NFSingleton<NFDBActorMgr>
{
public:
	/**
	* @brief ���캯��
	*/
	NFDBActorMgr();

	/**
	* @brief ��������
	*/
	virtual ~NFDBActorMgr();

	/**
	* @brief ��ʼ��DB�Լ�actorϵͳ
	*
	* @param dbInfo		db����
	* @param actor_num	actor����
	* @return
	*/
	virtual int Init(int actor_num = 10);

	/**
	 * @brief �ͷ���Դ
	 *
	 * @return int 
	 */
	virtual int UnInit();

	/**
	* @brief ��ϵͳ����actorNum��actor, ��ʼ��actor��
	*
	* @param actorNum	actor��Ŀ
	* @return �Ƿ�ɹ�
	*/
	virtual bool StartActorPool(int actorNum);

	/**
	* @brief �ͷ������actor���ݣ��ر�actor��
	*
	* @return �Ƿ�ɹ�
	*/
	virtual bool CloseActorPool();

	/**
	* @brief ��Ϣ���ݴ����������б�Ҫ�����ݷ��ظ����̣߳�
	*		 ��������������Ϣ�������͸����̣߳����������actor�߳���ִ��
	*
	* @param messag	��Ϣ����
	* @param from	������Ϣ��actor��ַ
	* @return �Ƿ�ɹ�
	*/
	virtual bool HandlerEx(const NFXActorMessage& message, const int from);

	/**
	* @brief ͨ������Ķ�̬����id�����actor
	*		 Ϊ�˷�ֹ���ݿ���ң���ֹͬʱ�����ݿ���е�һ�����ݣ���ȡд�룬
	*		 ʹ�ö�̬����id, ʹ����ĳ��ʱ��ֻ��һ���̶߳Ա��е�һ�����ݣ���ȡ��д��
	* @param balanceId ��̬����id
	* @return	һ��actor����
	*/
	int			GetBalanceActor(uint64_t balanceId);

	/**
	* @brief ������һ��actor
	*
	* @return actor����
	*/
	int			GetRandActor();

	/**
	* @brief ���Ҫ�첽�����task
	*
	* @param pTask Ҫ�첽�����task
	* @return
	*/
	bool		AddTask(NFTask* pTask);

	/**
	* @brief ���̴߳���actor���ص�����
	*
	* @return
	*/
	void		OnMainThreadTick();
protected:
	/**
	* @brief actor��������
	*/
	std::vector<int> m_vecActorPool;

	/**
	* @brief ����ƽ��������actor
	*/
	int mnSuitIndex;

	/**
	* @brief ���յ�������Ŀ
	*
	*/
	int nRecvTaskCount;

	/**
	* @brief �����������Ŀ
	* @return
	*/
	int nHandleTaskCount;

	/**
	* @brief ���ص���Ϣ���У��̰߳�ȫ, 
	* actor�߳̽����ݷ�����У� ���̴߳Ӷ�����ȡ���ݴ���
	*/
	NFQueue<NFXActorMessage>		m_mQueue;
};