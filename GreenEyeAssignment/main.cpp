#include <iostream>
#include <thread>
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;
using namespace std::chrono;

//Comment out the define in order to run production mode.
//debug mode consist additional logs and tests.
//#define APP_DEBUG_MODE

//Comment out the define in order to disable benchmark feature.
//the feature measures the total running time of the application.
#define APP_BENCHMARK

static const int NUM_OF_IMGS = 10;
static const string IMGS_FOLDER_PATH = "../greenEyeImgs/";
static const string IMGS_DEFAULT_FORMAT = ".jpg";
static const string IMG_RESULT_NAME_PREFIX = "result_";

static const double CHANNEL_FILTER_BLUE = 0.299;
static const double CHANNEL_FILTER_GREEN = 0.587;
static const double CHANNEL_FILTER_RED = 0.114;

enum e_BGR_channel_index {
	BGR_CHANNEL_INDEX_BLUE = 0,
	BGR_CHANNEL_INDEX_GREEN,
	BGR_CHANNEL_INDEX_RED,
	BGR_IMG_NUM_OF_CHANNELS
};

vector<thread> g_threads;
#ifdef APP_BENCHMARK
time_point<system_clock> g_benchmarkStartTime;
#endif //APP_BENCHMARK

static void applyGrayscaleFilterOnImage(string inputImgFullPath, string resultImgFullPath);
static Mat doSomething(Mat img);
double convert3ChannelsInto1(int blue, int green, int red);
inline void stopBenchmarkAndPrintResult();
inline void startBenchmark();


int main() {
	static const int EXIT_WITH_ERROR;
	
	startBenchmark();
	
	for (int i = 0; i < NUM_OF_IMGS; i++) {
		string inputImgPathStr = IMGS_FOLDER_PATH + to_string(i) + IMGS_DEFAULT_FORMAT;
		string resultImgPathStr = IMGS_FOLDER_PATH + IMG_RESULT_NAME_PREFIX + to_string(i) + IMGS_DEFAULT_FORMAT;
#ifdef APP_DEBUG_MODE
		cout << "image " << fullImgPathStr << endl;
#endif //APP_DEBUG_MODE
		g_threads.push_back(thread(applyGrayscaleFilterOnImage, inputImgPathStr, resultImgPathStr));
	}

	for (int i = 0; i < NUM_OF_IMGS; i++) {
		g_threads[i].join();
	}
	
	stopBenchmarkAndPrintResult();

	waitKey(0);
}


static void applyGrayscaleFilterOnImage(string inputImgFullPath, string resultImgFullPath) {
	Mat img = imread(inputImgFullPath);
	if (img.empty()) {
		cout << "Error- Cannot load image " << inputImgFullPath << " !" << endl;
		return;
	}

	cout << inputImgFullPath << " starts" << endl;
	Mat filterdImg = doSomething(img);

	imwrite(resultImgFullPath, filterdImg);
#ifdef APP_DEBUG_MODE
	imshow("Image", filterdImg);
#endif //APP_DEBUG_MODE
	cout << inputImgFullPath << " done" << endl;
}


static Mat doSomething(Mat img) {
	int imgWidth = img.size().width;
	int imgHeight = img.size().height;
	Mat grayValuesMatrix = Mat(imgHeight, imgWidth, CV_64F);
#ifdef APP_DEBUG_MODE
	cout << "Dims : " << img.dims << endl;
	cout << "Width : " << imgWidth << endl;
	cout << "Height: " << imgHeight << endl;
#endif //APP_DEBUG_MODE
	if (img.channels() != BGR_IMG_NUM_OF_CHANNELS) {
		cout << "Warning - Image must have 3 channels!" << endl;
		return grayValuesMatrix;
	}

	Vec3b intensity;
	uchar blue;
	uchar  green;
	uchar  red;
	for (int i = 0; i < imgHeight; i++) {
		for (int j = 0; j < imgWidth; j++) {
			intensity = img.at<Vec3b>(i, j);
			blue = intensity.val[BGR_CHANNEL_INDEX_BLUE];
			green = intensity.val[BGR_CHANNEL_INDEX_GREEN];
			red = intensity.val[BGR_CHANNEL_INDEX_RED];
#ifdef APP_DEBUG_MODE
			cout << "blue = " << (int)blue << ", green = " << (int)green << ", red = " << (int)red << endl;
#endif //APP_DEBUG_MODE

			double grayVal = convert3ChannelsInto1((int)blue, (int)green, (int)red);

#ifdef APP_DEBUG_MODE
			cout << grayVal << endl;
#endif //APP_DEBUG_MODE
			grayValuesMatrix.at<double>(i, j) = grayVal;
		}
	}

	return grayValuesMatrix;
}


double convert3ChannelsInto1(int blue, int green, int red) {
	static const double channelsFilters[BGR_IMG_NUM_OF_CHANNELS] = {
		CHANNEL_FILTER_BLUE, CHANNEL_FILTER_GREEN, CHANNEL_FILTER_RED};

	return ((channelsFilters[BGR_CHANNEL_INDEX_BLUE] * blue)
		+ (channelsFilters[BGR_CHANNEL_INDEX_GREEN] * green)
		+ (channelsFilters[BGR_CHANNEL_INDEX_RED] * red));
}


inline void startBenchmark() {
#ifdef APP_BENCHMARK
	g_benchmarkStartTime = high_resolution_clock::now();
#endif //APP_BENCHMARK
}


inline void stopBenchmarkAndPrintResult() {
#ifdef APP_BENCHMARK
	time_point<system_clock> end = high_resolution_clock::now();;
	long long elapsed_microseconds = std::chrono::duration_cast<microseconds>(end - g_benchmarkStartTime).count();
	cout << "===============================" << endl;
	cout << "Benchmark total run time:  " << elapsed_microseconds << " (usec)" << endl;
	cout << "===============================" << endl;
#endif //APP_BENCHMARK
}