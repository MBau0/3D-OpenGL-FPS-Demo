#include "Engine.h"

#include "../src/Utility/Clock.h"
#include "../src/Resources/Window.h"
#include "../src/Resources/ResourceManager.h"

#include "../src/Resources/Camera.h"

#include "../src/Resources/Entities/Entity.h"

Engine::Engine() :
	_exit			 ( false )
{
	Clock* clock = new Clock;
	_environment.set_clock(clock);

	Window* window = new Window;
	_environment.set_window(window);

	ResourceManager* resource_manager = new ResourceManager;
	_environment.set_resource_manager(resource_manager);
	resource_manager->load_resources();
}

Engine::~Engine() {
	_environment.shut_down();
}


void Engine::run() {

	while (!_exit) {
		_environment.get_clock()->update();
		_environment.get_window()->update();

		render();

		input();
	}
	
}

void Engine::input() {
	glfwPollEvents();
	GLFWwindow* window = _environment.get_window()->get_glfw_window();

	if (!glfwGetWindowAttrib(window, GLFW_FOCUSED)) {
		return;
	}

	_exit = glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE);

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	_environment.get_window()->get_camera()->move_angle((float)xpos, (float)ypos);
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window, width / 2, height / 2);

	if (glfwGetKey(window, GLFW_KEY_W)) {
		_environment.get_window()->get_camera()->move(CAMERA_FORWARD);
	}

	if (glfwGetKey(window, GLFW_KEY_S)) {
		_environment.get_window()->get_camera()->move(CAMERA_BACKWARD);
	}

	if (glfwGetKey(window, GLFW_KEY_A)) {
		_environment.get_window()->get_camera()->move(CAMERA_LEFT);
	}

	if (glfwGetKey(window, GLFW_KEY_D)) {
		_environment.get_window()->get_camera()->move(CAMERA_RIGHT);
	}

	if (glfwGetKey(window, GLFW_KEY_E)) {
		_environment.get_window()->get_camera()->move(CAMERA_UP);
	}

	if (glfwGetKey(window, GLFW_KEY_Q)) {
		_environment.get_window()->get_camera()->move(CAMERA_DOWN);
	}
}

void Engine::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearBufferfv(GL_COLOR, 0, WINDOW_BACKGROUND_COLOR);

	Environment::get().get_resources()->get_model(0)->draw();
	//Environment::get().get_resource_manager()->get_model(1)->draw();

	glfwSwapBuffers(_environment.get_window()->get_glfw_window());
}