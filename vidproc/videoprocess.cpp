#include "videoprocess.h"

#pragma warning(disable : 4244)

Videoprocess::Videoprocess()
{
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_WARNING);
}

void Videoprocess::video2bin(std::string video_path, std::string outname)
{
    cv::VideoCapture video(video_path);

    int width = video.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = video.get(cv::CAP_PROP_FRAME_HEIGHT);
    int fps = video.get(cv::CAP_PROP_FPS);

    cv::VideoWriter writer("videos/" + outname, cv::VideoWriter::fourcc('a', 'v', 'c', '1'), fps, cv::Size(width, height), false);

    cv::Mat frame;

    for (;;)
    {
        video >> frame;

        if (frame.empty())
            break;

        cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);

        cv::threshold(frame, frame, 127, 255, cv::THRESH_BINARY);

        cv::cvtColor(frame, frame, cv::COLOR_GRAY2BGR);

        printf("cadres is processed: %d from %d \n", int(video.get(cv::CAP_PROP_POS_FRAMES)), int(video.get(cv::CAP_PROP_FRAME_COUNT)));

        writer.write(frame);
    }

    video.release();
    writer.release();
    cv::destroyAllWindows();
}

std::vector<Pixel> Videoprocess::getwhitepixs(const cv::Mat &frame)
{
    cv::Mat outmat;

    cv::cvtColor(frame, outmat, cv::COLOR_BGR2GRAY);

    cv::resize(outmat, outmat, cv::Size(RESIZE_W, RESIZE_H), cv::INTER_AREA);

    std::vector<Pixel> whitepixels;

    for (int y = 0; y < outmat.size().height; y++)
    {
        for (int x = 0; x < outmat.size().width; x++)
        {
            uchar pixel = outmat.at<uchar>(y, x);

            if (int(pixel) >= 40)
            {
                whitepixels.emplace_back(x, y, pixel);
            }
        }
    }

    return whitepixels;
}

void Videoprocess::tosymb(const cv::Mat &frame)
{

    std::vector<Pixel> whitepixels = getwhitepixs(frame);

    for (int y = 0; y < RESIZE_H; y++)
    {
        for (int x = 0; x < RESIZE_W; x++)
        {

            auto it = std::find_if(whitepixels.begin(), whitepixels.end(),
                                   [x, y](const Pixel &p)
                                   { return p.x == x && p.y == y; });

            if (it != whitepixels.end())
            {
                int brightness = it->brightness; 

                char symbol;

                if (brightness < 100)
                {
                     symbol = '.';
                }  else if (brightness < 150)
                {
                    symbol = '*';
                } else if (brightness < 200)
                {
                    symbol = '+';
                } else if (brightness < 255)
                {
                    symbol = '#';
                } else {
                    symbol = ' ';
                }

                putchar(symbol);

            } else {
                putchar(' ');
            }
        }
        printf("\n");
    }
}

void Videoprocess::videotosymb(cv::VideoCapture video)
{

    std::string canvas;

    int width = video.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = video.get(cv::CAP_PROP_FRAME_HEIGHT);
    int fps = video.get(cv::CAP_PROP_FPS);

    if (!video.isOpened())
    {
        std::cerr << "video.isOpened() error";
    }

    cv::Mat frame;

    for (;;)
    {
        video >> frame;

        if (frame.empty())
        {
            break;
        }


        tosymb(frame);

        system("cls");
    }
}