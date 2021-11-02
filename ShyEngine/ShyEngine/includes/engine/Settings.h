#pragma once

#include <map>
#include <string>
#include <vector>

namespace ShyEngine
{
	/*
		\brief	Holds the collision settings, such as the layer collision matrix that tells which layers are allowed
				to collide with other ones.

				When the user creates a layer, an id starting from 0 is assigned to it. That id identifies a row
				or a column in the collision matrix, so that it's easy to determine whether or not an entity
				should collide with another one (collisionMatrix[layer1][layer2]).

				Each cell (i, j) in the collision matrix contains true if the layer with id i should collide with the
				layer with id j, false otherwise.
	*/
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

			/*
				\brief	Creates a layer given its name. An id is assigned to the layer and a new entry in the layerIds
						map is added, so that it's easy (constant time) to retrieve an id given a name.

				\param	name	The name of the layer to create.
			*/
			void addLayer(const std::string name);

			/*
				\brief Changes the collision settings for 2 layers, stating whether or not they should collide

				\param	layer1	The first layer
				\param	layer2	The second layer
				\param	collides	Tells whether or not layer1 and layer2 should collide
			*/
			void defineCollision(const std::string layer1, const std::string layer2, bool collides);

			/*
				\brief	Checks if layer1 collides with layer2 by converting the names into ids and
						looking up the collision matrix.

				\param layer1	The name of the first layer
				\param layer2	The name of the second layer

				\return	True if the layers collide, false oherwise
			*/
			bool collides(const std::string layer1, const std::string layer2);

			/*
				\brief	Checks if layer1 collides with layer2 by looking up the collision matrix.

				\param layer1	The id of the first layer
				\param layer2	The id of the second layer

				\return	True if the layers collide, false oherwise
			*/
			bool collides(short layer1, short layer2);

			/*
				\brief Converts a layer name to its id
			*/
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