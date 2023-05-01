

#include <CGraphics.h>



// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES      /     COLORS    /    TexCoord    /     NORMALS    //
	-10.0f, -10.0f, 0.0f, 0.0f, 0.0f, 0.0f,  -10.0f, -10.0f, 0.0f, 0.0f, 1.0f,
	-10.0f, 10.0f,  0.0f,  0.0f, 0.0f, 0.0f, -10.0f, 10.0f, 0.0f, 0.0f, 1.0f,
	10.0f, 10.0f,  0.0f,  0.0f, 0.0f, 0.0f,  10.0f,  10.0f, 0.0f, 0.0f, 1.0f,
	10.0f, -10.0f,  0.0f,  0.0f, 0.0f, 0.0f, 10.0f,  -10.0f, 0.0f, 0.0f, 1.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


int windowWidth = 1000;
int windowHeight = 1000;
glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);



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

	// Create a GLFWwindow object of 800 by 800 pixels, naming it CGraphics_Application_Name
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, CGraphics_Application_Name, NULL, NULL);
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



	// Generates Shader object using shaders defualt.vert and default.frag
	Shader lightShader("../res/shaders/light.vert", "../res/shaders/light.frag");
	Shader grassShader("../res/shaders/grass.vert", "../res/shaders/grass.frag");


	// Light object
	// Generates Vertex Array Object and binds it
	VAO lightVAO;
	lightVAO.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	// Generates Element Buffer Object and links it to indices
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	// Links VBO to VAO
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*) 0);
	// Unbind all to prevent accidentally modifying them
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);


	//Tropical pyramid
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*) 0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*) (3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*) (6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*) (8 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	glm::vec3 groundPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 groundModel = glm::mat4(1.0f);
	groundModel = glm::translate(groundModel, groundPos);
	
	// Texture
	//Texture tropical("../res/textures/tropical.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	//tropical.texUnit(pyramidShader, "tex0", 0);
	Texture grass_D("../res/textures/grass_D.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	grass_D.texUnit(grassShader, "diffuseTex", 0);
	Texture grass_R("../res/textures/grass_R.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
	grass_R.texUnit(grassShader, "roughnessTex", 1);
	Texture grass_N("../res/textures/grass_N.png", GL_TEXTURE_2D, 2, GL_RGBA, GL_UNSIGNED_BYTE);
	grass_N.texUnit(grassShader, "normalTex", 2);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	grassShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(grassShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(groundModel));
	glUniform4f(glGetUniformLocation(grassShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(grassShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	glEnable(GL_DEPTH_TEST);

	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 5.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		camera.key_input(window);
		
		grassShader.Activate();
		glUniform3f(glGetUniformLocation(grassShader.ID, "camPos"), camera.position.x, camera.position.y, camera.position.z);
		camera.matrix(grassShader, "camMatrix");
		// Binds texture so that it appears in rendering
		grass_D.Bind();
		grass_R.Bind();
		grass_N.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		lightShader.Activate();
		camera.matrix(lightShader, "camMatrix");
		lightVAO.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(lightIndices)/sizeof(int), GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	lightShader.Delete();

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	grass_D.Delete();
	grass_R.Delete();
	grass_N.Delete();
	grassShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}