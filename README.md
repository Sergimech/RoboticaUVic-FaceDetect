***** DOCUMENTATION ********
***** http://docs.opencv.org/ *****

Abstract:

This code allows us to evaluate a dynamic image provided with a webcam and find the faces of people using a classifier trained to detect faces and eyes. Use the classifier that is detailed below, to expand the information should be consulted in the page named above (OpenCV).

Cascade Classification¶

Haar Feature-based Cascade Classifier for Object Detection¶

CascadeClassifier::detectMultiScale¶

Detects objects of different sizes in the input image. The detected objects are returned as a list of rectangles.

C++: void CascadeClassifier::detectMultiScale(const Mat& image, vector<Rect>& objects, double scaleFactor=1.1, int minNeighbors=3, int flags=0, Size minSize=Size(), Size maxSize=Size())

Where Parameters are:	

cascade – Haar classifier cascade (OpenCV 1.x API only). It can be loaded from XML or YAML file using Load(). When the cascade is not needed anymore, release it using cvReleaseHaarClassifierCascade(&cascade).
image – Matrix of the type CV_8U containing an image where objects are detected.
objects – Vector of rectangles where each rectangle contains the detected object.
scaleFactor – Parameter specifying how much the image size is reduced at each image scale.
minNeighbors – Parameter specifying how many neighbors each candidate rectangle should have to retain it.
flags – Parameter with the same meaning for an old cascade as in the function cvHaarDetectObjects. It is not used for a new cascade.
minSize – Minimum possible object size. Objects smaller than that are ignored.
maxSize – Maximum possible object size. Objects larger than that are ignored.
The function is parallelized with the TBB library.






