#include <collisions/CollisionGrid.h>

namespace ShyEngine
{
	CollisionGrid::CollisionGrid(float cellSize, glm::vec2 gridPos, glm::vec2 nCells)
	{
		m_gridCellSize = cellSize;
		m_gridPosition = gridPos;
		m_nCells = nCells;

		m_gridSize = glm::vec2(std::ceil(m_nCells.x * m_gridCellSize), std::ceil(m_nCells.y * m_gridCellSize));
		m_cells.reserve(m_nCells.x * m_nCells.y);
		m_cells.resize(m_nCells.x * m_nCells.y);
	}

	SpatialPartitioningCell* CollisionGrid::getCell(int index)
	{
		return &m_cells[index];
	}

	SpatialPartitioningCell* CollisionGrid::getCell(glm::vec2 pos)
	{
		int i = pos.y * m_nCells.x + pos.x;

		if (i < m_cells.size())
			return &m_cells[i];

		return nullptr;
	}

	glm::vec2 CollisionGrid::addToGrid(Entity* toAdd, int x, int y)
	{
		glm::vec2 gridCoords = getEntityCoords(toAdd, x, y);
		SpatialPartitioningCell* cell = getCell(gridCoords);

		if (cell != nullptr)
		{
			getCell(gridCoords)->m_objects.push_back(toAdd);
			return gridCoords;
		}
		return glm::vec2(0, 0);
	}

	glm::vec2 CollisionGrid::getEntityCoords(Entity* e, int x, int y)
	{
		x += m_gridSize.x / 2;
		y += m_gridSize.y / 2;

		x /= m_gridCellSize;
		y /= m_gridCellSize;

		return glm::vec2(x, y);
	}

	void CollisionGrid::removeFromGrid(Entity* toRemove, int x, int y)
	{
		int index = y * m_nCells.x + x;

		if (index > m_cells.size())
			std::remove_if(m_cells[index].m_objects.begin(), m_cells[index].m_objects.end(),
				[&](Entity* entity) { return entity == toRemove; });
	}
}