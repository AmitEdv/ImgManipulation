#include <iostream>
#include <thread>
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

//Note! Please comment out the define in order to run production mode.
//debug mode consist additional logs and tests.
//#define DEBUG_MODE

static const int NUM_OF_IMGS = 10;
static const string IMGS_FOLDER_PATH = "c:/greenEyeImgs/";
static const string IMGS_DEFAULT_FORMAT = ".jpg";

static const int RGB_IMG_NUM_OF_CHANNELS = 3;
static const int RGB_CHANNEL_INDEX_BLUE = 0;
static const int RGB_CHANNEL_INDEX_GREEN = 1;
static const int RGB_CHANNEL_INDEX_RED = 2;
static const double CHANNEL_FILTER_BLUE = 0.299;
static const double CHANNEL_FILTER_GREEN = 0.587;
static const double CHANNEL_FILTER_RED = 0.114;

static vector<thread> g_threads;
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

#ifdef DEBUG_MODE
			cout << grayVal << endl;
#endif //DEBUG_MODE
			grayValuesMatrix.at<double>(i, j) = grayVal;
		}
	}

	return grayValuesMatrix;
}

static void applyGrayscaleFilterOnImage(string imgFullPath) {
	Mat img = imread(imgFullPath);
	if (img.empty()) {
		cout << "Error- Cannot load image!" << endl;
		//TODO- handle error
	}

	cout << imgFullPath << " starts" << endl;
	Mat filterdImg = doSomething(img);
	
	imwrite(imgFullPath, filterdImg);
#ifdef DEBUG_MODE
	imshow("Image", filterdImg);
#endif //DEBUG_MODE
	cout << imgFullPath << " done" << endl;
}

int main() {
	static const int EXIT_WITH_ERROR;
	
	cout << "LEGEN -waitforit- ..." << endl;
	
	for (int i = 0; i < NUM_OF_IMGS; i++) {
		string fullImgPathStr = IMGS_FOLDER_PATH + to_string(i) + IMGS_DEFAULT_FORMAT;
#ifdef DEBUG_MODE
		cout << "image " << fullImgPathStr << endl;
#endif //DEBUG_MODE
		g_threads.push_back(thread(applyGrayscaleFilterOnImage, fullImgPathStr));
	}

	for (int i = 0; i < NUM_OF_IMGS; i++) {
		g_threads[i].join();
	}
	
	cout << "DARY!" << endl;

	waitKey(0);
}
