#ifndef SCENE_HPP
#define SCENE_HPP

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "color.hpp"
#include "color_factory.hpp"
#include "log.hpp"
#include "sphere.hpp"
#include "surface.hpp"
#include "triangle.hpp"

class Scene {
  public:
    Scene(std::string name);

    std::string getName();
    std::vector<std::shared_ptr<Surface>> getSurfaces();

    void addSphere(double radius, Eigen::Vector4d positionPoint);
    void addSphere(double radius, Eigen::Vector4d positionPoint, std::shared_ptr<Color> color);
    void addTriangle(Eigen::Vector4d p1, Eigen::Vector4d p2, Eigen::Vector4d p3, std::shared_ptr<Color> color);
    void addMesh(Eigen::MatrixXd vertices, Eigen::MatrixXd faces, Eigen::Vector4d positionPoint, std::shared_ptr<Color> color);
    void addSurface(std::shared_ptr<Surface> surface);

  private:
    std::string name;

    std::vector<std::shared_ptr<Surface>> surfaces;
};

#endif // SCENE_HPP
