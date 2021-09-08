#include <engine/Module.h>
#include <engine/Entity.h>

namespace ShyEngine
{
	const std::size_t Module::Type = std::hash<std::string>()(TO_STRING(Module));
	const std::string Module::m_name = "Module";

	Module::Module(Entity* entity) 
	{ 
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