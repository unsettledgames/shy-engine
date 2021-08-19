#include <util/IdGenerator.h>

namespace ShyEngine
{
	int IdGenerator::get()
	{
		int ret = m_currId + 1;
		int vecSize = m_freeIds.size();

		if (vecSize > 0)
		{
			ret = m_freeIds[vecSize - 1];
			m_freeIds.pop_back();
			return ret;
		}

		m_currId++;
		return ret;
	}

	void IdGenerator::add(int id)
	{
		m_freeIds.push_back(id);
	}
}
