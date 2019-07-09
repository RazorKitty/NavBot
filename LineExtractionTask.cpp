#include "LineExtractionTask.h"
#include <iostream>


LineExtractionTask::LineExtractionTask(SensorSweepTask* sensorSweepTask_in,
                                        double euclideanDistance_in,
                                        double maxPointDistance_in,
                                        int minSampleNumber_in) : 
    euclideanDistance(euclideanDistance_in),
    maxPointDistance(maxPointDistance_in),
    minSampleNumber(minSampleNumber_in),
    sensorSweepTask(sensorSweepTask_in)
{}


void* LineExtractionTask::runThread(void*) {
    while(this->getRunningWithLock()) {
        arr_length = 0;
        pointPoses_arr = NULL;
        robotPoses_arr = NULL;
        sensorSweepTask->getData(pointPoses_arr, robotPoses_arr, &arr_length);
        for (int i = 0; i < arr_length; ++i) {
            pointPoses.push_back(pointPoses_arr[i]);
            robotPoses.push_back(robotPoses_arr[i]);
        }
        std::cout << robotPoses.size() << std::endl;
        for (size_t i = 0; i < robotPoses.size(); ++i) {
            std::cout << robotPoses[i]->getX() << "\t" << robotPoses[i]->getY() << std::endl; 
        }
    }
    return NULL;
}
