#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position) {
    Camera::width = width;
    Camera::height = height;
    Camera::position = position;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane) {
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 projectionMatrix = glm::mat4(1.0f);

    viewMatrix = glm::lookAt(position, position + orientation, up);
    projectionMatrix = glm::ortho(-1.2f, 1.2f, -1.2f, 1.2f, -100.0f, 100.0f);
    //projectionMatrix = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

    cameraMatrix = projectionMatrix * viewMatrix;
}

void Camera::matrix(Shader& shader, const char* uniform) {
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    zoom += 10.0*yoffset;
    zoom = std::max(std::min(zoom, 100), 0);
    position = glm::vec3(position.x, position.y, 5-((4.0/10.0)*std::sqrt(zoom)));
    orientation = glm::vec3(orientation.x, glm::radians(10.0 + ((45.0/10000.0)*zoom*zoom)), orientation.z);
}


// void Camera::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//     if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)            position += speed * glm::vec3(0.0f, 1.0f, 0.0f);    //orientation;
//     if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)            position -= speed * glm::vec3(0.0f, 1.0f, 0.0f);    //orientation;
//     if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)            position += speed * glm::vec3(1.0f, 0.0f, 0.0f);    //glm::normalize(glm::cross(orientation,up));
//     if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)            position -= speed * glm::vec3(1.0f, 0.0f, 0.0f);    //glm::normalize(glm::cross(orientation,up));

//     //if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)        position += speed * up;

//     //if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) position -= speed * up;

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
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)            position += speed * glm::vec3(0.0f, 1.0f, 0.0f);    //orientation;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)            position -= speed * glm::vec3(0.0f, 1.0f, 0.0f);    //orientation;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)            position += speed * glm::vec3(1.0f, 0.0f, 0.0f);    //glm::normalize(glm::cross(orientation,up));
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)            position -= speed * glm::vec3(1.0f, 0.0f, 0.0f);    //glm::normalize(glm::cross(orientation,up));

    //if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)        position += speed * up;

    //if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) position -= speed * up;

    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)   speed = 0.002f;
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) speed = 0.001f;

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}