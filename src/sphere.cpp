#include "sphere.hpp"

Sphere::Sphere(double radius, Eigen::Vector4d centerPoint) : radius(radius), centerPoint(centerPoint) {}

void Sphere::setRadius(double radius) {
    this->radius = radius;
}

double Sphere::getRadius() {
    return this->radius;
}

void Sphere::setCenterPoint(Eigen::Vector4d centerPoint) {
    this->centerPoint = centerPoint;
}

Eigen::Vector4d Sphere::getCenterPoint() {
    return this->centerPoint;
}

Eigen::Vector2d Sphere::calculateUVMapping(Eigen::Vector4d intersectionPoint) {
    // Reference: https://en.wikipedia.org/wiki/UV_mapping#Finding_UV_on_a_sphere
    Eigen::Vector4d surfacePoint = intersectionPoint - this->getCenterPoint();
    Eigen::Vector4d d = surfacePoint.normalized();
    double u = 0.5 + atan2(d.z(), d.x())/(2*M_PI);
    double v = 0.5 - asin(d.y())/M_PI;
    return Eigen::Vector2d(u, v);
}

std::string Sphere::getType() {
    return std::string("sphere");
}

double Sphere::calculateIntersectionTime(Ray ray) {
    Eigen::Vector3d c = this->centerPoint.head<3>();
    Eigen::Vector3d e = ray.getPosition().head<3>();
    Eigen::Vector3d d = ray.getDirection().head<3>();

    double delta = pow(d.dot(e - c), 2) - (d.dot(d))*((e - c).dot(e - c) - pow(this->radius, 2));

    if (delta < 0) {
        return -1;
    } else if (delta == 0) {
        return ((-d).dot(e - c) + sqrt(delta))/(d.dot(d));
    } else {
        double t1 = ((-d).dot(e - c) + sqrt(delta))/(d.dot(d));
        double t2 = ((-d).dot(e - c) - sqrt(delta))/(d.dot(d));

        if (t1 < 0 || t2 < 0)
            return std::max(t1, t2);
        return std::min(t1, t2);
    }
}

Eigen::Vector4d Sphere::calculateIntersectionNormal(Eigen::Vector4d intersectionPoint) {
    return -(intersectionPoint - this->centerPoint).normalized();
}