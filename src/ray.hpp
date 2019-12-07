#ifndef RAY_HPP
#define RAY_HPP

#include <Eigen/Core>

class Ray {
  public:
    Ray(Eigen::Vector4d origin_point, Eigen::Vector4d direction);

    Eigen::Vector4d getOriginPoint();
    Eigen::Vector4d getDirection();

  private:
    Eigen::Vector4d origin_point;
    Eigen::Vector4d direction;
};

#endif // RAY_HPP
