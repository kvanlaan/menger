#include "camera.h"
#include <GLFW/glfw3.h>
#include "glm/ext.hpp"

namespace {
float pan_speed = 0.1f;
float roll_speed = 0.1f;
float rotation_speed = 0.05f;
float zoom_speed = 0.1f;
};

// FIXME: Calculate the view matrix
glm::mat4 Camera::get_view_matrix() const {
    glm::mat4 matrix(0.0);
    matrix[0] = glm::vec4(tangent_.x, tangent_.y, tangent_.z, 0);
    matrix[1] = glm::vec4(up_.x, up_.y, up_.z, 0);
    matrix[2] = glm::vec4(-look_.x, -look_.y, -look_.z, 0);
    matrix[3] = glm::vec4(eye_.x, eye_.y, eye_.z, 1);
    return glm::inverse((matrix));
}

glm::vec3 Camera::newTangent() const{
    return glm::normalize(glm::cross(look_, up_));
}

void Camera::zoom(double currentMousePos) {
    bool zoomIn = true;
    double checkingForZoomDirection = currentMousePos;
    if(coordsSet) {
        if(oldCoords.y < currentMousePos) {
            zoomIn = false;
        }
    }
    auto oldCamera = camera_distance_ * look_;
    if(zoomIn) {
        camera_distance_ = camera_distance_ - zoom_speed;
        if(camera_distance_ <= 0.0001) {
            camera_distance_ = 0.001;
        }
        eye_ = (eye_ + oldCamera) -  (camera_distance_ * look_);
    } else {
        camera_distance_ = camera_distance_ + zoom_speed;
        eye_ = (eye_ + oldCamera) - (camera_distance_ * look_);
    }

}

void Camera::setCoords(double currentX, double currentY) {
    oldCoords = glm::vec2(currentX, currentY);
    coordsSet = true;
}

void Camera::rotate(double currentX, double currentY) {
    // my own version of center
    auto oldCamera = camera_distance_ * look_;
    double diffX = currentX - oldCoords.x;
    double diffY = currentY - oldCoords.y;
    // get the new vector
    glm::vec3 newVector = (-diffY*tangent_)+(diffX*up_);
    // translate to world coordinated
    glm::mat4 rotatedVector = glm::rotate(rotation_speed, newVector);

    // need to adjust remaining coords
    glm::vec4 changedLook = rotatedVector * glm::vec4(look_, 0);
    look_ = glm::normalize(glm::vec3(changedLook.x, changedLook.y, changedLook.z));
    glm::vec4 changedUp =  rotatedVector * glm::vec4(up_, 0);
    up_ = glm::normalize(glm::vec3(changedUp.x, changedUp.y, changedUp.z));
    tangent_ = newTangent();

    eye_ = eye_ + oldCamera - (camera_distance_ * look_);

}

void Camera::transformViewMatrix(int key) {
    // up down
    if(key == GLFW_KEY_UP){
        eye_ = eye_ + (pan_speed * up_);
    }
    if(key == GLFW_KEY_DOWN){
        eye_ = eye_ -(pan_speed * up_);
    }
    //rolling
    if(key == GLFW_KEY_LEFT){
        up_ = glm::normalize(glm::rotate(up_, -roll_speed, -look_));
    }
    if(key == GLFW_KEY_RIGHT){
        up_ = glm::normalize(glm::rotate(up_, roll_speed, -look_));
    }
    //strafing
    if(key == GLFW_KEY_W) {
        eye_ = eye_ + (zoom_speed * look_);
    }
    if(key == GLFW_KEY_A) {
        eye_ = eye_ -(pan_speed * newTangent());
    }
    if(key == GLFW_KEY_S){
        eye_ = eye_ - (zoom_speed * look_);
    }
    if(key == GLFW_KEY_D){
        eye_ = eye_ + (pan_speed * newTangent());
    }
}


