#ifndef ACTIONEXPLOREVELOCITY
#define ACTIONEXPLOREVELOCITY 
#include "Aria.h"

class ActionExploreVelocity : public ArAction {
    public:
        ActionExploreVelocity(double maxSpeed, double stopDistance);
        virtual ~ActionExploreVelocity(void){};
        virtual ArActionDesired *fire(ArActionDesired currentDesired);
        virtual void setRobot(ArRobot *robot);
    protected:
        ArRangeDevice *mySonar;
        ArActionDesired myDesired;
        double myMaxSpeed;
        double myStopDistance;
        double range;
};
#endif
