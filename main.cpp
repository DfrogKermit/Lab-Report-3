#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace cv;

void outputImage(Mat img, std::string name)
{
    namedWindow(name, WINDOW_NORMAL);
    imshow(name, img);
    imwrite(name + ".jpg", img);
}

int main()
{
    Mat img = imread("RedCar.bmp");

    if (img.empty())
    {
        printf("Error: Could not open image file\n");
        return -1;
    }

    // Convert the image from RGB to HSV color space
    Mat hsvImg;
    cvtColor(img, hsvImg, COLOR_BGR2HSV);

    // Define the color ranges for the colors we want to identify
    Scalar lowerRed = Scalar(0, 100, 100);
    Scalar upperRed = Scalar(10, 255, 255);
    Scalar lowerGreen = Scalar(50, 100, 100);
    Scalar upperGreen = Scalar(70, 255, 255);
    Scalar lowerBlue = Scalar(90, 100, 100);
    Scalar upperBlue = Scalar(130, 255, 255);

    // Create masks for each color range
    Mat redMask, greenMask, blueMask;
    inRange(hsvImg, lowerRed, upperRed, redMask);
    inRange(hsvImg, lowerGreen, upperGreen, greenMask);
    inRange(hsvImg, lowerBlue, upperBlue, blueMask);

    // Count the number of pixels for each color
    int redCount = countNonZero(redMask);
    int greenCount = countNonZero(greenMask);
    int blueCount = countNonZero(blueMask);

    // Print the results
    printf("Red pixels: %d\n", redCount);
    printf("Green pixels: %d\n", greenCount);
    printf("Blue pixels: %d\n", blueCount);

    // Determine the color with the highest pixel count
    if (redCount > greenCount && redCount > blueCount)
    {
        printf("The dominant color is red.\n");
        outputImage(img, "original");
        outputImage(redMask, "red_pixels");
    }
    else if (greenCount > redCount && greenCount > blueCount)
    {
        printf("The dominant color is green.\n");
        outputImage(img, "original");
        outputImage(greenMask, "green_pixels");
    }
    else if (blueCount > redCount && blueCount > greenCount)
    {
        printf("The dominant color is blue.\n");
        outputImage(img, "original");
        outputImage(blueMask, "blue_pixels");
    }
    else
    {
        printf("Could not determine the dominant color.\n");
    }

    waitKey(0);
    return 0;
}
