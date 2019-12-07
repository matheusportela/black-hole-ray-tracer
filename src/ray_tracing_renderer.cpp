#include "ray_tracing_renderer.hpp"

RayTracingRenderer::RayTracingRenderer(std::shared_ptr<Viewport> viewport, std::shared_ptr<Projection> projection, std::shared_ptr<Camera> camera) : viewport(viewport), projection(projection), camera(camera) {
}

void RayTracingRenderer::animate(Scene scene, double duration, double step, std::string prefix) {
    LOG_I("Animating scene \"" << scene.getName() << "\" for " << std::to_string(duration) << " seconds with steps of " << std::to_string(step) << " seconds");

    int frameNumber = 0;
    for (double t = 0; t < duration; t += step, frameNumber++) {
        Image frame = this->render(scene, PerspectiveProjection);
        frame.save(this->formatFrameName(prefix, frameNumber) + ".png");

        // Update positions
        this->camera->setPositionPoint(this->camera->getPositionPoint() + step*this->camera->getVelocityVector());
    }
}

std::string RayTracingRenderer::formatFrameName(std::string prefix, int frameNumber) {
    std::stringstream formattedFrameNumber;
    formattedFrameNumber << std::setw(4) << std::setfill('0') << std::to_string(frameNumber);
    std::string frameName = prefix + "_" + formattedFrameNumber.str();;
    return frameName;
}

Image RayTracingRenderer::render(Scene scene, ProjectionType projectionType) {
    std::string projectionName = (projectionType == OrthographicProjection) ? "orthographic" : "perspective";
    LOG_I("Rendering scene \"" << scene.getName() << "\" with " << projectionName << " projection");

    Image image(this->viewport->getWidth(), this->viewport->getHeight());

    tbb::parallel_for(0, this->viewport->getWidth(), [&](int x) {
        tbb::parallel_for(0, this->viewport->getHeight(), [&](int y) {
            auto ray = this->generateRay(x, y, projectionType);
            auto pixel = this->calculatePixelColor(scene, ray);
            image.setPixel(x, y, pixel);
        });
    });

    return image;
}

Ray RayTracingRenderer::generateRay(int x, int y, ProjectionType projectionType) {
    int width = this->viewport->getWidth();
    int height = this->viewport->getHeight();

    Eigen::Vector3d uc = this->camera->getUDirection().head<3>();
    Eigen::Vector3d vc = this->camera->getVDirection().head<3>();
    Eigen::Vector3d wc = this->camera->getWDirection().head<3>();
    Eigen::Vector3d ec = this->camera->getPositionPoint().head<3>();

    double l = this->projection->getLeft();
    double r = this->projection->getRight();
    double b = this->projection->getBottom();
    double t = this->projection->getTop();

    // Fixed focal point at 1 distance of camera origin
    double d = 1;

    double u = l + (r - l)*(x + 0.5)/width;
    double v = b + (t - b)*(y + 0.5)/height;

    Eigen::Vector4d rayOriginPoint;
    Eigen::Vector4d rayDirection;
    Eigen::Vector3d vector3;

    if (projectionType == OrthographicProjection) {
        vector3 = ec + u*uc + v*vc;
        rayOriginPoint = Eigen::Vector4d(vector3(0), vector3(1), vector3(2), 1);
        rayDirection = this->camera->getGazeDirection();
    } else if (projectionType == PerspectiveProjection) {
        rayOriginPoint = this->camera->getPositionPoint() - d*this->camera->getGazeDirection();
        vector3 = u*uc + v*vc - d*wc;
        rayDirection = Eigen::Vector4d(vector3(0), vector3(1), vector3(2), 0);
    }

    return Ray(rayOriginPoint, rayDirection);
}

std::shared_ptr<Color> RayTracingRenderer::calculatePixelColor(Scene scene, Ray ray) {
    std::shared_ptr<Surface> intersectedSurface = this->findIntersectedSurface(scene, ray);

    if (intersectedSurface != nullptr)
        return intersectedSurface->getColor();
    else
        return ColorFactory::generateBlack();
}

std::shared_ptr<Surface> RayTracingRenderer::findIntersectedSurface(Scene scene, Ray ray) {
    std::shared_ptr<Surface> intersectedSurface = nullptr;
    double intersectionTime = -1;

    double t;

    for (std::shared_ptr<Surface> surface : scene.getSurfaces()) {
        t = surface->calculateIntersectionTime(ray);

        if (t < 0)
            continue;

        if (intersectedSurface == nullptr || t < intersectionTime) {
            intersectedSurface = surface;
            intersectionTime = t;
        }
    }

    return intersectedSurface;
}
