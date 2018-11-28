// -------------------------------------------------------------------------
//    @FileName         :    NFTarsParse.h
//    @Author           :    GaoYi
//    @Date             :    2018-11-27
//    @Email			:    445267987@qq.com
//    @Module           :    NFCore
//
// -------------------------------------------------------------------------

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <stack>
#include <sstream>
#include "NFPlatform.h"
#include "NFAutoPtr.h"
#include "NFTarsElement.h"
#include "NFCommon.h"

enum yytokentype {
	TARS_VOID = 258,
	TARS_STRUCT = 259,
	TARS_BOOL = 260,
	TARS_BYTE = 261,
	TARS_SHORT = 262,
	TARS_INT = 263,
	TARS_DOUBLE = 264,
	TARS_FLOAT = 265,
	TARS_LONG = 266,
	TARS_STRING = 267,
	TARS_VECTOR = 268,
	TARS_MAP = 269,
	TARS_NAMESPACE = 270,
	TARS_INTERFACE = 271,
	TARS_IDENTIFIER = 272,
	TARS_OUT = 273,
	TARS_OP = 274,
	TARS_KEY = 275,
	TARS_ROUTE_KEY = 276,
	TARS_REQUIRE = 277,
	TARS_OPTIONAL = 278,
	TARS_CONST_INTEGER = 279,
	TARS_CONST_FLOAT = 280,
	TARS_FALSE = 281,
	TARS_TRUE = 282,
	TARS_STRING_LITERAL = 283,
	TARS_SCOPE_DELIMITER = 284,
	TARS_CONST = 285,
	TARS_ENUM = 286,
	TARS_UNSIGNED = 287,
	BAD_CHAR = 288
};

#define TARS_VERSION 1

/**
* Tars�ļ�������
*
*/
class TarsParse : public NF_HandleBase
{
public:
	/**
	* ���캯��
	*/
	TarsParse();

	/**
	* �Ƿ�֧��tars��ͷ�ı�ʶ
	* @param bWithTars
	*/
	void setTars(bool bWithTars);

	/**
	* ͷ�ļ�·��
	* @param sHeader
	*/
	void setHeader(const std::string &sHeader);

	/**
	* �Ƿ�֧������ʹ�õ�ǰtars�ļ�
	* @param bWithTars
	*/
	void setCurrentPriority(bool bFlag);

	/**
	* ��ȡͷ�ļ�·��
	*/
	std::string getHeader();

	/**
	* ����ĳһ���ļ�
	* @param sFileName
	*/
	void parse(const std::string &sFileName);

	/**
	* ������ʾ
	* @param msg
	*/
	void error(const std::string &msg);

	/**
	* ���ؼ���
	* @param s
	*
	* @return int
	*/
	int  checkKeyword(const std::string &s);

	/**
	* ��һ��
	*/
	void nextLine();

	/**
	* Ŀǰ�������ļ�����
	*
	* @return string
	*/
	std::string getCurrFileName();

	/**
	* tab
	*
	* @return string
	*/
	std::string getTab();

	/**
	* ����tab��
	*/
	void incTab() { _itab++; }

	/**
	* ����tab��
	*/
	void delTab() { _itab--; }

	/**
	* �����ļ�
	* @param file
	*/
	void pushFile(const std::string &file);

	/**
	* ���������ļ�
	*/
	ContextPtr popFile();

	/**
	* ��ȡ���е�������
	*
	* @return std::vector<ContextPtr>
	*/
	std::vector<ContextPtr> getContexts() { return _vcontexts; }

	/**
	* ��ȡĿǰ������
	*
	* @return ContainerPtr
	*/
	ContainerPtr currentContainer();

	/**
	* push����
	* @param c
	*/
	void pushContainer(const ContainerPtr &c);

	/**
	* Ŀǰ��������
	*
	* @return ContextPtr
	*/
	ContextPtr currentContextPtr();

	/**
	* ��������
	*
	* @return ContainerPtr
	*/
	ContainerPtr popContainer();

	/**
	* ����BuiltinԪ��
	* @param kind
	*
	* @return BuiltinPtr
	*/
	BuiltinPtr createBuiltin(Builtin::Kind kind, bool isUnsigned = false);

