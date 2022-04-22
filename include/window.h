#ifndef INCLUDE_WINDOW_H
#define INCLUDE_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace pengin { namespace graphics {

	class Window
	{
	private:
		const char* m_Title;
		int m_Width, m_Height;
		GLFWwindow* m_Window;

	public:
		Window(int width, int height, const char* title);
		~Window();


		void update();

		bool closed() const;
		void clear() const;
		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }

	private:
		bool init();
	};
} }

#endif /* INCLUDE_WINDOW_H */
