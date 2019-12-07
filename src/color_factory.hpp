#ifndef COLOR_FACTORY_HPP
#define COLOR_FACTORY_HPP

#include <memory>

#include "color.hpp"

class ColorFactory {
  public:
    static std::shared_ptr<Color> generateColor(double red, double green, double blue);
    static std::shared_ptr<Color> generateWhite();
    static std::shared_ptr<Color> generateBlack();
    static std::shared_ptr<Color> generateGray();
    static std::shared_ptr<Color> generateRed();
    static std::shared_ptr<Color> generateGreen();
    static std::shared_ptr<Color> generateBlue();
    static std::shared_ptr<Color> generateYellow();
    static std::shared_ptr<Color> generateMagenta();
    static std::shared_ptr<Color> generateCyan();
};

#endif // COLOR_FACTORY_HPP
