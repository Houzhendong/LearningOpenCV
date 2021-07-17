#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//vector<int> : {hmin,hmax,smin,smax,vmin,vmax}
vector<vector<int>> colors{{73, 94, 19, 106, 66, 110}};
vector<Scalar> brushColors{{255, 0, 255}};
vector<vector<int>> points;
VideoCapture cap(0);
Mat img;

Point GetContours(Mat imgDila)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(imgDila, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());
    Point mypoint(0, 0);

    for (int i = 0; i < contours.size(); i++)
    {
        auto area = contourArea(contours[i]);
        if (area > 1000)
        {
            auto peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

            boundRect[i] = boundingRect(conPoly[i]);
            mypoint.x = (boundRect[i].x + boundRect[i].width) / 2;
            mypoint.y = boundRect[i].y;
            drawContours(img, conPoly, i, Scalar(0xff, 0, 0xff), 2);
        }
    }

    return mypoint;
}

void FindColor(Mat img)
{
    Mat imgHSV;
    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    int i = 0;
    for (auto color : colors)
    {
        Scalar lower(color[0], color[2], color[4]);
        Scalar upper(color[1], color[3], color[5]);
        Mat mask;
        inRange(imgHSV, lower, upper, mask);

        Point point = GetContours(mask);
        if (point.x != 0 && point.y != 0)
            points.push_back({point.x, point.y, i});
        i++;
    }
}

void DrawOnCanvas(vector<vector<int>> newPoints, vector<Scalar> brushColors)
{
    for (int i = 0; i < newPoints.size(); i++)
    {
        circle(img, Point(points[i][0], points[i][1]), 10, brushColors[newPoints[i][2]], FILLED);
    }
}

int main()
{

    int key = 0;

    while (key != 'q')
    {
        cap.read(img);

        //find color
        FindColor(img);
        DrawOnCanvas(points, brushColors);
        imshow("image", img);
        key = waitKey(20);
    }

    return 0;
}