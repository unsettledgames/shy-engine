#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace ShyEngine
{
	typedef struct cell
	{
		std::vector<int*> objects;
	}Cell;

	class SpatialGrid
	{
		private:
			int m_width;
			int m_height;
			int m_cellSize;

			int m_nXCells;
			int m_nYCells;
			
			// List of cells
			std::vector<Cell> m_cells;

		public:
			SpatialGrid(int width, int height, int cellSize);
			~SpatialGrid();

			Cell* getCell(int x, int y);
			Cell* getCell(glm::vec2 pos);
	};
}
