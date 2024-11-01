//UTF8 文件
#include "wowjson/WowMetaType.h"

namespace wowjson 
{
	std::unordered_map<wowuint64, WowAbConverterFunction*> WowMetaType::s_convertFunctionMap;
	std::unordered_map<std::string, wowuint32> WowMetaType::s_classIdMap;
	std::unordered_map<std::string, AbMetaCreator*> WowMetaType::s_classCreatorMap;
	unsigned int WowMetaType::s_registerIndex = 1;
	std::vector<AbMetaCreator*> WowMetaType::s_abMetaCreators;


	void* WowMetaType::createObject(const std::string& className)
	{
		AbMetaCreator* abCreator = nullptr;
		std::unordered_map<std::string, AbMetaCreator*>::const_iterator creatorIte =
			s_classCreatorMap.find(className);
		if (s_classCreatorMap.end() != creatorIte)
		{
			abCreator = creatorIte->second;
		}
		if (abCreator)
			return abCreator->createObj();
		else
			return  nullptr;
	}

	void* WowMetaType::createObject(unsigned int id)
	{
		if (0 == id)
			return nullptr;
		id = id - 1;
		if (id >= s_abMetaCreators.size())
			return nullptr;
		return s_abMetaCreators[id]->createObj();
	}

}