// -------------------------------------------------------------------------
//    @FileName         :    NFTimerAxis.cpp
//    @Author           :    GaoYi
//    @Date             :    2018/05/25
//    @Email			:    445267987@qq.com
//    @Module           :    NFPluginModule
//
// -------------------------------------------------------------------------
#include "NFTimerAxis.h"
#include "NFComm/NFCore/NFProfiler.h"
#include "NFComm/NFCore/NFPlatform.h"

#define FIX_AXIS_ONE_DAY_HOUR 24
#define FIX_AXIS_ONE_HOUR_SECOND (60 * 60)
#define FIX_AXIS_ONE_DAY_SECOND (60*60*24)

NFFixTimerAxis::NFFixTimerAxis()
{
	m_FixTimerAxis.resize(FIX_AXIS_ONE_DAY_HOUR);
	m_nInitSec = NFGetSecondTime();
	m_nLastSec = m_nInitSec;
	for (size_t i = 0; i < m_FixTimerAxis.size(); ++i)
	{
		m_FixTimerAxis[i] = new FIXTIMER_LIST();
	}
}

NFFixTimerAxis::~NFFixTimerAxis()
{
	for (size_t i = 0; i < m_FixTimerAxis.size(); ++i)
	{
		FIXTIMER_LIST* pFixList = m_FixTimerAxis[i];
		FIXTIMER_LIST::iterator iter = pFixList->begin();
		for (; iter != pFixList->end(); ++iter)
		{
			FixTimer* pFixTimer = (*iter);
			NFSafeDelete(pFixTimer);
		}
		pFixList->clear();

		NFSafeDelete(pFixList);
	}
	m_FixTimerAxis.clear();
}

//���ù̶�ʱ��Ķ�ʱ��
bool NFFixTimerAxis::SetFixTimer(uint32_t nTimerID, uint64_t nStartTime, uint32_t nInterDays, NFTimerObj* handler, uint32_t nCallCount /*= INFINITY_CALL*/)
{
	if (nullptr == handler)
	{
		return false;
	}
	if (nCallCount < 1)
	{
		return false;
	}
	if (nInterDays < 1)
	{
		nInterDays = 1;
	}

	bool bNeedFind = true;
	void** ppFixTimerInfo = handler->GetFixTimerInfoPtr();
	FIXTIMER_LIST* pFixTimerList = *(FIXTIMER_LIST**)ppFixTimerInfo;
	if (nullptr == pFixTimerList)
	{
		pFixTimerList = new FIXTIMER_LIST();
		*ppFixTimerInfo = pFixTimerList;
		bNeedFind = false;
	}

	FixTimer* pFixTimer = nullptr;
	if (bNeedFind)
	{
		FIXTIMER_LIST::iterator iter = pFixTimerList->begin();
		for (; iter != pFixTimerList->end(); ++iter)
		{
			pFixTimer = (*iter);
			if (pFixTimer->nTimerID == nTimerID)
			{
				return false;
			}
		}
	}
	//ת����������ʱ��
	nStartTime += FIX_AXIS_ONE_DAY_SECOND - (8 * 60 * 60);
	nStartTime %= FIX_AXIS_ONE_DAY_SECOND;

	pFixTimer = new FixTimer();
	pFixTimer->nTimerID = nTimerID;
	pFixTimer->nInterDays = nInterDays;
	pFixTimer->nStartTime = nStartTime;
	pFixTimer->nCallCount = nCallCount;
	pFixTimer->pHandler = handler;

	uint64_t nowTime = NFGetSecondTime();
	uint64_t nowDaySecs = nowTime % FIX_AXIS_ONE_DAY_SECOND;
	//Ϊ���ڽ������Ĺ̶�ʱ���������Ч������pTimer ���һ�λص�ʱ��
	if (nStartTime < nowDaySecs)
	{
		//��ǰ�Ѿ����˹̶���ʼʱ��
		pFixTimer->nLastSec = GetMorningTime(nowTime) + nStartTime;
	}
	else
	{
		//
		pFixTimer->nLastSec = GetMorningTime(nowTime) - pFixTimer->nInterDays * FIX_AXIS_ONE_DAY_SECOND + pFixTimer->nStartTime;
	}
	pFixTimer->nGridIndex = static_cast<uint32_t>(pFixTimer->nStartTime / FIX_AXIS_ONE_HOUR_SECOND);

	pFixTimerList->push_back(pFixTimer);

	m_FixTimerAxis[pFixTimer->nGridIndex]->push_back(pFixTimer);
	pFixTimer->pos = --m_FixTimerAxis[pFixTimer->nGridIndex]->end();

	return true;
}

