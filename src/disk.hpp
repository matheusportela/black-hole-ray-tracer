#ifndef DISK_HPP
#define DISK_HPP

#include <algorithm>
#include <cmath>
#include <string>

#include <Eigen/Core>

#include "log.hpp"
#include "surface.hpp"
#include "ray.hpp"

class Disk : public Surface {
  public:
    Disk(double outerRadius, double innerRadius, Eigen::Vector4d centerPoint, Eigen::Vector4d normal);

    // void setRadius(double radius);
    // double getRadius();
    // void setCenterPoint(Eigen::Vector4d centerPoint);
    // Eigen::Vector4d getCenterPoint();
    // Eigen::Vector2d calculateUVMapping(Eigen::Vector4d intersectionPoint);

    std::string getType();
    double calculateIntersectionTime(Ray ray);
    Eigen::Vector4d calculateIntersectionNormal(Eigen::Vector4d intersectionPoint);

  private:
    double outerRadius;
    double innerRadius;
    Eigen::Vector4d centerPoint;
    Eigen::Vector4d normal;
};

#endif // DISK_HPP
