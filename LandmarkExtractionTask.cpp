#include "LandmarkExtractionTask.h"

LandmarkExtractionTask::LandmarkExtractionTask(SensorSweepTask* sensorSweepTask_in) : sensorSweepTask(sensorSweepTask_in) {}

ArLineSegment* LandmarkExtractionTask::getNextLine(void) {
    ArLineSegment* line = NULL;
    lineMutex.lock();
    if (!lineQueue.empty()) {
        line = lineQueue.front();
        lineQueue.pop();
    }
    lineMutex.unlock();
    return line;
}

void* LandmarkExtractionTask::runThread(void*) {
    while(this->getRunningWithLock()) {

    }
    return NULL;
}
