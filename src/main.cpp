// Do not include this line twice in your project!
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

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
Scene createScene3(); // With accretion disk but without black hole distortion
Scene createScene4(); // Without accretion disk nor black hole distortion
Scene createScene5(); // Without accretion disk but with black hole distortion
Scene createScene6(); // With background texture and no black hole
Scene createScene7(); // With background texture and black hole but no accretion disk
Scene createScene8(); // With background texture, black hole and accretion disk

std::shared_ptr<Renderer> createRenderer1(int width, int height);

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();
void task8();
void task9();
void task10();

int main() {
    // LOG_SET_DEBUG();
    // task1();
    // task2();
    // task3();
    // task4();
    // task5();
    // task6();
    // task7();
    // task8();
    // task9();
    task10();
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
    std::uniform_real_distribution<float> radius_distribution(0.03, 0.1);
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
    scene.addAccretionDisk(1.75, 0.75, Eigen::Vector4d(0, 0, 0, 1), Eigen::Vector4d(4, -30, 1, 0).normalized());
    return scene;
}

Scene createScene2() {
    std::random_device r;
    std::default_random_engine generator {0};

    Scene scene("Scene 2");

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

    return scene;
}

Scene createScene3() {
    std::random_device r;
    std::default_random_engine generator {0};

    Scene scene("Scene 3");

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

    scene.addAccretionDisk(1.75, 0.75, Eigen::Vector4d(0, 0, 0, 1), Eigen::Vector4d(4, -30, 1, 0).normalized());
    return scene;
}

Scene createScene4() {
    std::random_device r;
    std::default_random_engine generator {0};

    Scene scene("Scene 4");

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

    return scene;
}

Scene createScene5() {
    std::random_device r;
    std::default_random_engine generator {0};

    Scene scene("Scene 5");

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

    return scene;
}

Scene createScene6() {
    std::random_device r;
    std::default_random_engine generator {0};

    Scene scene("Scene 6");

    scene.addUniverse(5, Eigen::Vector4d(0, 0, 0, 1));
    return scene;
}

Scene createScene7() {
    std::random_device r;
    std::default_random_engine generator {0};

    Scene scene("Scene 7");

    scene.addUniverse(5, Eigen::Vector4d(0, 0, 0, 1));
    scene.addBlackHole(0.25, Eigen::Vector4d(0, 0, 0, 1));
    return scene;
}

Scene createScene8() {
    std::random_device r;
    std::default_random_engine generator {0};

    Scene scene("Scene 8");

    scene.addUniverse(5, Eigen::Vector4d(0, 0, 0, 1));
    scene.addBlackHole(0.25, Eigen::Vector4d(0, 0, 0, 1));
    scene.addAccretionDisk(1.75, 0.75, Eigen::Vector4d(0, 0, 0, 1), Eigen::Vector4d(4, -30, 1, 0).normalized());
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

void task4() {
    Scene scene = createScene3();
    LOG_I("Running task 4");
    std::shared_ptr<Renderer> renderer = createRenderer1(300, 300);
    Image image = renderer->render(scene, Renderer::PerspectiveProjection);
    image.save("task4.png");
}

void task5() {
    Scene scene = createScene4();
    LOG_I("Running task 5");
    std::shared_ptr<Renderer> renderer = createRenderer1(300, 300);
    Image image = renderer->render(scene, Renderer::PerspectiveProjection);
    image.save("task5.png");
}

void task6() {
    Scene scene = createScene5();
    LOG_I("Running task 6");
    std::shared_ptr<Renderer> renderer = createRenderer1(300, 300);
    Image image = renderer->render(scene, Renderer::PerspectiveProjection);
    image.save("task6.png");
}

void task7() {
    Scene scene = createScene6();
    LOG_I("Running task 7");
    std::shared_ptr<Renderer> renderer = createRenderer1(600, 600);
    renderer->animate(scene, 10, 0.25, "task7", Renderer::PerspectiveProjection);
}

void task8() {
    Scene scene = createScene7();
    LOG_I("Running task 8");
    std::shared_ptr<Renderer> renderer = createRenderer1(600, 600);
    renderer->animate(scene, 10, 0.25, "task8", Renderer::PerspectiveProjection);
}

void task9() {
    Scene scene = createScene8();
    LOG_I("Running task 9");
    std::shared_ptr<Renderer> renderer = createRenderer1(600, 600);
    renderer->animate(scene, 10, 0.25, "task9", Renderer::PerspectiveProjection);
}

void task10() {
    Scene scene = createScene8();
    LOG_I("Running task 10");
    std::shared_ptr<Renderer> renderer = createRenderer1(600, 600);
    Image image = renderer->render(scene, Renderer::PerspectiveProjection);
    image.save("task10.png");
}