#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <string>

#include <Eigen/Core>
#include <Eigen/Dense>

#include "surface.hpp"

class Triangle : public Surface {
  public:
    Triangle(Eigen::Vector4d p1, Eigen::Vector4d p2, Eigen::Vector4d p3);
    std::string getType();
    double calculateIntersectionTime(Eigen::Vector4d rayOrigin, Eigen::Vector4d rayDirection);
    Eigen::Vector4d calculateIntersectionNormal(Eigen::Vector4d intersectionPoint);

  private:
    Eigen::Vector4d p1;
    Eigen::Vector4d p2;
    Eigen::Vector4d p3;
};

#endif // TRIANGLE_HPP
