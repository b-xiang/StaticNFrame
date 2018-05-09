
#pragma once
#include "NFEventTemplate.h"
#include "NFEventObj.h"
#include "NFComm/NFCore/NFSingleton.hpp"

/* �¼�ʹ��ע������
 ȡ�������¼���ʱ����Ĳ���һ��Ҫ�Ͷ����¼�ʱ����Ĳ���һ�£�
 �¼��ڲ����Զ����¼�����Ĳ����������ص�ָ�룩���Ϊ�¼�key�ģ�
 ���ȡ���Ͷ���ʱ������һ�£� ȡ�����ľͻ�ʧ�ܣ��ͻᵼ�����¼�����������Ұָ�룩���´θ��¼�������ʱ�򴥷��ص��ͻ��쳣

 �¼�Ƕ�ײ�������̫�࣬������ԣ�������Ҫʹ���¼�Ƕ�ף���Ҫ��Ϊ�˱��������ѭ����Ŀǰ�¼����Ƕ�ײ���֧��5��
*/

class NFIEventModule;

class NFEventMgr : public NFSingleton<NFEventMgr>
{
public:
	NFEventMgr();
	virtual ~NFEventMgr();

	bool Init(NFIEventModule* pEventModule);
	void UnInit();

	//����ִ���¼�
	void FireExecute(uint16_t nEventID,uint64_t nSrcID,uint8_t bySrcType, NFEventContext* pEventContext);
	//����ִ���¼�
	bool Subscribe(NFEventObj *pSink, uint16_t nEventID, uint64_t nSrcID, uint8_t bySrcType, const std::string& desc);
	//ȡ������ִ���¼�
	bool UnSubscribe(NFEventObj *pSink, uint16_t nEventID, uint64_t nSrcID, uint8_t bySrcType);
	//ȡ������ִ���¼��Ķ���
	bool UnSubscribeAll(NFEventObj *pSink);
private:
	NFIEventModule* m_pEventModule;
};
