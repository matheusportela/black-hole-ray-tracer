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
#include "ray.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "viewport.hpp"

class RayTracingRenderer : public Renderer {
  public:
    RayTracingRenderer(std::shared_ptr<Viewport> viewport, std::shared_ptr<Projection> projection, std::shared_ptr<Camera> camera);
    void animate(Scene scene, double duration, double step, std::string prefix, ProjectionType projectionType);
    Image render(Scene scene, ProjectionType projectionType);

  private:
    void updateCamera(double step);
    double cameraRadius {2};
    double cameraXZAngle {M_PI_2};
    double cameraAngularVelocity {M_PI/5};

    std::string formatFrameName(std::string prefix, int frameNumber);

    Ray generateRay(int x, int y, ProjectionType projectionType);
    Ray updateRay(Scene scene, Ray ray);

    std::shared_ptr<Color> calculatePixelColor(Scene scene, Ray ray);
    bool calculateSpherePixelColor(std::shared_ptr<Sphere> sphere, Ray ray, double t);
    std::pair<std::shared_ptr<Sphere>, double> findIntersectedBlackHole(Scene scene, Ray ray);
    std::pair<std::shared_ptr<Sphere>, double> findIntersectedStar(Scene scene, Ray ray);
    std::pair<std::shared_ptr<Disk>, double> findIntersectedAccretionDisk(Scene scene, Ray ray);

    std::shared_ptr<Viewport> viewport;
    std::shared_ptr<Projection> projection;
    std::shared_ptr<Camera> camera;

    double timeStep {1};
    int numIterations {100};
};

#endif // RAY_TRACING_RENDERER_HPP
