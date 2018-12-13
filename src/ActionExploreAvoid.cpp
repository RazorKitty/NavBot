#include "ActionExploreAvoid.h"
#include "Aria.h"

ActionExploreAvoid::ActionExploreAvoid(double turnThreshold, double turnAmount):
    ArAction("exploreAvoid"),
    myTurnThreshold(turnThreshold),
    myTurnAmount(turnAmount),
    mySonar(NULL)
{
    setNextArgument(ArArg("turnThresholdExploreAvoid", &myTurnThreshold, "minimum distance to avoid while exploring"));
    setNextArgument(ArArg("turnAmountExploreAvoid", &myTurnAmount, "minimum degrees to turn to avoid colision while exploring"));
}
void ActionExploreAvoid::setRobot(ArRobot *robot) {
    ArAction::setRobot(robot);
    mySonar = robot->findRangeDevice("sonar");
    if (mySonar == NULL) {
        ArLog::log(ArLog::Terse, "ActionExploreAvoid: setRobot: Warning: no found sonar, deactivating.");
        deactivate();
    }
}
ArActionDesired *ActionExploreAvoid::fire(ArActionDesired currentDesired) {
    double leftRange, rightRange;
    myDesired.reset();
    if (mySonar == NULL) {
        deactivate();
        return NULL;
    }
    // Get the left readings and right readings off of the sonar
    leftRange = (mySonar->currentReadingPolar(0, 44) - myRobot->getRobotRadius());
    rightRange = (mySonar->currentReadingPolar(-44, 0) - myRobot->getRobotRadius());
    // if neither left nor right range is within the turn threshold,
    // reset the turning variable and don't turn
    if (leftRange > myTurnThreshold && rightRange > myTurnThreshold) {
        myTurning = 0;
        myDesired.setDeltaHeading(0);
    }
    // if we're already turning some direction, keep turning that direction
    else if (myTurning) {
        myDesired.setDeltaHeading(myTurnAmount * myTurning);
    }
    // if we're not turning already, but need to, and left is closer, turn right
    // and set the turning variable so we turn the same direction for as long as
    // we need to
    else if (leftRange < rightRange) {
        myTurning = -1;
        myDesired.setDeltaHeading(myTurnAmount * myTurning);
    }
    // if we're not turning already, but need to, and right is closer, turn left
    // and set the turning variable so we turn the same direction for as long as
    // we need to
    else {
        myTurning = 1;
        myDesired.setDeltaHeading(myTurnAmount * myTurning);
    }
    // return a pointer to the actionDesired, so resolver knows what to do
    return &myDesired;
}
