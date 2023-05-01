#ifndef CAMERA_H
#define CAMERA_H


#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include<math.h>

#include "Shader.h"


class Camera {

    public:
        glm::vec3 position;
        glm::vec3 orientation = glm::vec3(0.0f, 0.2f, -1.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::mat4 cameraMatrix = glm::mat4(1.0f);
        
        int zoom = 50;

        int width;
        int height;

        float speed = 0.001f;

        Camera(int width, int height, glm::vec3 position);

        void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
        void matrix(Shader& shader, const char* uniform);

        void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
        //void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void key_input(GLFWwindow* window);
        
};

#endif