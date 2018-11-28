// -------------------------------------------------------------------------
//    @FileName         :    NFFile.h
//    @Author           :    GaoYi
//    @Date             :    2018-11-27
//    @Email			:    445267987@qq.com
//    @Module           :    NFCore
//
// -------------------------------------------------------------------------

#pragma once

#include "NFException.hpp"
#include "NFCommon.h"

#include <iostream>
#include <fstream>
#include <string>

#if NF_PLATFORM == NF_PLATFORM_WIN
#include <direct.h>
#include <io.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#endif

/////////////////////////////////////////////////
/**
* @file tc_file.h
* @brief  �ļ�������.
*
*/
/////////////////////////////////////////////////


/**
* @brief �ļ��쳣��.
*
*/
struct NF_File_Exception : public NFException
{
	NF_File_Exception(const std::string &buffer) : NFException(buffer) {};
	NF_File_Exception(const std::string &buffer, int err) : NFException(buffer, err) {};
	~NF_File_Exception() throw() {};
};

/**
* @brief �����ļ���������.
*
*/
class NFFile
{
public:
#if NF_PLATFORM == NF_PLATFORM_LINUX
	/**
	* @brief ��ȡ�ļ���С, ����ļ�������, �򷵻�-1.
	*
	* @param  sFullFileName �ļ�ȫ·��(����Ŀ¼���ļ���)
	* @return               ofstream::pos_type�����ļ���С
	*/
	static std::ifstream::pos_type getFileSize(const std::string &sFullFileName);

	/**
	* @brief �ж��Ƿ�Ϊ����·��, ���Կո���'/'��ͷ.
	*
	* @param sFullFileName �ļ�ȫ·��(����Ŀ¼���ļ���)
	* @return              ture�Ǿ���·����false����Ǿ���·��
	*/
	static bool isAbsolute(const std::string &sFullFileName);

	/**
	* @brief �жϸ���·�����ļ��Ƿ����.
	* ����ļ��Ƿ�������,���Է��������ж϶������Է�������ָ����ļ��ж�
	* @param sFullFileName �ļ�ȫ·��
	* @param iFileType     �ļ�����, ȱʡS_IFREG
	* @return           true������ڣ�fals��������
	*/
	static bool isFileExist(const std::string &sFullFileName, mode_t iFileType = S_IFREG);

	/**
	* @brief �жϸ���·�����ļ��Ƿ����.
	* ע��: ����ļ��Ƿ�������,���Է�������ָ����ļ��ж�
	* @param sFullFileName  �ļ�ȫ·��
	* @param iFileType      �ļ�����, ȱʡS_IFREG
	* @return               true-���ڣ�fals-������
	*/
	static bool isFileExistEx(const std::string &sFullFileName, mode_t iFileType = S_IFREG);

	/**
	* @brief ����Ŀ¼����, ��һЩ���õ�ȥ��, ����./��.
	*
	* @param path Ŀ¼����
	* @return        �淶���Ŀ¼����
	*/
	static std::string simplifyDirectory(const std::string& path);

	/**
	* @brief ����Ŀ¼, ���Ŀ¼�Ѿ�����, ��Ҳ���سɹ�.
	*
	* @param sFullPath Ҫ������Ŀ¼����
	* @param iFlag     Ȩ��, Ĭ�� S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP| S_IXGRP | S_IROTH |  S_IXOTH
	* @return bool  true-�����ɹ� ��false-����ʧ��
	*/
	static bool makeDir(const std::string &sDirectoryPath, mode_t iFlag = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);

	/**
	*@brief ѭ������Ŀ¼, ���Ŀ¼�Ѿ�����, ��Ҳ���سɹ�.
	*
	* @param sFullPath Ҫ������Ŀ¼����
	* @param iFlag   Ȩ��, Ĭ�� S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH |  S_IXOTH
	* @return           true-�����ɹ���false-����ʧ��
	*/

	static bool makeDirRecursive(const std::string &sDirectoryPath, mode_t iFlag = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);

	/**
	* @brief �����ļ��Ƿ��ִ��.
	*
	* @param sFullFileName �ļ�ȫ·��
	* @param canExecutable true��ʾ��ִ��, false������֮��
	* @return                 �ɹ�����0, ����ʧ��
	*/
	static int setExecutable(const std::string &sFullFileName, bool canExecutable);

	/**
	* @brief �ж��ļ��Ƿ��ִ��.
	*
	* @param sFullFileName �ļ�ȫ·��
	* @return                 true-��ִ��, false-����ִ��
	*/
	static bool canExecutable(const std::string &sFullFileName);

	/**
	* @brief ɾ��һ���ļ���Ŀ¼.
	*
	* @param sFullFileName �ļ�����Ŀ¼��ȫ·��
	* @param bRecursive    �����Ŀ¼�Ƿ�ݹ�ɾ��
	* @return              0-�ɹ���ʧ�ܿ���ͨ��errno�鿴ʧ�ܵ�ԭ��
	*/
	static int removeFile(const std::string &sFullFileName, bool bRecursive);

	/**
	* @brief ��ȡ�ļ���string
	* �ļ������򷵻��ļ����ݣ������ڻ��߶�ȡ�ļ������ʱ��, ����Ϊ��
	* @param sFullFileName �ļ�����
	* @return              �ļ�����
	*/
	static std::string load2str(const std::string &sFullFileName);

