#include "image.hpp"

Image::Image(int width, int height) {
    this->red_channel = Eigen::MatrixXd::Zero(height, width);
    this->green_channel = Eigen::MatrixXd::Zero(height, width);
    this->blue_channel = Eigen::MatrixXd::Zero(height, width);
    this->alpha_channel = Eigen::MatrixXd::Ones(height, width);
}

void Image::setPixel(int row, int col, std::shared_ptr<Color> color) {
    this->red_channel(row, col) = color->getRed();
    this->green_channel(row, col) = color->getGreen();
    this->blue_channel(row, col) = color->getBlue();
}

void Image::save(std::string filename) {
    LOG_I("Saving image to \"" << filename << "\"");

    this->writeMatrixToRGB(red_channel, green_channel, blue_channel, alpha_channel, filename);
}

void Image::writeMatrixToRGB(const Eigen::MatrixXd& R, const Eigen::MatrixXd& G, const Eigen::MatrixXd& B, const Eigen::MatrixXd& A, const std::string& filename) {
    assert(R.rows() == G.rows() && G.rows() == B.rows() && B.rows() == A.rows());
    assert(R.cols() == G.cols() && G.cols() == B.cols() && B.cols() == A.cols());

    const int w = R.rows();                              // Image width
    const int h = R.cols();                              // Image height
    const int comp = 4;                                  // 3 Channels Red, Green, Blue, Alpha
    const int stride_in_bytes = w*comp;                  // Length of one row in bytes
    std::vector<unsigned char> data(w*h*comp,0);         // The image itself;

    for (unsigned wi = 0; wi<w;++wi)
    {
        for (unsigned hi = 0; hi < h; ++hi)
        {
            data[(hi * w * 4) + (wi * 4) + 0] = this->doubleToUnsignedChar(R(wi,hi));
            data[(hi * w * 4) + (wi * 4) + 1] = this->doubleToUnsignedChar(G(wi,hi));
            data[(hi * w * 4) + (wi * 4) + 2] = this->doubleToUnsignedChar(B(wi,hi));
            data[(hi * w * 4) + (wi * 4) + 3] = this->doubleToUnsignedChar(A(wi,hi));
        }
    }

    stbi_write_png(filename.c_str(), w, h, comp, data.data(), stride_in_bytes);
}

unsigned char Image::doubleToUnsignedChar(const double d) {
    return round(std::max(std::min(1.,d),0.)*255);
}