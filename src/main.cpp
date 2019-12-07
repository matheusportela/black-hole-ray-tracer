#define STB_IMAGE_WRITE_IMPLEMENTATION  // Do not include this line twice in your project!

#include <memory>

#include <Eigen/Core>

#include "camera.hpp"
#include "color_factory.hpp"
#include "image.hpp"
#include "log.hpp"
#include "orthographic_projection.hpp"
#include "ray_tracing_renderer.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "sphere.hpp"

Scene createScene1();

std::shared_ptr<Renderer> createRenderer1(int width, int height);

void task1();

int main() {
    // LOG_SET_DEBUG();
    task1();
    return 0;
}

Scene createScene1() {
    Scene scene("Scene 1");

    scene.addSphere(0.25, Eigen::Vector4d(-0.65, -0.7, 1, 1));
    scene.addSphere(0.1, Eigen::Vector4d(-0.8, -0.1, 0, 1));
    scene.addSphere(0.15, Eigen::Vector4d(-0.7, 0.65, 0, 1));
    scene.addSphere(0.4, Eigen::Vector4d(0.65, -0.75, 5, 1));
    scene.addSphere(0.5, Eigen::Vector4d(0, 0, 5, 1));
    scene.addSphere(0.2, Eigen::Vector4d(0.75, 0.75, 4, 1));

    return scene;
}

std::shared_ptr<Renderer> createRenderer1(int width, int height) {
    std::shared_ptr<Viewport> viewport = std::make_shared<Viewport>(width, height);

    std::shared_ptr<Projection> projection = std::make_shared<OrthographicProjection>(-1, 1, -1, 1, -1, 1);

    Eigen::Vector4d cameraPositionPoint(0, 0, 0, 1);
    Eigen::Vector4d cameraGazeDirection(0, 0, 1, 0);
    Eigen::Vector4d cameraViewUpDirection(0, -1, 0, 0);
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(cameraPositionPoint, cameraGazeDirection, cameraViewUpDirection);

    std::shared_ptr<Renderer> renderer = std::make_shared<RayTracingRenderer>(viewport, projection, camera);

    return renderer;
}

void task1() {
    Scene scene = createScene1();
    LOG_I("Running task 1");
    std::shared_ptr<Renderer> renderer = createRenderer1(500, 500);
    Image image = renderer->render(scene, Renderer::OrthographicProjection);
    image.save("task1.png");
}
