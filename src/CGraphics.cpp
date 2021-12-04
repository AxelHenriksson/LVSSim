

#include <CGraphics.h>



// Vertices coordinates
GLfloat vertices[] =
{	//X		Y		Z		R		G		B		U		V
	-1.0f, 	-1.0f, 	0.0f, 	1.0f, 	0.5f, 	0.0f, 	0.0f, 	0.0f,	
	1.0f, 	-1.0f, 	0.0f, 	0.8f,	0.4f,	0.1f, 	1.0f, 	0.0f,
	1.0f, 	1.0f, 	0.0f, 	0.1f,	0.3f,	0.8f, 	1.0f, 	1.0f,
	-1.0f, 	1.0f, 	0.0f, 	0.3f, 	0.1f,	0.9f, 	0.0f, 	1.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 2,
	0, 2, 1
};

// Triforce triangles
// GLfloat vertices[] =
// {	//X			Y								Z		R		G		B	
// 	-0.5f, 		-0.5f * float(sqrt(3)) / 3, 	0.0f, 	1.0f, 	0.5f, 	0.0f, 	// Lower left corner
// 	0.5f, 		-0.5f * float(sqrt(3)) / 3, 	0.0f, 	0.8f,	0.4f,	0.1f,	// Lower right corner
// 	0.0f, 		0.5f * float(sqrt(3)) * 2 / 3, 	0.0f, 	0.1f,	0.3f,	0.8f,	// Upper corner
// 	-0.5f / 2, 	0.5f * float(sqrt(3)) / 6, 		0.0f, 	0.3f, 	0.1f,	0.9f,	// Inner left
// 	0.5f / 2, 	0.5f * float(sqrt(3)) / 6, 		0.0f, 	0.1f,	0.1f,	0.2f,	// Inner right
// 	0.0f, 		-0.5f * float(sqrt(3)) / 3, 	0.0f,	0.0f,	0.0f,	0.0f	// Inner down
// };
// GLuint indices[] =
// {
// 	0, 3, 5, // Lower left triangle
// 	3, 2, 4, // Lower right triangle
// 	5, 4, 1 // Upper triangle
// };


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

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);



	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("../res/shaders/default.vert", "../res/shaders/default.frag");



	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*) 0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*) (3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*) (6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint scaleUniformID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Texture
	Texture tropical("../res/textures/tropical.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	tropical.texUnit(shaderProgram, "tex0", 0);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Assigns a value to the scale uniform, must always be done after activating shader program
		glUniform1f(scaleUniformID, 0.5f);
		// Binds texture so that it appears in rendering
		tropical.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	tropical.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}