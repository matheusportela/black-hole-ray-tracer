#ifndef RAY_HPP
#define RAY_HPP

#include <Eigen/Core>

class Ray {
  public:
    Ray(Eigen::Vector4d position, Eigen::Vector4d velocity, Eigen::Vector4d acceleration);

    Eigen::Vector4d getPosition();
    Eigen::Vector4d getVelocity();
    Eigen::Vector4d getAcceleration();
    Eigen::Vector4d getDirection();

  private:
    Eigen::Vector4d position;
    Eigen::Vector4d velocity;
    Eigen::Vector4d acceleration;
};

#endif // RAY_HPP
