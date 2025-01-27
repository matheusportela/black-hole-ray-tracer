#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <memory>
#include <string>

#include <Eigen/Core>

#include "color.hpp"
#include "color_factory.hpp"
#include "ray.hpp"

class Surface {
  public:
    Surface();

    virtual std::string getType() = 0;
    virtual double calculateIntersectionTime(Ray ray) = 0;
    virtual Eigen::Vector4d calculateIntersectionNormal(Eigen::Vector4d intersectionPoint) = 0;

    void setColor(std::shared_ptr<Color> color);
    std::shared_ptr<Color> getColor();

  private:
    std::shared_ptr<Color> color;
};

#endif // SURFACE_HPP
