#include "camera.hpp"

Camera::Camera(Eigen::Vector4d positionPoint, Eigen::Vector4d gazeDirection, Eigen::Vector4d viewUpDirection) {
    LOG_D("Creating camera");

    this->positionPoint = positionPoint;
    this->gazeDirection = gazeDirection;
    this->viewUpDirection = viewUpDirection;

    this->generateTransformation();

    LOG_D("Camera transformation\n" << this->transformation);
}

void Camera::generateTransformation() {
    Eigen::Vector3d u, v, w, e;

    // Calculate vector basis
    w = -this->gazeDirection.head<3>().normalized();
    u = this->viewUpDirection.head<3>().cross(w).normalized();
    v = w.cross(u).normalized();

    e = this->positionPoint.head<3>();

    LOG_D("Camera basis");
    LOG_D("u\n" << u);
    LOG_D("v\n" << v);
    LOG_D("w\n" << w);
    LOG_D("e\n" << e);

    // Calculate transformation matrix
    this->transformation << u.x(), v.x(), w.x(), e.x(),
                            u.y(), v.y(), w.y(), e.y(),
                            u.z(), v.z(), w.z(), e.z(),
                                0,     0,     0,     1;

    // Transform basis vectors into homogeneous coordinates
    this->u << u, 0;
    this->v << v, 0;
    this->w << w, 0;
}

Eigen::Matrix4d Camera::getTransformation() {
    return this->transformation;
}

Eigen::Vector4d Camera::getUDirection() {
    return this->u;
}

Eigen::Vector4d Camera::getVDirection() {
    return this->v;
}

Eigen::Vector4d Camera::getWDirection() {
    return this->w;
}

Eigen::Vector4d Camera::getPositionPoint() {
    return this->positionPoint;
}

void Camera::setPositionPoint(Eigen::Vector4d positionPoint) {
    this->positionPoint = positionPoint;
    this->generateTransformation();
}

Eigen::Vector4d Camera::getVelocityVector() {
    return this->velocityVector;
}

void Camera::setVelocityVector(Eigen::Vector4d velocityVector) {
    this->velocityVector = velocityVector;
}

Eigen::Vector4d Camera::getGazeDirection() {
    return this->gazeDirection;
}

Eigen::Vector4d Camera::getViewUpDirection() {
    return this->viewUpDirection;
}