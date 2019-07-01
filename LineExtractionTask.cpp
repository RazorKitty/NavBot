#include "LineExtractionTask.h"

LineExtractionTask::LineExtractionTask(SensorSweepTask* sensorSweepTask_in) : sensorSweepTask(sensorSweepTask_in) {}


void* LineExtractionTask::runThread(void*) {
    while(this->getRunningWithLock()) {

    }
    return NULL;
}
