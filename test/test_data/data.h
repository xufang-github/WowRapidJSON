//UTF8 文件
#ifndef _test_data_data_H_
#define _test_data_data_H_
#include "test_data/test_data_global.h"
#include <vector>
#include <memory>
#include <string>

namespace test_data 
{
	// 地理坐标
	struct GeoPostion 
	{
		double lon = 0.0;// 经度
		double lat = 0.0;// 纬度
		double alt = 0.0;// 高程
	};
	// 飞行航路计划
	class  PlaneRouteTask
	{
	public:
		test_data_api PlaneRouteTask();
		test_data_api PlaneRouteTask(const PlaneRouteTask& other);
		test_data_api ~PlaneRouteTask();
	public:
		std::vector<test_data::GeoPostion> postions;// 轨迹集合
		std::string from = "";// 航班出发地
		std::string to = "";// 航班终点
	};
}


struct Person
{
	std::string name_ = "";
	char age_ = 0;
};

struct Education
{
	std::string school_ = "";
	double GPA_ = 0.0;
};

struct Dependent : public Person
{
	std::shared_ptr<Education> education;
};

struct Employee : public Person
{
	std::vector<Dependent> dependents_;
	bool married_ = false;
};

#endif//_test_data_data_H_