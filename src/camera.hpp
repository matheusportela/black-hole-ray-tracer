#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "log.hpp"

class Camera {
  public:
    Camera(Eigen::Vector4d positionPoint, Eigen::Vector4d gazeDirection, Eigen::Vector4d viewUpDirection);
    Eigen::Matrix4d getTransformation();
    Eigen::Vector4d getUDirection();
    Eigen::Vector4d getVDirection();
    Eigen::Vector4d getWDirection();
    Eigen::Vector4d getPositionPoint();
    void setPositionPoint(Eigen::Vector4d positionPoint);
    Eigen::Vector4d getVelocityVector();
    void setVelocityVector(Eigen::Vector4d velocityVector);
    Eigen::Vector4d getGazeDirection();
    Eigen::Vector4d getViewUpDirection();

  private:
    void generateTransformation();

    // Camera model
    Eigen::Matrix4d transformation;
    Eigen::Vector4d u;
    Eigen::Vector4d v;
    Eigen::Vector4d w;
    Eigen::Vector4d positionPoint;
    Eigen::Vector4d velocityVector;
    Eigen::Vector4d gazeDirection;
    Eigen::Vector4d viewUpDirection;
};

#endif // CAMERA_HPP
