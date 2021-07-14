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
    Mat imgGray;

    cvtColor(img, imgGray, COLOR_BGR2GRAY);

    imshow("image", img);
    imshow("imageGray", imgGray);
    waitKey(0);
}

int main()
{
    File();
    return 0;
}