//UTF8 文件
#ifndef _wowjson_JsonConvertTemplate_H_
#define _wowjson_JsonConvertTemplate_H_

#include "wowjson_global.h"
#include "WowMetaType.h"

#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <deque>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <sstream>
#include <string>


namespace wowjson 
{
	template<typename T>
	inline bool string2T(const char* str, T& t)
	{
		std::stringstream ss(str);
		ss >> t;
		return !ss.fail() && ss.eof();
	}

	template<typename T>
	bool jsonValue2T(const ::rapidjson::Value& jsonValue,T& t)
	{
		return wowjson::WowMetaType::convert(jsonValue, t);
	}

	template<typename T>
	bool jsonValue2T(const ::rapidjson::Value& jsonValue, T*& t)
	{
		bool created = false;
		if (!t) { t = new T(); created = true;}
		if (!wowjson::WowMetaType::convert(jsonValue, *t)) 
		{
			if (created) 
			{
				delete t;
				t = nullptr;
			}
			return false;
		}
		return true;
	}

	template<typename T>
	bool jsonValue2T(const ::rapidjson::Value& jsonValue, std::shared_ptr<T>& t)
	{
		if (jsonValue.IsNull())
		{
			t = std::shared_ptr<T>(nullptr);
			return false; 
		}
		if (nullptr == t) t = std::shared_ptr<T>(new T());
		return wowjson::WowMetaType::convert(jsonValue, *t);
	}

	template<>
	bool jsonValue2T<bool>(const ::rapidjson::Value& jsonValue, bool& t)
	{
		if (jsonValue.IsNull()) { t = false; return false; }
		if (jsonValue.IsBool()) 
		{
			t = jsonValue.GetBool();
		}
		else if (jsonValue.IsInt()) 
		{
			t = jsonValue.GetInt() != 0;
		}
		else if (jsonValue.IsUint())
		{
			t = jsonValue.GetUint() != 0;
		}
		else if (jsonValue.IsInt64())
		{
			t = jsonValue.GetInt64() != 0;
		}
		else if (jsonValue.IsUint64())
		{
			t = jsonValue.GetUint64() != 0;
		}
		else if (jsonValue.IsFloat())
		{
			t = jsonValue.GetFloat() != 0;
		}
		else if (jsonValue.IsDouble() || jsonValue.IsLosslessFloat() || jsonValue.IsLosslessDouble())
		{
			t = jsonValue.GetDouble() != 0;
		}
		else if (jsonValue.IsNull())
		{
			t = false;
		}
		else if (jsonValue.IsString())
		{
			const char* data = jsonValue.GetString();
			t = "false" != data && "" != data && "0" != data;
		}
		else 
		{
			t = true;
		}
		return true;
	}

	template<typename T>
	bool jsonValue2Number(const ::rapidjson::Value& jsonValue, T& t)
	{
		if (jsonValue.IsBool())
		{
			t = jsonValue.GetBool();
		}
		else if (jsonValue.IsInt())
		{
			t = static_cast<T>(jsonValue.GetInt());
		}
		else if (jsonValue.IsUint())
		{
			t = static_cast<T>(jsonValue.GetUint());
		}
		else if (jsonValue.IsInt64())
		{
			t = static_cast<T>(jsonValue.GetInt64());
		}
		else if (jsonValue.IsUint64())
		{
			t = static_cast<T>(jsonValue.GetUint64());
		}
		else if (jsonValue.IsFloat())
		{
			t = static_cast<T>(jsonValue.GetFloat());
		}
		else if (jsonValue.IsDouble() || jsonValue.IsLosslessFloat() || jsonValue.IsLosslessDouble())
		{
			t = static_cast<T>(jsonValue.GetDouble());
		}
		else if (jsonValue.IsNull())
		{
			t = static_cast<T>(0);
		}
		else if (jsonValue.IsString())
		{
			return string2T(jsonValue.GetString(), t);
		}
		else
		{
			t = static_cast<T>(0);
		}
		return true;
	}


	template<>
	bool jsonValue2T<wowint8>(const ::rapidjson::Value& jsonValue, wowint8& t)
	{
		return jsonValue2Number<wowint8>(jsonValue,t);
	}

