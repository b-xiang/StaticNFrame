// -------------------------------------------------------------------------
//    @FileName         :    logconfig.h
//    @Author           :    GaoYi
//    @Date             :    2018-05-12
//    @Email			:    445267987@qq.com
//    @Module           :    NFCore
//
// -------------------------------------------------------------------------

#pragma once

//��������easylogging, ���ڱ���ʱ�ӷ���

//#define ELPP_THREAD_SAFE                              //
#define ELPP_NO_DEFAULT_LOG_FILE						//��ҪĬ�ϵ��Ǹ�LOG�ļ�
#define ELPP_FEATURE_ALL								//����ʱ�����ӡLOG
//#define ELPP_STACKTRACE


/** 
 * @brief ���ڹ�����Ҫ���ض���easylogging�м�����"��־��ʱ�����"����
 * �Ķ���ȷ��second�� ���������ļ���ʱ������ļ������뾫ȷ��second�� ����:all_server_fatal_%datetime{%Y%M%d%H%m%s}.log
 * ��Ȼ�޷�ʵ�ַָ�
*/