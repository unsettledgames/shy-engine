#pragma once

#include <memory>
#include <screen/ScreenList.h>
#include <screen/IGameScreen.h>

namespace ShyEngine
{
	class IMainGame
	{
	private:
	protected:
		std::unique_ptr<ScreenList> m_screens = nullptr;
		IGameScreen* m_currScreen = nullptr;

		bool m_isRunning = false;
		float m_fps;

		void run();
		void exit();
		bool init();

		virtual void onInit() = 0;
		virtual void onExit() = 0;
		virtual void addScreens() = 0;

		const float getFps() const { return m_fps; }

	public:
		IMainGame();
		virtual ~IMainGame();
	};
}