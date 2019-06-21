#include "DataClusterTask.h"

DataClusterTask::DataClusterTask(SensorSweepTask* sensorSweepTask_in) : sensorSweepTask(sensorSweepTask_in) {}


void* DataClusterTask::runThread(void*) {
    while(this->getRunningWithLock()) {

    }
    return NULL;
}
