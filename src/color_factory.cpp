#include "color_factory.hpp"

std::shared_ptr<Color> ColorFactory::generateColor(double red, double green, double blue) {
    std::shared_ptr<Color> color = std::make_shared<Color>(red, green, blue);
    return color;
}

std::shared_ptr<Color> ColorFactory::generateWhite() {
    return generateColor(1, 1, 1);
}

std::shared_ptr<Color> ColorFactory::generateBlack() {
    return generateColor(0, 0, 0);
}

std::shared_ptr<Color> ColorFactory::generateGray() {
    return generateColor(0.5, 0.5, 0.5);
}

std::shared_ptr<Color> ColorFactory::generateRed() {
    return generateColor(1, 0, 0);
}

std::shared_ptr<Color> ColorFactory::generateGreen() {
    return generateColor(0, 1, 0);
}

std::shared_ptr<Color> ColorFactory::generateBlue() {
    return generateColor(0, 0, 1);
}

std::shared_ptr<Color> ColorFactory::generateYellow() {
    return generateColor(1, 1, 0);
}

std::shared_ptr<Color> ColorFactory::generateMagenta() {
    return generateColor(1, 0, 1);
}

std::shared_ptr<Color> ColorFactory::generateCyan() {
    return generateColor(0, 1, 1);
}

