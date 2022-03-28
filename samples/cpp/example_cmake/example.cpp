#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void drawText(Mat & image);
std::string gstreamer_pipeline(int capture_width, int capture_height, int framerate, int display_width, int display_height)

int main()
{
    int capture_width = 2592; //1280 ;
    int capture_height = 1944; //720 ;
    int framerate = 30 ;
    int display_width = 320; //1280 ;
    int display_height = 240; //720 ;
    
    cout << "Built with OpenCV " << CV_VERSION << endl;
    Mat image;
    VideoCapture capture(pipeline, CAP_GSTREAMER);
    if(capture.isOpened())
    {
        cout << "Capture is opened" << endl;
        for(;;)
        {
            capture >> image;
            if(image.empty())
                break;
            drawText(image);
            imshow("Sample", image);
            if(waitKey(10) >= 0)
                break;
        }
    }
    else
    {
        cout << "No capture" << endl;
        image = Mat::zeros(480, 640, CV_8UC1);
        drawText(image);
        imshow("Sample", image);
        waitKey(0);
    }
    return 0;
}

void drawText(Mat & image)
{
    putText(image, "Hello OpenCV",
            Point(20, 50),
            FONT_HERSHEY_COMPLEX, 1, // font face and scale
            Scalar(255, 255, 255), // white
            1, LINE_AA); // line thickness and type
}

std::string gstreamer_pipeline(int capture_width, int capture_height, int framerate, int display_width, int display_height) {
    return
            " libcamerasrc ! video/x-raw, "
            " width=" + std::to_string(capture_width) + ","
            " height=" + std::to_string(capture_height) + ","
            " framerate=" + std::to_string(framerate) +"/1 !"
            " videoconvert ! videoscale ! "
            " video/x-raw,"
            " width=(int)" + std::to_string(display_width) + ","
            " height=(int)" + std::to_string(display_height) + " ! appsink";
}

