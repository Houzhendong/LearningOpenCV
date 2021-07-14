#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// read image from file
void File()
{
    string path = "Resources/test.png";
    Mat img = imread(path);
    imshow("image", img);
    waitKey(0);
}

// read video form file
void Video()
{
    string path = "Resources/test_video.mp4";
    VideoCapture cap(path);
    Mat img;

    while (true)
    {
        cap.read(img);
        imshow("image", img);
        waitKey(20);
    }
}

// Webcam
void Webcam()
{
    VideoCapture cap(0);
    Mat img;

    while (true)
    {
        cap.read(img);
        imshow("image", img);
        waitKey(20);
    }
}

int main()
{
    Webcam();
    return 0;
}