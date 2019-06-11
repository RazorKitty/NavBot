#ifndef SENSORSWEEPTASK
#define SENSORSWEEPTASK
#include <Aria/Aria.h>
#include <Aria/ArASyncTask.h>
#include <queue>

class SensorSweepTask : public ArASyncTask {
    public:
        SensorSweepTask(ArRobot*, double);
        ArPose* getNextPose(void);
        void* runThread(void*);
    private:
        ArRobot* robot;
        ArRangeDevice* sonar;
        std::queue<ArPose*> poseQueue;
        ArMutex queueMutex;
        ArPose currentPose;
        double maxRange;
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
