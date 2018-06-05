#ifndef KBE_THREADTASK_H
#define KBE_THREADTASK_H

#include <string>

/*
�̳߳ص��̻߳���
*/

class NFTask
{
public:
	NFTask()
	{
		m_balanceId = 0;
	}

	virtual ~NFTask()
	{
	}

	enum TPTaskState
	{
		/// һ�������Ѿ����
		TPTASK_STATE_COMPLETED = 0,

		/// ���������߳�ִ��
		TPTASK_STATE_CONTINUE_MAINTHREAD = 1,

		// ���������߳�ִ��
		TPTASK_STATE_CONTINUE_CHILDTHREAD = 2,
	};

	/**
	����ֵ�� thread::TPTask::TPTaskState�� ��ο�TPTaskState
	*/
	virtual TPTaskState presentMainThread()
	{
		return TPTASK_STATE_COMPLETED;
	}

	virtual uint64_t GetBalanceId() const { return m_balanceId; }
	void SetBalanceId(uint64_t balanceId) { m_balanceId = balanceId; }

	virtual bool db_thread_process() = 0;
protected:
	uint64_t  m_balanceId; //��̬����ID, �������Ҿ������CharId, �������һ����0
};

#endif