	/**
	* @brief ��ȡ�ļ���vector<char>
	* �ļ������򷵻��ļ����ݣ������ڻ��߶�ȡ�ļ������ʱ��, ����Ϊ��
	* @param sFullFileName �ļ�����
	*/
	static void load2str(const std::string &sFullFileName, std::vector<char> &buffer);

	/**
	* @brief д�ļ�.
	*
	* @param sFullFileName �ļ�����
	* @param sFileData     �ļ�����
	* @return
	*/
	static void save2file(const std::string &sFullFileName, const std::string &sFileData);

	/**
	* @brief д�ļ�.
	*
	* @param sFullFileName  �ļ���
	* @param sFileData      ����ָ��
	* @param length      д�볤��
	* @return               0-�ɹ�,-1-ʧ��
	*/
	static int save2file(const std::string &sFullFileName, const char *sFileData, size_t length);

	/**
	* @brief ��ȡǰ����ִ���ļ�·��.
	*
	* @return string ��ִ���ļ���·��ȫ����
	*/
	static std::string getExePath();

	/**
	* @brief ��ȡ�ļ�����
	*��һ����ȫ�ļ�����ȥ��·��������:/usr/local/temp.gif��ȡtemp.gif
	*@param sFullFileName  �ļ�����ȫ����
	*@return string        ��ȡ����ļ�����
	*/
	static string extractFileName(const std::string &sFullFileName);

	/**
	* @brief ��һ����ȫ�ļ�������ȡ�ļ���·��.
	*
	* ����1: "/usr/local/temp.gif" ��ȡ"/usr/local/"
	* ����2: "temp.gif" ��ȡ "./"
	* @param sFullFileName �ļ�����ȫ����
	* @return              ��ȡ����ļ�·��
	*/
	static std::string extractFilePath(const std::string &sFullFileName);

	/**
	* @brief ��ȡ�ļ���չ��.
	*
	* ����1: "/usr/local/temp.gif" ��ȡ"gif"
	* ����2: "temp.gif" ��ȡ"gif"
	*@param sFullFileName �ļ�����
	*@return              �ļ���չ��
	*/
	static std::string extractFileExt(const std::string &sFullFileName);

	/**
	* @brief ��ȡ�ļ�����,ȥ����չ��.
	* ����1: "/usr/local/temp.gif" ��ȡ"/usr/local/temp"
	* ����2: "temp.gif" ��ȡ"temp"
	* @param sFullFileName �ļ�����
	* @return              ȥ����չ�����ļ�����
	*/
	static std::string excludeFileExt(const std::string &sFullFileName);

	/**
	* @brief �滻�ļ���չ��
	*
	* �ı��ļ����ͣ��������չ��,�������չ�� =?1:
	* ����1��"/usr/temp.gif" �� �� "jpg" �õ�"/usr/temp.jpg"
	* ����2: "/usr/local/temp" �� �� "jpg" �õ�"/usr/local/temp.jpg"
	* @param sFullFileName �ļ�����
	* @param sExt          ��չ��
	* @return              �滻��չ������ļ���
	*/
	static std::string replaceFileExt(const std::string &sFullFileName, const std::string &sExt);

	/**
	* @brief ��һ��url�л�ȡ��ȫ�ļ���.
	*
	* ��ȡ��http://��,��һ��'/'����������ַ�
	* ����1:http://www.qq.com/tmp/temp.gif ��ȡtmp/temp.gif
	* ����2:www.qq.com/tmp/temp.gif ��ȡtmp/temp.gif
	* ����3:/tmp/temp.gif ��ȡtmp/temp.gif
	* @param sUrl url�ַ���
	* @return     �ļ�����
	*/
	static std::string extractUrlFilePath(const std::string &sUrl);

	/**
	* @brief �����ļ�ʱȷ���Ƿ�ѡ��.
	*
	* @return 1-ѡ��, 0-��ѡ��
	*/
	typedef int(*FILE_SELECT)(const dirent *);

	/**
	* @brief ɨ��һ��Ŀ¼.
	*
	* @param sFilePath     ��Ҫɨ���·��
	* @param vtMatchFiles  ���ص��ļ���ʸ����
	* @param f             ƥ�亯��,ΪNULL��ʾ�����ļ�����ȡ
	* @param iMaxSize      ����ļ�����,iMaxSize <=0ʱ,��������ƥ���ļ�
	* @return              �ļ�����
	*/
	static size_t scanDir(const std::string &sFilePath, std::vector<std::string> &vtMatchFiles, FILE_SELECT f = NULL, int iMaxSize = 0);

	/**
	* @brief ����Ŀ¼, ��ȡĿ¼����������ļ�����Ŀ¼.
	*
	* @param path       ��Ҫ������·��
	* @param files      Ŀ��·�����������ļ�
	* @param bRecursive �Ƿ�ݹ���Ŀ¼
	*
	**/
	static void listDirectory(const std::string &path, vector<std::string> &files, bool bRecursive);

	/**
	* @brief �����ļ���Ŀ¼.
	* ���ļ�����Ŀ¼��sExistFile���Ƶ�sNewFile
	* @param sExistFile ���Ƶ��ļ�����Ŀ¼Դ·��
	* @param sNewFile   ���Ƶ��ļ�����Ŀ¼Ŀ��·��
	* @param bRemove    �Ƿ���ɾ��sNewFile��copy ����ֹTextfile busy���¸���ʧ��
	* @return
	*/
	static void copyFile(const std::string &sExistFile, const std::string &sNewFile, bool bRemove = false);
#endif
};
