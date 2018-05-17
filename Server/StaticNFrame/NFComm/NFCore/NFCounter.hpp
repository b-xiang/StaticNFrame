// -------------------------------------------------------------------------
//    @FileName         :    NFCounter.h
//    @Author           :    GaoYi
//    @Date             :    2017-04-01
//    @Email			:    445267987@qq.com
//    @Module           :    NFCore
//
// -------------------------------------------------------------------------

#pragma once

#include "NFNonCopyable.h"
#include "NFMutex.h"

/**
 *@brief  �̰߳�ȫ�ļ�����.
 */
class NFCounter : public NFNonCopyable
{
public:
	/**
	* @brief ���캯��.
	*
	*/
	NFCounter() : mValue(0)  { }

	/**
	* @brief ���ؼ������̰߳�ȫ
	*
	* @return ���ؼ���
	*/
	int64_t Value() const
	{
		NFMutexLock lock(&mMutex);
		return mValue;

	}

	/**
	* @brief ��õ�ǰ����������1
	*
	* @return    ��õ�ǰ���� 
	*/
	int64_t GetAndIncrease()
	{
		NFMutexLock lock(&mMutex);
		int64_t ret = mValue++;
		return ret;
	}
private:
	/**
	 *@brief  ����.
	 */
	int64_t mValue;
	/**
	 *@brief  �߳���.
	 */
	mutable NFMutex mMutex;
};
