#include "camera.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

// OpenGL library includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <debuggl.h>
#include "menger.h"
#include "camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "glm/ext.hpp"
#include <iostream>

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

glm::vec3 Camera::newUp() const{
    return glm::normalize(glm::cross(glm::normalize(glm::cross(look_, up_)), look_));
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
    auto oldCamera = camera_distance_ * look_;
    double diffX = currentX - oldCoords.x;
    double diffY = currentY - oldCoords.y;
    glm::vec3 newVector = (-diffY*tangent_)+(diffX*up_);
    glm::mat4 rotatedVector = glm::rotate(rotation_speed, newVector);
    glm::vec4 changedLook = rotatedVector * glm::vec4(look_, 0);
       look_ = glm::normalize(glm::vec3(changedLook.x, changedLook.y, changedLook.z));
    glm::vec4 changedUp =  rotatedVector * glm::vec4(up_, 0);
    up_ = glm::normalize(glm::vec3(changedUp.x, changedUp.y, changedUp.z));
    tangent_ = newTangent();
    eye_ = eye_ + oldCamera - (camera_distance_ * look_);

}

void Camera::transformViewMatrix(int key) {
    if(key == GLFW_KEY_W) {
        eye_ = eye_ + (zoom_speed * look_);
    }
    if(key == GLFW_KEY_A) {
        eye_ = eye_ -(pan_speed * newTangent());
    }
    if(key == GLFW_KEY_S){
        eye_ = eye_ -  zoom_speed * look_;
    }
    if(key == GLFW_KEY_D){
        eye_ = eye_ + (pan_speed * newTangent());
    }
    if(key == GLFW_KEY_UP){
        eye_ = eye_ + (pan_speed * newUp());
    }
    if(key == GLFW_KEY_DOWN){
        eye_ = eye_ -(pan_speed * newUp());
    }
    if(key == GLFW_KEY_LEFT){
        up_ = glm::rotate(up_, -roll_speed, -look_);
    }
    if(key == GLFW_KEY_RIGHT){
        up_ = glm::rotate(up_, roll_speed, -look_);
    }
}


