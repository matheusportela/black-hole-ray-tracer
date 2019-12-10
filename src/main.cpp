#define STB_IMAGE_WRITE_IMPLEMENTATION  // Do not include this line twice in your project!

#include <memory>
#include <random>

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

Scene createScene1(); // With accretion disk
Scene createScene2(); // Without accretion disk

std::shared_ptr<Renderer> createRenderer1(int width, int height);

void task1();
void task2();
void task3();

int main() {
    // LOG_SET_DEBUG();
    task1();
    // task2();
    // task3();
    return 0;
}

Scene createScene1() {
    std::random_device r;
    std::default_random_engine generator {0};

    Scene scene("Scene 1");

    // Creating stars distributed in a sphere
    float radius;
    float x, y, z;
    float rho, theta, psi;
    std::uniform_real_distribution<float> radius_distribution(0.005, 0.12);
    std::uniform_real_distribution<float> rho_distribution(4.0, 9.0);
    std::uniform_real_distribution<float> theta_distribution(-M_PI, M_PI);
    std::uniform_real_distribution<float> psi_distribution(-M_PI/4, M_PI/4);
    for (int i = 0; i < 100; i++) {
        radius = radius_distribution(generator);
        rho = rho_distribution(generator);
        theta = theta_distribution(generator);
        psi = psi_distribution(generator);

        x = rho*sin(psi)*cos(theta);
        y = rho*sin(psi)*sin(theta);
        z = rho*cos(psi);

        scene.addStar(radius, Eigen::Vector4d(x, y, z, 1));
    }

    scene.addBlackHole(0.25, Eigen::Vector4d(0, 0, 0, 1));
    scene.addAccretionDisk(1.25, 0.75, Eigen::Vector4d(0, 0, 0, 1), Eigen::Vector4d(0, -5, 1, 0).normalized());
    return scene;
}

Scene createScene2() {
    std::random_device r;
    std::default_random_engine generator {0};

    Scene scene("Scene 1");

    // Creating stars distributed in a sphere
    float radius;
    float x, y, z;
    float rho, theta, psi;
    std::uniform_real_distribution<float> radius_distribution(0.005, 0.12);
    std::uniform_real_distribution<float> rho_distribution(4.0, 9.0);
    std::uniform_real_distribution<float> theta_distribution(-M_PI, M_PI);
    std::uniform_real_distribution<float> psi_distribution(-M_PI/4, M_PI/4);
    for (int i = 0; i < 100; i++) {
        radius = radius_distribution(generator);
        rho = rho_distribution(generator);
        theta = theta_distribution(generator);
        psi = psi_distribution(generator);

        x = rho*sin(psi)*cos(theta);
        y = rho*sin(psi)*sin(theta);
        z = rho*cos(psi);

        scene.addStar(radius, Eigen::Vector4d(x, y, z, 1));
    }

    scene.addBlackHole(0.25, Eigen::Vector4d(0, 0, 0, 1));
    // scene.addAccretionDisk(1.25, 0.75, Eigen::Vector4d(0, 0, 0, 1), Eigen::Vector4d(0, -5, 1, 0).normalized());

    return scene;
}

std::shared_ptr<Renderer> createRenderer1(int width, int height) {
    std::shared_ptr<Viewport> viewport = std::make_shared<Viewport>(width, height);

    std::shared_ptr<Projection> projection = std::make_shared<OrthographicProjection>(-1, 1, -1, 1, -1, 1);

    Eigen::Vector4d cameraPositionPoint(0, 0, -2, 1);
    Eigen::Vector4d cameraGazeDirection(0, 0, 1, 0);
    Eigen::Vector4d cameraViewUpDirection(0, -1, 0, 0);
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(cameraPositionPoint, cameraGazeDirection, cameraViewUpDirection);

    camera->setVelocityVector(Eigen::Vector4d(-0.1, 0, 0, 0));

    std::shared_ptr<Renderer> renderer = std::make_shared<RayTracingRenderer>(viewport, projection, camera);

    return renderer;
}

void task1() {
    Scene scene = createScene1();
    LOG_I("Running task 1");
    std::shared_ptr<Renderer> renderer = createRenderer1(300, 300);
    Image image = renderer->render(scene, Renderer::PerspectiveProjection);
    image.save("task1.png");
}

void task2() {
    Scene scene = createScene1();
    LOG_I("Running task 2");
    std::shared_ptr<Renderer> renderer = createRenderer1(300, 300);
    renderer->animate(scene, 10, 0.25, "task2", Renderer::PerspectiveProjection);
}

void task3() {
    Scene scene = createScene2();
    LOG_I("Running task 3");
    std::shared_ptr<Renderer> renderer = createRenderer1(300, 300);
    renderer->animate(scene, 10, 0.25, "task3", Renderer::PerspectiveProjection);
}