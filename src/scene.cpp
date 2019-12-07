#include "scene.hpp"

Scene::Scene(std::string name) : name(name) {
    LOG_D("Creating scene \"" << this->name << "\"");
}

std::string Scene::getName() {
    return this->name;
}

void Scene::addSphere(double radius, Eigen::Vector4d positionPoint) {
    this->addSphere(radius, positionPoint, ColorFactory::generateWhite());
}

void Scene::addSphere(double radius, Eigen::Vector4d positionPoint, std::shared_ptr<Color> color) {
    LOG_D("Adding sphere");
    LOG_D("Radius: " << radius);
    LOG_D("Position:\n" << positionPoint);

    std::shared_ptr<Surface> sphere = std::make_shared<Sphere>(radius, positionPoint);
    sphere->setColor(color);
    this->addSurface(sphere);
}

void Scene::addTriangle(Eigen::Vector4d p1, Eigen::Vector4d p2, Eigen::Vector4d p3, std::shared_ptr<Color> color) {
    std::shared_ptr<Surface> triangle = std::make_shared<Triangle>(p1, p2, p3);
    triangle->setColor(color);
    this->addSurface(triangle);
}

void Scene::addMesh(Eigen::MatrixXd vertices, Eigen::MatrixXd faces, Eigen::Vector4d positionPoint, std::shared_ptr<Color> color) {
    LOG_D("Adding mesh");
    LOG_D("Position:\n" << positionPoint);

    int p1_index, p2_index, p3_index;
    Eigen::Vector4d p1, p2, p3;

    for (int i = 0; i < faces.rows(); i++) {
        p1_index = faces(i, 0);
        p2_index = faces(i, 1);
        p3_index = faces(i, 2);

        p1 << vertices(p1_index, 0), vertices(p1_index, 1), vertices(p1_index, 2), 0;
        p2 << vertices(p2_index, 0), vertices(p2_index, 1), vertices(p2_index, 2), 0;
        p3 << vertices(p3_index, 0), vertices(p3_index, 1), vertices(p3_index, 2), 0;
        this->addTriangle(p1 + positionPoint, p2 + positionPoint, p3 + positionPoint, color);
    }
}

void Scene::addSurface(std::shared_ptr<Surface> surface) {
    this->surfaces.push_back(surface);
}

std::vector<std::shared_ptr<Surface>> Scene::getSurfaces() {
    return this->surfaces;
}
