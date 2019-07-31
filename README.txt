=========================
ImgManipulation README
=========================
The app reads images from a folder, applies grayscale filter on them,
and saves the results.


Development Environment
-------------------------
>	The app development and compilation is performed in Visual Studio 2013 IDE,
	and OpenCV library, version: opencv-2.4.11


Configure and run the app
-------------------------
>	The app reads the images from the default located in the project folder "./greenEyeImgs/".
	in case you'd like to change the folder location, please change the path defined as IMGS_FOLDER_PATH (main.c). 
	Note: the path should end with '/'.

>	The names of the images currently must be integers, starting from 0.
	i.e. : 0.jpg, 1.jpg, 2.jpg, etc' ...
	
>	10 images is the default amount of images (in the default folder there are 10 images as well).
	If you'd like to change the amount of images, please change NUM_OF_IMGS define (main.c) to the required number.
	Note: The limits of the supported amount have not been tested yes!!!
	
>	The officialy supported image format is ".jpg". 
	Any other format has not been tested yet!!!
	
>	The resulted images (images after manipulation output) will be save
	to the same folder specified in IMGS_FOLDER_PATH (same input images folder)
	with a prefix of "result_".
	i.e. : the result for image named 0.jpg will be the correlated image named "result_0.jpg"
 



