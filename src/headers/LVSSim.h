#ifndef LVSSim_H
#define LVSSim_H

#include <math.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"

#include "LVSSimConfig.h"

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

#endif