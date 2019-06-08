#include "AsyncTasksContainer.h"
#include "NavBotUtil.h"
#include <Aria/Aria.h>
#include <Aria/ArMap.h>
#include <iostream>
#include <math.h>

AsyncTasksContainer::AsyncTasksContainer(ArRobot *robot, ArMap *map):
    myRobot(robot),
    myMap(map),
    endTasks(false)
{
    poseQueue = new std::queue<ArPose*>();

    myRobot->lock();
    mySonar = myRobot->findRangeDevice("sonar");
    myRobot->unlock();
}

//AsyncTasksContainer::AsyncTasksContainer(const AsyncTasksContainer &ATC) {
//    myRobot = ATC.myRobot;
//    myMap = ATC.myMap;
//    poseQueue = ATC.poseQueue;
//    poseMutex = ATC.poseMutex;
//    mySonar = ATC.mySonar;
//    currentPose = ATC.currentPose;
//    endTasks = ATC.endTasks;
//}

void AsyncTasksContainer::SensorSweepTask(void) {
//    std::cout << "committing sensor sweep" << std::endl;

    while(!endTasks) {
        
        //get the robot pose
//        myRobot->lock();
        currentPose = myRobot->getPose();
 //       myRobot->unlock();

        //get sonar readings
        for (int i = 0; i < 8; ++i) {
            mySonar->tryLockDevice();
            sensorReadings[i][0] = mySonar->currentReadingPolar(sensorPositions[i]-4,sensorPositions[i]+4, &sensorReadings[i][1]);
            mySonar->unlockDevice();
        }

        //turn into poses
        //and queue items
        for (int i = 0; i < 8; ++i) {
            ArPose *pose = new ArPose(
                    currentPose.getX()+sensorReadings[i][0]*sin(utils::wrapAngle(currentPose.getTh(), sensorReadings[i][1])*(M_PI/180.0)),
                    currentPose.getY()+sensorReadings[i][0]*cos(utils::wrapAngle(currentPose.getTh(), sensorReadings[i][1])*(M_PI/180.0))
                );
            poseMutex.lock();
            poseQueue->push(pose);
            poseMutex.unlock();
        }
    }
}

void AsyncTasksContainer::LineMakerTask(void) {
    poseMutex.lock();
//    ArPose* pose = poseQueue->front();
    poseQueue->pop();
    poseMutex.unlock();
    //std::cout << pose->getX() << "\t" << pose->getY() << std::endl;

}
