CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(NFPluginLoader)

AUX_SOURCE_DIRECTORY(. SRC)

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} rt dl ${LIB_LINK_DEP} ${LIB_LINK_NF})

ADD_DEPENDENCIES(NFPluginLoader LuaBind G3Dlite Common Navigation 
NFMessageDefine NFCore NFKernelPlugin NFMath NFNetPlugin NFPluginModule NFTestPlugin NFActorPlugin NFLuaScriptPlugin NFMongoPlugin NFMysqlPlugin 
NFGameClientPlugin NFGameServerPlugin NFLoginClientPlugin NFLoginServerPlugin NFMasterServerPlugin NFProxyClientPlugin NFProxyServerPlugin 
NFServerCommon NFWorldClientPlugin NFWorldServerPlugin NFGameLogicPlugin NFLoginLogicPlugin NFProxyLogicPlugin NFServerLogicCommon)


if (CMAKE_BUILD_TYPE MATCHES "Release")
	SET_TARGET_PROPERTIES(${PROJECT_NAME} 
		PROPERTIES 
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Product/run/Release"
	)
else()
	SET_TARGET_PROPERTIES(${PROJECT_NAME} 
		PROPERTIES 
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Product/run/Debug"
	)
endif()