	/**
	* ����VectorԪ��
	* @param ptr
	*
	* @return VectorPtr
	*/
	VectorPtr createVector(const TypePtr &ptr);

	/**
	* ����MapԪ��
	* @param pleft
	* @param pright
	*
	* @return MapPtr
	*/
	MapPtr createMap(const TypePtr &pleft, const TypePtr &pright);

	/**
	* ��ӽṹԪ��
	* @param sPtr
	*/
	void addStructPtr(const StructPtr &sPtr);

	/**
	* ���ҽṹ
	* @param id
	*
	* @return StructPtr
	*/
	StructPtr findStruct(const string &sid);

	/**
	* ���ö��Ԫ��
	* @param ePtr
	*/
	void addEnumPtr(const EnumPtr &ePtr);

	/**
	* ���ҽṹ
	* @param id
	*
	* @return EnumPtr
	*/
	EnumPtr findEnum(const std::string &sid);

	/**
	* ����ͻ
	* @param id
	*/
	void checkConflict(const std::string &sid);

	/**
	* �����Զ�������
	* @param sid
	*
	* @return TypePtr
	*/
	TypePtr findUserType(const std::string &sid);

	/**
	* �������ֿռ�
	* @param id
	*
	* @return NamespacePtr
	*/
	NamespacePtr findNamespace(const std::string &id);

	/**
	* Ŀǰ�����ֿռ�
	*
	* @return NamespacePtr
	*/
	NamespacePtr currentNamespace();

	/**
	* ���tag�ĺϷ���
	* @param i
	*/
	void checkTag(int i);


	/**
	* ���szie�ĺϷ���
	* @param i
	*/
	void checkSize(int i);

	/**
	* ���array�ĺϷ���
	* @param i
	*/
	void checkArrayVaid(TypePtr &tPtr, int size);

	/**
	* ���pointer�ĺϷ���
	* @param i
	*/
	void checkPointerVaid(TypePtr &tPtr);

	/**
	* ��鳣�����ͺ�ֵ�Ƿ�һ��
	* @param c
	* @param b
	*/
	void checkConstValue(TypeIdPtr &tPtr, int b);

	/**
	* ��ȡ�ļ���
	* @param s
	*
	* @return string
	*/
	bool getFilePath(const std::string &s, std::string &file);

	void setKeyStruct(const StructPtr& key)
	{
		_key = key;
	}

	StructPtr getKeyStruct()
	{
		return _key;
	}

	/**
	* ��ӡ�ļ���ͷע��
	*/
	std::string printHeaderRemark();


	/**
	* �жϵ�ǰ�ı�ʶ���Ƿ���ö�ٱ���
	*/
	bool checkEnum(const std::string &idName);

	/**

	* ����include��tars�ļ�ȫ���ӵ�ǰ�ļ���Ѱ
	*/
	void setUseCurrentPath(const bool & bEnable) { _bUseCurrentPath = bEnable; }

	/**
	* ����tars�ļ�ʱ,����include·��
	*/
	void addIncludePath(const std::string &include)
	{
		std::vector<std::string> v = NFCommon::sepstr<std::string>(include, "; ,", false);

		_vIncludePath.insert(_vIncludePath.end(), v.begin(), v.end());
	}

protected:
	/**
	* ������ֿռ�
	* @param nPtr
	*/
	void addNamespacePtr(const NamespacePtr &nPtr);

	/**
	* ��ʼ��
	*/
	void initScanner();

	/**
	* ���
	*/
	void clear();

protected:
	bool                            _bWithTars;
	std::map<std::string, int>      _keywordMap;
	int                             _itab;
	StructPtr                       _key;
	std::stack<ContextPtr>          _contexts;
	std::stack<ContainerPtr>        _contains;
	std::vector<ContextPtr>         _vcontexts;
	std::vector<StructPtr>          _structs;
	std::vector<EnumPtr>            _enums;
	std::vector<NamespacePtr>       _namespaces;
	std::string                          _sHeader;
	bool                            _bUseCurrentPath;
	bool                            _bUseCurrentPathFirst;
	std::vector<string>             _vIncludePath;
};

extern int yyparse();
extern int yylex();
extern FILE *yyin, *yyout;

typedef NFAutoPtr<TarsParse> TarsParsePtr;

extern TarsParsePtr g_parse;
