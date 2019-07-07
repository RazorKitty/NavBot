#include "LineExtractionTask.h"

LineExtractionTask::LineExtractionTask(SensorSweepTask* sensorSweepTask_in, double euclideanDistance_in) : 
    euclideanDistance(euclideanDistance_in),
    sensorSweepTask(sensorSweepTask_in)
{}


void* LineExtractionTask::runThread(void*) {
    while(this->getRunningWithLock()) {
        int length;
        ArPose*** pointPoses_arr = NULL;
        ArPose** robotPoses_arr = NULL;
        sensorSweepTask->getData(pointPoses_arr, robotPoses_arr, &length);
    }
    return NULL;
}
