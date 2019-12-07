#include "viewport.hpp"

Viewport::Viewport(int width, int height) : width(width), height(height) {
    LOG_D("Creating viewport");
    this->generateTransformation();
    LOG_D("Viewport transformation\n" << this->transformation);
}

int Viewport::getWidth() {
    return this->width;
}

int Viewport::getHeight() {
    return this->height;
}

void Viewport::generateTransformation() {
    this->transformation << this->width/2.0, 0, 0, (this->width - 1)/2.0,
                            0, this->height/2.0, 0, (this->height - 1)/2.0,
                            0, 0, 1, 0,
                            0, 0, 0, 1;
}

Eigen::Matrix4d Viewport::getTransformation() {
    return this->transformation;
}