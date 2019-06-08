#include "ActionExploreNavigateNear.h"
#include "NavBotUtil.h"
#include <Aria/Aria.h>
#include "math.h"

ActionExploreNavigateNear::ActionExploreNavigateNear(double threshold):
    ArAction("exploreNavigateNear"),
    mySonar(NULL),
    myThreshold(threshold)
{
    setNextArgument(ArArg("exploreNavigateNearThreshold", &myThreshold, "threshold at which to pivot around corners"));
}

void ActionExploreNavigateNear::setRobot(ArRobot *robot) {
    ArAction::setRobot(robot);
    robot->lock();
    mySonar = robot->findRangeDevice("sonar");
    robot->unlock();
    if (!mySonar) {
        ArLog::log(ArLog::Terse, "ActoinExploreNavigateNear::setRobot: Warning: Nosonardevice found, deactivating.");
        deactivate();
    }
}

ArActionDesired *ActionExploreNavigateNear::fire(ArActionDesired currentDesired) {
    myDesired.reset();
    if (!mySonar) {
        deactivate();
        return NULL;
    }

    mySonar->tryLockDevice();
    leftOppositeLength = mySonar->currentReadingPolar(81, 99, &leftOppositeOffsetAngle);
    rightOppositeLength = mySonar->currentReadingPolar(-99, -81, &rightOppositeOffsetAngle);
    mySonar->unlockDevice();
    
    if (leftOppositeLength < rightOppositeLength) {
        oppositeLength = leftOppositeLength;
        oppositeOffsetAngle = leftOppositeOffsetAngle;
        direction = 1;
        mySonar->tryLockDevice();
        hypotenuseLength = mySonar->currentReadingPolar(0, 50, &hypotenuseOffsetAngle);
        mySonar->unlockDevice();
    } else {
        oppositeLength = rightOppositeLength;
        oppositeOffsetAngle = rightOppositeOffsetAngle;
        direction = -1;
        mySonar->tryLockDevice();
        hypotenuseLength = mySonar->currentReadingPolar(-50, 0, &hypotenuseOffsetAngle);
        mySonar->unlockDevice();
    }
    hypotenuseOppositeAngle = abs(oppositeOffsetAngle) - abs(hypotenuseOffsetAngle);
    

    if (oppositeLength < myThreshold && hypotenuseLength > (utils::getHypotenuseLength(oppositeLength, hypotenuseOppositeAngle)*2)) {
        oppositeAjdacentAngle = utils::getOppositeAngle(hypotenuseLength, oppositeLength); 
        myDesired.setDeltaHeading((oppositeAjdacentAngle*2)*direction);
    }


    return &myDesired;
}
