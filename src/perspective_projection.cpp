#include "perspective_projection.hpp"

PerspectiveProjection::PerspectiveProjection(double left, double right, double bottom, double top, double near, double far) {
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->top = top;
    this->near = near;
    this->far = far;

    LOG_D("Creating projection");
    this->generateTransformation();
    LOG_D("PerspectiveProjection transformation\n" << this->transformation);
}

void PerspectiveProjection::generateTransformation() {
    this->transformation << 2*this->near/(this->right - this->left), 0, -(this->right + this->left)/(this->right - this->left), 0,
                            0, 2*this->near/(this->top - this->bottom), -(this->top + this->bottom)/(this->top - this->bottom), 0,
                            0, 0, (this->far + this->near)/(this->far - this->near), 2*(this->far*this->near)/(this->far - this->near),
                            0, 0, 1, 0;
}
