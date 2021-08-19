#pragma once

#include <vector>

namespace ShyEngine
{
	class IdGenerator
	{
	private:
		std::vector<int> m_freeIds;

		int m_currId = 0;
	public:
		int get();

		void add(int id);

		IdGenerator() {}
	};
}
