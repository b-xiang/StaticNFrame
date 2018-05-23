// -------------------------------------------------------------------------
//    @FileName         :    NFCEventModule.cpp
//    @Author           :    LvSheng.Huang
//    @Date             :    2012-12-15
//    @Module           :    NFCEventModule
//
// -------------------------------------------------------------------------

#include "NFCEventModule.h"

#include "NFComm/NFPluginModule/NFIKernelModule.h"

bool NFCEventModule::Init()
{
	return true;
}

bool NFCEventModule::AfterInit()
{
	return true;
}

bool NFCEventModule::BeforeShut()
{
	return true;
}

bool NFCEventModule::Shut()
{
	return true;
}

bool NFCEventModule::Execute()
{
	return true;
}

//����ִ���¼�
void NFCEventModule::FireExecute(uint16_t nEventID, uint64_t nSrcID, uint8_t bySrcType, NFEventContext* pEventContext)
{
	m_ExecuteCenter.Fire(nEventID, nSrcID, bySrcType, pEventContext);
}
//����ִ���¼�
bool NFCEventModule::Subscribe(NFEventObj *pSink, uint16_t nEventID, uint64_t nSrcID, uint8_t bySrcType, const std::string& desc)
{
	return m_ExecuteCenter.Subscribe(pSink, nEventID, nSrcID, bySrcType, desc);
}
//ȡ������ִ���¼�
bool NFCEventModule::UnSubscribe(NFEventObj *pSink, uint16_t nEventID, uint64_t nSrcID, uint8_t bySrcType)
{
	return m_ExecuteCenter.UnSubscribe(pSink, nEventID, nSrcID, bySrcType);
}

//ȡ������ִ���¼��Ķ���
bool NFCEventModule::UnSubscribeAll(NFEventObj *pSink)
{
	m_ExecuteCenter.UnSubscribeAll(pSink);
	return true;
}