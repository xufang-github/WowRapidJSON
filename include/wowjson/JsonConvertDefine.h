//UTF8 文件
#ifndef _wowjson_JsonConvertDefine_H_
#define _wowjson_JsonConvertDefine_H_

#include "wowjsonDefine.h"
#include "JsonConvertTemplate.h"

#define WOW_JSON_VALUE_2_T_PARAM(pName) \
	wowjson::jsonValue2T(obj[#pName], src.pName);

#define T_PARAM_2_WOW_JSON_VALUE(pName) \
	 writer.Key(#pName);\
	 wowjson::t2JsonValue(src.pName,writer);


#define WOW_JSON_CONVERT_REALIZE(_namespace,_className,_argN,...) \
bool jsonValue2##_className(const ::rapidjson::Value& jsonValue, _namespace::_className& src) \
{\
	if(!jsonValue.IsObject())\
		return false;\
	::rapidjson::Value::ConstObject obj = jsonValue.GetObject();\
	WOW_FOR_EACH_CODE(WOW_JSON_VALUE_2_T_PARAM, _argN, __VA_ARGS__)\
		return true;\
}\
bool _className##2JsonValue(const _namespace::_className& src, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)\
{\
	writer.StartObject();\
	WOW_FOR_EACH_CODE(T_PARAM_2_WOW_JSON_VALUE, _argN, __VA_ARGS__)\
	writer.EndObject();\
	return true;\
}\
int registerWowJsonConvert_##_className()\
{\
	WowMetaType::registerConvertFunction<::rapidjson::Value, _namespace::_className>(jsonValue2##_className);\
	WowMetaType::registerConvertFunction<_namespace::_className, ::rapidjson::Writer<::rapidjson::StringBuffer>>(_className##2JsonValue);\
	return 1;\
}\
int registerWowJsonConvert_##_className##_ID = registerWowJsonConvert_##_className();

#endif//_wowjson_JsonConvertDefine_H_
