#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <algorithm>
#include <cmath>
#include <string>

#include <Eigen/Core>

#include "image.hpp"
#include "surface.hpp"
#include "ray.hpp"

class Sphere : public Surface {
  public:
    Sphere(double radius, Eigen::Vector4d centerPoint, std::string texture = "");

    void setRadius(double radius);
    double getRadius();
    void setCenterPoint(Eigen::Vector4d centerPoint);
    Eigen::Vector4d getCenterPoint();
    Eigen::Vector2d calculateUVMapping(Eigen::Vector4d intersectionPoint);

    std::string getType();
    double calculateIntersectionTime(Ray ray);
    Eigen::Vector4d calculateIntersectionNormal(Eigen::Vector4d intersectionPoint);
    std::shared_ptr<Color> getTextureColor(Eigen::Vector4d intersectionPoint);

  private:
    Image texture;
    double radius;
    Eigen::Vector4d centerPoint;
};

#endif // SPHERE_HPP
