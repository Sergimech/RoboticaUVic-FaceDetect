//Face Detector C++ code

// ********** Implem. Sergi Baiges about Juampe code********** - MASTER on ROBOTICS (Eurecat-UVic)
//Execute cmake CMakeLists in file directory after make files, and then execute ./(example)


//Libraries //

#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/core/core.hpp>

#include <iostream>
#include <stdio.h>

/** Global variables */
std::string haar_face_cascade_filename = "haarcascade_frontalface_default.xml";
std::string lbp_face_cascade_filename = "lbpcascade_frontalface.xml";
cv::CascadeClassifier face_detect;

void drawImageOnSomething(cv::Mat image, cv::Mat something, cv::Rect rect, int x_offset, int y_offset)
{
    int x, y;
    for (y=0; y<image.cols; y++)
    {
        for (x=0; x<image.rows; x++)
        {
            cv::Vec4b pixel = image.at<cv::Vec4b>(x,y);
            if (pixel[3] > 32)
            {
                something.at<cv::Vec3b>(x+rect.y+x_offset,y+rect.x+y_offset)[0] = image.at<cv::Vec4b>(x,y)[0];
                something.at<cv::Vec3b>(x+rect.y+x_offset,y+rect.x+y_offset)[1] = image.at<cv::Vec4b>(x,y)[1];
                something.at<cv::Vec3b>(x+rect.y+x_offset,y+rect.x+y_offset)[2] = image.at<cv::Vec4b>(x,y)[2];
            }
        }
    }
}


int main(int argc, char *argv[])
{
    int i,x,y;
    bool draw_rectangle = false;
    bool draw_hat_moustache = true;
    bool use_lbp = true;

    // OpenCV video capture object
    cv::VideoCapture capture;



    // OpenCV image objects
    cv::Mat frame, gray, safeImg, moustacheROI;

    cv::Mat moustache = cv::imread("../img/moustache.png", cv::IMREAD_UNCHANGED);
    cv::Mat resized_moustache;
    cv::Mat hat = cv::imread("../img/hat.png", cv::IMREAD_UNCHANGED);
    cv::Mat resized_hat;

    std::vector<cv::Rect> rects;
    cv::Rect roi;

    // Camera ID associated to device number in /dev/videoX in case
    // we use a webcam
    int cam_id = 0;

    // Open the video stream and make sure it's open
    if( !capture.open("../img/video.mpeg") )
    {
        std::cout << "Error opening the capture. May be invalid device id. EXIT program." << std::endl;
        return -1;
    }

    // Train the face classifier
    if (use_lbp)
    {
        face_detect = cv::CascadeClassifier(lbp_face_cascade_filename);
    }
    else
    {
        face_detect = cv::CascadeClassifier(haar_face_cascade_filename);
    }


    // Capture loop until user presses a key
    while(true)
    {
        // Read image and check it
        if(!capture.read(frame))
        {
            std::cout << "No frame" << std::endl;
            cv::waitKey();
        }

        // Convert to grayscale
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Detect faces and generate the rectangles associated
        face_detect.detectMultiScale(gray, rects, 1.3, 4, cv::CASCADE_SCALE_IMAGE, cv::Size(50, 50), cv::Size(200,200));

        // Safe copy
        safeImg = frame.clone();

        // Draw the rectangles
        for (i=0; i<rects.size(); i++)
        {
            if (draw_rectangle)
            {
                cv::rectangle(safeImg, rects[i], cv::Scalar(0,255,0), 2);
            }

            if (draw_hat_moustache)
            {
                cv::resize(moustache, resized_moustache, rects[i].size(), 0, 0, cv::INTER_LINEAR);
                cv::resize(hat, resized_hat, rects[i].size(), 0, 0, cv::INTER_LINEAR);

                drawImageOnSomething(resized_moustache, safeImg, rects[i], rects[i].height/10, 0);
                drawImageOnSomething(resized_hat, safeImg, rects[i], -rects[i].height, 0);
            }
        }

        // Show image in a window
        cv::imshow("Output Window", safeImg);

        // Waits 1 millisecond to check if a key has been pressed. If so, breaks the loop. Otherwise continues.
        if(cv::waitKey(1) >= 0) break;
    }
}
