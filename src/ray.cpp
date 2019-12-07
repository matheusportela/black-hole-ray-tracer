#include "ray.hpp"

Ray::Ray(Eigen::Vector4d origin_point, Eigen::Vector4d direction) :
    origin_point(origin_point), direction(direction) {}

Eigen::Vector4d Ray::getOriginPoint() {
    return this->origin_point;
}

Eigen::Vector4d Ray::getDirection() {
    return this->direction;
}
