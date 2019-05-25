#include "ActionExploreNavigateNear.h"
#include "NavBotUtil.h"
#include <Aria/Aria.h>
#include "math.h"

ActionExploreNavigateNear::ActionExploreNavigateNear(double threshold):
    ArAction("exploreNavigateNear"),
    myThreshold(threshold),
    mySonar(NULL)
{
    setNextArgument(ArArg("exploreNavigateNearThreshold", &myThreshold, "threshold at which to pivot around corners"));
}

void ActionExploreNavigateNear::setRobot(ArRobot *robot) {
    ArAction::setRobot(robot);
    mySonar = robot->findRangeDevice("sonar");
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

    leftOppositeLength = mySonar->currentReadingPolar(81, 99, &leftOppositeOffsetAngle);

    rightOppositeLength = mySonar->currentReadingPolar(-99, -81, &rightOppositeOffsetAngle);
    
    if (leftOppositeLength < rightOppositeLength) {
        oppositeLength = leftOppositeLength;
        oppositeOffsetAngle = leftOppositeOffsetAngle;
        direction = 1;
        hypotenuseLength = mySonar->currentReadingPolar(0, 50, &hypotenuseOffsetAngle);
    } else {
        oppositeLength = rightOppositeLength;
        oppositeOffsetAngle = rightOppositeOffsetAngle;
        direction = -1;
        hypotenuseLength = mySonar->currentReadingPolar(-50, 0, &hypotenuseOffsetAngle);
    }
    hypotenuseOppositeAngle = abs(oppositeOffsetAngle) - abs(hypotenuseOffsetAngle);
    

    if (oppositeLength < myThreshold && hypotenuseLength > (utils::getHypotenuseLength(oppositeLength, hypotenuseOppositeAngle)*2)) {
        
        oppositeAjdacentAngle = utils::getOppositeAngle(hypotenuseLength, oppositeLength, hypotenuseOppositeAngle);
        myDesired.setDeltaHeading((oppositeAjdacentAngle*2)*direction);
//        myDesired.setVel(200);
    }


    return &myDesired;
}
