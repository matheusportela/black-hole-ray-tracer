#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <iostream>
#include <string>
#include <vector>

#include <Eigen/Core>

#include "color.hpp"
#include "log.hpp"

#include "stb_image.h"
#include "stb_image_write.h"

class Image {
  public:
    Image() {}
    Image(int width, int height);

    void setPixel(int row, int col, std::shared_ptr<Color> color);

    void save(std::string filename);
    void load(std::string filename);
    Eigen::Vector4d at(int width, int height);
    Eigen::Vector4d at(double u, double v);

  private:
    void writeMatrixToRGB(const Eigen::MatrixXd& R, const Eigen::MatrixXd& G, const Eigen::MatrixXd& B, const Eigen::MatrixXd& A, const std::string& filename);
    unsigned char doubleToUnsignedChar(const double d);
    double unsignedCharToDouble(const unsigned char x);

    Eigen::MatrixXd red_channel;
    Eigen::MatrixXd green_channel;
    Eigen::MatrixXd blue_channel;
    Eigen::MatrixXd alpha_channel;
};

#endif // IMAGE_HPP
