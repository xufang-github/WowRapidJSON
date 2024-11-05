#include <wowjson/JsonConvertDefine.h>
#include <iostream>

namespace Test 
{
	struct Student
	{
		std::string name = "";
		int age = 0;
		std::unordered_map<std::string, float> scores = { };
	};
	struct School
	{
		std::string name = "";
		std::map<std::string, Student> students = {};
	};
}

WOW_DECLARE_METAYPE(Test::Student);
WOW_JSON_CONVERT_REALIZE(Test, Student, 3, name, age, scores);
WOW_DECLARE_METAYPE(Test::School);
WOW_JSON_CONVERT_REALIZE(::Test, School, 2, name, students);

#ifdef _WIN32
#include <windows.h>
#endif

void enableUtf8Console() {
#ifdef _WIN32
	// 设置 Windows 控制台代码页为 UTF-8
	SetConsoleOutputCP(CP_UTF8);
#endif
}

int main(int argc,char** argv)
{
	enableUtf8Console();
	Test::School school;
	school.name = "某某实验小学";
	school.students["2024060001"] = { "小明",10,{{"语文",89.0f},{"数学",88.0f},{"AI",90.0f}}};
	school.students["2024060002"] = { "小方",11,{{"语文",89.0f},{"数学",88.0f},{"AI",90.0f}}};
	school.students["2024060003"] = { "小六",12,{{"语文",89.0f},{"数学",70.0f},{"AI",99.0f}}};
	// 序列化
	std::string outMsg;
	wowjson::object2Json(school, outMsg);
	std::cout << outMsg << std::endl;
	//{ "name":"某某实验小学", "students" : {"2024060001":{"name":"小明", "age" : 10, "scores" : {"语文":89.0, "数学" : 88.0, "AI" : 90.0}}, "2024060002" : {"name":"小方", "age" : 11, "scores" : {"语文":89.0, "数学" : 88.0, "AI" : 90.0}}, "2024060003" : {"name":"小六", "age" : 12, "scores" : {"语文":89.0, "数学" : 70.0, "AI" : 99.0}}} }
	// 反序列化
	Test::School school2;
	wowjson::json2Object(outMsg, school2);
	// 序列化
	wowjson::object2Json(school2, outMsg);
	std::cout << outMsg << std::endl;
	//{ "name":"某某实验小学", "students" : {"2024060001":{"name":"小明", "age" : 10, "scores" : {"语文":89.0, "数学" : 88.0, "AI" : 90.0}}, "2024060002" : {"name":"小方", "age" : 11, "scores" : {"语文":89.0, "数学" : 88.0, "AI" : 90.0}}, "2024060003" : {"name":"小六", "age" : 12, "scores" : {"语文":89.0, "数学" : 70.0, "AI" : 99.0}}} }
	return 1;
} 
