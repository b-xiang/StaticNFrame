// -------------------------------------------------------------------------
//    @FileName         :    NFCPluginManager.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2012-12-15
//    @Module           :    NFCPluginManager
//
// -------------------------------------------------------------------------

#ifndef NFC_PLUGIN_MANAGER_H
#define NFC_PLUGIN_MANAGER_H

#include <map>
#include <string>
#include <time.h>
#include <list>
#include "NFComm/NFCore/NFSingleton.hpp"
#include "NFComm/NFPluginModule/NFIPluginManager.h"
#include "NFComm/NFCore/NFRandom.hpp"

/*
	ϵͳ��Module����Ϊ����DLL������ΨһModule�����Լ���������������Module��
	DLL������ΨһModule��ͳһ��ϵͳ������
	���������ĵ���Module,
	���ǵ�Awake,Init,AfterInit�ɴ����߸���
	����ReadExecute��Execute������,�Լ���Դ���ͷ���ϵͳ����
*/

class NFCPluginManager
	: public NFIPluginManager,
	  public NFSingleton<NFCPluginManager>
{
public:
	NFCPluginManager();
	virtual ~NFCPluginManager();

	virtual bool InitSingleton();

	virtual bool Awake() override;

	virtual bool Init() override;

	virtual bool AfterInit() override;

	virtual bool CheckConfig() override;

	virtual bool ReadyExecute() override;

	virtual bool BeforeShut() override;

	virtual bool Shut() override;

	virtual bool Finalize() override;

	virtual bool ReleaseSingletion();

	//////////////////////////////////////////////////////////////////////////

	virtual void RegisteredStaticPlugin(const std::string& strPluginName, const CREATE_PLUGIN_FUNCTION& createFunc) override;

	virtual void Registered(NFIPlugin* pPlugin) override;

	virtual void UnRegistered(NFIPlugin* pPlugin) override;

	//////////////////////////////////////////////////////////////////////////

	virtual NFIPlugin* FindPlugin(const std::string& strPluginName) override;

	virtual void AddModule(const std::string& strModuleName, NFIModule* pModule) override;

	virtual void RemoveModule(const std::string& strModuleName) override;

	virtual NFIModule* FindModule(const std::string& strModuleName) override;

	virtual void RegisterAloneModule(const std::string& strModuleName, const CREATE_ALONE_MODULE& createFunc) override;

	virtual NFIModule* CreateAloneModule(const std::string& strModuleName) override;

	virtual bool Execute() override;

	virtual int GetAppID() const override;

	virtual int GetAppID(int serverType) const override;

	virtual void SetAppID(const int nAppID) override;

	virtual void SetAppID(int serverType, int appID) override;

	virtual const std::string& GetConfigPath() const override;
	virtual void SetConfigPath(const std::string& strPath) override;

	virtual void SetConfigName(const std::string& strFileName) override;
	virtual const std::string& GetConfigName() const override;

	virtual const std::string& GetAppName() const override;

	virtual void SetAppName(const std::string& strAppName) override;

	virtual const std::string& GetLogConfigName() const override;

	virtual void SetLogConfigName(const std::string& strName) override;

	virtual bool IsLoadAllServer() const override;

	virtual uint32_t GetFrame() const
	{
		return mFrame;
	}

	virtual uint32_t GetFrameTime() const
	{
		return mFrameTime;
	}

protected:
	bool LoadPluginConfig();
	bool RegisterStaticPlugin();

	bool LoadStaticPlugin(const std::string& strPluginDLLName);
	bool UnLoadStaticPlugin(const std::string& strPluginDLLName);

	bool LoadKernelPlugin();
private:
	const uint32_t mFrame = 30; //������֡�ʣ�һ��30֡
	const uint32_t mFrameTime = 1000 / mFrame; //һ֡����ʱ��
private:
	int mnAppID;
	std::string mstrConfigPath;
	std::string mstrConfigName;
	std::string mstrAppName;
	std::string mstrLogConfigName;

	typedef std::map<std::string, bool> PluginNameMap;
	typedef std::map<std::string, NFIPlugin*> PluginInstanceMap;
	typedef std::list<NFIPlugin*> PluginInstanceList;
	typedef std::map<std::string, NFIModule*> ModuleInstanceMap;
	typedef std::map<std::string, CREATE_ALONE_MODULE> ModuleAloneFuncMap; //��������,ɾ����Module
	typedef std::map<std::string, CREATE_PLUGIN_FUNCTION> PluginFuncMap; //��̬����Plugin, ��ע�ᴴ������
	typedef std::multimap<std::string, NFIModule*> ModuleAloneMultiMap; //����������Module����
	typedef std::map<int, int> ServerTypeToIdMap; //����AllServer����£�ServerType��ServerId�Ĺ�ϵ

	typedef void (*DLL_START_PLUGIN_FUNC)(NFIPluginManager* pm);
	typedef void (*DLL_STOP_PLUGIN_FUNC)(NFIPluginManager* pm);

	PluginNameMap mPluginNameMap;
	PluginInstanceMap mPluginInstanceMap;
	PluginInstanceList mPluginInstanceList;
	ModuleInstanceMap mModuleInstanceMap;
	ModuleAloneFuncMap mModuleAloneFuncMap; //��������,ɾ����Module
	ServerTypeToIdMap mServerTypeIdMap; //����AllServer����£�ServerType��ServerId�Ĺ�ϵ
	ModuleAloneMultiMap mModuleAloneMultiMap; //����������Module����
	PluginFuncMap mPluginFuncMap; ////��̬����Plugin, ��ע�ᴴ�������ٺ���
};

#endif

