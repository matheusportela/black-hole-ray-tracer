#include "triangle.hpp"

Triangle::Triangle(Eigen::Vector4d p1, Eigen::Vector4d p2, Eigen::Vector4d p3) : p1(p1), p2(p2), p3(p3) {}

std::string Triangle::getType() {
    return "triangle";
}

double Triangle::calculateIntersectionTime(Eigen::Vector4d rayOrigin, Eigen::Vector4d rayDirection) {
    double ax = this->p1(0);
    double ay = this->p1(1);
    double az = this->p1(2);
    double bx = this->p2(0);
    double by = this->p2(1);
    double bz = this->p2(2);
    double cx = this->p3(0);
    double cy = this->p3(1);
    double cz = this->p3(2);
    double dx = rayDirection(0);
    double dy = rayDirection(1);
    double dz = rayDirection(2);
    double ex = rayOrigin(0);
    double ey = rayOrigin(1);
    double ez = rayOrigin(2);


    double a = ax - bx;
    double b = ay - by;
    double c = az - bz;
    double d = ax - cx;
    double e = ay - cy;
    double f = az - cz;
    double g = dx;
    double h = dy;
    double i = dz;

    double j = ax - ex;
    double k = ay - ey;
    double l = az - ez;

    double M = a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g);
    double t = -(f*(a*k -j*b) + e*(j*c - a*l) + d*(b*l - k*c))/M;

    if (t < 0)
        return -1;

    double gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c))/M;

    if (gamma < 0 || gamma > 1)
        return -1;

    double beta = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g))/M;

    if (beta < 0 || beta > (1 - gamma))
        return -1;

    return t;
}

Eigen::Vector4d Triangle::calculateIntersectionNormal(Eigen::Vector4d intersectionPoint) {
    Eigen::Vector3d a, b, c, n;
    Eigen::Vector4d intersectionNormal;

    a << this->p1.head<3>();
    b << this->p2.head<3>();
    c << this->p3.head<3>();

    n = (c - a).cross(b - a).normalized();
    intersectionNormal << n, 0;

    return intersectionNormal;
}