
#include "utilsVid.h"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/*
*/
int main(int argc, char* argv[]){

    const string vid_path = "vidtest8.mp4";

    VideoCapture capture( vid_path );
    if (!capture.isOpened()){
        //error in opening the video input
        cerr << "Unable to open: " << vid_path << endl;
        return 0;
    }

    vector<int> demodulated;
    String decoded;
    int win_size = 3;

    cout << "Initializing demodulation" << endl; 

    demodulated = fWindow(capture, win_size, 240, 0);

    // std::cout << "Sum of pixel values for each row in channel " << channel << " (blue):" << std::endl;
    for (size_t i = 0; i < demodulated.size(); ++i) {
        std::cout << demodulated[i] << " ";
    }
    // cout << "Demodulation done" << endl;

    // int header_len = 5;
    // int package_len = 8;

    // cout << "Initializing demodulation" << endl; 
    // decoded = detectAndDemodulate(demodulated, header_len, package_len);

    // cout << "The message decoded is:" << endl;
    // cout << decoded << endl;

    return 0;
}


/*

int detect( Mat src_gray, double threshold_value, double th2);

int main(int argc, char* argv[])
{
    const string vid_path = "vidtest9.mp4";

    VideoCapture capture( vid_path);
    if (!capture.isOpened()){
        //error in opening the video input
        cerr << "Unable to open: " << vid_path << endl;
        return 0;
    }

    capture.set(CAP_PROP_FPS, 4);
    Mat frame;
    while (true) {
        capture >> frame;
        if (frame.empty())
            break;

        cvtColor(frame,frame, COLOR_RGB2GRAY);
        // imshow("Frame", frame);
        detect(frame, 240, 0);
        //get the input from the keyboard
        // if (cv::waitKey(200) >= 0) break;
        int keyboard = waitKey(200);
        if (keyboard == 'q' || keyboard == 27)
            break;
    }
    return 0;
}

int detect( Mat src_gray, double threshold_value, double th2){
   
    int rows = src_gray.rows;          // Number of rows (height)
    int cols = src_gray.cols;          // Number of columns (width)

    int width = 60, height = 60;
    int startX = cols/2;
    int startY = rows/2;

    Mat cropped_image = src_gray(Range(startY - height,startY + height), Range(startX - width, startX + width));
    Mat dst, erosion_dst, dilation_dst;

    threshold( cropped_image, dst, threshold_value, 255, THRESH_BINARY );
    int erosion_size = 3;
    int dilation_size = 3;
    
    Mat element_ero = getStructuringElement( MORPH_ELLIPSE,
                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                       Point( erosion_size, erosion_size ) );

    Mat element_dil = getStructuringElement( MORPH_ELLIPSE,
                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                       Point( dilation_size, dilation_size ) );
    
    cv::erode(dst, erosion_dst, element_ero);
    cv::dilate(erosion_dst, dilation_dst, element_dil);
    double sum = cv::sum(dilation_dst)[0];

    // cout << sum << ",";
    
    imshow("video", dst);
    return 0;
}
 */