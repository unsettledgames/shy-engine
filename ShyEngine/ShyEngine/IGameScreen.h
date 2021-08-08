#pragma once

#define NO_SCREEN	-1

namespace ShyEngine
{
	class IMainGame;

	enum class ScreenState
	{
		NONE,
		RUNNING,
		EXIT,
		CHANGE_NEXT,
		CHANGE_PREV
	};

	class IGameScreen
	{
		private:

		protected:
			int m_index = -1;
			ScreenState m_currState = ScreenState::NONE;
			IMainGame* m_game = nullptr;
		public:
			IGameScreen() {};
			~IGameScreen() {};

			virtual void build() = 0;
			virtual void destroy() = 0;

			virtual void onEnter() = 0;
			virtual void onExit() = 0;

			virtual void update() = 0;
			virtual void draw() = 0;

			virtual int getNextScreenIndex() const = 0;
			virtual int getPrevScreenIndex() const = 0;

			int getIndex() const { return m_index; }

			void setParentGame(IMainGame* game) { m_game = game; }
	};
}
