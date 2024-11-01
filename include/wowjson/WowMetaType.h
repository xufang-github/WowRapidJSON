#ifndef _wowjson_WowMetaType_H_
#define _wowjson_WowMetaType_H_

#include "wowjson/wowjson_global.h"
#include "wowjson/AtomType.h"
#include <unordered_map>
#include <mutex>
#include <vector>
#include <string>

namespace wowjson 
{
	template<typename T>
	struct WowMetaTypeInfo
	{
	public:
		// 获取类名
		static std::string getClassName() { return "";}
		// 获取类id
		static wowuint32 getClassId() { return 0;}
	};
}

namespace wowjson
{
	// 抽象的转化类型函数
	struct  WowAbConverterFunction
	{
	public:
		virtual bool convert(const void* src, void* target) = 0;
	};
	// SrcClass 到 TargetClass 的转化函数
	template<typename SrcClass, typename TargetClass, typename ConvertFunction>
	struct  WowMetaTypeConverter : public WowAbConverterFunction
	{
		WowMetaTypeConverter(ConvertFunction convertFunction) :
			WowAbConverterFunction(),
			m_function(convertFunction)
		{
		
		}
	private:
		ConvertFunction m_function;
	public:
		bool convert(const void* src, void* target) override
		{
			const SrcClass *src1 = static_cast<const SrcClass*>(src);
			TargetClass *target1 = static_cast<TargetClass*>(target);
			m_function(*src1,*target1);
			return true;
		}

	};
	// 抽象的反射接口
	struct  AbMetaCreator
	{
	public:
		virtual void* createObj() const = 0;
		virtual std::string getClassName() const = 0;
	};
	// 模板反射 实现了的反射接口
	template<typename T>
	struct WowMetaCreator : public AbMetaCreator
	{
	public:
		virtual void* createObj() const override { return new T();}
		virtual std::string getClassName() const override { return WowMetaTypeInfo<T>::getClassName();}
	};

	class WowMetaType
	{
	public:
		//************************************
		// Method:    registerClass 通过类名注册类，若已经注册，则直接返回注册id
		// FullName:  WowMetaType::registerClass
		// Access:    public static 
		// Returns:   unsigned int 注册的id
		// Qualifier:
		// Parameter: const std::string & className 注册的类名
		//************************************
		template<typename T>
		static const wowuint32 registerClass(const std::string &className)
		{
			wowint32 id = s_registerIndex;
			std::unordered_map<std::string, wowuint32>::iterator idIte = s_classIdMap.find(className);
			if (s_classIdMap.end() == idIte) 
			{
				s_classIdMap[className] = s_registerIndex;
				AbMetaCreator* abCreator =  createMetCreator<T>();
				s_classCreatorMap[className] = abCreator;
				s_abMetaCreators.push_back(abCreator);
				++s_registerIndex;
			}
			else 
			{
				id = idIte->second;
			}
			return id;
		}

		template<typename SrcClass,typename TargetClass,typename ConvertFunction>
		static bool registerConvertFunction(ConvertFunction  convertfunction)
		{
			if (!canConvert<SrcClass, TargetClass>()) return false;
			wowuint64 convertId = getConvertId<SrcClass, TargetClass>();
			WowAbConverterFunction*  abConverterFunction = new WowMetaTypeConverter<SrcClass, TargetClass, ConvertFunction>(convertfunction);
			s_convertFunctionMap[convertId] = abConverterFunction;
			return true;
		}

		//************************************
		// Method:    canConvert 是否能从SrcClass转化为TargetClass
		// FullName:  WowMetaType::canConvert
		// Access:    public static 
		// Returns:   bool
		// Qualifier:
		//************************************
		template<typename SrcClass, typename TargetClass>
		static inline bool canConvert() 
		{
			if ("" == WowMetaTypeInfo<SrcClass>::getClassName() ||
				"" == WowMetaTypeInfo<TargetClass>::getClassName())
				return false;
			return true;
		}

		//************************************
		// Method:    getConvertId 获取转化函数id
		// FullName:  WowMetaType::getConvertId
		// Access:    public static 
		// Returns:   bool
		// Qualifier:
		//************************************
		template<typename SrcClass, typename TargetClass>
		static inline wowuint64 getConvertId()
		{
			wowuint64 convertId = WowMetaTypeInfo<SrcClass>::getClassId();
			convertId = (convertId << 32) | WowMetaTypeInfo<TargetClass>::getClassId();
			return convertId;
		}

		//************************************
		// Method:    convert 从src转换到targetClass
		// FullName:  WowMetaType::convert
		// Access:    public static 
		// Returns:   void
		// Qualifier:
		// Parameter: const SrcClass & src
		// Parameter: TargetClass & targetClass
		//************************************
		template<typename SrcClass, typename TargetClass>
		static bool convert(const SrcClass& src, TargetClass & targetClass) 
		{
			if (!canConvert<SrcClass, TargetClass>()) return false;
			wowuint64 convertId = getConvertId<SrcClass, TargetClass>();
			WowAbConverterFunction*  abConverterFunction = nullptr;
			std::unordered_map<wowuint64, WowAbConverterFunction*>::iterator convertIte =  
				s_convertFunctionMap.find(convertId);
			if (convertIte != s_convertFunctionMap.end()) 
			{
				abConverterFunction = convertIte->second;
			}
			if (nullptr == abConverterFunction) return false;
			return abConverterFunction->convert(&src,&targetClass);
		}

		//************************************
		// Method:    createObject 根据类名创建类
		// FullName:  WowMetaType::createObject
		// Access:    public 
		// Returns:   T
		// Qualifier:
		// Parameter: const std::string & className
		//************************************
		wowjson_api static void* createObject(const std::string& className);

		//************************************
		// Method:    createObject 根据classId创建对象
		// FullName:  WowMetaType::createObject
		// Access:    public static 
		// Returns:   void* 未注册返回nullptr
		// Qualifier:
		// Parameter: unsigned int id
		//************************************
		wowjson_api static void* createObject(unsigned int id);
	private:
		template<typename T>
		static AbMetaCreator* createMetCreator() {
			return new WowMetaCreator<T>();
		}

		template<typename T>
		static AbMetaCreator* createMetCreator(T* t) {
			return new WowMetaCreator<T>();
		}
	private:
		// 类型转化函数 key:SrcID*INTMAX + TargetID value:类型转化函数
		wowjson_api static std::unordered_map<wowuint64, WowAbConverterFunction*> s_convertFunctionMap;
		//key:className 类的唯一标识 建议用namespace::ClassName value:类的id
		wowjson_api static std::unordered_map<std::string, unsigned int> s_classIdMap;
		// key:className 类的唯一标识 value:创建者 用于更具类名创建类
		wowjson_api static std::unordered_map<std::string, AbMetaCreator*> s_classCreatorMap;
		// 注册索引
		wowjson_api static unsigned int s_registerIndex;
		//index:类的id - 1 value:类的创建者
		wowjson_api static std::vector<AbMetaCreator*> s_abMetaCreators;
	};
}

#define  WOW_DECLARE_METAYPE(_className)\
namespace wowjson\
{\
	template<>\
	struct WowMetaTypeInfo<_className>\
	{\
	public:\
		static std::string getClassName() { return #_className; }\
		static wowuint32 getClassId()\
		{\
			static wowjson::AtomType<wowuint32> id = {0};\
			if (id.loaded())\
			{\
				return id.value();\
			}\
			wowuint32 classId = wowjson::WowMetaType::registerClass<_className>(#_className);\
			id.load(classId);\
			return classId;\
		}\
	};\
}

#endif//_wowjson_WowMetaType_H_