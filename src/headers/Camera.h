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

    private:

    glm::vec3 m_position;
    glm::vec3 m_orientation;
    glm::vec3 m_up;
    glm::vec2 m_dimensions;
    float m_scale;

    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_cameraMatrix;


    void updateViewMatrix();
    void updateProjectionMatrix();

    public:

    Camera(
        glm::vec2 dimensions,
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f), 
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float scale = 1.0f
        ): m_position(position), m_orientation(orientation), m_up(up), m_scale(scale), m_dimensions(dimensions) {
            updateViewMatrix();
            updateProjectionMatrix();
    }

    Camera() {}

    void applyMatrix(Shader& shader, const char* uniform);

    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    //void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void key_input(GLFWwindow* window);

    void setPosition(glm::vec3 position) { 
        m_position = position; 
        updateViewMatrix();
    }

    glm::vec3 getPosition() { 
        return m_position;
    }

    void setOritentation(glm::vec3 orientation) { 
        m_orientation = orientation; 
        updateViewMatrix();
    }

    void setUp(glm::vec3 up) {
        m_up = up;
        updateViewMatrix();
    }

    void setDimensions(glm::vec2 dimensions) { 
        m_dimensions = dimensions; 
        updateProjectionMatrix();
    }

    void setScale(float scale) {
        m_scale = scale;
        updateProjectionMatrix();
    }


        
};

#endif