#include "../include/window.h"

#include <iostream>

namespace pengin { namespace graphics {

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mousebutton_callback(GLFWwindow* window, int button, int action, int mods);
	void cursorpos_callback(GLFWwindow* window, double xpos, double ypos);

	Window::Window(int width, int height, const char* title)
	{
		m_Width = width;
		m_CurrWidth = width;
		m_Height = height;
		m_CurrHeight = height;
		m_Title = title;
		m_Fullscreen = false;
		mx = 0;
		my = 0;
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

		m_Monitor = glfwGetPrimaryMonitor();
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
		glfwSetCursorPosCallback(m_Window, cursorpos_callback);

		glfwSetWindowUserPointer(m_Window, this);
		return true;
	}

	void Window::setFullscreen(bool fullscreen)
	{
		if (fullscreen == m_Fullscreen)
			return;

		m_Fullscreen = fullscreen;

		const GLFWvidmode* mode = glfwGetVideoMode(m_Monitor);

		if (fullscreen)
		{
			m_CurrWidth = mode->width;
			m_CurrHeight = mode->height;
			glfwSetWindowMonitor(m_Window, m_Monitor, 0, 0, m_CurrWidth, m_CurrHeight, mode->refreshRate);
		}
		else
		{
			m_CurrWidth = m_Width;
			m_CurrHeight = m_Height;
			glfwSetWindowMonitor(m_Window, NULL, 0, 0, m_CurrWidth, m_CurrHeight, mode->refreshRate);
		}

	}

	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_Window);
	}

	void Window::update()
	{
		//printf("w, h: (%d, %d); cw, ch: (%d, %d)\n", m_Width, m_Height, m_CurrWidth, m_CurrHeight);
		glfwSwapBuffers(m_Window);
		glfwGetFramebufferSize(m_Window, &m_CurrWidth, &m_CurrHeight);
		glViewport(0, 0, m_CurrWidth, m_CurrHeight);
		glfwPollEvents();
	}

	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	bool Window::isKeyDown(int keycode)
	{
		if (keycode >= MAX_KEYS)
			return false;
		return m_Keys[keycode];
	}

	bool Window::isKeyPressed(int keycode)
	{
		if (keycode >= MAX_KEYS)
			return false;
		return m_KeysPressed[keycode];
	}

	bool Window::isMousePressed(int keycode)
	{
		if (keycode >= MAX_MOUSEBUTTONS)
			return false;
		return m_MouseButtons[keycode];
	}

	void Window::getMousePosition(double* x, double* y)
	{
		*x = mx;
		*y = my;
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

	void cursorpos_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* win = (Window*) glfwGetWindowUserPointer(window);
		win->mx = xpos;
		win->my = ypos;
	}

} }
