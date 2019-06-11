#ifndef LANDMARKEXTRACTIONTASK
#define LANDMARKEXTRACTIONTASK 
#include <Aria/Aria.h>
#include <Aria/ArASyncTask.h>
#include <Aria/ariaUtil.h>
#include <queue>
#include "SensorSweepTask.h"

class LandmarkExtractionTask : public ArASyncTask {
    public:
        LandmarkExtractionTask(SensorSweepTask*);
        ArLineSegment* getNextLine(void);
        void* runThread(void*);
    private:
        SensorSweepTask* sensorSweepTask;
        std::queue<ArLineSegment*> lineQueue;
        ArMutex lineMutex;
};
#endif