	template<>
	bool jsonValue2T<wowuint8>(const ::rapidjson::Value& jsonValue, wowuint8& t)
	{
		return jsonValue2Number<wowuint8>(jsonValue, t);
	}


	template<>
	bool jsonValue2T<wowint16>(const ::rapidjson::Value& jsonValue, wowint16& t)
	{
		return jsonValue2Number<wowint16>(jsonValue, t);
	}

	template<>
	bool jsonValue2T<wowuint16>(const ::rapidjson::Value& jsonValue, wowuint16& t)
	{
		return jsonValue2Number<wowuint16>(jsonValue, t);
	}


	template<>
	bool jsonValue2T<wowint32>(const ::rapidjson::Value& jsonValue, wowint32& t)
	{
		return jsonValue2Number<wowint32>(jsonValue, t);
	}

	template<>
	bool jsonValue2T<wowuint32>(const ::rapidjson::Value& jsonValue, wowuint32& t)
	{
		return jsonValue2Number<wowuint32>(jsonValue, t);
	}

	template<>
	bool jsonValue2T<wowint64>(const ::rapidjson::Value& jsonValue, wowint64& t)
	{
		return jsonValue2Number<wowint64>(jsonValue, t);
	}

	template<>
	bool jsonValue2T<wowuint64>(const ::rapidjson::Value& jsonValue, wowuint64& t)
	{
		return jsonValue2Number<wowuint64>(jsonValue, t);
	}

	template<>
	bool jsonValue2T<float>(const ::rapidjson::Value& jsonValue, float& t)
	{
		return jsonValue2Number <float> (jsonValue, t);
	}

	template<>
	bool jsonValue2T<double>(const ::rapidjson::Value& jsonValue, double& t)
	{
		return jsonValue2Number<double>(jsonValue, t);
	}

	template<>
	bool jsonValue2T<std::string>(const ::rapidjson::Value& jsonValue, std::string& t)
	{
		if (jsonValue.IsString()) 
		{
			t = jsonValue.GetString();
			return true;
		}
		else if (jsonValue.IsObject() || jsonValue.IsArray() || jsonValue.IsNull()) 
		{
			t = "";
			return false;
		}
		else if (jsonValue.IsBool())
		{
			if (jsonValue.GetBool())
				t = "true";
			else
				t = "false";
			return true;
		}
		else if (jsonValue.IsInt())
		{
			t = std::to_string(jsonValue.GetInt());
		}
		else if (jsonValue.IsUint())
		{
			t = std::to_string(jsonValue.GetUint());
			return true;
		}
		else if (jsonValue.IsInt64())
		{
			t = std::to_string(jsonValue.GetInt64());
			return true;
		}
		else if (jsonValue.IsUint64())
		{
			t = std::to_string(jsonValue.GetUint64());
			return true;
		}
		else if (jsonValue.IsFloat())
		{
			t = std::to_string(jsonValue.GetFloat());
			return true;
		}
		else if (jsonValue.IsDouble() || jsonValue.IsLosslessFloat() || jsonValue.IsLosslessDouble())
		{
			t = std::to_string(jsonValue.GetDouble());
			return true;
		}
		return false;
	}

	template<typename T>
	bool jsonValue2T(const ::rapidjson::Value& jsonValue, std::vector<T> &t)
	{
		t.clear();
		if (!jsonValue.IsArray()) return false;
		::rapidjson::Value::ConstArray  arrays  = jsonValue.GetArray();
		for (wowuint32 i = 0; i < arrays.Size(); i++)
		{
			const ::rapidjson::Value& value = arrays[i];
			T temp;
			t.push_back(temp);
			int index = (int)t.size() - 1;
			if (!wowjson::jsonValue2T(value, t[index]))
			{
				t.erase(t.begin() + index);
			}
		}
		return true;
	}

	template<typename T>
	bool jsonValue2T(const ::rapidjson::Value& jsonValue, std::list<T> &t)
	{
		t.clear();
		if (!jsonValue.IsArray()) return false;
		::rapidjson::Value::ConstArray  arrays = jsonValue.GetArray();
		for (wowuint32 i = 0; i < arrays.Size(); i++)
		{
			const ::rapidjson::Value& value = arrays[i];
			T temp;
			if (wowjson::jsonValue2T(value, temp))
			{
				t.push_back(temp);
			}
		}
		return true;
	}

