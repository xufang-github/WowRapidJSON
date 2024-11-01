//UTF8 文件
#include "test_serial/data_serial.h"
#include "wowjson/JsonConvertDefine.h"

using namespace test_data;
using namespace wowjson;
namespace test_serial
{
	std::shared_ptr<test_data::PlaneRouteTask> getPlaneRouteTask()
	{
		test_data::PlaneRouteTask* task = new test_data::PlaneRouteTask();
		task->postions.push_back({ 114.12323433234,34.00000000000001,100 });
		task->postions.push_back({ 115,35,5000 });
		task->postions.push_back({ 114,36,6000 });
		task->postions.push_back({ 114,37,7000 });
		task->postions.push_back({ 114,34,8000 });
		task->from = "阿富汗";
		task->to = "阿根廷";
		return std::shared_ptr<test_data::PlaneRouteTask>(task);
	}



	WOW_JSON_CONVERT_REALIZE(test_serial, TestBaseData, 13, 
		boolV, int8V, unint8V, strV, floatV,
		doubleV, floatList, doubleVectors,floatSet,strMap,
		intMap, intDeque, mapList);
	

	WOW_JSON_CONVERT_REALIZE(, Person, 2,name_,age_);
	WOW_JSON_CONVERT_REALIZE(, Education, 2, school_, GPA_);
	WOW_JSON_CONVERT_REALIZE(, Dependent, 3, name_, age_, education);
	WOW_JSON_CONVERT_REALIZE(, Employee, 4, name_, age_, dependents_, married_);
}