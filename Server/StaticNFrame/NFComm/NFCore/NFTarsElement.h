// -------------------------------------------------------------------------
//    @FileName         :    NFTarsElement.h
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
#include "NFAutoPtr.h"

using namespace std;


void yyerror(char const *msg);

/**
* �﷨Ԫ�ػ���
*/
class GrammarBase : virtual public NF_HandleBase
{
public:
	virtual ~GrammarBase() {};
};

typedef NFAutoPtr<GrammarBase> GrammarBasePtr;

/**
* ���������е��ַ���
*/
class StringGrammar : public GrammarBase
{
public:

	StringGrammar() { }
	string v;
};

typedef NFAutoPtr<StringGrammar> StringGrammarPtr;

/**
* ���������е�������
*/
class IntergerGrammar : public GrammarBase
{
public:

	IntergerGrammar() :v(0) { }
	long long v;
};

typedef NFAutoPtr<IntergerGrammar> IntergerGrammarPtr;

/**
* ���������еĸ�����
*/
class FloatGrammar : public GrammarBase
{
public:

	FloatGrammar() :v(0.0f) { }
	double v;
};

typedef NFAutoPtr<FloatGrammar> FloatGrammarPtr;

/**
* ���������е�bool����
*/
class BoolGrammar : public GrammarBase
{
public:

	BoolGrammar() :v(false) { }
	bool v;
};

typedef NFAutoPtr<BoolGrammar> BoolGrammarPtr;

/**
* ���������еĳ�����
*/
class ConstGrammar : public GrammarBase
{
public:

	ConstGrammar() :t(VALUE) { }

	enum
	{
		VALUE,
		STRING,
		BOOL,
		ENUM
	};

	int    t;
	string v;
};

typedef NFAutoPtr<ConstGrammar> ConstGrammarPtr;

///////////////////////////////////////////////

/**
* ���ͻ���
*/
class Type : virtual public GrammarBase
{
public:
	/**
	* ���캯��
	* @param Type
	*/
	Type() :_size(0), _array(false), _pointer(false) {};

	//�Ƿ������
	virtual bool isSimple() const { return false; }

	//�Ƿ���������
	virtual bool isArray() const { return _array; }
	virtual void setArray(int size) { _array = true; _size = size; }
	virtual int  getSize() const { return _size; };

	//�Ƿ�ָ������
	virtual bool isPointer() const { return _pointer; }
	virtual void setPointer(bool b) { _pointer = b; }
public:
	int     _size;
	bool    _array;
	bool    _pointer;
};

typedef NFAutoPtr<Type> TypePtr;

/**
* �ڽ�����
*/
class Builtin : public Type
{
public:

	enum Kind
	{
		KindVoid,
		KindBool,
		KindByte,
		KindShort,
		KindInt,
		KindLong,
		KindFloat,
		KindDouble,
		KindString,
		KindVector,
		KindMap
	};

	/**
	* ���캯��
	* @param kind
	*/
	Builtin(Kind kind, bool isUnsigned);

	/**
	* ����
	*
	* @return Kind
	*/
	Kind kind() const;

	/**
	* �Ƿ��Ǽ�����
	*
	* @return bool
	*/
	bool isSimple() const;

	/**
	* �Ƿ���unsined����
	*
	* @return bool
	*/
	bool isUnsigned() const { return _isUnsigned; }

	/**
	* ������unsined����
	*
	* @return bool
	*/
	void setUnsigned(bool isUnsigned = false) { _isUnsigned = isUnsigned; }

	/**
	* ȱʡֵ
	*
	* @return string
	*/
	string def() const;

	/**
	* �ַ�����ʾ
	*/
	static const char* builtinTable[];

protected:

	Kind _kind;
	bool _isUnsigned;
};

typedef NFAutoPtr<Builtin> BuiltinPtr;

/**
* Vector����
*/
class Vector : public Type
{
public:
	/**
	* ���캯��
	* @param ptr
	*/
	Vector(const TypePtr& ptr);

	/**
	* ��ȡ����
	*
	* @return TypePtr&
	*/
	TypePtr& getTypePtr() { return _ptr; }
protected:
	TypePtr _ptr;
};

