#include "movement.h"

using namespace cv;
using namespace std;

void objectMovement(string contour_color, Mat* movement, Mat* input){
    // create color
    Scalar color;
    if(contour_color == "red") { color = Scalar(0, 0, 255); }
    else if(contour_color == "blue") { color = Scalar(255, 0, 0); }
    else if(contour_color == "green") { color = Scalar(0, 255, 0); }
    else if(contour_color == "white") { color = Scalar(255, 255, 255); }
    else if(contour_color == "black") { color = Scalar(0, 0, 0); }

    // contour from OpenCV documentation
    vector<vector<Point>>* contours = new vector<vector<Point>>;
    vector<vector<Point>>* movingObject = new vector<vector<Point>>;
    vector<Vec4i>* hierarchy = new vector<Vec4i>;

    // check memory
    if((contours == 0) || (movingObject == 0) || (hierarchy == 0)) {
        cout << "Error: out of memory" << endl;
        exit(1);
    }
    findContours(*movement, *contours, *hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

    // to calculate the center of mass
    Rect centerOfMass = Rect(0, 0, 0, 0);
    int position[2] = {0, 0};
    double slope;

    // if movement occurs
    if(contours->size() > 0){
        // update vector
        movingObject->push_back(contours->at(contours->size()-1));

        // calculate the center of mass and slope and update
        centerOfMass = boundingRect(movingObject->at(0));
        position[0] = centerOfMass.x + centerOfMass.width/2;
        position[1] = centerOfMass.y + centerOfMass.height/2;

        // colorize
        drawContours(*input, *contours, -1, color, -1, 8, *hierarchy);

        // draw the trajectory
        Point a(centerOfMass.x, centerOfMass.y);
        Point b(position[0], position[1]);
        if ((b.x-a.x) == 0) slope = 0;
        else { slope = (double) (b.y-a.y)/(b.x-a.x); }
        Point q(input->cols, input->rows);
        q.y = -(b.x - q.x) * slope + b.y;
        line(*input, b, q, Scalar(255,255,255), 2);
    }
    // free memory
    delete hierarchy;
    delete movingObject;
    delete contours;
}
