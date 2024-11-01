#ifndef _wowjson_AtomType_h_
#define _wowjson_AtomType_h_
namespace wowjson 
{
	template<typename T>
	class AtomType 
	{
	public:
		AtomType() = default;
		AtomType(const AtomType &) = delete;
		AtomType &operator=(const AtomType &) = delete;
		AtomType &operator=(const AtomType &) volatile = delete;
		constexpr AtomType(T value):
			m_loadFlag(false),
			m_value(value)
		{
		
		}
		~AtomType() {}
		void load(const T& t) 
		{
			m_value = t; 
			m_loadFlag = true;
		}
		const T& value() 
		{
			return m_value;
		}
		bool loaded()
		{
			return m_loadFlag;
		}
	private:
		T m_value;
		bool m_loadFlag;
	};
}

#endif//_wowjson_AtomType_h_
