#include <iostream> 
#include <opencv2/opencv.hpp> 
#include <vector>

using namespace cv; 
using namespace std;
RNG rng(12345); 
  
// Driver code 
int main(int argc, char** argv) 
{ 
    // Read the image file as 
    // imread("default.jpg"); 
    const string image_path = "Whatsapp/Upper.jpeg";

    Mat img = imread(image_path, 
                       IMREAD_GRAYSCALE); 
                       
                       
    // Error Handling 
    if (img.empty()) { 
        cout << "Image File "
             << "Not Found" << endl; 
  
        // wait for any key press 
        cin.get(); 
        return -1; 
    } 

    int blueChannel = 0; int greenChannel = 1; int redChannel = 2;

    // Get the shape of the image
    int rows = img.rows;          // Number of rows (height)
    int cols = img.cols;          // Number of columns (width)
    int channels = img.channels(); // Number of channels

    int width = 300, height = 300;
    int startX = cols/2;
    int startY = rows/2;

    Mat cropped_image = img(Range(startY - height,startY + height), Range(startX - width, startX + width));

    int erosion_size = 8;
    int dilation_size = 10;

    Mat dst, erosion_dst, dilation_dst;
    
    Mat element_ero = getStructuringElement( MORPH_ELLIPSE,
                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                       Point( erosion_size, erosion_size ) );

    Mat element_dil = getStructuringElement( MORPH_ELLIPSE,
                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                       Point( dilation_size, dilation_size ) );
    // dst.copySize(img);

    double thresh;
    cout << "Ingresar threshold \n";
    cin >> thresh;
    double maxValue = 255;
    
    long double thres = cv::threshold(cropped_image, dst, thresh, maxValue, THRESH_BINARY);
    
    cv::erode(dst, erosion_dst, element_ero);
    cv::dilate(erosion_dst, dilation_dst, element_dil);

    // Print the shape information
    cout << "Shape: " << rows << "x" << cols << " with " << channels << " channels" << endl;

    double sum = cv::sum(dilation_dst)[0];
    cout << sum << endl;

    imshow("Result", dilation_dst); 
    // imshow("Otra", img);
  
    // Wait for any keystroke 
    waitKey(0); 
    return 0; 

}
