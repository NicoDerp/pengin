#include "include/window.h"
#include <iostream>

int main()
{
	using namespace pengin;
	using namespace graphics;

	Window window(600, 600, "Pengin test");
	glClearColor(0.2f, 0.3f, 0.6f, 1.0f);

	while (!window.closed())
	{
		if (window.isKeyDown(GLFW_KEY_ESCAPE))
			break;

		if (window.isKeyDown(GLFW_KEY_L))
			printf("aa\n");

		if (window.isKeyDown(GLFW_KEY_Q))
		{
			bool fullscreen = window.isFullscreen();
			window.setFullscreen(!fullscreen);
		}

		double x, y;
		window.getMousePosition(&x, &y);
		printf("Cursor position: %f, %f\n", x, y);

		window.clear();
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f( 0.0f,  0.5f);
		glVertex2f( 0.5f, -0.5f);
		glEnd();
		window.update();
	}

	/*
	float t[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
	};
	uint32_t v;
	glGenBuffers(1, &v);
	glBindBuffer(GL_ARRAY_BUFFER, v);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t)*sizeof(t)/sizeof(t[0]), &t[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
	glEnableVertexAttribArray(0);
	glViewport(0, 0, 600, 600);
	while(!glfwWindowShouldClose(w))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(w);
		glfwPollEvents();
	}*/
	return 0;
}
