#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    string workSpaceFolder = "D:/PersonalCode/Cpp/LearningOpenCV/";
    string path = workSpaceFolder + "Resources/cards.jpg";
    Mat img = imread(path);

    float w = 250, h = 350;
    Mat matrix, imgWarp;

    Point2f src[4] = {{529, 142}, {771, 190}, {405, 395}, {674, 457}};
    Point2f dst[4] = {{0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h}};

    matrix = getPerspectiveTransform(src, dst);
    warpPerspective(img, imgWarp, matrix, Point(w, h));

    for (auto p : src)
    {
        circle(img, p, 10, Scalar(0, 0, 0xff), FILLED);
    }

    imshow("Source", img);
    imshow("img Warp", imgWarp);

    waitKey(0);
    return 0;
}