//�رչ̶�ʱ�䶨ʱ��
bool NFFixTimerAxis::KillFixTimer(uint32_t nTimerID, NFTimerObj* handler)
{
	if (nullptr == handler)
	{
		return false;
	}
	void** ppFixTimerInfo = handler->GetFixTimerInfoPtr();
	FIXTIMER_LIST* pFixTimerList = *(FIXTIMER_LIST**)ppFixTimerInfo;
	if (nullptr == pFixTimerList)
	{
		return false;
	}

	FIXTIMER_LIST::iterator iter = pFixTimerList->begin();
	for (; iter != pFixTimerList->end(); ++iter)
	{
		FixTimer* pFixTimer = (*iter);
		if (pFixTimer && pFixTimer->nTimerID == nTimerID)
		{
			pFixTimerList->erase(iter);

			pFixTimer->nCallCount = 0;
			pFixTimer->pHandler = nullptr;

			//������ʱ�����ϵ�λ��
			ResetFixTimerPos(pFixTimer);

			NFSafeDelete(pFixTimer);

			if (pFixTimerList->empty())
			{
				NFSafeDelete(pFixTimerList);
				*ppFixTimerInfo = nullptr;
			}

			return true;
		}
	}
	return false;
}

//�ر����й̶�ʱ�䶨ʱ��
bool NFFixTimerAxis::KillAllFixTimer(NFTimerObj* handler)
{
	if (nullptr == handler)
	{
		return false;
	}
	void** ppFixTimerInfo = handler->GetFixTimerInfoPtr();
	FIXTIMER_LIST* pFixTimerList = *(FIXTIMER_LIST**)ppFixTimerInfo;
	if (nullptr == pFixTimerList)
	{
		return false;
	}
	FIXTIMER_LIST::iterator iter = pFixTimerList->begin();
	for (; iter != pFixTimerList->end(); ++iter)
	{
		FixTimer* pFixTimer = (*iter);
		if (nullptr != pFixTimer)
		{
			pFixTimer->nCallCount = 0;
			pFixTimer->pHandler = nullptr;

			//������ʱ�����ϵ�λ��
			ResetFixTimerPos(pFixTimer);

			NFSafeDelete(pFixTimer);
		}
	}

	pFixTimerList->clear();
	NFSafeDelete(pFixTimerList);
	*ppFixTimerInfo = nullptr;

	return false;
}

//���ö�ʱ����ʱ�����ϵ�λ��
bool NFFixTimerAxis::ResetFixTimerPos(FixTimer* pTimer)
{
	if (nullptr == pTimer)
	{
		return false;
	}
	(*pTimer->pos) = nullptr;

	return true;
}

uint64_t NFFixTimerAxis::GetMorningTime(uint64_t nTimeSec)
{
	return (nTimeSec / FIX_AXIS_ONE_DAY_SECOND) * FIX_AXIS_ONE_DAY_SECOND;
}

