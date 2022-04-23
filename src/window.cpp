#include "../include/window.h"

#include <iostream>

namespace pengin { namespace graphics {

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mousebutton_callback(GLFWwindow* window, int button, int action, int mods);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

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
		if (!glfwInit())
		{
			printf("Failed to initialize GLFW\n");
			return false;
		}
		for (int i=0; i<MAX_KEYS;i++)
			m_Keys[i] = false;

		for (int i=0; i<MAX_MOUSEBUTTONS;i++)
			m_MouseButtons[i] = false;

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
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mousebutton_callback);
		glfwSetWindowUserPointer(m_Window, this);
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

	bool Window::isKeyPressed(int keycode)
	{
		if (keycode >= MAX_KEYS)
			return false;
		return m_Keys[keycode];
	}

	bool Window::isMousePressed(int keycode)
	{
		if (keycode >= MAX_MOUSEBUTTONS)
			return false;
		return m_MouseButtons[keycode];
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*) glfwGetWindowUserPointer(window);
		win->m_Keys[key] = action != GLFW_RELEASE;
	}

	void mousebutton_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*) glfwGetWindowUserPointer(window);
		win->m_MouseButtons[button] = action != GLFW_RELEASE;
	}


} }
