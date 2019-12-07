#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "image.hpp"
#include "scene.hpp"

class Renderer {
  public:
    enum ProjectionType {
        OrthographicProjection,
        PerspectiveProjection
    };

    virtual void animate(Scene scene, double duration, double step, std::string prefix) = 0;
    virtual Image render(Scene scene, ProjectionType projectionType) = 0;
};

#endif // RENDERER_HPP
