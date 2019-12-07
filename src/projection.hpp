#ifndef PROJECTION_HPP
#define PROJECTION_HPP

#include <Eigen/Core>

class Projection {
  public:
    Eigen::Matrix4d getTransformation();
    double getLeft();
    double getRight();
    double getBottom();
    double getTop();
    double getNear();
    double getFar();

  protected:
    virtual void generateTransformation() = 0;
    Eigen::Matrix4d transformation;

    double left;
    double right;
    double bottom;
    double top;
    double near;
    double far;
};

#endif // PROJECTION_HPP
