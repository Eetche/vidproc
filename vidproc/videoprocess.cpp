#include "Videoprocess.h"

#pragma warning(disable : 4244)


Videoprocess::Videoprocess() : resizeH(75), resizeW(100)
{
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_WARNING);
}

void Videoprocess::video2bin(std::string video_path, std::string outname)
{
    cv::VideoCapture video(video_path);

    int width = video.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = video.get(cv::CAP_PROP_FRAME_HEIGHT);
    int fps = video.get(cv::CAP_PROP_FPS);

    cv::VideoWriter writer(outname, cv::VideoWriter::fourcc('a', 'v', 'c', '1'), fps, cv::Size(width, height), false);

    cv::Mat frame;

    for (;;)
    {
        video >> frame;

        if (frame.empty())
            break;

        cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);

        cv::threshold(frame, frame, 100, 255, cv::THRESH_BINARY);

        cv::cvtColor(frame, frame, cv::COLOR_GRAY2BGR);

        printf("cardes is processed: %d from %d \n", int(video.get(cv::CAP_PROP_POS_FRAMES)), int(video.get(cv::CAP_PROP_FRAME_COUNT)));

        writer.write(frame);
    }

    video.release();
    writer.release();
    cv::destroyAllWindows();
}

std::vector<cv::Point> Videoprocess::getdarkpixs(const cv::Mat &frame)
{
    cv::Mat outmat;

    cv::cvtColor(frame, outmat, cv::COLOR_BGR2GRAY);

    cv::resize(outmat, outmat, cv::Size(resizeW, resizeH), cv::INTER_AREA);
    
    cv::threshold(outmat, outmat, 120, 255, cv::THRESH_BINARY);

    for (int y = 0; y < outmat.size().height; y++)
    {
        for (int x = 0; x < outmat.size().width; x++)
        {
            uchar pixel = outmat.at<uchar>(y, x);

            if (int(pixel) <= 120)
            {
                darkpixels.push_back(cv::Point(y, x));
            }
        }
    }

    return darkpixels;
}

void Videoprocess::tosymb(std::vector<cv::Point> darkpixels)
{
    
    for (int y = 0; y < resizeH; y++)
    {
        for (int x = 0; x < resizeW; x++)
        {
            
            auto has = std::find(darkpixels.begin(), darkpixels.end(), cv::Point(y, x));
            if (has != darkpixels.end())
            {
                printf("#");
            } else {
                printf(" ");
            }

            if (x == resizeW - 1)
            {
                printf("\n");
            }
        }
        
    }
}