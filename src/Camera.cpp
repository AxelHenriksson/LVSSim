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
    projectionMatrix = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

    cameraMatrix = projectionMatrix * viewMatrix;
}

void Camera::matrix(Shader& shader, const char* uniform) {
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}


void Camera::inputs(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)            position += speed * orientation;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)            position -= speed * orientation;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)            position += speed * glm::normalize(glm::cross(orientation,up));
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)            position -= speed * glm::normalize(glm::cross(orientation,up));

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)        position += speed * up;

    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) position -= speed * up;

    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)   speed = 0.004f;
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) speed = 0.001f;

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if(firstClick) {
            glfwSetCursorPos(window, (width / 2), (height / 2));
            firstClick = false;
        }

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float rotX = sensitivity * (float)(mouseX - (height / 2)) / height;
        float rotY = sensitivity * (float)(mouseY - (height / 2)) / height;

        glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotY), glm::normalize(glm::cross(orientation, up)));
        if(!(glm::angle(newOrientation, up) <= glm::radians(5.0f)) or !(glm::angle(newOrientation, -up) <= glm::radians(5.0f))) {
            orientation = newOrientation;
        }

        orientation = glm::rotate(orientation, glm::radians(-rotX), up);

        glfwSetCursorPos(window, (width / 2), (height / 2));
    }

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE)  {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }

}
