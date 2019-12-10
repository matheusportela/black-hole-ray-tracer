#include "disk.hpp"

Disk::Disk(double outerRadius, double innerRadius, Eigen::Vector4d centerPoint, Eigen::Vector4d normal) :
outerRadius(outerRadius), innerRadius(innerRadius), centerPoint(centerPoint), normal(normal) {
    if (outerRadius < innerRadius) {
        LOG_E("Disk outer radius cannot be smaller than inner radius");
        exit(1);
    }

    this->texture.load("../textures/adisk.jpg");
}

std::string Disk::getType() {
    return "disk";
}

double Disk::calculateIntersectionTime(Ray ray) {
    // Reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection

    // Intersecting plane
    Eigen::Vector4d n = this->normal;
    Eigen::Vector4d l = ray.getDirection();
    Eigen::Vector4d l0 = ray.getPosition();
    Eigen::Vector4d p0 = this->centerPoint;

    double denom = n.dot(l);

    if (denom <= 1e-6) {
        // LOG_D("Small denom");
        return -1;
    }

    double t = (p0 - l0).dot(n)/denom;
    if (t < 0) {
        // LOG_D("Not intersecting plane");
        return -1;
    }

    // Intersecting disk
    Eigen::Vector4d p = l0 + l*t;
    Eigen::Vector4d v = p - p0;
    double d = sqrt(v.dot(v));

    if (d < this->innerRadius || d > this->outerRadius) {
        // LOG_D("Out of radius - d = " << d);
        return -1;
    }

    return t;
}

Eigen::Vector4d Disk::calculateIntersectionNormal(Eigen::Vector4d intersectionPoint) {
    return this->normal;
}

Eigen::Vector2d Disk::calculateUVMapping(Eigen::Vector4d intersectionPoint) {
    // Reference: https://en.wikipedia.org/wiki/UV_mapping#Finding_UV_on_a_sphere
    Eigen::Vector4d surfacePoint = intersectionPoint - this->centerPoint;
    Eigen::Vector4d d = surfacePoint.normalized();

    // Projecting d to the x-y plane
    d[2] = 0;
    d = d.normalized();

    double u = (0.5 - acos(d.y())/(2*M_PI));
    double v = (surfacePoint.norm() - this->innerRadius)/(this->outerRadius - this->innerRadius);
    return Eigen::Vector2d(u, v);
}

std::shared_ptr<Color> Disk::getTextureColor(Eigen::Vector4d intersectionPoint) {
    Eigen::Vector2d uv = this->calculateUVMapping(intersectionPoint);
    LOG_D("UV:\n" << uv);
    Eigen::Vector4d color = this->texture.at(uv[0], uv[1]);
    LOG_D("Color:\n" << color);
    return std::make_shared<Color>(color[0], color[1], color[2]);
}
