#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

//Note! Please comment out the define in order to run production mode.
//debug mode consist additional logs and tests.
#define DEBUG_MODE

static const int RGB_IMG_NUM_OF_CHANNELS = 3;
static const int RGB_CHANNEL_INDEX_BLUE = 0;
static const int RGB_CHANNEL_INDEX_GREEN = 1;
static const int RGB_CHANNEL_INDEX_RED = 2;
static const double CHANNEL_FILTER_BLUE = 0.299;
static const double CHANNEL_FILTER_GREEN = 0.587;
static const double CHANNEL_FILTER_RED = 0.114;

static const double g_channels_filters[RGB_IMG_NUM_OF_CHANNELS] = {CHANNEL_FILTER_BLUE, CHANNEL_FILTER_GREEN, CHANNEL_FILTER_RED};

double convert3ChannelsInto1(int blue, int green, int red) {
	return ((g_channels_filters[RGB_CHANNEL_INDEX_BLUE] * blue)
		+ (g_channels_filters[RGB_CHANNEL_INDEX_GREEN] * green)
		+ (g_channels_filters[RGB_CHANNEL_INDEX_RED] * red));
}

static Mat doSomething(Mat img) {
	int imgWidth = img.size().width;
	int imgHeight = img.size().height;
#ifdef DEBUG_MODE
	cout << "Dims : " << img.dims << endl;
	cout << "Width : " << imgWidth << endl;
	cout << "Height: " << imgHeight << endl;
#endif //DEBUG_MODE
	if (img.channels() != RGB_IMG_NUM_OF_CHANNELS) {
		cout << "Error - Image must be an RGB image!" << endl;
		//TODO- handle error
	}
	
	Mat grayValuesMatrix = Mat(imgHeight, imgWidth, CV_64F);
	Vec3b intensity;
	uchar blue;
	uchar  green;
	uchar  red;
	for (int i = 0; i < imgHeight; i++) {
		for (int j = 0; j < imgWidth; j++) {
			intensity = img.at<Vec3b>(i, j);
			blue = intensity.val[RGB_CHANNEL_INDEX_BLUE];
			green = intensity.val[RGB_CHANNEL_INDEX_GREEN];
			red = intensity.val[RGB_CHANNEL_INDEX_RED];
#ifdef DEBUG_MODE
			cout << "blue = " << (int)blue << ", green = " << (int)green << ", red = " << (int)red << endl;
#endif //DEBUG_MODE

			double grayVal = convert3ChannelsInto1((int)blue, (int)green, (int)red);
			cout << grayVal << endl;
			grayValuesMatrix.at<double>(i, j) = grayVal;
		}
	}

	return grayValuesMatrix;
}

int main() {
	static const int EXIT_WITH_ERROR;

	Mat img = imread("c:/greenEyeImgs/img1.jpg");
	if (img.empty()) {
		cout << "Error- Cannot load image!" << endl;
		return EXIT_WITH_ERROR;
	}

	Mat filterdImg = doSomething(img);

	imwrite("c:/greenEyeImgs/img1.jpg", filterdImg);
#ifdef DEBUG_MODE
	imshow("Image", filterdImg);
#endif //DEBUG_MODE
	waitKey(0);
}
