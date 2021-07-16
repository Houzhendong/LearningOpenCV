#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void BasicFunction()
{
    string path = "Resources/Lenna.jpg";
    Mat img = imread(path);
    Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(img, imgBlur, Size(7, 7), 5, 0);
    Canny(img, imgCanny, 50, 150);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny, imgDil, kernel);
    erode(imgDil, imgErode, kernel);

    imshow("image", img);
    imshow("imageGray", imgGray);
    imshow("imageBlur", imgBlur);
    imshow("imageCanny", imgCanny);
    imshow("image Dilation", imgDil);
    imshow("image Erode", imgErode);
    waitKey(0);
}

//Basic Function
int main()
{
    BasicFunction();
    return 0;
}