//���¹̶�ʱ��Ķ�ʱ��
void NFFixTimerAxis::UpdateFix()
{
	uint64_t now = NFGetTime();
	if (now - m_nLastSec < 3)
	{
		return;
	}

	uint32_t start_grid = (m_nLastSec % FIX_AXIS_ONE_DAY_SECOND) / FIX_AXIS_ONE_HOUR_SECOND;
	uint32_t cur_grid = (now % FIX_AXIS_ONE_DAY_SECOND) / FIX_AXIS_ONE_HOUR_SECOND;

	m_nLastSec = now;

	uint32_t i = start_grid;

	// ����ʱ��̶�
	do
	{
		// ������ǰʱ��̶��е����д�������ʱ��
		FIXTIMER_LIST* pTimerList = m_FixTimerAxis[i];
		FIXTIMER_LIST::iterator it = pTimerList->begin();
		for (; it != pTimerList->end();)
		{
			FixTimer* pFixTimer = *it;
			if (nullptr == pFixTimer || nullptr == pFixTimer->pHandler)
			{
				it = pTimerList->erase(it);
				continue;
			}

			if (pFixTimer->nCallCount == 0)
			{
				it = pTimerList->erase(it);
				NFSafeDelete(pFixTimer);
				continue;
			}

			// ������ʱ��
			if (now - pFixTimer->nLastSec >= (static_cast<uint64_t>(pFixTimer->nInterDays) * FIX_AXIS_ONE_DAY_SECOND))
			{
				pFixTimer->pHandler->OnTimer(pFixTimer->nTimerID);
				pFixTimer = *it;
				if (nullptr == pFixTimer || nullptr == pFixTimer->pHandler)
				{
					it = pTimerList->erase(it);
					continue;
				}

				pFixTimer->nLastSec = GetMorningTime(now) + pFixTimer->nStartTime;
				if (pFixTimer->nCallCount > 0)
					pFixTimer->nCallCount -= 1;

				if (pFixTimer->nCallCount == 0)
				{
					// ���ô����Ѿ�����
					KillFixTimer(pFixTimer->nTimerID, pFixTimer->pHandler);
					it = pTimerList->erase(it);
					continue;
				}
			}

			++it;
		}

		// �ݽ�����һ���̶�
		if (i == cur_grid)
		{
			break;
		}

		i = (i + 1) % m_FixTimerAxis.size();
		//}while(i!=cur_grid);
	}
	while (i != cur_grid);
}

NFTimerAxis::NFTimerAxis()
{
	m_TimerAxis.resize((TIME_AXIS_LENGTH + TIME_GRID - 1) / TIME_GRID);

	m_nInitTick = GetTick();
	m_nLastTick = m_nInitTick;
	for (uint32_t i = 0; i < m_TimerAxis.size(); ++i)
	{
		m_TimerAxis[i] = new TIMER_LIST();
	}

	m_TimerAxisSec.resize(TIME_AXIS_SECLENGTH);
	m_nInitSec = time(nullptr);
	m_nLastSec = m_nInitSec;
	for (uint32_t i = 0; i < m_TimerAxisSec.size(); ++i)
	{
		m_TimerAxisSec[i] = new TIMER_LIST();
	}
}

NFTimerAxis::~NFTimerAxis()
{
	for (size_t i = 0; i < m_TimerAxis.size(); ++i)
	{
		TIMER_LIST* pTimerList = m_TimerAxis[i];
		TIMER_LIST::iterator iter = pTimerList->begin();
		for (; iter != pTimerList->end(); ++iter)
		{
			Timer* pTimer = (*iter);
			NFSafeDelete(pTimer);
		}
		pTimerList->clear();
		NFSafeDelete(pTimerList);
	}
	m_TimerAxis.clear();

	for (size_t j = 0; j < m_TimerAxisSec.size(); ++j)
	{
		TIMER_LIST* pTimerList = m_TimerAxisSec[j];
		TIMER_LIST::iterator iter = pTimerList->begin();
		for (; iter != pTimerList->end(); ++iter)
		{
			Timer* pTimer = (*iter);
			NFSafeDelete(pTimer);
		}
		pTimerList->clear();
		NFSafeDelete(pTimerList);
	}
	m_TimerAxisSec.clear();
}

bool NFTimerAxis::Init()
{
	return true;
}

bool NFTimerAxis::UnInit()
{
	return true;
}

//�����붨ʱ��
bool NFTimerAxis::SetTimerSec(uint32_t nTimerID, uint64_t nInterVal, NFTimerObj* handler, uint32_t nCallCount/* = INFINITY_CALL*/)
{
	if (nullptr == handler)
	{
		return false;
	}
	if (nCallCount == 0)
	{
		return false;
	}
	if (nInterVal < 1)
	{
		nInterVal = 1;
	}

	bool bNeedFind = true;
	void** ppTimerInfo = handler->GetTimerInfoPtr();
	TIMER_LIST* pTimerList = *(TIMER_LIST**)ppTimerInfo;
	if (nullptr == pTimerList)
	{
		pTimerList = new TIMER_LIST();
		*ppTimerInfo = pTimerList;
		bNeedFind = false;
	}

	Timer* pTimer = nullptr;
	if (bNeedFind)
	{
		TIMER_LIST::iterator iter = pTimerList->begin();
		for (; iter != pTimerList->end(); ++iter)
		{
			pTimer = (*iter);
			if (pTimer->nTimerID == nTimerID)
			{
				//��ʱ��ID �Ѵ���
				return false;
			}
		}
	}

	pTimer = new Timer();
	pTimer->byType = 1;
	pTimer->nTimerID = nTimerID;
	pTimer->nCallCount = nCallCount;
	pTimer->nInterVal = nInterVal;
	pTimer->pHandler = handler;
	pTimer->nLastTick = m_nLastSec;
	uint32_t nTemp = (uint32_t)(pTimer->nLastTick - m_nInitSec + pTimer->nInterVal);
	pTimer->nGridIndex = nTemp % m_TimerAxisSec.size();

	pTimerList->push_back(pTimer);

	m_TimerAxisSec[pTimer->nGridIndex]->push_back(pTimer);
	pTimer->pos = --m_TimerAxisSec[pTimer->nGridIndex]->end();

	return true;
}

