#pragma once

#include <util/Classes.h>
#include <engine/modules/collisions/Collider2D.h>

namespace ShyEngine
{
	class CircleCollider2D : public Collider2D 
	{
		friend class Collider2D;
		CLASS_DECLARATION(CircleCollider2D);

		private:
			float m_radius;

		public:
			CircleCollider2D();
			CircleCollider2D(Entity* entity, float radius);
			~CircleCollider2D() {};

			float getRadius() { return m_radius; }
			void setRadius(float r) { m_radius = r; }
	};
}