typedef NFAutoPtr<Vector> VectorPtr;

/**
* Map����
*/
class Map : public Type
{
public:
	/**
	* ���캯��
	* @param pleft
	* @param pright
	*/
	Map(const TypePtr& pleft, const TypePtr& pright);

	/**
	* ��ȡ������
	*
	* @return TypePtr&
	*/
	TypePtr& getLeftTypePtr() { return _pleft; }

	/**
	* ��ȡ������
	*
	* @return TypePtr&
	*/
	TypePtr& getRightTypePtr() { return _pright; }

protected:
	TypePtr _pleft;
	TypePtr _pright;
};

typedef NFAutoPtr<Map> MapPtr;

/**
* ��������
*/
class TypeId : public GrammarBase
{
public:
	/**
	* ���캯��
	* @param ptr
	* @param id
	*/
	TypeId(const TypePtr& ptr, const string& id);

	/**
	* ��������
	*
	* @return string
	*/
	string getId() const { return _id; }

	/**
	* ��������
	*
	* @return Type*
	*/
	TypePtr& getTypePtr() { return _ptr; }

	/**
	* �Ƿ���Ҫ�ò���
	*
	* @return bool
	*/
	bool isRequire() const { return _bRequire; }

	/**
	* ���ñ�ѡ�ֶ�
	* @param tag
	*/
	void setRequire(int tag);

	/**
	* ���ÿ�ѡ�ֶ�
	* ֻ�л������Ͳ���ȱʡֵ
	*/
	void setDefault(const string &def);

	/**
	*
	* ֻ�л������Ͳ���ȱʡֵ
	*/
	void disableDefault();

	/**
	* ���ÿ�ѡ�ֶ�
	* @param tag
	*/
	void setOptional(int tag);

	/**
	* tag��ʶ
	*/
	int getTag() const { return _tag; }

	/**
	* ȱʡֵ
	*
	* @return string
	*/
	string def() const { return _default; }

	/**
	* �Ƿ���ȱʡֵ
	*
	* @return bool
	*/
	bool hasDefault() const { return _bHasDefault; }

protected:
	TypePtr _ptr;
	string  _id;
	bool    _bRequire;
	int     _tag;
	bool    _bHasDefault;
	string  _default;

public:
	int     _size;
	bool    _array;
};

typedef NFAutoPtr<TypeId> TypeIdPtr;


////////////////////////////////////////////////////
//
class Namespace;
typedef NFAutoPtr<Namespace> NamespacePtr;
/**
* ��������, ���п��԰�������Ԫ�ص�Ԫ�ض��Ӹû���̳�
*/
class Container : virtual public GrammarBase
{
public:
	/**
	* ���캯��
	* @param id
	*/
	Container(const string &id) : _id(id)
	{
	}

	/**
	* �������ֿռ�
	* @param id
	*
	* @return NamespacePtr
	*/
	NamespacePtr createNamespace(const string &id);

	/**
	* ��ȡID
	*
	* @return string
	*/
	string getId() const { return _id; }

	/**
	* ��ȡ���е����ֿռ�
	*
	* @return vector<NamespacePtr>&
	*/
	vector<NamespacePtr> &getAllNamespacePtr() { return _ns; }
protected:
	string                  _id;
	vector<NamespacePtr>    _ns;
};

typedef NFAutoPtr<Container> ContainerPtr;

////////////////////////////////////////////////////
//
class Const : public GrammarBase
{
public:
	/**
	*
	* @param tPtr
	* @param cPtr
	*/
	Const(TypeIdPtr &tPtr, ConstGrammarPtr &cPtr) : _tPtr(tPtr), _cPtr(cPtr)
	{
	}

	/**
	*
	*
	* @return TypePtr&
	*/
	TypeIdPtr &getTypeIdPtr() { return _tPtr; }

	/**
	*
	*
	* @return ConstGrammarPtr
	*/
	ConstGrammarPtr getConstGrammarPtr() { return _cPtr; }

protected:
	TypeIdPtr   _tPtr;
	ConstGrammarPtr _cPtr;
};

