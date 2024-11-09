#ifndef UTILSVID_H
#define UTILSVID_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

const int THRESHOLD = 240;

int detectOnOff( Mat src_gray, double threshold_value, double th2);

char matusByteCharDemodulation(vector<int> package, int p_begin);

int matusByteIntDemodulation(vector<int> package, int p_begin);

char binaryToChar(vector<int> binary);

String detectAndDemodulate(vector<int> data, int header_len, int package_len);

vector<int> fWindow(VideoCapture vid, int win_size, double th1, double th2);

#endif