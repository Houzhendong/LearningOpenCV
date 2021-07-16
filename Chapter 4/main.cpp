#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//Draw shapes and Text
int main()
{
    Mat img(512, 512, CV_8UC3, Scalar(0xda, 0xf5, 0xff));

    circle(img, Point(256, 256), 155, Scalar(0, 65, 255), FILLED);
    rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), 3);
    line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);

    putText(img, "Hello World", Point(137, 262), FONT_HERSHEY_DUPLEX, 2, Scalar(0xff));

    imshow("Image", img);

    waitKey(0);
    return 0;
}