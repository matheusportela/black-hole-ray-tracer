#include "ray_tracing_renderer.hpp"

RayTracingRenderer::RayTracingRenderer(std::shared_ptr<Viewport> viewport, std::shared_ptr<Projection> projection, std::shared_ptr<Camera> camera) : viewport(viewport), projection(projection), camera(camera) {
}

void RayTracingRenderer::animate(Scene scene, double duration, double step, std::string prefix, ProjectionType projectionType) {
    LOG_I("Animating scene \"" << scene.getName() << "\" for " << std::to_string(duration) << " seconds with steps of " << std::to_string(step) << " seconds");

    int frameNumber = 0;
    for (double t = 0; t < duration; t += step, frameNumber++) {
        Image frame = this->render(scene, projectionType);
        frame.save(this->formatFrameName(prefix, frameNumber) + ".png");

        double omega = 10*M_PI/180;
        Eigen::Matrix4d transformation;
        transformation <<
            0, -omega, 0, 0,
            omega, 0, -omega, 0,
            0, omega, 0, 0,
            0, 0, 0, 1;

        // Update positions
        this->camera->setPositionPoint(this->camera->getPositionPoint() + step*this->camera->getVelocityVector());
        // this->camera->setPositionPoint(transformation*this->camera->getPositionPoint());
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
    // for(int x = 0; x < this->viewport->getWidth(); x++) {
    //     for(int y = 0; y < this->viewport->getHeight(); y++) {
            // Render background
            // int stride = 50;
            // if ((x/stride) % 2 == (y/stride) % 2)  {
            //     image.setPixel(x, y, ColorFactory::generateGray());
            // } else {
            //     image.setPixel(x, y, ColorFactory::generateWhite());
            // }
            image.setPixel(x, y, ColorFactory::generateBlack());

            // Render surfaces
            auto ray = this->generateRay(x, y, projectionType);
            auto color = this->calculatePixelColor(scene, ray);
            if (color != nullptr)
                image.setPixel(x, y, color);
    //     };
    // };
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

    Eigen::Vector4d rayPosition;
    Eigen::Vector4d rayDirection;
    Eigen::Vector3d vector3;
    Eigen::Vector4d cameraGazeDirection = this->camera->getTransformation()*Eigen::Vector4d(0, 0, -1, 0);

    if (projectionType == OrthographicProjection) {
        vector3 = ec + u*uc + v*vc;
        rayPosition = Eigen::Vector4d(vector3(0), vector3(1), vector3(2), 1);
        rayDirection = cameraGazeDirection;
    } else if (projectionType == PerspectiveProjection) {
        rayPosition = this->camera->getPositionPoint() - d*cameraGazeDirection;
        vector3 = u*uc + v*vc - d*wc;
        rayDirection = Eigen::Vector4d(vector3(0), vector3(1), vector3(2), 0);
    }

    return Ray(rayPosition, rayDirection, Eigen::Vector4d(0, 0, 0, 0));
}

Ray RayTracingRenderer::updateRay(Scene scene, Ray ray) {
    Eigen::Vector4d position = ray.getPosition();
    Eigen::Vector4d velocity = ray.getVelocity();
    Eigen::Vector4d acceleration = ray.getAcceleration();
    double delta_t = this->timeStep;

    acceleration = Eigen::Vector4d(0, 0, 0, 0);
    for (std::shared_ptr<Sphere> black_hole : scene.getBlackHoles()) {
        // between 0 and -1.5
        double power_coeff = -1.5;
        // double h2 = 0.0125*black_hole->getRadius();
        double h2 = 0.025*black_hole->getRadius();
        Eigen::Vector4d p = (position - black_hole->getCenterPoint());
        p[3] = 0;
        // Eigen::Vector4d p(position.x(), position.y(), position.z(), 0);
        acceleration += power_coeff*h2*p/pow(p.squaredNorm(), 2.5);
    }

    velocity += acceleration*delta_t;
    position += velocity*delta_t;

    return Ray(position, velocity, acceleration);
}

std::shared_ptr<Color> RayTracingRenderer::calculatePixelColor(Scene scene, Ray ray) {
    for (int i = 0; i < this->numIterations; i++) {
        auto [intersectedBlackHole, tBlackHole] = this->findIntersectedBlackHole(scene, ray);

        if (intersectedBlackHole != nullptr) {
            // return intersectedBlackHole->getColor();
            return this->calculateSpherePixelColor(intersectedBlackHole, ray, tBlackHole) ? ColorFactory::generateRed() : ColorFactory::generateBlack();
        }

        auto [intersectedStar, tStar] = this->findIntersectedStar(scene, ray);

        if (intersectedStar != nullptr) {
            // return intersectedStar->getColor();
            return this->calculateSpherePixelColor(intersectedStar, ray, tStar) ? ColorFactory::generateBlue() : ColorFactory::generateWhite();
        }

        ray = this->updateRay(scene, ray);
    }

    return nullptr;
}

bool RayTracingRenderer::calculateSpherePixelColor(std::shared_ptr<Sphere> sphere, Ray ray, double t) {
    Eigen::Vector4d intersectionPoint = ray.getPosition() + (ray.getDirection()*t);
    Eigen::Vector2d uv = sphere->calculateUVMapping(intersectionPoint);
    return ((int)(10*uv.x()) % 2 == (int)(10*uv.y()) % 2);
}

std::pair<std::shared_ptr<Sphere>, double> RayTracingRenderer::findIntersectedBlackHole(Scene scene, Ray ray) {
    std::shared_ptr<Sphere> intersectedBlackHole = nullptr;
    double intersectionTime = -1;

    double t;

    for (std::shared_ptr<Sphere> black_hole : scene.getBlackHoles()) {
        t = black_hole->calculateIntersectionTime(ray);

        if (t < 0 || t > this->timeStep) {
            continue;
        }

        if (intersectedBlackHole == nullptr || t < intersectionTime) {
            intersectedBlackHole = black_hole;
            intersectionTime = t;
        }
    }

    return std::make_pair(intersectedBlackHole, intersectionTime);
}

std::pair<std::shared_ptr<Sphere>, double> RayTracingRenderer::findIntersectedStar(Scene scene, Ray ray) {
    std::shared_ptr<Sphere> intersectedStar = nullptr;
    double intersectionTime = -1;

    double t;

    for (std::shared_ptr<Sphere> star : scene.getStars()) {
        t = star->calculateIntersectionTime(ray);

        if (t < 0 || t > this->timeStep)
            continue;

        if (intersectedStar == nullptr || t < intersectionTime) {
            intersectedStar = star;
            intersectionTime = t;
        }
    }

    return std::make_pair(intersectedStar, intersectionTime);
}
