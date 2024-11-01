project(wowjson)
set(LIB_NAME wowjson)
find_path(RAPIDJSON_INCLUDE_DIR rapidjson/document.h)

include_directories(../../include . ${RAPIDJSON_INCLUDE_DIR})
file(GLOB_RECURSE ALLHEADERS 
	../../include/${PROJECT_NAME}/*.h
	./*.h
	)
	
find_package(RapidJSON REQUIRED)

# 扫描所有cpp文件，并且递归
file(GLOB_RECURSE SOURCES "*.cpp")
#Generate the SHARED library from the sources
add_library(${PROJECT_NAME} SHARED ${SOURCES})
add_library(${PROJECT_NAME} SHARED ${ALLHEADERS})