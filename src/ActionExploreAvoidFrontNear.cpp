#include "ActionExploreAvoidFrontNear.h"
#include "NavBotUtil.h"
#include <Aria/Aria.h>
#include <Aria/ariaUtil.h>
#include <math.h>

ActionExploreAvoidFrontNear::ActionExploreAvoidFrontNear(double threshold):
    ArAction("exploreAvoidFrontNear"),
    myThreshold(threshold),
    mySonar(NULL)
{
    setNextArgument(ArArg("exploreAvoidFrontNearThreshold", &myThreshold, "threshold at which to start avoiding"));
}

void ActionExploreAvoidFrontNear::setRobot(ArRobot *robot) {
    ArAction::setRobot(robot);
    mySonar = robot->findRangeDevice("sonar");
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

    hypotenuseLength = mySonar->currentReadingPolar(-20, 20, &hypotenuseOffsetAngle);

    if (hypotenuseLength < myThreshold) {
        leftOppositeLength = mySonar->currentReadingPolar(21, 99, &leftOppositeOffsetAngle);
        rightOppositeLength = mySonar->currentReadingPolar(-99, -21, &rightOppositeOffsetAngle); 
        if (leftOppositeLength < rightOppositeLength) {
            oppositeLength = leftOppositeLength;
            oppositeOffsetAngle = leftOppositeOffsetAngle;
            direction = -1;
        } else {
            oppositeLength = rightOppositeLength;
            oppositeOffsetAngle = rightOppositeOffsetAngle;
            direction = 1;
        }
        myDesired.setDeltaHeading(utils::getOppositeAngle(hypotenuseLength, oppositeLength, abs(oppositeOffsetAngle) - abs(hypotenuseOffsetAngle))*direction);
    }
    return &myDesired;
}
