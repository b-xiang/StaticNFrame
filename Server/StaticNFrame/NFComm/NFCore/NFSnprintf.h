// -------------------------------------------------------------------------
//    @FileName         :    NFSnprintf.h
//    @Author           :    GaoYi
//    @Date             :    2018-05-11
//    @Email			:    445267987@qq.com
//    @Module           :    NFCore
//
// -------------------------------------------------------------------------

#pragma once

#include "NFPlatform.h"

#include <stdarg.h>

/**
 * ��׼ C snprintf API ��װ�����Ա�֤����������е����һ���ֽ�Ϊ '\0'
 * @param buf {char*} �洢����Ļ�����
 * @param size {size_t} buf ����������
 * @param fmt {const char*} ��θ�ʽ�ַ���
 * @return {int} �����������ȹ���ʱ����ʵ�ʿ��������ݳ��ȣ�����:
 *  1) UNIX/LINUX ƽ̨�·���ʵ����Ҫ�Ļ��������ȣ��������������Ȳ���ʱ����ֵ
 *     >= size����Ҫע��÷���ֵ�ĺ����� _WIN32 �µĲ�ͬ
 *  2) _WIN32 ƽ̨�·��� -1
 */
#if defined(__GNUC__) && (__GNUC__ > 4 ||(__GNUC__ == 4 && __GNUC_MINOR__ >= 4))
_NFExport int NFSafeSnprintf(char *buf, size_t size,
	const char *fmt, ...);
#else
_NFExport int NFSafeSnprintf(char *buf, size_t size, const char *fmt, ...);
#endif

/**
 * ��׼ C snprintf API ��װ�����Ա�֤����������е����һ���ֽ�Ϊ '\0'
 * @param buf {char*} �洢����Ļ�����
 * @param size {size_t} buf ����������
 * @param fmt {const char*} ��θ�ʽ�ַ���
 * @param ap {va_list} ��α���
 * @return {int} �����������ȹ���ʱ����ʵ�ʿ��������ݳ��ȣ�����:
 *  1) UNIX/LINUX ƽ̨�·���ʵ����Ҫ�Ļ��������ȣ��������������Ȳ���ʱ����ֵ
 *     >= size����Ҫע��÷���ֵ�ĺ����� _WIN32 �µĲ�ͬ
 *  2) _WIN32 ƽ̨�·��� -1
 */
_NFExport int NFSafeVsnprintf(char *buf, size_t size, const char *fmt, va_list ap);
