#include "../include/window.h"

#include <iostream>

namespace pengin { namespace graphics {

	Window::Window(int width, int height, const char* title)
	{
		m_Width = width;
		m_Height = height;
		m_Title = title;
		if (!init())
			glfwTerminate();
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::init()
	{
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window)
		{
			printf("[ERROR] Failed to create GLFW window!");
			return false;
		}
		glfwMakeContextCurrent(m_Window);
		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		{
			printf("Failed to initialize Glad\n");
			return false;
		}
		return true;
	}

	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_Window);
	}

	void Window::update()
	{
		glfwSwapBuffers(m_Window);
		glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
		glViewport(0, 0, m_Width, m_Height);
		glfwPollEvents();
	}

	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

} }
