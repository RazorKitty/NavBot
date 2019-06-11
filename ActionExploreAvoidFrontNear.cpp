#include "ActionExploreAvoidFrontNear.h"
#include "NavBotUtil.h"
#include <math.h>

ActionExploreAvoidFrontNear::ActionExploreAvoidFrontNear(double threshold):
    ArAction("exploreAvoidFrontNear"),
    mySonar(NULL),
    myThreshold(threshold)
{
    setNextArgument(ArArg("exploreAvoidFrontNearThreshold", &myThreshold, "threshold at which to start avoiding"));
}

void ActionExploreAvoidFrontNear::setRobot(ArRobot *robot) {
    ArAction::setRobot(robot);
    robot->lock();
    mySonar = robot->findRangeDevice("sonar");
    robot->unlock();
    if (!mySonar) {
        ArLog::log(ArLog::Terse, "ActionExploreAvoidFrontNear::setRobot: Warning: No sonar device found, deactivating.");
        deactivate();
    }
}

ArActionDesired *ActionExploreAvoidFrontNear::fire(ArActionDesired currentDesired) {
    myDesired.reset();
    if (!mySonar) {
        deactivate();
        return NULL;
    }

    mySonar->lockDevice();
    hypotenuseLength = mySonar->currentReadingPolar(-20, 20, &hypotenuseOffsetAngle);
    mySonar->unlockDevice();

    if (hypotenuseLength < myThreshold) {
        mySonar->lockDevice();
        leftOppositeLength = mySonar->currentReadingPolar(21, 99, &leftOppositeOffsetAngle);
        rightOppositeLength = mySonar->currentReadingPolar(-99, -21, &rightOppositeOffsetAngle); 
        mySonar->unlockDevice();
        if (leftOppositeLength < rightOppositeLength) {
            oppositeLength = leftOppositeLength;
            oppositeOffsetAngle = leftOppositeOffsetAngle;
            direction = -1;
        } else {
            oppositeLength = rightOppositeLength;
            oppositeOffsetAngle = rightOppositeOffsetAngle;
            direction = 1;
        }
        myDesired.setDeltaHeading(utils::getOppositeAngle(hypotenuseLength, oppositeLength)*direction);
    }
    return &myDesired;
}
