#include <SpatialGrid.h>

namespace ShyEngine
{
	SpatialGrid::SpatialGrid(int width, int height, int cellSize) :
		m_width(width), m_height(height), m_cellSize(cellSize)
	{
		// Get number of cells per dimension
		m_nXCells = ceil((float)m_width / (float)m_cellSize);
		m_nYCells = ceil((float)m_height / (float)m_cellSize);
		
		// Allocate all the cells
		m_cells.resize(m_nYCells * m_nXCells);
	}

	Cell* SpatialGrid::getCell(int x, int y)
	{
		if (x < 0) x = 0;
		if (y < 0) y = 0;

		if (x >= m_nXCells) x = m_nXCells - 1;
		if (y >= m_nYCells) y = m_nYCells - 1;

		return &m_cells[y * m_nYCells + x];
	}

	Cell* SpatialGrid::getCell(glm::vec2 pos)
	{
		if (pos.x < 0) pos.x = 0;
		if (pos.y < 0) pos.y = 0;

		return getCell(pos.x, pos.y);
	}
}