	template<typename T>
	bool jsonValue2T(const ::rapidjson::Value& jsonValue, std::set<T> &t)
	{
		t.clear();
		if (!jsonValue.IsArray()) return false;
		::rapidjson::Value::ConstArray  arrays = jsonValue.GetArray();
		for (wowuint32 i = 0; i < arrays.Size(); i++)
		{
			const ::rapidjson::Value& value = arrays[i];
			T temp;
			if (wowjson::jsonValue2T(value, temp))
			{
				t.insert(temp);
			}
		}
		return true;
	}

	template<typename T>
	bool jsonValue2T(const ::rapidjson::Value& jsonValue, std::deque<T>& t)
	{
		t.clear();
		if (!jsonValue.IsArray()) return false;
		::rapidjson::Value::ConstArray  arrays = jsonValue.GetArray();
		for (wowuint32 i = 0; i < arrays.Size(); i++)
		{
			const ::rapidjson::Value& value = arrays[i];
			T temp;
			if (wowjson::jsonValue2T(value, temp))
			{
				t.push_back(temp);
			}
		}
		return true;
	}

	template<typename K,typename V>
	bool jsonValue2T(const ::rapidjson::Value& jsonValue, std::map<K,V> &t)
	{
		t.clear();
		if (!jsonValue.IsObject()) return false;
		for (auto& member : jsonValue.GetObject())
		{
			K k;
			wowjson::jsonValue2T(member.name, k);
			V temp;
			if (wowjson::jsonValue2T(member.value, temp))
			{
				t[k] =  temp;
			}
		}
		return true;
	}

	template<typename K, typename V>
	bool jsonValue2T(const ::rapidjson::Value& jsonValue, std::unordered_map<K, V> &t)
	{
		t.clear();
		if (!jsonValue.IsObject()) return false;
		for (auto& member : jsonValue.GetObject())
		{
			K k;
			wowjson::jsonValue2T(member.name, k);
			V temp;
			if (wowjson::jsonValue2T(member.value, temp))
			{
				t[k] = temp;
			}
		}
		return true;
	}

	template<typename T>
	void t2JsonValue(const T& t, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)
	{
		wowjson::WowMetaType::convert(t, writer);
	}

	template<typename T>
	void t2JsonValue(const T*& t, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)
	{
		if (nullptr == t)
		{
			writer.Null(t);
		}else 
			wowjson::WowMetaType::convert(*t, writer);
	}


	template<typename T>
	void t2JsonValue(const std::shared_ptr<T>& t, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)
	{
		if (nullptr == t)
			writer.Null();
		else 
			wowjson::WowMetaType::convert(*t, writer);
	}

	template<typename T>
	std::string toString(const T& t)
	{
		return "";
	}

	template<>
	std::string toString(const bool& t)
	{
		if (t)
			return "true";
		else
			return "false";
	}

	template<>
	std::string toString(const wowint16& t)
	{
		return std::to_string((int)t);
	}

	template<>
	std::string toString(const wowuint16& t)
	{
		return std::to_string((int)t);
	}

	template<>
	std::string toString(const wowint32& t)
	{
		return std::to_string(t);
	}

	template<>
	std::string toString(const wowuint32& t)
	{
		return std::to_string(t);
	}


	std::string toString(const wowint64& t)
	{
		return std::to_string(t);
	}

	template<>
	std::string toString(const wowuint64& t)
	{
		return std::to_string(t);
	}

	template<>
	std::string toString(const std::string& t)
	{
		return t;
	}

	std::string toString(const float& t)
	{
		return std::to_string((double)t);
	}

	template<>
	std::string toString(const double& t)
	{
		return std::to_string(t);
	}


	template<>
	void t2JsonValue(const bool& t, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)
	{
		writer.Bool(t);
	}

	template<>
	void t2JsonValue(const wowint8& t, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)
	{
		writer.Int(t);
	}

	template<>
	void t2JsonValue(const wowuint8& t, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)
	{
		writer.Int(t);
	}

	template<>
	void t2JsonValue(const wowint16& t, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)
	{
		writer.Int(t);
	}

