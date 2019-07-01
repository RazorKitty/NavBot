#ifndef DATACLUSTERTASK
#define DATACLUSTERTASK 
#include <Aria/Aria.h>
#include <Aria/ArASyncTask.h>
#include <Aria/ariaUtil.h>
#include <queue>
#include <vector>
#include "SensorSweepTask.h"

class LineExtractionTask : public ArASyncTask {
    public:
        LineExtractionTask(SensorSweepTask*);
        void* runThread(void*);
    private:
        double euclideanDistance;
        SensorSweepTask* sensorSweepTask;
        ArMutex clusterMutex;
        std::vector<ArPose*> poses;
};
#endif
