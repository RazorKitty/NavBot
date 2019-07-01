#include "SensorSweepTask.h"
#include "NavBotUtil.h"

SensorSweepTask::SensorSweepTask(ArRobot* robot_in, double maxRange_in): 
    robot(robot_in),
    maxRange(maxRange_in)
{
    robot->lock();
    sonar = robot->findRangeDevice("sonar");
    robot->unlock();
}

void SensorSweepTask::getData(ArPose*** &pointPoses, ArPose** &robotPoses, int* length) {
    queueMutex.lock();
    *length = pointPoseQueue.size();
    pointPoses = new ArPose**[*length];
    robotPoses = new ArPose*[*length];
    for (int i = 0; i < *length; ++i) {
        pointPoses[i] = pointPoseQueue.front();
        pointPoseQueue.pop();
        robotPoses[i] = robotPoseQueue.front();
        robotPoseQueue.pop();
    }
    queueMutex.unlock();
}

void* SensorSweepTask::runThread(void* args) {
    while(this->getRunningWithLock()) {
        robot->lock();

        currentRobotPose = new ArPose(robot->getPose());
        robot->unlock();
        

        //get sonar readings
        for (int i = 0; i < 8; ++i) {
            sonar->lockDevice();
            sensorReadings[i][0] = sonar->currentReadingPolar(sensorPositions[i]-4,sensorPositions[i]+4, &sensorReadings[i][1]);
            sonar->unlockDevice();
        }

        //turn into poses
        //and queue items
        
        pointPoseArray = new ArPose*[8];
        for (int i = 0; i < 8; ++i) {
            if (sensorReadings[i][0] < maxRange) {
                pointPoseArray[i] = new ArPose(
                        currentRobotPose->getX()+sensorReadings[i][0]*sin(utils::wrapAngle(currentRobotPose->getTh(), sensorReadings[i][1])*(M_PI/180.0)),
                        currentRobotPose->getY()+sensorReadings[i][0]*cos(utils::wrapAngle(currentRobotPose->getTh(), sensorReadings[i][1])*(M_PI/180.0))
                    );
            }
        }
        queueMutex.lock();
        pointPoseQueue.push(pointPoseArray);
        robotPoseQueue.push(currentRobotPose);
        queueMutex.unlock();
    }
    return NULL;
}
