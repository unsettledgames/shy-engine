#pragma once

#include <memory>
#include <screen/IGameScreen.h>

namespace ShyEngine
{
	class IMainGame
	{
	private:
	protected:
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