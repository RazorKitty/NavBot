#ifndef LINEEXTRACTIONTASK
#define LINEEXTRACTIONTASK 
#include <Aria/Aria.h>
#include <Aria/ArASyncTask.h>
#include <Aria/ariaUtil.h>
#include <queue>
#include <vector>
#include "SensorSweepTask.h"

class LineExtractionTask : public ArASyncTask {
    public:
        LineExtractionTask(ArRobot*, SensorSweepTask*, double, double, int);
        void* runThread(void*);
    private:
        std::vector<ArPose*> robotPoses;
        std::vector<ArPose**> pointPoses;
        SensorSweepTask* sensorSweepTask;
        ArRobot* robot;
        double euclideanDistance;
        double maxPointDistance;
        int minSampleNumber;
};
#endif
