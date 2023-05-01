#include "Camera.h"


void Camera::updateViewMatrix() {
    m_viewMatrix = glm::lookAt(m_position, m_position + m_orientation, m_up);
}

void Camera::updateProjectionMatrix() {
    m_projectionMatrix = glm::ortho(-m_dimensions.x/2, m_dimensions.x/2, -m_dimensions.y/2, m_dimensions.y/2, -100.0f, 100.0f);
    //projectionMatrix = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);
}

void Camera::applyMatrix(Shader& shader, const char* uniform) {
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(m_viewMatrix * m_projectionMatrix));
}

void Camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    // m_scale += 10.0*yoffset;
    // m_scale = std::max(std::min(m_scale, 100.0f), 0.0f);
    // m_position = glm::vec3(m_position.x, m_position.y, 5-((4.0/10.0)*std::sqrt(m_scale)));
}


// void Camera::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//     if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)            m_position += speed * glm::vec3(0.0f, 1.0f, 0.0f);    //orientation;
//     if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)            m_position -= speed * glm::vec3(0.0f, 1.0f, 0.0f);    //orientation;
//     if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)            m_position += speed * glm::vec3(1.0f, 0.0f, 0.0f);    //glm::normalize(glm::cross(orientation,up));
//     if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)            m_position -= speed * glm::vec3(1.0f, 0.0f, 0.0f);    //glm::normalize(glm::cross(orientation,up));

//     //if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)        m_position += speed * up;

//     //if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) m_position -= speed * up;

//     if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)   speed = 0.2f;
//     if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) speed = 0.1f;

//     if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
//         glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//     }
//     if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  {
//         glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//     }
// }

void Camera::key_input(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)            m_position += glm::vec3(0.0f, 1.0f, 0.0f);    //orientation;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)            m_position -= glm::vec3(0.0f, 1.0f, 0.0f);    //orientation;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)            m_position += glm::vec3(1.0f, 0.0f, 0.0f);    //glm::normalize(glm::cross(orientation,up));
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)            m_position -= glm::vec3(1.0f, 0.0f, 0.0f);    //glm::normalize(glm::cross(orientation,up));

    //if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)        m_position += speed * up;

    //if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) m_position -= speed * up;

    // if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)   speed = 0.002f;
    // if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) speed = 0.001f;
}