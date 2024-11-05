project(QuickStartExample)
set(LIB_NAME QuickStartExample)
#包含的目录
find_path(RAPIDJSON_INCLUDE_DIR rapidjson/document.h)

include_directories(../../include . ../../test ${RAPIDJSON_INCLUDE_DIR})
#递归当前项目生成的头文件
file(GLOB_RECURSE ALLHEADERS 
	./*.h
	)
# 扫描cpp文件但是不递归
#file(GLOB SOURCES "*.cpp")
# 扫描所有cpp文件，并且递归
file(GLOB_RECURSE SOURCES "*.cpp")
##生成exe
add_executable(${PROJECT_NAME} ${SOURCES})
# 设置依赖库的集合 可以填写多个
set(PROJECT_LINK_LIBS wowjson)
# 设置本项目依赖的依赖库
target_link_libraries(${PROJECT_NAME} ${PROJECT_LINK_LIBS})