	template<>
	void t2JsonValue(const wowuint16& t, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)
	{
		writer.Int(t);
	}

	template<>
	void t2JsonValue(const wowint32& t, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)
	{
		writer.Int(t);
	}

	template<>
	void t2JsonValue(const wowuint32& t, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)
	{
		writer.Uint(t);
	}

	template<>
	void t2JsonValue(const wowint64& t, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)
	{
		writer.Int64(t);
	}

	template<>
	void t2JsonValue(const wowuint64& t, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)
	{
		writer.Uint64(t);
	}

	template<>
	void t2JsonValue(const float& t, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)
	{
		writer.Double(t);
	}

	template<>
	void t2JsonValue(const double& t, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)
	{
		writer.Double(t);
	}

	template<>
	void t2JsonValue(const std::string& t, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)
	{
		writer.String(t.c_str());
	}

	template<typename T>
	void t2JsonValue(const std::vector<T>& t, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)
	{
		writer.StartArray();  
		for (std::vector<T>::const_iterator ite = t.begin(); ite != t.end(); ++ite)
		{
			wowjson::t2JsonValue(*ite, writer);
		}
		writer.EndArray();
	}

	template<typename T>
	void t2JsonValue(const std::list<T>& t, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)
	{
		writer.StartArray();
		for (std::list<T>::const_iterator ite = t.begin(); ite != t.end(); ++ite)
		{
			wowjson::t2JsonValue(*ite, writer);
		}
		writer.EndArray();
	}

	template<typename T>
	void t2JsonValue(const std::set<T>& t, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)
	{
		writer.StartArray();
		for (std::set<T>::const_iterator ite = t.begin(); ite != t.end(); ++ite)
		{
			wowjson::t2JsonValue(*ite, writer);
		}
		writer.EndArray();
	}

	template<typename T>
	void t2JsonValue(const std::deque<T>& t, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)
	{
		writer.StartArray();
		for (std::deque<T>::const_iterator ite = t.begin(); ite != t.end(); ++ite)
		{
			wowjson::t2JsonValue(*ite, writer);
		}
		writer.EndArray();
	}

	template<typename K,typename V>
	void t2JsonValue(const std::map<K,V>& map, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)
	{
		writer.StartObject();
		std::map<K, V>::const_iterator ite = map.begin();
		for (; ite != map.end(); ++ite)
		{
			wowjson::t2JsonValue(wowjson::toString(ite->first), writer);
			//wowjson::t2JsonValue(ite->first, writer);
			wowjson::t2JsonValue(ite->second, writer);
		}
		writer.EndObject();
	}

	template<typename K, typename V>
	void t2JsonValue(const std::unordered_map<K, V>& map, ::rapidjson::Writer<::rapidjson::StringBuffer>& writer)
	{
		writer.StartObject();
		std::unordered_map<K, V>::const_iterator ite = map.begin();
		for (; ite != map.end(); ++ite)
		{
			wowjson::t2JsonValue(wowjson::toString(ite->first), writer);
			//wowjson::t2JsonValue(ite->first, writer);
			wowjson::t2JsonValue(ite->second, writer);
		}
		writer.EndObject();
	}

	template<typename T>
	bool object2Json(const T& data, std::string& out) 
	{
		::rapidjson::StringBuffer buffer;
		::rapidjson::Writer<::rapidjson::StringBuffer> writer(buffer);
		::wowjson::t2JsonValue(data, writer);
		out = std::string(buffer.GetString(),buffer.GetSize());
		return out.size() > 0;
	}

	template<typename T>
	bool json2Object(const std::string& out,T& t)
	{
		::rapidjson::Document d;
		if (d.Parse(out.c_str()).HasParseError())
		{
			throw false;
		}
		if (d.IsObject())
		{
			::wowjson::jsonValue2T(d.GetObject(), t);
		}
		else 
		{
			::wowjson::jsonValue2T(d.GetArray(), t);
		}
		return true;
	}

}

WOW_DECLARE_METAYPE(::rapidjson::Writer<::rapidjson::StringBuffer>);
WOW_DECLARE_METAYPE(::rapidjson::Value);

#endif//_wowjson_JsonConvertTemplate_H_
