#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <algorithm>

#pragma once

#define RESIZE_W 100
#define RESIZE_H 75

struct Pixel {
    int x;
    int y;
    uint8_t brightness;
    Pixel(int x, int y, uint8_t brightness) : x(x), y(y), brightness(brightness) {}; 
};

class Videoprocess
{
public:
    static void video2bin(std::string, std::string);
    static std::vector<Pixel> getwhitepixs(const cv::Mat&);
    static void tosymb(const cv::Mat&);
    static void videotosymb(cv::VideoCapture);

    Videoprocess();
};