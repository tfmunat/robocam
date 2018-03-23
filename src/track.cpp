#include "visual.h"
#include "track.h"
#include "movement.h"

using namespace cv;

/* Usage of the Visual class and movement function to track an object */

int run_camera(Visual& visual){
    //video capture object
    VideoCapture capture = visual.getVideoCap();

    // open camera and check if we succeeded
    capture.open(visual.getCamSource());
    if(visual.camError()){
        std::cout << "No Camera detected" << std::endl;
        return -1;
    }

    // get color to fill up the moving object
    std::string color = visual.getColor();
   
    // Matrices
    Mat* origin = new Mat(visual.getWidth(), visual.getHeight(), CV_8UC3);
    Mat* current = new Mat(visual.getWidth(), visual.getHeight(), CV_8UC3);
    Mat* prev = new Mat(visual.getWidth(), visual.getHeight(), CV_8UC3);

    while(1){
        // read the source
        capture.read(*origin);

        // read two frames, convert them to grayscale for findContours(...) and get their absolute differences
        capture.read(*current);
        cvtColor(*current, *current, COLOR_BGR2GRAY); // this line appears before the next read to add minimal delay
        capture.read(*prev);
        cvtColor(*prev, *prev, COLOR_BGR2GRAY);
        absdiff(*current, *prev, *current);

        // output processing and noise reduction: threshold, blur and threshold
        threshold(*current, *current, 20 ,255, THRESH_BINARY);
        blur(*current, *current, Size(10, 10));
        threshold(*current, *current, 20, 255, THRESH_BINARY);        
     
        // track movement and show result
        objectMovement(color, current, origin);
        imshow("Object Tracker", *origin);

        // quit by pressing 'q'
        if (waitKey(10) == 'q') break;
    }
    delete origin;
    delete current;
    delete prev;
    return 0;
}
