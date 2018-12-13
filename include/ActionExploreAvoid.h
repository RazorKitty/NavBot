#ifndef ACTIONEXPLOREAVOID
#define ACTIONEXPLOREAVOID
#include "Aria.h"

class ActionExploreAvoid : public ArAction {
    public:
        ActionExploreAvoid(double turnThreshold, double turnAmount);
        virtual ~ActionExploreAvoid(void){};
        virtual ArActionDesired *fire(ArActionDesired currentdesired);
        virtual void setRobot(ArRobot *robot);
    protected:
        ArRangeDevice *mySonar;
        ArActionDesired myDesired;
        double myTurnThreshold;
        double myTurnAmount;
        int myTurning;
};

#endif
