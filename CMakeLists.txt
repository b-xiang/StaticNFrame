CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

add_compile_options(-std=c++11)

if( CMAKE_BUILD_TYPE MATCHES "Release" )
	set(CMAKE_BUILD_TYPE "Release")
	set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -fPIC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fPIC -std=c++11 -O3 -Wall")
	add_definitions(
        -DNDEBUG
        -fPIC
    )
else()
	set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -fPIC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0 -Wall -g -ggdb -fPIC")
	add_definitions(
        -D_DEBUG
        -fPIC
    )
endif()

message("PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message("CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")

SET(INCLUDE_DIR "./" "/usr/local/include"
	"${CMAKE_SOURCE_DIR}/Server"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/LuaBind/lua5.3"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/LuaBind/"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/g3dlite"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/libevent/include/"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/libevent/linux/include/"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/Theron/Include"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/protobuf/src"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/navigation"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/mysql/include"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/mysql/linux"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/mysqlpp/lib"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/mongo/src/libmongoc/src/mongoc"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/mongo/src/libmongoc/src"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/mongo/src/libbson/src"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/mongo/src/libbson/src/bson"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/mongo/linux"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/openssl/include"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/openssl/linux/include"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/common/sigar/linux"
	"${CMAKE_SOURCE_DIR}/Server/StaticNFrame/")


if (CMAKE_BUILD_TYPE MATCHES "Release")
		SET(LIB_DIR "/usr/lib"
			"/usr/local/lib"
			"/usr/lib64"
			"/usr/local/lib64"
			"${CMAKE_SOURCE_DIR}/Product/run/Release"
			"${CMAKE_SOURCE_DIR}/Product/Lib/Release")
else()
	SET(LIB_DIR "/usr/lib"
		"/usr/local/lib"
		"/usr/lib64"
		"/usr/local/lib64"
		"${CMAKE_SOURCE_DIR}/Product/run/Debug"
		"${CMAKE_SOURCE_DIR}/Product/Lib/Debug")
endif()

SET(LIB_LINK_DEP resolv dl rt libssl.a libcrypto.a pthread libbson-static-1.0.a libmysqlpp.a libmysqlclient.a libevent_core.a libevent_extra.a libtheron.a
		libevent.a libLuaBind.a libtheron.a libprotobuf.a libmongoc-static-1.0.a libbson-static-1.0.a libCommon.a)
		
SET(LIB_LINK_NF libNFActorPlugin.a libNFCore.a libNFKernelPlugin.a libNFLuaScriptPlugin.a
				libNFMath.a libNFMessageDefine.a libNFNetPlugin.a libNFPluginModule.a libNFMongoPlugin.a
				libNFTestPlugin.a libNFMysqlPlugin.a libNFGameClientPlugin.a libNFGameServerPlugin.a 
				libNFLoginClientPlugin.a libNFLoginServerPlugin.a libNFMasterServerPlugin.a 
				libNFProxyClientPlugin.a libNFProxyServerPlugin.a 
				libNFServerCommon.a libNFWorldClientPlugin.a libNFWorldServerPlugin.a
				libNFGameLogicPlugin.a libNFLoginLogicPlugin.a libNFProxyLogicPlugin.a libNFServerLogicCommon.a)
	
include_directories( ${INCLUDE_DIR} )
	

link_directories( ${LIB_DIR} )


ADD_SUBDIRECTORY("Server/Dependencies")
ADD_SUBDIRECTORY("Server/NFMessageDefine")
ADD_SUBDIRECTORY("Server/StaticNFrame/NFComm")
ADD_SUBDIRECTORY("Server/StaticNFrame/NFTest")
ADD_SUBDIRECTORY("Server/NFServer")
ADD_SUBDIRECTORY("Server/NFServerLogic")
ADD_SUBDIRECTORY("Server/StaticNFrame/NFPluginLoader")