bool NFTimerAxis::SetTimer(uint32_t nTimerID, uint64_t nInterVal, NFTimerObj* handler, uint32_t nCallCount /*= INFINITY_CALL*/)
{
	if (nullptr == handler)
	{
		//���󣬻ص�ָ��Ϊ�գ���Ҫ��ӡ��־
		return false;
	}
	if (nCallCount == 0)
	{
		//���󣬵��ô���Ϊ0����Ҫ��ӡ��־
		return false;
	}
	if (nInterVal < TIMER_AXIS_CHECK_FREQUENCE)
	{
		nInterVal = TIMER_AXIS_CHECK_FREQUENCE;
	}
	if (nInterVal >= 2000)
	{
		//�����������ĵ�����̶�ʱ����
		return SetTimerSec(nTimerID, nInterVal / 1000, handler, nCallCount);
	}

	bool bNeedFind = true;
	void** ppTimerInfo = handler->GetTimerInfoPtr();
	TIMER_LIST* pTimerList = *(TIMER_LIST**)ppTimerInfo;
	if (nullptr == pTimerList)
	{
		pTimerList = new TIMER_LIST();
		*ppTimerInfo = pTimerList;
		bNeedFind = false;
	}

	Timer* pTimer = nullptr;
	if (bNeedFind)
	{
		TIMER_LIST::iterator iter = pTimerList->begin();
		for (; iter != pTimerList->end(); ++iter)
		{
			pTimer = (*iter);
			if (pTimer->nTimerID == nTimerID)
			{
				//��ʱ��ID �Ѵ���
				return false;
			}
		}
	}

	CheckTick();
	pTimer = new Timer();
	pTimer->nTimerID = nTimerID;
	pTimer->nInterVal = nInterVal;
	pTimer->pHandler = handler;
	pTimer->nCallCount = nCallCount;
	pTimer->nLastTick = m_nLastTick;
	pTimer->byType = 0;
	uint64_t nTemp = pTimer->nLastTick - m_nInitTick + pTimer->nInterVal;
	pTimer->nGridIndex = (nTemp / TIME_GRID) % m_TimerAxis.size();

	pTimerList->push_back(pTimer);

	m_TimerAxis[pTimer->nGridIndex]->push_back(pTimer);
	pTimer->pos = --m_TimerAxis[pTimer->nGridIndex]->end();

	return true;
}

//�رն�ʱ��
bool NFTimerAxis::KillTimer(uint32_t nTimerID, NFTimerObj* handler)
{
	if (nullptr == handler)
	{
		return false;
	}

	void** ppTimerInfo = handler->GetTimerInfoPtr();
	TIMER_LIST* pTimerList = *(TIMER_LIST**)ppTimerInfo;
	if (nullptr == pTimerList)
	{
		return false;
	}

	TIMER_LIST::iterator iter = pTimerList->begin();
	for (; iter != pTimerList->end(); ++iter)
	{
		Timer* pTimer = (*iter);
		if (pTimer && pTimer->nTimerID == nTimerID)
		{
			pTimerList->erase(iter);
			pTimer->nCallCount = 0;
			pTimer->pHandler = nullptr;

			//���ö�ʱ����ʱ�����ϵ�λ��
			ResetTimerPos(pTimer);

			NFSafeDelete(pTimer);

			if (pTimerList->empty())
			{
				NFSafeDelete(pTimerList);
				*ppTimerInfo = nullptr;
			}

			return true;
		}
	}

	return false;
}

