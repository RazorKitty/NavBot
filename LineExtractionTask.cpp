#include "LineExtractionTask.h"
#include <iostream>


LineExtractionTask::LineExtractionTask(ArRobot* robot_in,
                                        SensorSweepTask* sensorSweepTask_in,
                                        double euclideanDistance_in,
                                        double maxPointDistance_in,
                                        int minSampleNumber_in) : 
    euclideanDistance(euclideanDistance_in),
    maxPointDistance(maxPointDistance_in),
    minSampleNumber(minSampleNumber_in),
    sensorSweepTask(sensorSweepTask_in),
    robot(robot_in)
{}


void* LineExtractionTask::runThread(void*) {
    while(this->getRunningWithLock()) {
        sensorSweepTask->getData(pointPoses, robotPoses);
        if (robotPoses.size() > 100000) {
            robot->lock();
            robot->disableMotors();
            robot->unlock();
            sensorSweepTask->getData(pointPoses, robotPoses);

            std::cout << robotPoses.size() << std::endl;
            for (size_t i = 0; i < robotPoses.size(); ++i) {
                std::cout << robotPoses[i]->getX() << "\t" << robotPoses[i]->getY() << std::endl;
            }
            robotPoses.clear();
            
            // iterate over all points starting with the most recent data
//            ArPose** sweep = pointPoses[pointPoses.size()-1];
//            for (int i = 1; i < 7; ++i) {
//                // ensure we have 3 points to make a line
//                if (sweep[i-1] != NULL && sweep[i] != NULL && sweep[i+1] != NULL) {
//                    // make a line of best fit
//
//                    // check all points fall within euclideanDistance of this line
//                    
//                    // check other points in this sweep
//
//                    // check history
//
//                    // check we have minSampleNumber for a line
//
//                    // add line to our list of lines
//
//                    
//                }
//            }

            robot->lock();
            robot->enableMotors();
            robot->unlock();
        }
        

    }
    return NULL;
}
