#include "projection.hpp"

Eigen::Matrix4d Projection::getTransformation() {
    return this->transformation;
}

double Projection::getLeft() {
    return this->left;
}

double Projection::getRight() {
    return this->right;
}

double Projection::getBottom() {
    return this->bottom;
}

double Projection::getTop() {
    return this->top;
}

double Projection::getNear() {
    return this->near;
}

double Projection::getFar() {
    return this->far;
}
