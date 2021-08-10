#pragma once

#include <vector>
#include <screen/IGameScreen.h>

namespace ShyEngine
{
	class ScreenList
	{
		private:
		protected:
			IMainGame* m_game = nullptr;

			std::vector<IGameScreen*> m_screens;
			int m_currScreen = -1;

		public:
			ScreenList(IMainGame* game);
			~ScreenList();

			IGameScreen* moveNext();
			IGameScreen* movePrev();

			void setScreen(int nextScreen);
			void addScreen(IGameScreen* newScreen);
			IGameScreen* getCurrScreen();

			void destroy(); 

	};
}