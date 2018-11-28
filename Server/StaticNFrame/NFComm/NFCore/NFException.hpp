// -------------------------------------------------------------------------
//    @FileName         :    NFException.hpp
//    @Author           :    LvSheng.Huang
//    @Date             :    2016-12-22
//    @Module           :    NFException
//
// -------------------------------------------------------------------------

#ifndef NF_EXCEPTION_HPP
#define NF_EXCEPTION_HPP

#include <string>
#include <exception>
#include "NFPlatform.h"

#if NF_PLATFORM == NF_PLATFORM_LINUX
#include <execinfo.h>
#include <string.h>
#include <stdlib.h>
#include <cerrno>
#endif

/**
* @brief �쳣��.
*/
class NFException : public std::exception
{
public:
	/**
	* @brief ���캯�����ṩ��һ�����Դ���errno�Ĺ��캯����
	*
	*        �쳣�׳�ʱֱ�ӻ�ȡ�Ĵ�����Ϣ
	*
	* @param buffer �쳣�ĸ澯��Ϣ
	*/
	explicit NFException(const std::string &buffer)
		:_buffer(buffer), _code(0)
	{
		//    getBacktrace();
	}

	/**
	* @brief ���캯��,�ṩ��һ�����Դ���errno�Ĺ��캯����
	*
	*        �쳣�׳�ʱֱ�ӻ�ȡ�Ĵ�����Ϣ
	*
	* @param buffer �쳣�ĸ澯��Ϣ
	* @param err    ������, ����strerror��ȡ������Ϣ
	*/
	NFException(const std::string &buffer, int err)
	{
		_buffer = buffer + " :" + strerror(err);
		_code = err;
		//    getBacktrace();
	}

	/**
	* @brief ��������
	*/
	virtual ~NFException() throw()
	{

	}

	/**
	* @brief ������Ϣ.
	*
	* @return const char*
	*/
	virtual const char* what() const throw()
	{
		return _buffer.c_str();
	}

	/**
	* @brief ��ȡ������
	*
	* @return �ɹ���ȡ����0
	*/
	int getErrCode() { return _code; }
private:
	void getBacktrace()
	{
#if NF_PLATFORM == NF_PLATFORM_LINUX
		void * array[64];
		int nSize = backtrace(array, 64);
		char ** symbols = backtrace_symbols(array, nSize);

		for (int i = 0; i < nSize; i++)
		{
			_buffer += symbols[i];
			_buffer += "\n";
		}
		free(symbols);
#endif
	}
private:
	/**
	* �쳣�������Ϣ
	*/
	std::string  _buffer;

	/**
	* ������
	*/
	int     _code;
};

#endif

