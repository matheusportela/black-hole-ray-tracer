#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <string>

#include <Eigen/Core>
#include <Eigen/Dense>

#include "surface.hpp"
#include "ray.hpp"

class Triangle : public Surface {
  public:
    Triangle(Eigen::Vector4d p1, Eigen::Vector4d p2, Eigen::Vector4d p3);
    std::string getType();
    double calculateIntersectionTime(Ray ray);
    Eigen::Vector4d calculateIntersectionNormal(Eigen::Vector4d intersectionPoint);

  private:
    Eigen::Vector4d p1;
    Eigen::Vector4d p2;
    Eigen::Vector4d p3;
};

#endif // TRIANGLE_HPP