//�ر����ж�ʱ��
bool NFTimerAxis::KillAllTimer(NFTimerObj* handler)
{
	if (nullptr == handler)
	{
		return false;
	}

	void** ppTimerInfo = handler->GetTimerInfoPtr();
	TIMER_LIST* pTimerList = *(TIMER_LIST**)ppTimerInfo;
	if (nullptr == pTimerList)
	{
		return false;
	}

	TIMER_LIST::iterator iter = pTimerList->begin();
	for (; iter != pTimerList->end(); ++iter)
	{
		Timer* pTimer = (*iter);
		if (nullptr != pTimer)
		{
			pTimer->nCallCount = 0;
			pTimer->pHandler = nullptr;

			//���ö�ʱ����ʱ�����ϵ�λ��
			ResetTimerPos(pTimer);
			NFSafeDelete(pTimer);
		}
	}
	pTimerList->clear();
	NFSafeDelete(pTimerList);
	*ppTimerInfo = nullptr;

	return false;
}

//���tick
void NFTimerAxis::CheckTick()
{
	uint64_t nowTick = GetTick();
	if (nowTick < m_nLastTick || nowTick < m_nInitTick || m_nLastTick < m_nInitTick)
	{
		m_nInitTick = nowTick;
		m_nLastTick = nowTick;
	}
}

//���ù̶�ʱ��Ķ�ʱ��
bool NFTimerAxis::SetFixTimer(uint32_t nTimerID, uint64_t nStartTime, uint32_t nInterDays, NFTimerObj* handler, uint32_t nCallCount /*= INFINITY_CALL*/)
{
	return m_FixTimerAxis.SetFixTimer(nTimerID, nStartTime, nInterDays, handler, nCallCount);
}

//�رչ̶�ʱ�䶨ʱ��
bool NFTimerAxis::KillFixTimer(uint32_t nTimerID, NFTimerObj* handler)
{
	return m_FixTimerAxis.KillFixTimer(nTimerID, handler);
}

//�ر����й̶�ʱ�䶨ʱ��
bool NFTimerAxis::KillAllFixTimer(NFTimerObj* handler)
{
	return m_FixTimerAxis.KillAllFixTimer(handler);
}

//���¹̶�ʱ�䶨ʱ��
void NFTimerAxis::UpdateFix()
{
	m_FixTimerAxis.UpdateFix();
}

void NFTimerAxis::Update()
{
	CheckTick();

	uint64_t now = GetTick();

	if ((now - m_nLastTick) < TIMER_AXIS_CHECK_FREQUENCE)
	{
		return;
	}

	uint32_t start_grid = (static_cast<uint32_t>(m_nLastTick - m_nInitTick) / TIME_GRID) % m_TimerAxis.size();
	uint32_t cur_grid = (static_cast<uint32_t>(now - m_nInitTick) / TIME_GRID) % m_TimerAxis.size();

	m_nLastTick = now;

	uint32_t i = start_grid;

	int iCount = 0;
	bool bFlag = true;
	// ����ʱ��̶�
	do
	{
		iCount++;
		if (iCount == 1000)
		{
			//ĳһ���̶ȶ�ʱ�����࣬�����ӡһ����־
		}
		// ������ǰʱ��̶��е����д�������ʱ��
		TIMER_LIST* TimerList = m_TimerAxis[i];
		TIMER_LIST::iterator it = TimerList->begin();
		for (; it != TimerList->end();)
		{
			Timer* pTimer = *it;
			if (nullptr == pTimer || nullptr == pTimer->pHandler)
			{
				it = TimerList->erase(it);
				continue;
			}
			if (pTimer->nCallCount == 0)
			{
				it = TimerList->erase(it);
				NFSafeDelete(pTimer);
				continue;
			}

			// ������ʱ��
			if (now < pTimer->nLastTick)
			{
				pTimer->nLastTick = now;
			}
			if (static_cast<uint32_t>(now - pTimer->nLastTick) >= pTimer->nInterVal)
			{
				BEGIN_PROFILE("pTimer->pHandler->OnTimer");
					pTimer->pHandler->OnTimer(pTimer->nTimerID);
					END_PROFILE();
				pTimer = *it;
				if (nullptr == pTimer || nullptr == pTimer->pHandler)
				{
					it = TimerList->erase(it);
					continue;
				}

				pTimer->nLastTick = now;
				if (pTimer->nCallCount > 0)
				{
					pTimer->nCallCount -= 1;
				}

				if (pTimer->nCallCount == 0)
				{
					// ���ô����Ѿ�����
					KillTimer(pTimer->nTimerID, pTimer->pHandler);
					it = TimerList->erase(it);
					continue;
				}
				else
				{
					// ��Ǩ����һ�δ�����λ��
					it = TimerList->erase(it);
					if (pTimer->nLastTick < m_nInitTick)
					{
						pTimer->nLastTick = m_nLastTick;
					}
					uint32_t nTemp = static_cast<uint32_t>((pTimer->nLastTick - m_nInitTick) + pTimer->nInterVal);
					pTimer->nGridIndex = (nTemp / TIME_GRID) % m_TimerAxis.size();
					m_TimerAxis[pTimer->nGridIndex]->push_back(pTimer);
					pTimer->pos = --m_TimerAxis[pTimer->nGridIndex]->end();
				}

				continue;
			} // end of if ((uint32_t)(now - pTimer->nLastTick) >= pTimer->nInterVal)

			++it;
		}

		// �ݽ�����һ���̶�
		if (i == cur_grid)
		{
			bFlag = false;
		}
		else
		{
			i = (i + 1) % m_TimerAxis.size();
		}
	}
	while (bFlag);

	//�����붨ʱ��
	UpdateSec();
}

