#ifndef COLOR_HPP
#define COLOR_HPP

#include <Eigen/Core>

class Color {
  public:
    Color(double red = 0, double green = 0, double blue = 0);

    Eigen::Vector3d getVector();

    void setRed(double red);
    double getRed();

    void setGreen(double green);
    double getGreen();

    void setBlue(double blue);
    double getBlue();

  private:
    Eigen::Vector3d color;
};

#endif // COLOR_HPP
