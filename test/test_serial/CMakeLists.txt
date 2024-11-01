project(test_serial)
set(LIB_NAME test_serial)

find_path(RAPIDJSON_INCLUDE_DIR rapidjson/document.h)

include_directories(../../include ../ ${RAPIDJSON_INCLUDE_DIR})
file(GLOB_RECURSE ALLHEADERS 
	./*.h
	)
# 扫描cpp文件但是不递归
#file(GLOB SOURCES "*.cpp")
# 扫描所有cpp文件，并且递归
file(GLOB_RECURSE SOURCES "*.cpp")
##生成exe
add_library(${PROJECT_NAME} SHARED ${SOURCES})
add_library(${PROJECT_NAME} SHARED ${ALLHEADERS})
# 设置依赖库的集合 可以填写多个
set(PROJECT_LINK_LIBS wowjson test_data)
# 设置本项目依赖的依赖库
target_link_libraries(${PROJECT_NAME} ${PROJECT_LINK_LIBS})
