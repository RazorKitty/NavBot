#ifndef ASYNCTASKSCONTAINER
#define ASYNCTASKSCONTAINER 
#include <Aria/Aria.h>
#include <Aria/ArMap.h>
#include "NavBotUtil.h"
#include <iostream>
#include <math.h>
#include <queue>

class AsyncTasksContainer {
    public:
        AsyncTasksContainer(ArRobot*, ArMap*);
        //AsyncTasksContainer(const AsyncTasksContainer &ATC);
        virtual ~AsyncTasksContainer(void){};
        void SensorSweepTask(void);
        void LineMakerTask(void);
    private:
        ArRobot *myRobot;
        ArMap *myMap;
        std::queue<ArPose*> *poseQueue;
        ArMutex poseMutex;
        ArRangeDevice *mySonar;
        ArPose currentPose;
        bool endTasks;
        // these are hard coded as we only deal with one kind or robot, the amigobt
        double sensorPositions[8] {
            -144.0,
            -90.0,
            -44.0,
            -12.0,
            12.0,
            44.0,
            90.0,
            144.0
        };
        // first element is the distance, second is the angle
        double sensorReadings[8][2];
};
#endif 