typedef NFAutoPtr<Const> ConstPtr;

/////////////////////////////////////////////////////////
//
class Enum : virtual public Container, virtual public Type
{
public:
	Enum(const string &id, const string &sid) : Container(id), _sid(sid)
	{
	}

	/**
	* ��ӳ�Ա����
	* @param ptid
	*/
	void addMember(const TypeIdPtr &ptr);

	/**
	* ��ȡ���еĳ�Ա����
	*
	* @return vector<TypeIdPtr>&
	*/
	vector<TypeIdPtr>& getAllMemberPtr() { return _members; }

	/**
	* ��ȡ�ṹ������
	*
	* @return string
	*/
	string getSid() const { return _sid; }

	/**
	* �Ƿ��Ǽ�����
	*
	* @return bool
	*/
	virtual bool isSimple() const { return true; }

protected:

	/**
	* ÿ����������
	*/
	vector<TypeIdPtr>   _members;

	/**
	* �������ֵĿռ������
	*/
	string          _sid;
};

typedef NFAutoPtr<Enum> EnumPtr;

////////////////////////////////////////////////////
//
/**
* �ṹ
*/
class Struct : virtual public Container, virtual public Type
{
public:
	/**
	* ���캯��
	* @param id
	*/
	Struct(const string& id, const string &sid) : Container(id), _sid(sid)
	{
	}

	/**
	* ��ӳ�Ա����
	* @param ptid
	*/
	void addTypeId(const TypeIdPtr &ptr);

	/**
	* ��ȡ���еĳ�Ա����
	*
	* @return vector<TypeIdPtr>&
	*/
	vector<TypeIdPtr>& getAllMemberPtr() { return _members; }

	/**
	* ��ȡ�ṹ������
	*
	* @return string
	*/
	string getSid() const { return _sid; }

	/**
	* ����С��memeber
	* @param member
	*/
	void addKey(const string &member);

	vector<string> getKey() { return _key; }
protected:
	vector<TypeIdPtr>   _members;
	vector<string>      _key;
	string              _sid;
};

typedef NFAutoPtr<Struct> StructPtr;

////////////////////////////////////////////////////
//
/**
* ��������
*/
class ParamDecl : public GrammarBase
{
public:
	/**
	* ����
	* @param typeIdPtr
	* @param v
	*/
	ParamDecl(const TypeIdPtr &typeIdPtr, bool v, bool k)
		: _typeIdPtr(typeIdPtr), _v(v), _k(k)
	{
	}

	/**
	* ��������
	*
	* @return TypeIdPtr&
	*/
	TypeIdPtr& getTypeIdPtr() { return _typeIdPtr; }

	/**
	* �Ƿ����������
	*
	* @return bool
	*/
	bool    isOut() const { return _v; }

	/**
	* �Ƿ�����Ҫ·�ɵ��ֶ�
	*
	* @return bool
	*/
	bool    isRouteKey() const { return _k; }

protected:
	TypeIdPtr   _typeIdPtr;
	bool        _v;
	bool        _k;
};
typedef NFAutoPtr<ParamDecl> ParamDeclPtr;

///////////////////////////////////////////////////////
//
/**
* ������
*/
class Operation : public Container
{
public:
	/**
	* ���캯��
	* @param id
	* @param typePtr
	*/
	Operation(const string &id, const TypePtr &typePtr) : Container(id), _itag(0)
	{
		_retPtr = new TypeId(typePtr, "_ret");
		_retPtr->setRequire(_itag);
	}

	/**
	* ����һ������
	* @param typeIdPtr
	* @param v
	* @param k
	*
	* @return ParamDeclPtr
	*/
	ParamDeclPtr createParamDecl(const TypeIdPtr &typeIdPtr, bool v, bool k);

	/**
	* ��ȡ����ֵ����
	*
	* @return TypePtr&
	*/
	TypeIdPtr &getReturnPtr() { return _retPtr; }

	/**
	* ��ȡ���в���
	*
	* @return vector<ParamDeclPtr>&
	*/
	vector<ParamDeclPtr> &getAllParamDeclPtr() { return _ps; }
protected:
	int                     _itag;
	TypeIdPtr               _retPtr;
	vector<ParamDeclPtr>    _ps;
};

