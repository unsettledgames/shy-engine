#include <ScreenList.h>

namespace ShyEngine
{
	ScreenList::ScreenList(IMainGame* game) : m_game(game){}

	ScreenList::~ScreenList()
	{
		this->destroy();
	}

	IGameScreen* ScreenList::moveNext()
	{
		IGameScreen* curr = getCurrScreen();

		if (curr->getNextScreenIndex() != NO_SCREEN)
			m_currScreen = curr->getNextScreenIndex();

		return getCurrScreen();
	}

	IGameScreen* ScreenList::movePrev()
	{
		IGameScreen* curr = getCurrScreen();

		if (curr->getPrevScreenIndex() != NO_SCREEN)
			m_currScreen = curr->getPrevScreenIndex();

		return getCurrScreen();
	}

	void ScreenList::setScreen(int nextScreen)
	{
		m_currScreen = nextScreen;
	}

	void ScreenList::addScreen(IGameScreen* newScreen)
	{
		m_screens.push_back(newScreen);
		newScreen->build();
		newScreen->setParentGame(m_game);
	}

	IGameScreen* ScreenList::getCurrScreen()
	{
		if (m_currScreen != NO_SCREEN)
			return m_screens[m_currScreen];
		return nullptr;
	}

	void ScreenList::destroy()
	{
		for (auto screen : m_screens)
		{
			screen->destroy();
			delete screen;
		}

		m_screens.resize(0);
		m_currScreen = NO_SCREEN;
	}
}