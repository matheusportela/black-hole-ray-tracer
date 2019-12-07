#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <algorithm>
#include <cmath>
#include <string>

#include <Eigen/Core>

#include "surface.hpp"

class Sphere : public Surface {
  public:
    Sphere(double radius, Eigen::Vector4d centerPoint);

    void setRadius(double radius);
    double getRadius();
    void setCenterPoint(Eigen::Vector4d centerPoint);
    Eigen::Vector4d getCenterPoint();

    std::string getType();
    double calculateIntersectionTime(Eigen::Vector4d rayOrigin, Eigen::Vector4d rayDirection);
    Eigen::Vector4d calculateIntersectionNormal(Eigen::Vector4d intersectionPoint);

  private:
    double radius;
    Eigen::Vector4d centerPoint;
};

#endif // SPHERE_HPP
