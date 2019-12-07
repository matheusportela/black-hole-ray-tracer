#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include <Eigen/Core>

#include "log.hpp"

class Viewport {
  public:
    Viewport(int width, int height);
    int getWidth();
    int getHeight();
    Eigen::Matrix4d getTransformation();

  private:
    void generateTransformation();

    int width;
    int height;

    Eigen::Matrix4d transformation;
};

#endif // VIEWPORT_HPP
