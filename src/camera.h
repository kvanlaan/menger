#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
    glm::mat4 get_view_matrix() const;
    void transformViewMatrix(int key);
    glm::vec3 newTangent() const;
    glm::vec3 newUp() const;
    void rotate(double currentX, double currentY);
    void zoom(double mousePos);
    void setCoords(double currentX, double currentY);
    glm::vec2 oldCoords;
    bool coordsSet = false;
    // FIXME: add functions to manipulate camera objects.
private:
    float camera_distance_ = 3.0;
    glm::vec3 look_ = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up_ = glm::vec3(0.0f, 1.0, 0.0f);
    glm::vec3 eye_ = glm::vec3(0.0f, 0.0f, camera_distance_);
    glm::vec3 tangent_ = glm::cross(look_, up_);
    // Note: you may need additional member variables
};

#endif
