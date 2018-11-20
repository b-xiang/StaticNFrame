// -------------------------------------------------------------------------
//    @FileName         :    NFCLuaScriptModule.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2013-07-08
//    @Module           :    NFCLuaScriptModule
//    @Desc             :
// -------------------------------------------------------------------------

#ifndef NFC_LUA_SCRIPT_MODULE_H
#define NFC_LUA_SCRIPT_MODULE_H

#define LUAINTF_LINK_LUA_COMPILED_IN_CXX 0
#include "Dependencies/LuaBind/luaintf/LuaIntf.h"

#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFComm/NFPluginModule/NFILuaScriptModule.h"
#include "NFComm/NFPluginModule/NFIScriptModule.h"
#include "NFComm/NFPluginModule/NFIEventModule.h"
#include "NFComm/NFPluginModule/NFIEventModule.h"

#include "NFComm/NFPluginModule/NFTimerMgr.h"

namespace LuaIntf
{
	LUA_USING_SHARED_PTR_TYPE(std::shared_ptr);
	LUA_USING_LIST_TYPE(std::vector)
	LUA_USING_MAP_TYPE(std::map)
}

typedef LuaIntf::LuaRef NFLuaRef;
typedef LuaIntf::LuaTableRef NFLuaTableRef;

class NFLuaTimer
{
public:
	NFLuaTimer()
	{
		mTimerId = 0;
		mInterVal = 0;
		mCallCount = 0;
	}
	uint32_t mTimerId;
	std::string mLuaFunc;
	uint64_t mInterVal;
	uint32_t mCallCount;
	uint32_t mCurCallCount;
	std::string mUseData;
};

class NFCLuaScriptModule
    : public NFILuaScriptModule, public NFTimerObj
{
public:
    NFCLuaScriptModule(NFIPluginManager* p)
    {
        pPluginManager = p;
		m_luaTimerIndex = 10000;
    }
public:
	lua_State* GetLuaState() const
	{
		return l.state();
	}
public:
	template <typename V = LuaIntf::LuaRef>
	V GetGlobal(const std::string& keyName) const
	{
		return l.getGlobal(keyName.c_str());
	}

	template <typename T>
	bool GetValue(const std::string& keyName, T& value) const
	{
		LuaIntf::LuaRef ref = GetGlobal(keyName);
		if (!ref.isValid())
		{
			return false;
		}

		try
		{
			value = ref.toValue<T>();
			return true;
		}
		catch (LuaIntf::LuaException& e)
		{
			std::cout << e.what() << std::endl;
		}

		return true;
	}

public:
	bool TryLoadScriptString(const std::string& strScript)
	{
		try
		{
			l.doString(strScript.c_str());
			return true;
		}
		catch (LuaIntf::LuaException& e)
		{
			std::cout << e.what() << std::endl;
		}
		return false;
	}

	bool TryLoadScriptFile(const std::string& strFileName)
	{
		try
		{
			l.doFile(strFileName.c_str());
			return true;
		}
		catch (LuaIntf::LuaException& e)
		{
			std::cout << e.what() << std::endl;
		}
		return false;
	}

	bool TryAddPackagePath(const std::string& strFilePath)
	{
		try
		{
			l.addPackagePath(strFilePath);
			return true;
		}
		catch (LuaIntf::LuaException& e)
		{
			std::cout << e.what() << std::endl;
		}
		return false;
	}

public:
	bool TryRunGlobalScriptFunc(const std::string& strFuncName) const
	{
		try
		{
			LuaIntf::LuaRef func(l, strFuncName.c_str());
			func.call<LuaIntf::LuaRef>();
			return true;
		}
		catch (LuaIntf::LuaException& e)
		{
			std::cout << e.what() << std::endl;
		}
		return false;
	}

	template <typename... Arg>
	bool TryRunGlobalScriptFunc(const std::string& strFuncName, Arg&&... args)
	{
		try
		{
			LuaIntf::LuaRef func(l, strFuncName.c_str());
			func.call<LuaIntf::LuaRef>(std::forward<Arg>(args)...);
			return true;
		}
		catch (LuaIntf::LuaException& e)
		{
			std::cout << e.what() << std::endl;
		}
		return false;
	}

public:
	template <typename KEY, typename VALUE>
	bool GetLuaTableValue(const LuaIntf::LuaRef& table, const KEY& keyName, VALUE& value)
	{
		try
		{
			LuaIntf::LuaRef valueRef = table[keyName];
			if (!valueRef.isValid())
			{
				std::cout << "load lua table " << keyName << " failed!" << std::endl;
				return false;
			}

			value = valueRef.toValue<VALUE>();
			return true;
		}
		catch (LuaIntf::LuaException& e)
		{
			std::cout << e.what() << std::endl;
		}
		return false;
	}
public:

    virtual bool Init();
    virtual bool AfterInit();
	virtual bool ReadyExecute();

    virtual bool Execute();

    virtual bool BeforeShut();
    virtual bool Shut();
    virtual bool Finalize();
public:
	virtual void RunNetRecvLuaFunc(const std::string& luaFunc, const uint32_t unLinkId, const uint64_t valueId, const uint32_t nMsgId, const std::string& strMsg) override;
	virtual void RunNetEventLuaFunc(const std::string& luaFunc, const eMsgType nEvent, const uint32_t unLinkId) override;
	virtual void RunHtttpClientLuaFunc(const std::string& luaFunc, const int state_code, const std::string& strRespData, const std::string& strUserData) override;
	virtual void RunHttpServerLuaFunc(const std::string& luaFunc, const NFHttpRequest & req) override;
public:
	virtual void OnTimer(uint32_t nTimerID) override;
	virtual uint32_t AddTimer(const std::string& luaFunc, uint64_t nInterVal, const std::string& useData) override;
	virtual uint32_t AddClocker(const std::string& luaFunc, uint64_t nStartTime, uint32_t nInterDays, const std::string& useData) override;
	virtual void StopTimer(uint32_t nTimerID) override;
	virtual void StopClocker(uint32_t nTimerID) override;
public:
    bool Register();
	void LoadScript();
protected:
    NFIKernelModule* m_pKernelModule;
    NFIEventModule* m_pEventModule;
protected:
    int64_t mnTime;
protected:
	LuaIntf::LuaContext l;
protected:
	std::map<uint64_t, NFLuaTimer> m_luaTimerMap;
	uint32_t m_luaTimerIndex;
};

#endif
