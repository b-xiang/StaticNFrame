// -------------------------------------------------------------------------
//    @FileName         :    NFCEventModule.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2012-12-15
//    @Module           :    NFCEventModule
//
// -------------------------------------------------------------------------

#ifndef NFC_EVENT_MODULE_H
#define NFC_EVENT_MODULE_H

#include <iostream>
#include "NFComm/NFPluginModule/NFIEventModule.h"

#include "NFComm/NFPluginModule/NFEventTemplate.h"
#include "NFComm/NFPluginModule/NFEventObj.h"

/* �¼�ʹ��ע������
 ȡ�������¼���ʱ����Ĳ���һ��Ҫ�Ͷ����¼�ʱ����Ĳ���һ�£�
 �¼��ڲ����Զ����¼�����Ĳ����������ص�ָ�룩���Ϊ�¼�key�ģ�
 ���ȡ���Ͷ���ʱ������һ�£� ȡ�����ľͻ�ʧ�ܣ��ͻᵼ�����¼�����������Ұָ�룩���´θ��¼�������ʱ�򴥷��ص��ͻ��쳣

 �¼�Ƕ�ײ�������̫�࣬������ԣ�������Ҫʹ���¼�Ƕ�ף���Ҫ��Ϊ�˱��������ѭ����Ŀǰ�¼����Ƕ�ײ���֧��5��
*/


//�¼�ִ�ж���
struct OnEventExecuteObj 
{
	bool operator()(NFEventObj *pSink, uint16_t nEventID, uint64_t nSrcID, uint8_t bySrcType, NFEventContext* pEventContext)
	{
		if (nullptr == pSink)
		{
			return false;
		}

		pSink->OnExecute(nEventID, nSrcID, bySrcType, pEventContext);

		return true;
	}
};

class NFIKernelModule;

class NFCEventModule
    : public NFIEventModule
{
	typedef EventTemplate< NFEventObj, OnEventExecuteObj > TEXECUTE_CENTER;
public:
    NFCEventModule(NFIPluginManager* p)
    {
        pPluginManager = p;
    }


    virtual ~NFCEventModule()
    {
    }

    virtual bool Init();
    virtual bool AfterInit();
    virtual bool BeforeShut();
    virtual bool Shut();
    virtual bool Execute();

public:
	//����ִ���¼�
	virtual void FireExecute(uint16_t nEventID,uint64_t nSrcID,uint8_t bySrcType, NFEventContext* pEventContext);

	//����ִ���¼�
	virtual bool Subscribe(NFEventObj *pSink, uint16_t nEventID, uint64_t nSrcID, uint8_t bySrcType, const std::string& desc);

	//ȡ������ִ���¼�
	virtual bool UnSubscribe(NFEventObj *pSink, uint16_t nEventID, uint64_t nSrcID, uint8_t bySrcType);

	//ȡ������ִ���¼��Ķ���
	virtual bool UnSubscribeAll(NFEventObj *pSink);
private:
	TEXECUTE_CENTER m_ExecuteCenter;
};

#endif