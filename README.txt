=========================
ImgManipulation README
=========================
The app reads images from a folder, creates a grayscaled copy of them,
and saves the results.
The app processes each image on a seperate thread.


Development Environment
-------------------------
>	The app development and compilation performed in Visual Studio 2013 IDE,
>	The app uses OpenCV library, version: opencv-2.4.11
	make sure the linker include path matchs the location of the library on your computer.
	The following link details the library install and include process:
	https://www.opencv-srf.com/2017/11/install-opencv-with-visual-studio.html


Configure and run the app
-------------------------
>	App build configuration is currently DEBUG.
	In addition, there is a DEBUG_MODE defined in the code. When enabled, the app runs additional debug code (mostly logs).
	default is DEBUG_MODE disabled.

>	The app reads the images from the default folder located in the project folder "../greenEyeImgs/".
	in case you'd like to change the folder location, please change the path defined as IMGS_FOLDER_PATH (main.c). 
	Note: the path should end with '/'.

>	The names of the images currently must be consecutive integers starting from 0.
	i.e. : 0.jpg, 1.jpg, 2.jpg, etc' ...
	
>	10 images is the default amount of images (in the default folder there are 10 images as well).
	If you'd like to change the amount of images, please change NUM_OF_IMGS define (main.c) to the required number.
	Note: The limit of the supported amount has not been tested yet!!!
	
>	The officialy supported image format is ".jpg". 
	Any other format has not been tested yet!!!
	
>	The resulted images (images after manipulation, output) are saved
	to the same folder specified in IMGS_FOLDER_PATH (same input images folder)
	with a prefix of "result_".
	i.e. : The result for image named 0.jpg will be the correlated image named "result_0.jpg"
	
>	The app has a benchmark feature defined by APP_BENCHMARK (main.c). The default is enabled. 



