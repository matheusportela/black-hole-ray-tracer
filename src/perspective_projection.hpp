#ifndef PERSPECTIVE_PROJECTION_HPP
#define PERSPECTIVE_PROJECTION_HPP

#include <Eigen/Core>

#include "log.hpp"
#include "projection.hpp"

class PerspectiveProjection : public Projection {
  public:
    PerspectiveProjection(double left, double right, double bottom, double top, double near, double far);

  private:
    void generateTransformation();
};

#endif // PERSPECTIVE_PROJECTION_HPP
