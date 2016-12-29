//Face Detector C++ code

// ********** Impl. by Sergi Baiges ********** - MASTER on ROBOTICS (Eurecat-UVic)
//Execute cmake CMakeLists in file directory after make files, and then execute ./(example)


//Libraries //

#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/core/core.hpp>

#include <iostream>
#include <stdio.h>

//Variables //

using namespace std;
using namespace cv;

// Function Headers //

void detectAndDisplay( Mat screenFrame );

// Global variables - Load XML classifier //

String face_cascade_name = "haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "### Face detector ### - Press -C- to quit";


// Main function //

int main(int argc, char *argv[] )
{
    VideoCapture capture;
    Mat screenFrame;

    //-- 1. Load the cascades filters
    
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };

    if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eyes cascade\n"); return -1; };


    //-- 2. Read the video stream

    capture.open( -1 );

    if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }

    while ( capture.read(screenFrame) )
    {
        if( screenFrame.empty() )
        {
            printf(" --(!) No captured screenFrame -- Break!");
            break;
        }

        detectAndDisplay( screenFrame );

        int c = waitKey(10);
        if( (char)c == 'c' ) break;
    }
    return 0;
    
}

//-- 3. Apply the classifier to the screenFrame.

//We create a Mat to save the image in gray and 
//a vector called faces that stores all the pixels

void detectAndDisplay( Mat screenFrame )
{
    std::vector<Rect> faces;
    Mat screenFrame_gray;

    cvtColor( screenFrame, screenFrame_gray, COLOR_BGR2GRAY );
    equalizeHist( screenFrame_gray, screenFrame_gray );  //We improved the image

    //-- Detect faces

    face_cascade.detectMultiScale( screenFrame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

    // We create a loop that allows us to draw an ellipse around a point

    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( screenFrame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 0, 0, 255 ), 4, 8, 0 );

        Mat faceROI = screenFrame_gray( faces[i] );
        std::vector<Rect> eyes;

        //-- In each face, detect eyes (perform detection) and draw a circles around eyes

        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );

        for ( size_t j = 0; j < eyes.size(); j++ )
        {
            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( screenFrame, eye_center, radius, Scalar( 0, 255, 0 ), 4, 8, 0 );
        }
    }
    
    //-- Show what you got
    imshow( window_name, screenFrame );
}