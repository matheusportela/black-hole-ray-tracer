#include "scene.hpp"

Scene::Scene(std::string name) : name(name) {
    LOG_D("Creating scene \"" << this->name << "\"");
}

std::string Scene::getName() {
    return this->name;
}

void Scene::addBlackHole(double radius, Eigen::Vector4d positionPoint) {
    LOG_D("Adding black hole");
    LOG_D("Radius: " << radius);
    LOG_D("Position:\n" << positionPoint);

    std::shared_ptr<Sphere> black_hole = std::make_shared<Sphere>(radius, positionPoint);
    black_hole->setColor(ColorFactory::generateBlack());
    this->black_holes.push_back(black_hole);
}

void Scene::addAccretionDisk(double innerRadius, double outerRadius, Eigen::Vector4d positionPoint, Eigen::Vector4d normal) {
    LOG_D("Adding accretion disk");
    LOG_D("Inner Radius: " << innerRadius);
    LOG_D("Outer Radius: " << outerRadius);
    LOG_D("Position:\n" << positionPoint);
    LOG_D("Normal:\n" << normal);

    auto color = ColorFactory::generateColor(255/256.0, 247/256.0, 103/256.0);

    std::shared_ptr<Disk> top_accretion_disk = std::make_shared<Disk>(innerRadius, outerRadius, positionPoint, normal);
    top_accretion_disk->setColor(color);
    // top_accretion_disk->setColor(ColorFactory::generateRed());
    this->accretion_disks.push_back(top_accretion_disk);

    std::shared_ptr<Disk> bottom_accretion_disk = std::make_shared<Disk>(innerRadius, outerRadius, positionPoint, -normal);
    top_accretion_disk->setColor(color);
    // bottom_accretion_disk->setColor(ColorFactory::generateBlue());
    this->accretion_disks.push_back(bottom_accretion_disk);
}

void Scene::addStar(double radius, Eigen::Vector4d positionPoint) {
    LOG_D("Adding star");
    LOG_D("Radius: " << radius);
    LOG_D("Position:\n" << positionPoint);

    std::shared_ptr<Sphere> star = std::make_shared<Sphere>(radius, positionPoint, "../textures/star.jpg");
    star->setColor(ColorFactory::generateWhite());
    this->stars.push_back(star);
}

void Scene::addUniverse(double radius, Eigen::Vector4d positionPoint) {
    LOG_D("Adding universe");
    LOG_D("Radius: " << radius);
    LOG_D("Position:\n" << positionPoint);

    std::shared_ptr<Sphere> star = std::make_shared<Sphere>(radius, positionPoint, "../textures/universe.jpg");
    star->setColor(ColorFactory::generateWhite());
    this->stars.push_back(star);
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

std::vector<std::shared_ptr<Sphere>> Scene::getStars() {
    return this->stars;
}

std::vector<std::shared_ptr<Sphere>> Scene::getBlackHoles() {
    return this->black_holes;
}

std::vector<std::shared_ptr<Disk>> Scene::getAccretionDisks() {
    return this->accretion_disks;
}
