#ifndef INCLUDE_WINDOW_H
#define INCLUDE_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define MAX_KEYS 1024
#define MAX_MOUSEBUTTONS 32

namespace pengin { namespace graphics {

	class Window
	{
	private:
		const char* m_Title;
		int m_Width, m_Height, m_CurrWidth, m_CurrHeight;
		bool m_Fullscreen;
		GLFWwindow* m_Window;
		GLFWmonitor* m_Monitor;

		bool m_Keys[MAX_KEYS];
		bool m_KeysPressed[MAX_KEYS];
		bool m_MouseButtons[MAX_MOUSEBUTTONS];
		double mx, my;

	public:
		Window(int width, int height, const char* title);
		~Window();

		void update();
		bool isKeyDown(int keycode);
		bool isKeyPressed(int keycode);
		bool isMousePressed(int keycode);
		void setFullscreen(bool fullscreen);

		bool closed() const;
		void clear() const;
		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }
		inline bool isFullscreen() const { return m_Fullscreen; }
		void getMousePosition(double* x, double* y);

	private:
		bool init();
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void mousebutton_callback(GLFWwindow* window, int button, int action, int mods);
		friend void cursorpos_callback(GLFWwindow* window, double xpos, double ypos);

	};
} }

#endif /* INCLUDE_WINDOW_H */
