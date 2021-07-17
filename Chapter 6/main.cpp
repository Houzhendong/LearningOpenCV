#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//Color Detection
int main()
{
    string resource = "D:/PersonalCode/Cpp/LearningOpenCV/Resources/";
    string path = resource + "shapes.png";
    VideoCapture cap(0);
    Mat img = imread(path);
    Mat imgHSV, mask;

    int hmin = 0, smin = 0, vmin = 0,
        hmax = 179, smax = 255, vmax = 255;

    namedWindow("Trackbars", (640, 200));
    createTrackbar("Hum Min", "Trackbars", &hmin, 179);
    createTrackbar("Hun Max", "Trackbars", &hmax, 179);
    createTrackbar("Sat Min", "Trackbars", &smin, 255);
    createTrackbar("Sat Max", "Trackbars", &smax, 255);
    createTrackbar("Val Min", "Trackbars", &vmin, 255);
    createTrackbar("Val Max", "Trackbars", &vmax, 255);

    while (true)
    {
        cap.read(img);
        cvtColor(img, imgHSV, COLOR_BGR2HSV);
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(imgHSV, lower, upper, mask);

        imshow("Source", img);
        // imshow("HSV Image", imgHSV);
        imshow("mask Image", mask);

        cout << hmin << " " << hmax << " "
             << smin << " " << smax << " "
             << vmin << " " << vmax << endl;

        waitKey(10);
    }
    return 0;
}