#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//Face Detection
int main()
{
    string resource = "D:/Code/Cpp/LearningOpenCV/Resources/";
    string path = resource + "Lenna.jpg";
    Mat img = imread(path);
    Mat imgGray, imgBlur, imgCanny, imgDila;

    CascadeClassifier faceCascade;
    faceCascade.load("Resources/haarcascade_frontalface_default.xml");

    if (faceCascade.empty())
        cout << "XML file not loaded" << endl;

    vector<Rect> faces;
    faceCascade.detectMultiScale(img, faces, 1.1, 10);

    for (auto face : faces)
    {
        rectangle(img, face.tl(), face.br(), Scalar(0, 0xff, 0), 2);
    }

    imshow("Source", img);

    waitKey(0);
    return 0;
}