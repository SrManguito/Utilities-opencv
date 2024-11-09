
#include "utilsVid.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

/**
 * @brief  Detects whether the LED is On (1) or Off (0)
 * 
 * @param  src_gray:  Image or frame in grayscale
 * @param  threshold_value: Threshold for the light-intensity of the LED 
 * @param  th2: A secondary threshold in case of high luminosity enviroment
 * 
 * @return  1/0 in case the LED is On/Off
 */
int detectOnOff( Mat src_gray, double threshold_value, double th2){
   
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
    
    if(sum > 0 && sum > th2){
        return 1;
    }
    else{
        return 0;
    }

}

/**
 * @brief Detects a package based on the package format of Matus paper
 */
char matusByteCharDemodulation(vector<int> package, int p_begin){
    int num = 0;
    vector<int> pos = {1,2,3,4,6,7,8,9};

    for(int i = 0; i<8; i++){
        num += package[p_begin + pos[i]] * pow(2,i);
    }

    return static_cast<char>(num);
};

/**
 * @brief Detects a package based on the package format of Matus paper
 */
int matusByteIntDemodulation(vector<int> package, int p_begin){
    int num = 0;
    vector<int> pos = {1,2,3,4,6,7,8,9};

    for(int i = 0; i<8; i++){
        num += package[p_begin + pos[i]] * pow(2,i);
    }
    
    return num;
}

/**
 * @brief Transforms a binary number in a vector of ints to its representation in ascii
 */
char binaryToChar(vector<int> binary){
    int asciiNum = 0;

    for(int i = 0; i<8; i++){
        asciiNum += binary[i] * pow(2,i);
    }

    return static_cast<char>(asciiNum);
};

/**
 * @brief Detects the headers containted in the data vector
 * 
 * @param
 * @param
 * @param
 * 
 * @return Returns the positions of the headers
 */
String detectAndDemodulate(vector<int> data, int header_len, int package_len){

    String message;

    int data_len = data.size();

    for(int i = 0; i < data_len - header_len + 1; i++){
        int win_sum = 0;

        for(int j = 0; j < header_len; j++){
            win_sum += data[ i+j];
        }

        if(win_sum = 5){
            cout << "Header found" << endl;
            message += matusByteCharDemodulation(data, (i + header_len));
            i += 9;
        }

    }
    return message;

};

/**
 * @brief Using the SlidingWindow technique decodes the video
 * 
 * @param vid: VideoCapture of the vidd
 * @param win_size: len of the sliding window
 * @param th1: Threshold for the light-intensity of the LED 
 * @param th2: A secondary threshold in case of high luminosity enviroment
 * 
 * @return An array of ints with the resulting detectión
 */
vector<int> fWindow(VideoCapture vid, int win_size, double th1 , double th2 ){

    int total_frames = vid.get(CAP_PROP_FRAME_COUNT);
    // cout << total_frames << endl;
    vector<int> decoded;
    Mat frame;


    for (int i = 0; i < total_frames - win_size + 1; i+= 2) {

        vid.set(CAP_PROP_POS_FRAMES, i);
        int current_sum = 0;

        for (int j = 0; j < win_size; j++){

            // cout << vid.get(CAP_PROP_POS_FRAMES) << " " ;
            vid >> frame;
            cvtColor(frame,frame, COLOR_RGB2GRAY);
            int detection = detectOnOff(frame, th1, th2);
            current_sum += detection;
        }


        if(current_sum >1){
            decoded.push_back(1);
        }
        else{
            decoded.push_back(0);
        }
        
               
    }

    return decoded;
};


