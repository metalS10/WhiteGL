/**
*	@file GLFWEW
*/

//#pragma once
#ifndef GLFWEW_INCLUDED
#define GLFWEW_INCLUDED
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "GamePad.h"


namespace GLFWEW
{
	/**
	*	GLFWとGLEWのラッパークラス
	*/
	class Window
	{
	public:
		static Window& Instance();
		GLFWwindow* Init(int w, int h, const char* title);
		const GamePad& GetGamePad() const;
		void UpdateGamePad();

	private:
		Window();
		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		bool isGLFWInitialized;
		bool isInitialized;
		GLFWwindow* window;
		GamePad gamepad;
	};
}	//namespace GLFWEW

#endif // !GLFWEW_INCLUDED