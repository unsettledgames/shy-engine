#include <engine/Module.h>

namespace ShyEngine
{
	bool Module::operator==(Module* other)
	{
		return other->m_reference == m_reference;
	}

	bool operator==(const Module& e1, const Module& e2)
	{
		return e1.m_reference == e2.m_reference;
	}
}