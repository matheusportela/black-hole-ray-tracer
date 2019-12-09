#ifndef SCENE_HPP
#define SCENE_HPP

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "color.hpp"
#include "color_factory.hpp"
#include "disk.hpp"
#include "log.hpp"
#include "sphere.hpp"
#include "surface.hpp"
#include "triangle.hpp"

class Scene {
  public:
    Scene(std::string name);

    std::string getName();
    std::vector<std::shared_ptr<Surface>> getSurfaces();
    std::vector<std::shared_ptr<Sphere>> getStars();
    std::vector<std::shared_ptr<Sphere>> getBlackHoles();
    std::vector<std::shared_ptr<Disk>> getAccretionDisks();

    void addStar(double radius, Eigen::Vector4d positionPoint);
    void addBlackHole(double radius, Eigen::Vector4d positionPoint);
    void addAccretionDisk(double innerRadius, double outerRadius, Eigen::Vector4d positionPoint, Eigen::Vector4d normal);

    void addSphere(double radius, Eigen::Vector4d positionPoint);
    void addSphere(double radius, Eigen::Vector4d positionPoint, std::shared_ptr<Color> color);
    void addTriangle(Eigen::Vector4d p1, Eigen::Vector4d p2, Eigen::Vector4d p3, std::shared_ptr<Color> color);
    void addMesh(Eigen::MatrixXd vertices, Eigen::MatrixXd faces, Eigen::Vector4d positionPoint, std::shared_ptr<Color> color);
    void addSurface(std::shared_ptr<Surface> surface);

  private:
    std::string name;

    std::vector<std::shared_ptr<Surface>> surfaces;

    std::vector<std::shared_ptr<Sphere>> stars;
    std::vector<std::shared_ptr<Sphere>> black_holes;
    std::vector<std::shared_ptr<Disk>> accretion_disks;
};

#endif // SCENE_HPP
