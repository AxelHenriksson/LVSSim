#include <LVSSim.h>


double lastX;
double lastY;
bool pressed = false;

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);

class LVSSimApp {

	private:
	GLFWwindow* m_window;
	Camera m_camera;
	
	int m_windowWidth = 1600;
	int m_windowHeight = 900;

	public:

	LVSSimApp(int width, int height): m_windowWidth(width), m_windowHeight(height) {
		m_camera = Camera(
			glm::vec2(m_windowWidth/m_windowHeight, 1.0f), 
			glm::vec3(0.0f, 0.0f, 1.0f)
		);
	}
	
	int start() {

		

		// Initialize GLFW
		glfwInit();
		
		// Tell GLFW what version of OpenGL we are using 
		// In this case we are using OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		// Tell GLFW we are using the CORE profile
		// So that means we only have the modern functions
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create a GLFWwindow object naming it LVSSim_Application_Name
		m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, LVSSim_Application_Name, NULL, NULL);
		// Error check if the window fails to create
		if (m_window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}

		// Introduce the window into the current context
		glfwMakeContextCurrent(m_window);

		// Set callback function for resizing of window
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		});

		glfwSetCursorPosCallback(m_window, cursorPosCallback);

		//Load GLAD so it configures OpenGL
		gladLoadGL();
		// Specify the viewport of OpenGL in the Window
		glViewport(0, 0, m_windowWidth, m_windowHeight);

		Shader windowShader("../res/shaders/window.vert", "../res/shaders/window.frag");

		// Window
		// Generates Vertex Array Object and binds it
		VAO windowVAO;
		windowVAO.Bind();

		// Generates Vertex Buffer Object and links it to vertices
		VBO windowVBO(windowVertices, sizeof(windowVertices));
		// Generates Element Buffer Object and links it to indices
		EBO windowEBO(windowIndices, sizeof(windowIndices));

		// Links VBO to VAO
		windowVAO.LinkAttrib(windowVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*) 0);	// Coordinates
		windowVAO.LinkAttrib(windowVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*) (3*sizeof(float)));	// Coordinates
		// Unbind all to prevent accidentally modifying them
		windowVAO.Unbind();
		windowVBO.Unbind();
		windowEBO.Unbind();

		glm::vec3 windowPos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::mat4 windowModel = glm::mat4(1.0f);
		windowModel = glm::translate(windowModel, windowPos);
		
		// Texture
		//Texture grass_D("../res/textures/grass_D.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
		//grass_D.texUnit(grassShader, "diffuseTex", 0);

		windowShader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(windowShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(windowModel));
		glUniform4fv(glGetUniformLocation(windowShader.ID, "grabberColor"), 1, glm::value_ptr(glm::vec4(0.9f, 0.1f, 0.1f, 1.0f)));


		glEnable(GL_DEPTH_TEST);

		// Main while loop
		while (!glfwWindowShouldClose(m_window))
		{
			// Specify the color of the background
			glClearColor(0.16f, 0.16f, 0.16f, 0.16f);
			// Clean the back buffer and assign the new color to it
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_camera.key_input(m_window);
			
			windowShader.Activate();
			glm::vec3 camPos = m_camera.getPosition();
			glUniform3f(glGetUniformLocation(windowShader.ID, "camPos"), camPos.x, camPos.y, camPos.z);
			m_camera.applyMatrix(windowShader, "camMatrix");
			// Binds texture so that it appears in rendering
			//grass_D.Bind();
			// Bind the VAO so OpenGL knows to use it
			windowVAO.Bind();
			// Draw primitives, number of indices, datatype of indices, index of indices
			glDrawElements(GL_TRIANGLES, sizeof(windowIndices)/sizeof(int), GL_UNSIGNED_INT, 0);

			// Swap the back buffer with the front buffer
			glfwSwapBuffers(m_window);
			// Take care of all GLFW events
			glfwPollEvents();
		}



		// Delete all the objects we've created
		windowVAO.Delete();
		windowVBO.Delete();
		windowEBO.Delete();

		//grass_D.Delete();
		windowShader.Delete();

		// Delete window before ending the program
		glfwDestroyWindow(m_window);
		// Terminate GLFW before ending the program
		glfwTerminate();
		return 0;
	}

	void dragCallback(double deltaX, double deltaY) {
		glm::vec3 camPos = m_camera.getPosition();
		m_camera.setPosition(glm::vec3(camPos.x - 0.001*deltaX, camPos.y + 0.001*(1.6)*deltaY, camPos.z));
	}
};

LVSSimApp application = LVSSimApp(1600, 1000);

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)  {
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) 
			{
				pressed = false;
				return;
			}

			if(pressed) {
				application.dragCallback(xpos-lastX, ypos-lastY);
			}

			lastX = xpos;
			lastY = ypos;

			pressed = true;
}


int main()
{
	return application.start();
}