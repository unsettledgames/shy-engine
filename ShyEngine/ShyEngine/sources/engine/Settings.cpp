#include <engine/Settings.h>

namespace ShyEngine
{
	short _CollisionSettings::m_currId = 0;
	_Settings* settings = new _Settings();

	_CollisionSettings::_CollisionSettings()
	{
		m_currId = 0;
		// Adding at least the default layer
		addLayer("Default");
	}

	void _CollisionSettings::addLayer(const std::string name)
	{
		// Associate an id to the layer name
		m_layerIds.emplace(std::make_pair(name, m_currId));
		// Add a row to the collision matrix
		m_collisionMatrix.resize(m_collisionMatrix.size() + 1);
		// Add a column to the collision matrix, enable collisions by default
		for (int i = 0; i < m_collisionMatrix.size(); i++)
			m_collisionMatrix[i].push_back(true);

		m_currId++;
	}

	void _CollisionSettings::defineCollision(const std::string layer1, const std::string layer2, bool collides)
	{
		m_collisionMatrix[m_layerIds[layer1]][m_layerIds[layer2]] = collides;
		m_collisionMatrix[m_layerIds[layer2]][m_layerIds[layer1]] = collides;
	}

	bool _CollisionSettings::collides(short layer1, short layer2)
	{
		return m_collisionMatrix[layer1][layer2];
	}

	bool _CollisionSettings::collides(const std::string layer1, const std::string layer2)
	{
		return m_collisionMatrix[m_layerIds[layer1]][m_layerIds[layer2]];
	}

}