#include "ray.hpp"

Ray::Ray(Eigen::Vector4d position, Eigen::Vector4d velocity, Eigen::Vector4d acceleration) :
    position(position), velocity(velocity), acceleration(acceleration) {}

Eigen::Vector4d Ray::getPosition() {
    return this->position;
}

Eigen::Vector4d Ray::getVelocity() {
    return this->velocity;
}

Eigen::Vector4d Ray::getAcceleration() {
    return this->acceleration;
}

Eigen::Vector4d Ray::getDirection() {
    return this->velocity.normalized();
}