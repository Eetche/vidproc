#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <algorithm>

#pragma once


class Videoprocess
{
private:
    int resizeW;
    int resizeH;
public:
    void video2bin(std::string, std::string);
    std::vector<cv::Point3i> getwhitepixs(const cv::Mat&);
    void tosymb(std::vector<cv::Point3i>);

    Videoprocess();
};