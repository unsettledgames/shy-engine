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
			ScreenState m_currState = ScreenState::NONE;
		public:
			IGameScreen() {};
			~IGameScreen() {};

			virtual void build() = 0;
			virtual void destroy() = 0;

			virtual void onEnter() = 0;
			virtual void onExit() = 0;

			virtual void updateSystems() = 0;
	};
}
