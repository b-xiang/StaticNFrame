#include <stdint.h>

#include "NFEventObj.h"
#include "NFEventMgr.h"

NFEventObj::NFEventObj()
{
}

NFEventObj::~NFEventObj()
{
	UnSubscribeAll();
}

//����ִ���¼�
void NFEventObj::FireExecute(uint16_t nEventID, uint64_t nSrcID, uint8_t bySrcType, NFEventContext* pEventContext)
{
	NFEventMgr::Instance()->FireExecute(nEventID, nSrcID, bySrcType, pEventContext);
}

//����ִ���¼�
bool NFEventObj::Subscribe(uint16_t nEventID, uint64_t nSrcID, uint8_t bySrcType, const std::string& desc)
{
	return NFEventMgr::Instance()->Subscribe(this, nEventID, nSrcID, bySrcType, desc);
}

//ȡ������ִ���¼�
bool NFEventObj::UnSubscribe(uint16_t nEventID, uint64_t nSrcID, uint8_t bySrcType)
{
	return NFEventMgr::Instance()->UnSubscribe(this, nEventID, nSrcID, bySrcType);
}

//ȡ������ִ���¼��Ķ���
bool NFEventObj::UnSubscribeAll()
{
	return NFEventMgr::Instance()->UnSubscribeAll(this);
}

