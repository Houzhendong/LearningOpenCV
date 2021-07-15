#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    string path = "Resources/Lenna.jpg";
    Mat img = imread(path);
    Mat imgResize, imgCrop;

    resize(img, imgResize, Size(), 1.5, 1.5);

    Rect roi(100, 100, 200, 150);
    imgCrop = imgResize(roi);

    imshow("image", img);
    imshow("image resize", imgResize);
    imshow("image Crop", imgCrop);

    waitKey(0);
    return 0;
}