void NFTimerAxis::UpdateSec()
{
	uint64_t now = NFGetSecondTime();

	if (now - m_nLastSec < 1)
	{
		return;
	}

	uint32_t start_grid = static_cast<uint32_t>(m_nLastSec - m_nInitSec) % m_TimerAxisSec.size();
	uint32_t cur_grid = static_cast<uint32_t>(now - m_nInitSec) % m_TimerAxisSec.size();

	m_nLastSec = now;

	uint32_t i = start_grid;

	int iCount = 0;
	bool bFlag = true;
	// ����ʱ��̶�
	do
	{
		iCount++;
		if (iCount == 60)
		{
		}
		// ������ǰʱ��̶��е����д�������ʱ��
		TIMER_LIST* TimerList = m_TimerAxisSec[i];
		TIMER_LIST::iterator it = TimerList->begin();
		for (; it != TimerList->end();)
		{
			Timer* pTimer = *it;
			if (nullptr == pTimer || nullptr == pTimer->pHandler)
			{
				it = TimerList->erase(it);
				continue;
			}

			if (pTimer->nCallCount == 0)
			{
				it = TimerList->erase(it);
				NFSafeDelete(pTimer);
				continue;
			}

			// ������ʱ��
			if (now < pTimer->nLastTick)
			{
				pTimer->nLastTick = now;
			}
			if ((now - pTimer->nLastTick) >= pTimer->nInterVal)
			{
				pTimer->pHandler->OnTimer(pTimer->nTimerID);
				//������Ҫ���¸�ֵ�£������ڻص��а�
				pTimer = *it;
				if (nullptr == pTimer || nullptr == pTimer->pHandler)
				{
					it = TimerList->erase(it);
					continue;
				}

				pTimer->nLastTick = now;
				if (pTimer->nCallCount > 0)
				{
					pTimer->nCallCount -= 1;
				}

				if (pTimer->nCallCount == 0)
				{
					// ���ô����Ѿ�����
					KillTimer(pTimer->nTimerID, pTimer->pHandler);
					it = TimerList->erase(it);

					continue;
				}
				else
				{
					// ��Ǩ����һ�δ�����λ��
					it = TimerList->erase(it);
					if (pTimer->nLastTick < m_nInitSec)
					{
						pTimer->nLastTick = m_nLastSec;
					}
					uint64_t nTemp = (pTimer->nLastTick - m_nInitSec) + pTimer->nInterVal;
					pTimer->nGridIndex = nTemp % m_TimerAxisSec.size();
					m_TimerAxisSec[pTimer->nGridIndex]->push_back(pTimer);
					pTimer->pos = --m_TimerAxisSec[pTimer->nGridIndex]->end();
				}

				continue;
			}

			++it;
		}

		// �ݽ�����һ���̶�
		if (i == cur_grid)
		{
			bFlag = false;
		}
		else
		{
			i = (i + 1) % m_TimerAxisSec.size();
		}
	}
	while (bFlag);
}

//���ö�ʱ����ʱ�����ϵ�λ��
bool NFTimerAxis::ResetTimerPos(Timer* pTimer)
{
	if (nullptr == pTimer)
	{
		return false;
	}
	(*pTimer->pos) = nullptr;

	return true;
}

