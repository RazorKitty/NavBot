#ifndef SENSORINTERPRETTASKSCONTAINER
#define SENSORINTERPRETTASKSCONTAINER 
#include <Aria/Aria.h>
#include <Aria/ArMap.h>

class SensorInterpretTasksContainer {
    public:
        SensorInterpretTasksContainer(ArRobot*, ArMap*);
        ~SensorInterpretTasksContainer(void){};
        void SensePoint(void);
    private:
        ArRobot *myRobot;
        ArMap *myMap;
};
#endif 
