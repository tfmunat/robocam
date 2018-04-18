/* main takes a color name as a command line argument */
/* valgrind gives an expected constant memory leak from libraries
 * definitely lost: 2,984 bytes in 6 blocks
 * indirectly lost: 82 bytes in 2 blocks
 */

#include "visual.h"
#include "track.h"
#include "xiApiPlusOcv.hpp"

/* enum for available cameras */
enum CAMERAS {
    // builtin camera (video0) is default (in a Linux environment)
    webcam,
    // change in main if camera is changed
    roboeye,
    usbcam,
    kinect
};

int main(int argc, char **argv){
    std::string usage_1 = "usage: ./main red/green/blue/white/black"; 
    std::string usage_2 = "usage_2: make run COLOR=red/green/blue/white/black";
	    
    // check arguments
    if (argc != 2){ 
        std::cout << usage_1 << std::endl << usage_2 << std::endl;
        return 0;
    }
    
    // get color name
    std::string color = argv[1];
    if ((color != "red") && (color != "green") && (color != "blue")
            && (color != "white") && (color != "black")){
        std::cout << usage_1 << std::endl << usage_2 << std::endl;
        return 0;
    }
    
    // choose camera
    //CAMERAS cam = CAMERAS::ps3eye;
    //CAMERAS cam = CAMERAS::roboeye;
    
    // create visual for camera
    Visual vis("test.avi", color);
    
    // start camera
    run_camera(vis);
    
    return 0;
}
