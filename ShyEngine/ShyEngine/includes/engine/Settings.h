#pragma once

#include <map>
#include <string>
#include <vector>

namespace ShyEngine
{
	class _CollisionSettings
	{
		private:
			// This map associates the name of a layer with its id
			std::map<const std::string, int> m_layerIds;
			// Collision matrix: tells whether the layer at row i collides with the layer at column j
			std::vector<std::vector<bool>> m_collisionMatrix;
			// Current id for the next layer. Starts at 0, gets incremented every time a layer is added
			static short m_currId;

		public:
			_CollisionSettings();

			void addLayer(const std::string name);

			void defineCollision(const std::string layer1, const std::string layer2, bool collides);

			bool collides(const std::string layer1, const std::string layer2);
			bool collides(short layer1, short layer2);

			short nameToId(const std::string name) { return m_layerIds[name]; }
	};

	class _Settings
	{
		private:
		public:
			_CollisionSettings collisions;
	};

	extern _Settings* settings;
}