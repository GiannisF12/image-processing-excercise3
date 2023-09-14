#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() 
{
    Mat image, image_gray;//image input
    image = imread("C:/Users/user/Desktop/UTH/epeksergasia_eikonas/project/darker.jpg");
    if(!image.data)
    {
        printf("No image data");
    }
    cvtColor(image, image_gray, COLOR_BGR2GRAY); //convert to grayscale


    CascadeClassifier faceCascade; //loading front face data
    faceCascade.load("C:/opencv/build/etc/haarcascades/haarcascade_frontalface_default.xml");
    if(faceCascade.empty())
    {
        printf("XML file not loaded");
    }
    CascadeClassifier profCascade; //loading profile face data
    profCascade.load("C:/opencv/build/etc/haarcascades/haarcascade_profileface.xml");
    if(profCascade.empty())
    {
        printf("XML file not loaded");
    }

    vector<Rect> faces;
    faceCascade.detectMultiScale(image_gray, faces, 1.3, 5);  //detecting faces

    //FRONT FACE DETECTION
    for (int i = 0; i< faces.size(); i++)
    {
        rectangle (image, faces[i].tl(), faces[i].br(), Scalar(0, 0, 255), 3);   //creates square on detected faces
        putText(image, "Faces Detected", Point(40, 40), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 0, 0), 2);   //top left corner text
        putText(image, to_string(faces.size()), Point(10,40),FONT_HERSHEY_DUPLEX, 1, Scalar(255, 0, 0), 2);   //number of faces on top left corner

        //PROFILE FACE DETECTION
        if(faces.size()<0)
        {
            vector<Rect> prof;
            profCascade.detectMultiScale(image_gray, prof, 1.3, 5); //detecting profile faces
            for (int i = 0; i< prof.size(); i++)
            {
                rectangle (image, prof[i].tl(), prof[i].br(), Scalar(0, 0, 255), 3);   //creates square on detected faces
                putText(image, "Faces Detected", Point(40, 40), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 0, 0), 2);   //top left corner text
                putText(image, to_string(prof.size()), Point(10,40),FONT_HERSHEY_DUPLEX, 1, Scalar(255, 0, 0), 2);   //number of faces on top left corner
            }
        }
                
    }
    imshow("Face detection", image);
    waitKey(0);

    return 0;
}
