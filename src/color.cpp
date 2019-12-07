#include "color.hpp"

Color::Color(double red, double green, double blue) {
    this->color = Eigen::Vector3d(red, green, blue);
}

Eigen::Vector3d Color::getVector() {
    return this->color;
}

void Color::setRed(double red) {
    this->color[0] = red;
}

double Color::getRed() {
    return this->color[0];
}

void Color::setGreen(double green) {
    this->color[1] = green;
}

double Color::getGreen() {
    return this->color[1];
}

void Color::setBlue(double blue) {
    this->color[2] = blue;
}

double Color::getBlue() {
    return this->color[2];
}