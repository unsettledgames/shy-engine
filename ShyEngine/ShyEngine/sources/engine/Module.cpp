#include <engine/Module.h>

namespace ShyEngine
{
	bool Module::operator==(Module& other)
	{
		return other.m_reference == m_reference;
	}
}