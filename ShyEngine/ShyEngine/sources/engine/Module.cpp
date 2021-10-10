#include <engine/Module.h>
#include <engine/Entity.h>

namespace ShyEngine
{
	// Each module has a Type, which is the hash of its name: in that way it's possible to implement module-related
	// functions (getModule, addModule etc)
	const std::size_t Module::Type = std::hash<std::string>()(TO_STRING(Module));
	// Each module also has a name. This is mainly used for debug purposes
	const std::string Module::m_name = "Module";

	Module::Module(Entity* entity) 
	{ 
		// Each module has a reference to its entity to speed up systems
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