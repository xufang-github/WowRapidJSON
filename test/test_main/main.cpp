//UTF8 文件
#include <iostream>
#include <wowjson/JsonConvertTemplate.h>
#include <test_serial/data_serial.h>
#include <sstream>
#include <map>
#include <test_serial/data_serial.h>
#include <wowjson/WowMetaType.h>


void testConvert() 
{
	std::cout << "*****************testConvert**********************" << std::endl;
	test_serial::TestBaseData data;
	data.boolV = true;
	data.doubleV = 1.0;
	data.doubleVectors.push_back(1.1);
	data.doubleVectors.push_back(1.2e100);
	data.floatList.push_back(1.0);
	data.floatList.push_back(3.0);
	data.floatSet.insert(1.0);
	data.floatSet.insert(3.0);
	data.floatV = 1.0;
	data.int8V = '2';
	data.unint8V = (wowuint8)256;
	data.intDeque.push_back(1);
	data.intDeque.push_back(2);
	data.intMap[1] = "你好, 世界!";
	data.intMap[2] = "こんにちは世界！";
	data.mapList.push_back(data.intMap);
	data.mapList.push_back(data.intMap);
	data.strMap["aa"] = "aa";
	data.strMap["bb"] = "bb";
	data.strV = "xdd";
	test_serial::TestBaseData data2 = data;
	test_serial::TestBaseData data3 = data;
	int count = 10000;
	for (int i = 0; i < count; i++)
	{
		test_serial::TestBaseData data2 = data;
		//test_serial::TestBaseData data3 = data;
		data2.boolV = !data.boolV;
		//data3.boolV = data.int8V;
	}

	std::string msg;
	wowjson::object2Json(data,msg);

	test_serial::TestBaseData tempData;
	wowjson::json2Object(msg, tempData);

	std::string msg2;
	wowjson::object2Json(tempData, msg2);


	std::cout << msg << std::endl << std::endl << msg2 << std::endl;

	for (int i = 0; i < 25 * 10000; ++i) 
	{
		std::string msg;
		wowjson::object2Json(data, msg);

		test_serial::TestBaseData tempData;
		wowjson::json2Object(msg, tempData);

	}

	std::cout << msg << std::endl << std::endl << msg2 << std::endl;

}

#ifdef _WIN32
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#endif

void enableUtf8Console() {
#ifdef _WIN32
	// 设置 Windows 控制台代码页为 UTF-8
	SetConsoleOutputCP(CP_UTF8);
#else
	// 非 Windows 平台通常默认支持 UTF-8 无需特殊处理
#endif
}

int main(int argc,char** argv)
{
	enableUtf8Console();
	test_serial::getPlaneRouteTask();
	testConvert();
	std::cout << "请输入任意的字符回车结束" << std::endl;
	char c;
	std::cin >> c;
	return 1;
}
  
