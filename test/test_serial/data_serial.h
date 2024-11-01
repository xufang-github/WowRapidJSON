//UTF8 文件
#ifndef _test_serial_h_ 
#define _test_serial_h_
#include "test_serial/data_serial_global.h"
#include <wowjson/WowMetaType.h>
#include <test_data/data.h>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <deque>
#include <stack>
#include <memory>
namespace test_serial 
{
	struct TestBaseData
	{
		bool boolV = false;
		wowint8  int8V = 0;
		wowuint8 unint8V = 0;
		std::string strV = "";
		float floatV = 0.0f;
		double doubleV = 0.0;
		std::list<float> floatList;
		std::vector<double> doubleVectors;
		std::set<float> floatSet;
		std::map<std::string, std::string> strMap;
		std::unordered_map<int, std::string> intMap;
		std::deque<int> intDeque;
		std::list<std::unordered_map<int, std::string>> mapList;
	};


	// 获取一条计划航路
	std::shared_ptr<test_data::PlaneRouteTask> test_serial_api getPlaneRouteTask();
}
// 非侵入式
WOW_DECLARE_METAYPE(test_data::GeoPostion);
WOW_DECLARE_METAYPE(test_data::PlaneRouteTask);
WOW_DECLARE_METAYPE(test_serial::TestBaseData);
WOW_DECLARE_METAYPE(Person);
WOW_DECLARE_METAYPE(Education);
WOW_DECLARE_METAYPE(Dependent);
WOW_DECLARE_METAYPE(Employee);

#endif//_test_serial_h_



