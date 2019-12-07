#ifndef RAY_TRACING_RENDERER_HPP
#define RAY_TRACING_RENDERER_HPP

#include <algorithm>
#include <memory>
#include <string>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

#include <Eigen/Core>

#include <tbb/tbb.h>
#include <tbb/parallel_for.h>

#include "camera.hpp"
#include "image.hpp"
#include "log.hpp"
#include "projection.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "viewport.hpp"

class RayTracingRenderer : public Renderer {
  public:
    RayTracingRenderer(std::shared_ptr<Viewport> viewport, std::shared_ptr<Projection> projection, std::shared_ptr<Camera> camera);
    void animate(Scene scene, double duration, double step, std::string prefix);
    Image render(Scene scene, ProjectionType projectionType);

  private:
    std::string formatFrameName(std::string prefix, int frameNumber);

    std::pair<std::shared_ptr<Color>, double> calculatePixelColor(Scene scene, Eigen::Vector4d rayOriginPoint, Eigen::Vector4d rayDirection, int iterations = 2);
    std::shared_ptr<Surface> calculateIntersectedSurface(Scene scene, Eigen::Vector4d rayOriginPoint, Eigen::Vector4d rayDirection);

    std::shared_ptr<Viewport> viewport;
    std::shared_ptr<Projection> projection;
    std::shared_ptr<Camera> camera;

    std::shared_ptr<Surface> intersectedSurface;
    double intersectionTime;
};

#endif // RAY_TRACING_RENDERER_HPP