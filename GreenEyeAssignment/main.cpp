#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

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
	//nothing yet
	return img;
}

int main() {
	static const int EXIT_WITH_ERROR;

	Mat img = imread("c:/greenEyeImgs/img1.jpg");
	if (img.empty()) {
		cout << "Error- Cannot load image!" << endl;
		return EXIT_WITH_ERROR;
	}

	int imgWidth = img.size().width;
	int imgHeight = img.size().height;
	cout << "Dims : " << img.dims << endl;
	cout << "Width : " << imgWidth << endl;
	cout << "Height: " << imgHeight << endl;
	if (img.channels() != RGB_IMG_NUM_OF_CHANNELS) {
		cout << "Error - Image must be an RGB image!" << endl;
		return EXIT_WITH_ERROR;
	}

	doSomething(img);

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
			cout << "blue = " << (int)blue << ", green = " << (int)green << ", red = " << (int)red << endl;

			double grayVal = convert3ChannelsInto1((int)blue, (int)green, (int)red);
			cout << grayVal << endl;
			grayValuesMatrix.at<double>(i, j)= grayVal;
		}
	}

	imwrite("c:/greenEyeImgs/img1.jpg", grayValuesMatrix);
	imshow("Image", grayValuesMatrix);
	waitKey(0);
}
