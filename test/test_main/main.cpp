//UTF8 文件
#include <iostream>
#include <wowjson/JsonConvertTemplate.h>
#include <test_serial/data_serial.h>
#include <sstream>
#include <map>
#include <test_serial/data_serial.h>
#include <wowjson/WowMetaType.h>


void test(int d) {
	std::cout << d << std::endl;
}


using namespace wowjson;
template<typename T>
void test_log(const T& t)
{
	std::ostringstream os;
	os.precision(BaseNumberCount<T>::count);
	os << t;
	std::cout << os.str() << std::endl;
	std::map<int, int> map;
}

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
	data.intMap[1] = "aa";
	data.intMap[2] = "bb";
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

}

void testSerial2() 
{
	std::vector<Employee> employees;
	Employee e;
	e.name_ = "Milo YIP";
	e.age_ = 34;
	e.married_ = true;
	{
		Dependent d;
		d.name_ = "Lua YIP";
		d.age_ = 3;
		d.education = std::shared_ptr<Education>(new Education());
		d.education->GPA_ = 3.5;
		d.education->school_ = "Happy Kindergarten";
		e.dependents_.push_back(d);
	}
	{
		Dependent d;
		d.name_ = "Mio YIP";
		d.age_ = 1;
		d.education = std::shared_ptr<Education>(nullptr);
		e.dependents_.push_back(d);
	}

	employees.push_back(e);
	{
		Employee e;
		e.name_ = "Percy TSE";
		e.age_ = 30;
		e.married_ = false;
		employees.push_back(e);
	}
	
	for (int i = 0; i < 10000; i++)
	{
		
	}
	
	
}


int main(int argc,char** argv)
{
	test_serial::getPlaneRouteTask();
	testConvert();
	testSerial2();
	std::cout << "请输入任意的字符回车结束" << std::endl;
	char c;
	std::cin >> c;
	return 1;
}

