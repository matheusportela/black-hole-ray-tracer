#include "surface.hpp"

Surface::Surface() {
    this->setColor(ColorFactory::generateGray());
}

void Surface::setColor(std::shared_ptr<Color> color) {
    this->color = color;
}

std::shared_ptr<Color> Surface::getColor() {
    return this->color;
}