

#include <LVSSim.h>



// Vertices coordinates
GLfloat windowVertices[] =
{ // COORDINATES		TEX COORDS
	0.0f, 0.0f, 0.0f, 	0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 	1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,	1.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 	0.0f, 1.0f,
};

// Indices for vertices order
GLuint windowIndices[] =
{
	0, 1, 2,
	0, 2, 3
};


int windowWidth = 1600;
int windowHeight = 900;

glm::vec4 backgroundColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
glm::vec4 grabberColor = glm::vec4(1.0f, 0.5f, 0.5f, 1.0f);
float grabberWidth = 0.1f;



int main()
{
	

	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it LVSSim_Application_Name
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, LVSSim_Application_Name, NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Set callback function for resizing of window
	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		windowWidth = width;
		windowHeight = height;
		glViewport(0, 0, windowWidth, windowHeight);
	});
	

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	glViewport(0, 0, windowWidth, windowHeight);


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
	glUniform1f(glGetUniformLocation(windowShader.ID, "grabberWidth"), grabberWidth);
	glUniform4fv(glGetUniformLocation(windowShader.ID, "grabberColor"), 1, glm::value_ptr(grabberColor));


	glEnable(GL_DEPTH_TEST);

	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 1.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		camera.key_input(window);
		
		windowShader.Activate();
		//glUniform3f(glGetUniformLocation(windowShader.ID, "camPos"), camera.position.x, camera.position.y, camera.position.z);
		camera.matrix(windowShader, "camMatrix");
		// Binds texture so that it appears in rendering
		//grass_D.Bind();
		// Bind the VAO so OpenGL knows to use it
		windowVAO.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(windowIndices)/sizeof(int), GL_UNSIGNED_INT, 0);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
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
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}