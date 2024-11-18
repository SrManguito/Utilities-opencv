#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using std::cout;

int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;
Mat src, src_gray, dst;
const char* window_name = "Threshold Demo";
const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";


static void Threshold_Demo( int, void* ){
    /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
    */
    int rows = src_gray.rows;          // Number of rows (height)
    int cols = src_gray.cols;          // Number of columns (width)

    int width = 120, height = 120;
    int startX = cols/2;
    int startY = rows/2;

    Mat cropped_image = src_gray(Range(startY - height,startY + height), Range(startX - width, startX + width));
    threshold( cropped_image, dst, threshold_value, max_binary_value, threshold_type );
    int erosion_size = 10;
    int dilation_size = 10;
    Mat erosion_dst, dilation_dst;
    
    Mat element_ero = getStructuringElement( MORPH_ELLIPSE,
                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                       Point( erosion_size, erosion_size ) );

    Mat element_dil = getStructuringElement( MORPH_ELLIPSE,
                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                       Point( dilation_size, dilation_size ) );
    
    cv::erode(dst, erosion_dst, element_ero);
    imshow( window_name, erosion_dst );
    cv::dilate(erosion_dst, dilation_dst, element_dil);

}
int main( int argc, char** argv )
{
    String imageName("Whatsapp/Close.jpeg"); // by default
    if (argc > 1)
    {
        imageName = argv[1];
    }
    
    src = imread( samples::findFile( imageName ), IMREAD_COLOR ); // Load an image
    if (src.empty())
    {
        cout << "Cannot read the image: " << imageName << std::endl;
        return -1;
    }
    imshow("Natural Source", src);
    cvtColor( src, src_gray, COLOR_BGR2GRAY ); // Convert the image to Gray
    namedWindow( window_name, WINDOW_AUTOSIZE ); // Create a window to display results
    createTrackbar( trackbar_type,
                    window_name, &threshold_type,
                    max_type, Threshold_Demo ); // Create a Trackbar to choose type of Threshold
    createTrackbar( trackbar_value,
                    window_name, &threshold_value,
                    max_value, Threshold_Demo ); // Create a Trackbar to choose Threshold value
    Threshold_Demo( 0, 0 ); // Call the function to initialize
    waitKey();
    return 0;
}