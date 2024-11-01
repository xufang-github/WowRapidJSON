project(test_data)
set(LIB_NAME test_data)
include_directories(../../include ../)
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
