// -------------------------------------------------------------------------
//    @FileName         :    NFCpu.h
//    @Author           :    GaoYi
//    @Date             :    2017-08-01
//    @Email			:    445267987@qq.com
//    @Module           :    NFCore
//
// -------------------------------------------------------------------------

#pragma once

#include "NFPlatform.h"

#if NF_PLATFORM == NF_PLATFORM_WIN
#include  <windows.h>
#include  <Psapi.h>
#include  <conio.h>
#include  <stdio.h>

//��windows�»��CPUʹ���ʵķ���
class _NFExport CpuUsage
{
public:
	CpuUsage() :m_nCpuUsage(-1), IsFirstRun(true), m_lRunCount(0)
	{
		ZeroMemory(&m_ftPrevSysKernel, sizeof(FILETIME));
		ZeroMemory(&m_ftPrevSysUser, sizeof(FILETIME));

		ZeroMemory(&m_ftPrevProcKernel, sizeof(FILETIME));
		ZeroMemory(&m_ftPrevProcUser, sizeof(FILETIME));
	}

	short  GetUsage()
	{
		short nCpuCopy = m_nCpuUsage;

		if (::InterlockedIncrement(&m_lRunCount) == 1)
		{
			FILETIME ftSysIdle, ftSysKernel, ftSysUser;
			FILETIME ftProcCreation, ftProcExit, ftProcKernel, ftProcUser;

			if (!GetSystemTimes(&ftSysIdle, &ftSysKernel, &ftSysUser) ||
				!GetProcessTimes(GetCurrentProcess(), &ftProcCreation, &ftProcExit, &ftProcKernel, &ftProcUser))
			{
				::InterlockedDecrement(&m_lRunCount);
				return nCpuCopy;
			}

			if (!IsFirstRun)
			{
				/*
				CPU usage is calculated by getting the total amount of time the system has operated
				since the last measurement (made up of kernel + user) and the total
				amount of time the process has run (kernel + user).
				*/
				ULONGLONG ftSysKernelDiff = SubtractTimes(ftSysKernel, m_ftPrevSysKernel);
				ULONGLONG ftSysUserDiff = SubtractTimes(ftSysUser, m_ftPrevSysUser);

				ULONGLONG ftProcKernelDiff = SubtractTimes(ftProcKernel, m_ftPrevProcKernel);
				ULONGLONG ftProcUserDiff = SubtractTimes(ftProcUser, m_ftPrevProcUser);

				ULONGLONG nTotalSys = ftSysKernelDiff + ftSysUserDiff;
				ULONGLONG nTotalProc = ftProcKernelDiff + ftProcUserDiff;

				if (nTotalSys > 0)
				{
					m_nCpuUsage = (short)((100.0 * nTotalProc) / nTotalSys);
				}
			}

			m_ftPrevSysKernel = ftSysKernel;
			m_ftPrevSysUser = ftSysUser;
			m_ftPrevProcKernel = ftProcKernel;
			m_ftPrevProcUser = ftProcUser;

			nCpuCopy = m_nCpuUsage;
		}

		IsFirstRun = false;
		::InterlockedDecrement(&m_lRunCount);

		return nCpuCopy;
	}
private:
	ULONGLONG SubtractTimes(const FILETIME& ftA, const FILETIME& ftB)
	{
		LARGE_INTEGER a, b;
		a.LowPart = ftA.dwLowDateTime;
		a.HighPart = ftA.dwHighDateTime;

		b.LowPart = ftB.dwLowDateTime;
		b.HighPart = ftB.dwHighDateTime;

		return a.QuadPart - b.QuadPart;
	}

	bool IsFirstRun;
	short m_nCpuUsage;

	//system total times
	FILETIME m_ftPrevSysKernel;
	FILETIME m_ftPrevSysUser;

	//process times
	FILETIME m_ftPrevProcKernel;
	FILETIME m_ftPrevProcUser;

	volatile LONG m_lRunCount;
};
#endif

class _NFExport NFCpu
{
public:
    /// @brief ��ȡ��ǰ���̵�cpuʹ��ʱ��
    static long long GetCurCpuTime();

    /// @brief ��ȡ����ϵͳ��cpuʹ��ʱ��
    static long long GetTotalCpuTime();

    /// @brief ������̵�cpuʹ����
    /// @param cur_cpu_time_start ��ǰ����cpuʹ��ʱ���-start
    /// @param cur_cpu_time_stop ��ǰ����cpuʹ��ʱ���-stop
    /// @param total_cpu_time_start ����ϵͳcpuʹ��ʱ���-start
    /// @param total_cpu_time_start ����ϵͳcpuʹ��ʱ���-stop
    static float CalculateCurCpuUseage(long long cur_cpu_time_start, long long cur_cpu_time_stop,
                                       long long total_cpu_time_start, long long total_cpu_time_stop);

    /// @brief ��ȡ���̵�ǰ�ڴ�ʹ�����
    /// @param vm_size_kb �����������棬��λΪK
    /// @param rss_size_kb ��������������ڴ棬��λΪK
    static int GetCurMemoryUsage(int* vm_size_kb, int* rss_size_kb);

	/// @brief ������̵�cpuʹ����
	static int GetCurCpuUseage();

	/// @brief ��ȡ���̵�ǰ�ڴ�ʹ�����
	static int GetCurMemorySize();
};

