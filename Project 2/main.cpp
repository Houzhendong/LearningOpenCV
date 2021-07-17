#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgOriginal, imgGray, imgCanny, imgThre, imgDil, imgErode, imgBlur;
float w = 420, h = 596;

Mat PreProcessing(Mat img)
{
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
    Canny(imgBlur, imgCanny, 25, 75);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny, imgDil, kernel);

    return imgDil;
    // erode(imgDil,imgErode, kernel);
}

vector<Point> GetContours(Mat imgDila)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(imgDila, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());
    vector<Point> biggest;
    double maxArea = 0;

    for (int i = 0; i < contours.size(); i++)
    {
        auto area = contourArea(contours[i]);
        if (area > 1000)
        {
            auto peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
            // rectangle(dst, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 0xff, 0), 5);

            if (area > maxArea && conPoly[i].size() == 4)
            {
                //drawContours(imgOriginal, conPoly, i, Scalar(0xff, 0, 0xff), 2);
                biggest = {conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3]};
                maxArea = area;
            }
        }
    }

    return biggest;
}

void drawPoints(vector<Point> points, Scalar color)
{
    for (int i = 0; i < points.size(); i++)
    {
        circle(imgOriginal, points[i], 30, color, FILLED);
        putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 5, color, 5);
    }
}

vector<Point> Reorder(vector<Point> p)
{
    vector<Point> result;
    vector<int> sumPoints, subPoints;

    for (auto t : p)
    {
        sumPoints.push_back(t.x + t.y);
        subPoints.push_back(t.x - t.y);
    }

    result.push_back(p[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);
    result.push_back(p[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
    result.push_back(p[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
    result.push_back(p[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);

    return result;
}

Mat getWarp(Mat imgOriginal, vector<Point> points, float w, float h)
{
    Mat matrix, imgWarp;

    Point2f src[4] = {points[0], points[1], points[2], points[3]};
    Point2f dst[4] = {{0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h}};

    matrix = getPerspectiveTransform(src, dst);
    warpPerspective(imgOriginal, imgWarp, matrix, Point(w, h));

    return imgWarp;
}

int main()
{
    string resource = "D:/Code/Cpp/LearningOpenCV/Resources/";
    string path = resource + "paper.jpg";
    imgOriginal = imread(path);
    //resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);

    //Preprocessing
    imgThre = PreProcessing(imgOriginal);
    // Get contours
    auto p = GetContours(imgDil);
    auto docPoint = Reorder(p);
    //Warp
    auto imgWarp = getWarp(imgOriginal, docPoint, w, h);
    drawPoints(docPoint, Scalar(0, 255, 0));

    imshow("image", imgOriginal);
    imshow("image dil", imgWarp);

    waitKey(0);
    return 0;
}