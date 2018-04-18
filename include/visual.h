#ifndef __VISUAL__
#define __VISUAL__

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <string>

/* Visual Class
 * contains an OpenCV VideoCapture object
 * instantiated in main.cpp with camera source and color
 * color is taken from the command line argument
 * camera source is chosen from enum
 */

class Visual{
    protected:
        // member variables
        cv::VideoCapture cap;
        std::string color;
        const std::string& camSource;
        int width = 480;
        int height = 640;
    public:
        // constructor
        Visual(const std::string& input, std::string objectColor)
            :color(objectColor), camSource(input){}

        // check if we succeeded
        bool camError(){ return cap.isOpened(); }

        // getters
        cv::VideoCapture getVideoCap(){ return cap; }
        std::string getColor() { return color; }
        int getWidth() { return width; }
        int getHeight() { return height; }
        const std::string& getCamSource() { return camSource; }

        // destructor
        ~Visual() { cap.release(); }
};

#endif
