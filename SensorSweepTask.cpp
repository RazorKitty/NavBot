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

std::vector<ArPose*>* SensorSweepTask::getPoses(void) {
    std::vector<ArPose*>* poses = new std::vector<ArPose*>();
    queueMutex.lock();
    while(!poseQueue.empty()) {
        poses->push_back(poseQueue.front());
        poseQueue.pop();
    }
    queueMutex.unlock();
    return poses;
}

void* SensorSweepTask::runThread(void* args) {
    while(this->getRunningWithLock()) {
        robot->lock();
        currentPose = robot->getPose();
        robot->unlock();
        

        //get sonar readings
        for (int i = 0; i < 8; ++i) {
            sonar->lockDevice();
            sensorReadings[i][0] = sonar->currentReadingPolar(sensorPositions[i]-4,sensorPositions[i]+4, &sensorReadings[i][1]);
            sonar->unlockDevice();
        }

        //turn into poses
        //and queue items
        for (int i = 0; i < 8; ++i) {
            if (sensorReadings[i][0] < maxRange) {
                ArPose *pose = new ArPose(
                        currentPose.getX()+sensorReadings[i][0]*sin(utils::wrapAngle(currentPose.getTh(), sensorReadings[i][1])*(M_PI/180.0)),
                        currentPose.getY()+sensorReadings[i][0]*cos(utils::wrapAngle(currentPose.getTh(), sensorReadings[i][1])*(M_PI/180.0))
                    );
                queueMutex.lock();
                poseQueue.push(pose);
                queueMutex.unlock();
            }
        }
    }
    return NULL;
}
