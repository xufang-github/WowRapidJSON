//UTF8 文件
#include "data.h"

namespace test_data 
{
	PlaneRouteTask::PlaneRouteTask():
		postions(),
		from(""),
		to("")
	{
		
	}

	PlaneRouteTask::PlaneRouteTask(const PlaneRouteTask&other)
	{
		this->postions = other.postions;
		this->from = other.from;
		this->to = other.to;
	}


	PlaneRouteTask::~PlaneRouteTask()
	{
	}
}