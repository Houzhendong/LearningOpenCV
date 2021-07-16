#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void GetContours(Mat imgDila, Mat dst)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(imgDila, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());
    string objType;

    for (int i = 0; i < contours.size(); i++)
    {
        auto area = contourArea(contours[i]);
        if (area > 1000)
        {
            auto peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
            drawContours(dst, conPoly, i, Scalar(0xff, 0, 0xff), 2);
            boundRect[i] = boundingRect(conPoly[i]);
            rectangle(dst, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 0xff, 0), 5);
            int objCorner = (int)(conPoly[i].size());

            if (objCorner == 3)
            {
                objType = "Tri";
            }
            else if (objCorner == 4)
            {
                float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
                if (aspRatio > 0.95 && aspRatio < 1.05)
                    objType = "Square";
                else
                    objType = "Rect";
            }
            else if (objCorner > 4)
            {
                objType = "Circle";
            }
            putText(dst, objType, {boundRect[i].x, boundRect[i].y - 5}, FONT_HERSHEY_PLAIN, 0.75, Scalar(0, 0, 0));
        }
    }
}

//Shape Detection
int main()
{
    string resource = "D:/PersonalCode/Cpp/LearningOpenCV/Resources/";
    string path = resource + "shapes.png";
    Mat img = imread(path);
    Mat imgGray, imgBlur, imgCanny, imgDila;

    //Preprocessing image
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 4, 0);
    Canny(imgBlur, imgCanny, 25, 75);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny, imgDila, kernel);

    GetContours(imgDila, img);

    imshow("Source", img);
    // imshow("image Gray", imgGray);
    // imshow("image blur", imgBlur);
    // imshow("image canny", imgCanny);
    // imshow("image dilate", imgDila);

    waitKey(0);
    return 0;
}