#include "SensorInterpretTasksContainer.h"
#include <Aria/Aria.h>
#include <Aria/ArMap.h>
#include <iostream>

SensorInterpretTasksContainer::SensorInterpretTasksContainer(ArRobot *robot, ArMap *map):
    myRobot(robot),
    myMap(map)
{}

void SensorInterpretTasksContainer::SensePoint(void) {
    std::cout << "Sensing point" << std::endl;
}
