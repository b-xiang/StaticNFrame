CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
add_compile_options(-std=c++11)
SET(CMAKE_C_COMPILER "ccache")
SET(CMAKE_C_COMPILER_ARG1 " gcc")
SET(CMAKE_CXX_COMPILER  "ccache")
SET(CMAKE_CXX_COMPILER_ARG1 " g++")

SET(CMAKE_CXX_FLAGS_DEBUG   " -O0 -Wall -g -ggdb -DDEBUG -fPIC")
SET(CMAKE_CXX_FLAGS_RELEASE " -Wall -g -O2 -DNDEBUG -fpermissive -fPIC")

message("PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message("CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")

if(UNIX)
	add_definitions(
		-DELPP_NO_DEFAULT_LOG_FILE
	)
else()
	add_definitions(
		-DWIN
		-DELPP_NO_DEFAULT_LOG_FILE
	)
endif()

SET(INCLUDE_DIR "./" "/usr/local/include"
	"${CMAKE_SOURCE_DIR}/Server"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/lua"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/g3dlite"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/libevent/include/event2"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/libevent/include/"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/libevent/compat/"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/Theron/Include"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/protobuf/src"
	"${CMAKE_SOURCE_DIR}/Server/Dependencies/navigation"
	"${CMAKE_SOURCE_DIR}/Server/Server_rc2/")


if (CMAKE_BUILD_TYPE MATCHES "Release")
		SET(LIB_DIR "/usr/lib"
			"/usr/local/lib"
			"/usr/lib64"
			"/usr/local/lib64"
			"${CMAKE_SOURCE_DIR}/Product/Lib"
			"${CMAKE_SOURCE_DIR}/Server/Lib/Release")
else()
	SET(LIB_DIR "/usr/lib"
		"/usr/local/lib"
		"/usr/lib64"
		"/usr/local/lib64"
		"${CMAKE_SOURCE_DIR}/Product/Lib"
		"${CMAKE_SOURCE_DIR}/Server/Lib/Debug")
endif()

SET(LIB_LINK_DEP libevent_core.a libevent_extra.a libtheron.a
		libevent.a liblua.a libprofiler.a libtcmalloc_minimal.a libtheron.a libevent_pthreads.a protobuf pthread dl rt)
		
SET(LIB_LINK_NF libG3Dlite.a libNavigation.a libNFActorPlugin.a libNFCore.a libNFKernelPlugin.a
				libNFMath.a libNFMessageDefine.a libNFNetPlugin.a libNFPluginModule.a libNFTestPlugin.a)
	
include_directories( ${INCLUDE_DIR} )
	
link_directories( ${LIB_DIR} )

PROJECT(Dependencies)
ADD_SUBDIRECTORY("Server/Dependencies")

PROJECT(NFTest)
ADD_SUBDIRECTORY("Server/Server_rc2/NFTest")

PROJECT(NFComm)
ADD_SUBDIRECTORY("Server/Server_rc2/NFComm")