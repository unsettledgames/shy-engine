#include <engine/Module.h>
#include <engine/Entity.h>

namespace ShyEngine
{
	Module::Module(const std::string& name, Entity* entity) 
	{ 
		m_name = name; 
		m_entity = entity;
	}

	bool Module::operator==(Module* other)
	{
		return other->m_reference == m_reference;
	}

	bool operator==(const Module& e1, const Module& e2)
	{
		return e1.m_reference == e2.m_reference;
	}
}