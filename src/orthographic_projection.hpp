#ifndef ORTHOGRAPHIC_PROJECTION_HPP
#define ORTHOGRAPHIC_PROJECTION_HPP

#include <Eigen/Core>

#include "log.hpp"
#include "projection.hpp"

class OrthographicProjection : public Projection {
  public:
    OrthographicProjection(double left, double right, double bottom, double top, double near, double far);

  private:
    void generateTransformation();
};

#endif // ORTHOGRAPHIC_PROJECTION_HPP
