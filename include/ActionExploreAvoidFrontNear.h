#ifndef ACTIONEXPLOREAVOIDFRONTNEAR
#define ACTIONEXPLOREAVOIDFRONTNEAR 
#include "Aria.h"

class ActionExploreAvoidFrontNear : public ArAction {
    public:
        ActionExploreAvoidFrontNear(double threshold);
        virtual ~ActionExploreAvoidFrontNear(void){};
        virtual ArActionDesired *fire(ArActionDesired currentDesired);
        virtual void setRobot(ArRobot *robot);
    protected:
        ArRangeDevice *mySonar;
        ArActionDesired myDesired;
        double myThreshold;
};
#endif
