#include "orthographic_projection.hpp"

OrthographicProjection::OrthographicProjection(double left, double right, double bottom, double top, double near, double far) {
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->top = top;
    this->near = near;
    this->far = far;

    LOG_D("Creating projection");
    this->generateTransformation();
    LOG_D("OrthographicProjection transformation\n" << this->transformation);
}

void OrthographicProjection::generateTransformation() {
    this->transformation << 2/(this->right - this->left), 0, 0, -(this->right + this->left)/(this->right - this->left),
                            0, 2/(this->top - this->bottom), 0, -(this->top + this->bottom)/(this->top - this->bottom),
                            0, 0, 2/(this->near - this->far), -(this->near + this->far)/(this->near - this->far),
                            0, 0, 0, 1;
}