typedef NFAutoPtr<Operation> OperationPtr;
///////////////////////////////////////////////////////
//
/**
* �ӿ�����
*/
class Interface : public Container
{
public:
	/**
	* ����
	* @param id
	*/
	Interface(const string &id) : Container(id)
	{
	}

	/**
	* ����һ������
	* @param id
	* @param typePtr
	*
	* @return OperationPtr
	*/
	OperationPtr createOperation(const string &id, const TypePtr &typePtr);

	/**
	* ��ȡ���в���
	*
	* @return vector<OperationPtr>&
	*/
	vector<OperationPtr> &getAllOperationPtr() { return _ops; }
protected:
	vector<OperationPtr>    _ops;
};

typedef NFAutoPtr<Interface> InterfacePtr;

/////////////////////////////////////////////////////////
//
/**
* ���ֿռ�
*/
class Namespace : public Container
{
public:
	/**
	* ���캯��
	* @param id
	*/
	Namespace(const string &id) : Container(id)
	{
	}

	/**
	* ���ɽӿ�
	* @param id
	*
	* @return InterfacePtr
	*/
	InterfacePtr createInterface(const string &id);

	/**
	* ���ɽṹ
	* @param id
	*
	* @return StructPtr
	*/
	StructPtr createStruct(const string& id);

	/**
	* ����ö������
	* @param id
	*
	* @return EnumPtr
	*/
	EnumPtr createEnum(const string &id);

	/**
	*
	* @param pPtr
	* @param cPtr
	*
	* @return ConstPtr
	*/
	ConstPtr createConst(TypeIdPtr &pPtr, ConstGrammarPtr &cPtr);

	/**
	* �Ƿ��нӿ�
	*
	* @return bool
	*/
	bool hasInterface() const { return !_is.empty(); }

	/**
	* ��ȡ���еĽӿ�
	*
	* @return vector<InterfacePtr>&
	*/
	vector<InterfacePtr> &getAllInterfacePtr() { return _is; }

	/**
	* ��ȡ���еĽṹ
	*
	* @return vector<StructPtr>&
	*/
	vector<StructPtr> &getAllStructPtr() { return _ss; }

	/**
	* ����ö������
	*
	* @return vector<EnumPtr>&
	*/
	vector<EnumPtr> &getAllEnumPtr() { return _es; }

	/**
	* ��������
	*
	* @return vector<ConstPtr>&
	*/
	vector<ConstPtr> &getAllConstPtr() { return _cs; }

protected:
	vector<InterfacePtr>    _is;
	vector<StructPtr>       _ss;
	vector<EnumPtr>         _es;
	vector<ConstPtr>        _cs;
};

/////////////////////////////////////////////////////////////////
/**
* ������
*/
class Context : public NF_HandleBase
{
public:
	/**
	* ���캯��
	*/
	Context(const string &file) : _currline(1), _filename(file)
	{
	}

	/**
	* ��һ��
	*/
	void nextLine() { _currline++; }

	/**
	* Ŀǰ����
	*
	* @return size_t
	*/
	size_t getCurrLine() { return _currline; }

	/**
	* ��ǰ�ļ���
	*
	* @return string
	*/
	string getFileName() { return _filename; }

	/**
	* ���include���ļ�
	* @param incl
	*/
	void addInclude(const string &incl);

	/**
	* �����������ļ������ֿռ�
	* @param c
	*/
	void addNamespacePtr(const NamespacePtr &c)
	{
		_namespaces.push_back(c);
	}

	/**
	* ��ȡincludes���ļ�
	*
	* @return vector<string>
	*/
	vector<string> getIncludes() { return _includes; }

	/**
	* ��ȡ���ֿռ�
	*
	* @return vector<NamespacePtr>
	*/
	vector<NamespacePtr> getNamespaces() { return _namespaces; }

protected:
	size_t                  _currline;
	string                  _filename;
	vector<string>          _includes;
	vector<NamespacePtr>    _namespaces;
};

typedef NFAutoPtr<Context> ContextPtr;
